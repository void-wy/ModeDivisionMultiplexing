///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"





void SimulatedAnnealing::setRangeSpot(int margin)
{
	ccd->snapShot(imageCCD);

	int left, right, top, bottom;

	IP->findContour(imageCCD, left, right, top, bottom);

	leftSpot = left - margin;
	bottomSpot = bottom - margin;
	heightSpot = top - bottom + 2 * margin;
	widthSpot = right - left + 2 * margin;

	*fileLog << "leftSpot : " << leftSpot << std::endl;
	*fileLog << "bottomSpot : " << bottomSpot << std::endl;
	*fileLog << "heightSpot : " << heightSpot << std::endl;
	*fileLog << "widthSpot : " << widthSpot << std::endl;
}



void SimulatedAnnealing::createImageIdeal(int margin, std::string name, std::string path)
{
	int left, right, top, bottom;

	path = path + "\\" + name + ".bmp";

	IplImage *imageOriginalIdeal = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

	IP->findContour(imageOriginalIdeal, left, right, top, bottom);

	int width = ((double)(widthSpot - 2 * margin) / (right - left)) * imageOriginalIdeal->width;
	int height = ((double)(heightSpot - 2 * margin) / (top - bottom)) * imageOriginalIdeal->height;

	IplImage *imageOriginalResize = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

	IP->resizeImage(imageOriginalIdeal, imageOriginalResize);

	IP->findContour(imageOriginalResize, left, right, top, bottom);

	imageIdeal = cvCreateImage(cvSize(widthSpot, heightSpot), IPL_DEPTH_8U, 1);

	for(int i = 0; i < imageIdeal->height; i++)
	{
		for(int j = 0; j < imageIdeal->width; j++)
		{
			((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep + j] = ((uchar *)imageOriginalResize->imageData)[(bottom - margin + i) * imageOriginalResize->widthStep + (left - margin + j)];
		}
	}

	cvReleaseImage(&imageOriginalIdeal);
	cvReleaseImage(&imageOriginalResize);

	IP->setNormalization(imageIdeal);
}



void SimulatedAnnealing::showImageIdeal()
{
	cvShowImage("Image_Ideal", imageIdeal);

	runEventProcessing();
}



void SimulatedAnnealing::createImageCurrent()
{
	imageCurrent = cvCreateImage(cvSize(widthSpot, heightSpot), IPL_DEPTH_8U, 1);
}



void SimulatedAnnealing::createImageDesired()
{
	imageDesiredCCD = cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
	imageDesiredCurrent = cvCreateImage(cvGetSize(imageCurrent), IPL_DEPTH_8U, 1);
}



void SimulatedAnnealing::runEventProcessing()
{
	while(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////