///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"

#include "cv.h"

#include <iostream>





void SimulatedAnnealing::setRangeSpot(int margin)
{
	int left, right, top, bottom;

	IP->findContour(imageCurrent, left, right, top, bottom);

	leftSpot = left - margin;
	bottomSpot = bottom - margin;
	heightSpot = top - bottom + 2 * margin;
	widthSpot = right - left + 2 * margin;

	std::cout << "leftSpot : " << leftSpot << std::endl;
	std::cout << "bottomSpot : " << bottomSpot << std::endl;
	std::cout << "heightSpot : " << heightSpot << std::endl;
	std::cout << "widthSpot : " << widthSpot << std::endl;

	std::cout << std::endl;
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

	cvResize(imageOriginalIdeal, imageOriginalResize);

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

	cvWaitKey(20);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////