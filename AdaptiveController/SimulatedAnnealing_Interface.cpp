///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"





void SimulatedAnnealing::createWindow(int flag)
{
	switch(flag)
	{
	case AC_IMAGE_ALL:
		{
			cvNamedWindow("Image_CCD");
			cvNamedWindow("Image_Current");
			cvNamedWindow("Image_Ideal");
		}

		break;

	case AC_IMAGE_CCD:
		{
			cvNamedWindow("Image_CCD");
		}

		break;

	case AC_IMAGE_CURRENT:
		{
			cvNamedWindow("Image_Current");
		}

		break;

	case AC_IMAGE_IDEAL:
		{
			cvNamedWindow("Image_Ideal");
		}

		break;

	default:
		break;
	}
}



void SimulatedAnnealing::destroyWindow(int flag)
{
	switch(flag)
	{
	case AC_IMAGE_ALL:
		{
			cvDestroyWindow("Image_CCD");
			cvDestroyWindow("Image_Current");
			cvDestroyWindow("Image_Ideal");
		}

		break;

	case AC_IMAGE_CCD:
		{
			cvDestroyWindow("Image_CCD");
		}

		break;

	case AC_IMAGE_CURRENT:
		{
			cvDestroyWindow("Image_Current");
		}

		break;

	case AC_IMAGE_IDEAL:
		{
			cvDestroyWindow("Image_Ideal");
		}

		break;

	default:
		break;
	}
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

	setImageIdeal(margin, name, path);

	normalizeImageIdeal();
}



void SimulatedAnnealing::createImage(int flag)
{
	switch(flag)
	{
	case AC_IMAGE_IDEAL:
		{
			imageIdeal = cvCreateImage(cvSize(widthSpot, heightSpot), IPL_DEPTH_8U, 1);
		}

		break;

	case AC_IMAGE_ALL:
		{
			imageCurrent = cvCreateImage(cvSize(widthSpot, heightSpot), IPL_DEPTH_8U, 1);
			imageDesiredCCD = cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
			imageDesiredCurrent = cvCreateImage(cvGetSize(imageCurrent), IPL_DEPTH_8U, 1);
		}

		break;

	case AC_IMAGE_CURRENT:
		{
			imageCurrent = cvCreateImage(cvSize(widthSpot, heightSpot), IPL_DEPTH_8U, 1);
		}

		break;

	case AC_IMAGE_DESIRED:
		{
			imageDesiredCCD = cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
			imageDesiredCurrent = cvCreateImage(cvGetSize(imageCurrent), IPL_DEPTH_8U, 1);
		}

		break;

	default:
		break;
	}
}



void SimulatedAnnealing::releaseImage(int flag)
{
	switch(flag)
	{
	case AC_IMAGE_ALL:
		{
			cvReleaseImage(&imageIdeal);
			cvReleaseImage(&imageCurrent);
			cvReleaseImage(&imageDesiredCCD);
			cvReleaseImage(&imageDesiredCurrent);
		}

		break;

	case AC_IMAGE_IDEAL:
		{
			cvReleaseImage(&imageIdeal);
		}

		break;

	case AC_IMAGE_CURRENT:
		{
			cvReleaseImage(&imageCurrent);
		}

		break;

	case AC_IMAGE_DESIRED:
		{
			cvReleaseImage(&imageDesiredCCD);
			cvReleaseImage(&imageDesiredCurrent);
		}

		break;

	default:
		break;
	}
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



void SimulatedAnnealing::showImage(int flag)
{
	switch(flag)
	{
	case AC_IMAGE_ALL:
		{
			cvShowImage("Image_CCD", imageCCD);
			cvShowImage("Image_Current", imageCurrent);
			cvShowImage("Image_Ideal", imageIdeal);

			runEventProcessing();
		}

		break;

	case AC_IMAGE_CCD:
		{
			cvShowImage("Image_CCD", imageCCD);

			runEventProcessing();
		}

		break;

	case AC_IMAGE_CURRENT:
		{
			cvShowImage("Image_Current", imageCurrent);

			runEventProcessing();
		}

		break;

	case AC_IMAGE_IDEAL:
		{
			cvShowImage("Image_Ideal", imageIdeal);

			runEventProcessing();
		}

		break;

	default:
		break;
	}
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

	showImage(AC_IMAGE_CURRENT);

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

					showImage(AC_IMAGE_CURRENT);

					updateImageDesired();
				}

				if(0 == TN % 100)
				{
					createWindow(AC_IMAGE_IDEAL);

					showImage(AC_IMAGE_IDEAL);

					if(27 == cvWaitKey(0))
					{
						destroyWindow(AC_IMAGE_IDEAL);

						return;
					}

					destroyWindow(AC_IMAGE_IDEAL);
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
						slm->showImage();

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