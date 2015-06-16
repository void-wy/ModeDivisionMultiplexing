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

	initializeData();

	createImage();
}



void FakeCCD::openFileLog(std::string name, std::string path)
{
	path = path + "\\" + name;

	fileLog = new std::ofstream();

	fileLog->open(path.c_str());

	fileLog->precision(10);
}



void FakeCCD::initializeData()
{
	directory = "FakeCCD";
	name = "Blank";
	numMax = 10;
	num = 0;
}



void FakeCCD::createImage(int flag)
{
	switch(flag)
	{
	case AC_IMAGE_ALL:
		{
			std::string path = directory + "\\" + name + ".bmp";

			imageCCD = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

			imageDesired = cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
		}

		break;

	case AC_IMAGE_CCD:
		{
			std::string path = directory + "\\" + name + ".bmp";

			imageCCD = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		}

		break;

	case AC_IMAGE_DESIRED:
		{
			imageDesired = cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
		}

		break;

	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////