///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "FakeCCD.h"

#include "cv.h"





void FakeCCD::createWindow()
{
	cvNamedWindow("Image_CCD");
}



void FakeCCD::destroyWindow()
{
	cvDestroyWindow("Image_CCD");
}



IplImage * FakeCCD::createImageCopy()
{
	return cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
}



void FakeCCD::updateImageCopy(IplImage *imageCopy)
{
	for(int i = 0; i < imageCopy->height; i++)
	{
		for(int j = 0; j < imageCopy->width; j++)
		{
			((uchar *)imageCopy->imageData)[i * imageCopy->widthStep + j] =
				((uchar *)imageCCD->imageData)[i * imageCCD->widthStep + j];
		}
	}
}



void FakeCCD::releaseImageCopy(IplImage *imageCopy)
{
	cvReleaseImage(&imageCopy);
}



void FakeCCD::snapShot()
{
	if(numMax == num)
	{
		num = 0;
	}

	num++;

	char name[3];

	sprintf(name, "%d", num);

	std::string path = directory + "\\" + name + ".bmp";

	IplImage *temp = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

	cvResize(temp, imageCCD);

	cvReleaseImage(&temp);
}



void FakeCCD::snapShot(IplImage *imageCopy)
{
	if(numMax == num)
	{
		num = 0;
	}

	num++;

	char name[3];

	sprintf(name, "%d", num);

	std::string path = directory + "\\" + name + ".bmp";

	IplImage *temp = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

	cvResize(temp, imageCopy);

	cvReleaseImage(&temp);
}



void FakeCCD::showImage()
{
	cvShowImage("Image_CCD", imageCCD);

	runEventProcessing();
}



void FakeCCD::updateImageDesired()
{
	for(int i = 0; i < imageDesired->height; i++)
	{
		for(int j = 0; j < imageDesired->width; j++)
		{
			((uchar *)imageDesired->imageData)[i * imageDesired->widthStep + j] =
				((uchar *)imageCCD->imageData)[i * imageCCD->widthStep + j];
		}
	}
}



void FakeCCD::saveImageDesired(std::string name, std::string path)
{
	path = path + "\\" + name + ".bmp";

	cvSaveImage(path.c_str(), imageDesired);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////