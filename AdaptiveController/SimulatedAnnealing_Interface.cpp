///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"





void SimulatedAnnealing::createWindow()
{
	cvNamedWindow("Image_CCD");
	cvNamedWindow("Image_Current");
	cvNamedWindow("Image_Ideal");
}



void SimulatedAnnealing::destroyWindow()
{
	cvDestroyWindow("Image_CCD");
	cvDestroyWindow("Image_Current");
	cvDestroyWindow("Image_Ideal");
}



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



void SimulatedAnnealing::createImageSA()
{
	createImageCurrent();

	createImageDesired();
}



void SimulatedAnnealing::updateImageCurrent()
{
	//	Median Filtering
	uchar sort[9];
	uchar temp;

	int i, j;
	int m, n;
	int k;
	int min;

	for(i = 0; i < imageCurrent->height; i++)
	{
		for(j = 0; j < imageCurrent->width; j++)
		{
			k = 0;

			for(m = i - 1; m < i + 2; m++)
			{
				for(n = j - 1; n < j + 2; n++)
				{
					sort[k] = ((uchar *)imageCCD->imageData)[(m + bottomSpot) * imageCCD->widthStep + n + leftSpot];

					k++;
				}
			}

			for(m = 0; m < 5; m++)
			{
				min = m;

				for(n = m + 1; n < 9; n++)
				{
					if(sort[n] < sort[min])
					{
						min = n;
					}
				}

				temp = sort[m];
				sort[m] = sort[min];
				sort[min] = temp;
			}

			((uchar *)imageCurrent->imageData)[i * imageCurrent->widthStep + j] = sort[4];
		}
	}

	//	Normalization
	IP->setNormalization(imageCurrent);
}



void SimulatedAnnealing::updateImageDesired()
{
	int i, j;

	for(i = 0; i < imageDesiredCCD->height; i++)
	{
		for(j = 0; j < imageDesiredCCD->width; j++)
		{
			((uchar *)imageDesiredCCD->imageData)[i * imageDesiredCCD->widthStep + j] =
				((uchar *)imageCCD->imageData)[i * imageCCD->widthStep + j];
		}
	}

	for(i = 0; i < imageDesiredCurrent->height; i++)
	{
		for(j = 0; j < imageDesiredCurrent->width; j++)
		{
			((uchar *)imageDesiredCurrent->imageData)[i * imageDesiredCurrent->widthStep + j] =
				((uchar *)imageCurrent->imageData)[i * imageCurrent->widthStep + j];
		}
	}
}



void SimulatedAnnealing::showImageCCD()
{
	cvShowImage("Image_CCD", imageCCD);

	runEventProcessing();
}



void SimulatedAnnealing::showImageCurrent()
{
	cvShowImage("Image_Current", imageCurrent);

	runEventProcessing();
}



void SimulatedAnnealing::saveImageIdeal(std::string name, std::string path)
{
	path = path + "\\" + name + ".bmp";

	cvSaveImage(path.c_str(), imageIdeal);
}



void SimulatedAnnealing::saveImageDesired(std::string nameCCD, std::string nameSA, std::string path)
{
	nameCCD = path + "\\" + nameCCD + ".bmp";
	nameSA = path + "\\" + nameSA + ".bmp";

	cvSaveImage(nameCCD.c_str(), imageDesiredCCD);
	cvSaveImage(nameSA.c_str(), imageDesiredCurrent);
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



void SimulatedAnnealing::runSA(int height, int width)
{
	int x, y;
	double correlation = 0;
	double tempCorrelation;

	slm->updateImageDesired();

	snapShot();

	showImageCCD();

	showImageCurrent();

	updateImageDesired();

	IP->getCorrelation(imageCurrent, imageIdeal);

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

					showImageCCD();

					showImageCurrent();

					updateImageDesired();
				}

				if(0 == TN % 1000)
				{
					if(27 == cvWaitKey(0))
					{
						return;
					}
				}

				snapShot();

				tempCorrelation = IP->getCorrelation(imageCurrent, imageIdeal);

				//	TN
				TN += 1;

				if(tempCorrelation > correlation)
				{
					correlation = tempCorrelation;

					if(correlation > correlationBest)
					{
						slm->showImageVisible();

						slm->updateImageDesired();
					}

					//	DRN
					DRN += 1;
				}
				else if(exp((tempCorrelation - correlation) / (BoltzmannConstant * Ts)) > rand() / (double)RAND_MAX)
				{
					correlation = tempCorrelation;

					//	PRN
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



void SimulatedAnnealing::snapShot()
{
	ccd->snapShot(imageCCD);

	updateImageCurrent();
}



void SimulatedAnnealing::saveImageResult(std::string nameSLM, std::string nameCCD, std::string nameSA,
										 std::string nameIdeal, std::string path)
{
	slm->saveImageDesired(nameSLM, path);

	saveImageDesired(nameCCD, nameSA, path);

	saveImageIdeal(nameIdeal, path);
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