///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "FakeCCD.h"





FakeCCD::FakeCCD(std::string name, std::string path)
{
	openFileLog(name, path);

	createWindow();

	initializeData();

	createImageCCD();

	createImageDesired();
}



void FakeCCD::openFileLog(std::string name, std::string path)
{
	path = path + "\\" + name;

	fileLog = new std::ofstream();

	fileLog->open(path.c_str());

	fileLog->precision(10);
}



void FakeCCD::createWindow()
{
	cvNamedWindow("Image_CCD");
}



void FakeCCD::initializeData()
{
	directory = "FakeCCD";
	name = "Blank";
	numMax = 10;
	num = 0;
}



void FakeCCD::createImageCCD()
{
	std::string path = directory + "\\" + name + ".bmp";

	imageCCD = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
}



void FakeCCD::createImageDesired()
{
	imageDesired = cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////