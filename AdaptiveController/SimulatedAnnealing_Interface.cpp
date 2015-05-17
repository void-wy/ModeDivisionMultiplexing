///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"





void SimulatedAnnealing::openFileSA(std::string nameProcess, std::string nameResult, std::string path)
{
	nameProcess = path + "\\" + nameProcess;
	nameResult = path + "\\" + nameResult;

	fileProcess = new std::ofstream();
	fileResult = new std::ofstream();

	fileProcess->open(nameProcess.c_str());
	fileResult->open(nameResult.c_str());

	fileProcess->precision(10);
	fileResult->precision(10);
}



void SimulatedAnnealing::closeFileSA()
{
	fileProcess->close();
	fileResult->close();

	delete fileProcess;
	delete fileResult;
}



void SimulatedAnnealing::setModeIdeal(int margin, std::string name, std::string path)
{
	setRangeSpot(margin);

	createImageIdeal(margin, name, path);

	showImageIdeal();
}



void SimulatedAnnealing::saveImageIdeal(std::string name, std::string path)
{
	path = path + "\\" + name + ".bmp";

	cvSaveImage(path.c_str(), imageIdeal);
}



void SimulatedAnnealing::setPhaseInitial(std::string name, std::string path)
{
	slm->setPhase(name, path);

	slm->loadPhase();

	slm->showImageVisible();
}



void SimulatedAnnealing::setParameterSA(double Ts, double Tt, double c, int cyc)
{
	this->Ts = Ts;
	this->Tt = Tt;
	this->c = c;
	this->cyc = cyc;
	BoltzmannConstant = 1.3806488e-23;

	correlationBest = 0;
	DRN = 0;
	PRN = 0;
	TN = 0;
}



void SimulatedAnnealing::run(int height, int width)
{
	int x, y;
	double correlation = 0;
	double tempCorrelation;

	while(TRUE)
	{
		if(Ts > Tt)
		{
			for(int i = 0; i < cyc; i++)
			{
				x = (rand() % (heightPM / height)) * height;
				y = (rand() % (widthPM / width)) * width;

				slm->setPhase(x, y, 127^slm->getPhase(x, y), height, width);

				slm->loadPhase();

				if(correlation > correlationBest)
				{
					correlationBest = correlation;

					*fileProcess << "Correlation : \t" << correlationBest << std::endl;

					ccd->showImageCCD();

					ccd->updateImageDesired();
				}

				if(0 == TN % 1000)
				{
					if(27 == cvWaitKey(0))
					{
						return;
					}
				}

				ccd->snapShot();

				noiseSolution(30);

				tempCorrelation = getCorrelation();

				//TN
				TN += 1;

				if(tempCorrelation > correlation)
				{
					correlation = tempCorrelation;

					if(correlation > correlationBest)
					{
						slm->showImageVisible();

						slm->updateImageDesired();
					}

					//DRN
					DRN += 1;
				}
				else if(exp((tempCorrelation - correlation) / (BoltzmannConstant * Ts)) > rand() / (double)RAND_MAX)
				{
					correlation = tempCorrelation;

					//PRN
					PRN += 1;
				}
				else
				{
					slm->setPhase(x, y, 127^slm->getPhase(x, y), height, width);
				}
			}

			Ts = c * Ts;
		}
		else
		{
			break;
		}
	}
}



void SimulatedAnnealing::noiseSolution(int noiseMaxValue)
{
	int i, j;

	int imageMaxValue = 0;
	int imageMinValue = 0;

	for(i = 0; i < imageIdeal->height; i++)
	{
		for(j = 0; j < imageIdeal->width; j++)
		{
			if(noiseMaxValue > ((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot])
			{
				((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot] = 0;
			}
			else
			{
				((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot] =
					((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot] - noiseMaxValue;

				if(imageMaxValue < ((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot])
				{
					imageMaxValue = ((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot];
				}

				if(imageMinValue > ((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot])
				{
					imageMinValue = ((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot];
				}
			}
		}
	}

	int range = imageMaxValue - imageMinValue;

	if(0 == range)
	{
		return;
	}

	double ratio = 255 / range;

	for(i = 0; i < imageIdeal->height; i++)
	{
		for(j = 0; j < imageIdeal->width; j++)
		{
			((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot] =
				ratio * (((uchar *)imageCurrent->imageData)[(i + bottomSpot) * imageCurrent->widthStep + j + leftSpot] - imageMinValue);
		}
	}
}



double SimulatedAnnealing::getCorrelation()
{
	int cdIdeal, cdCurrent;

	double sumNumerator = 0, sumDenominator1 = 0, sumDenominator2 = 0;

	for(int i = 0; i < imageIdeal->height; i++)
	{
		for(int j = 0; j < imageIdeal->width; j++)
		{
			cdIdeal = i * imageIdeal->widthStep + j;
			cdCurrent = (i + bottomSpot) * imageCurrent->widthStep + j + leftSpot;

			sumNumerator += ((uchar *)imageIdeal->imageData)[cdIdeal] * ((uchar *)imageCurrent->imageData)[cdCurrent];
			sumDenominator1 += ((uchar *)imageIdeal->imageData)[cdIdeal] * ((uchar *)imageIdeal->imageData)[cdIdeal];
			sumDenominator2 += ((uchar *)imageCurrent->imageData)[cdCurrent] * ((uchar *)imageCurrent->imageData)[cdCurrent];
		}
	}

	return (sumNumerator * sumNumerator) / (sumDenominator1 * sumDenominator2);
}



void SimulatedAnnealing::saveImageResult(std::string nameSLM, std::string nameCCD, std::string nameSA, std::string path)
{
	slm->saveImageDesired(nameSLM, path);

	ccd->saveImageDesired(nameCCD, path);

	saveImageIdeal(nameSA, path);
}



void SimulatedAnnealing::saveFileResult()
{
	*fileResult << "Ts : " << Ts << std::endl;
	*fileResult << "Tt : " << Tt << std::endl;
	*fileResult << "c : " << c << std::endl;
	*fileResult << "cyc : " << cyc << std::endl;
	*fileResult << "BoltzmannConstant : " << BoltzmannConstant << std::endl;

	*fileResult << "TN : \t" << TN << std::endl;
	*fileResult << "DRN : \t" << DRN << std::endl;
	*fileResult << "PRN : \t" << PRN << std::endl;
	*fileResult << "CorrelationBest : \t" << correlationBest << std::endl;
	*fileResult << "Duration : \t" << duration << std::endl;
}



void SimulatedAnnealing::startClock()
{
	start = clock();
}



double SimulatedAnnealing::finishClock()
{
	duration = (double)(clock() - start) / CLOCKS_PER_SEC;

	return duration;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////