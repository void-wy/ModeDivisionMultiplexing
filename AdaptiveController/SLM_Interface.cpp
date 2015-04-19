///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"

#include "cv.h"





void SLM::getRangePM(int &height, int &width)
{
	height = heightPM;
	width = widthPM;
}



int SLM::getPhase(int x, int y)
{
	return ((uchar *)imageSLM->imageData)[(bottomPM + x) * imageSLM->widthStep + leftPM + y];
}



void SLM::setPhase(std::string name, std::string path)
{
	path = path + "\\" + name + ".jpg";

	IplImage *temp = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

	cvResize(temp, imageSLM);

	cvReleaseImage(&temp);

	for(int i = 0; i < imageVisible->height; i++)
	{
		for(int j = 0; j < imageVisible->width; j++)
		{
			((uchar *)imageVisible->imageData)[i * imageVisible->widthStep + j] =
				((uchar *)imageSLM->imageData)[(bottomPM + i) * imageSLM->widthStep + leftPM + j];
		}
	}

	updateImageDesired();
}



void SLM::setPhase(int x, int y, int value, int height, int width)
{
	for(int i = x; i < x + height; i++)
	{
		for(int j = y; j < y + width; j++)
		{
			((uchar *)imageSLM->imageData)[(bottomPM + i) * imageSLM->widthStep + leftPM + j] = value;
			((uchar *)imageVisible->imageData)[i * imageVisible->widthStep + j] = value;
		}
	}
}



void SLM::loadPhase()
{
	cvShowImage("Image_SLM", imageSLM);

	cvWaitKey(20);
}



void SLM::showImageVisible()
{
	cvShowImage("Image_Visible", imageVisible);

	cvWaitKey(20);
}



void SLM::updateImageDesired()
{
	for(int i = 0; i < imageDesired->height; i++)
	{
		for(int j = 0; j < imageDesired->width; j++)
		{
			((uchar *)imageDesired->imageData)[i * imageDesired->widthStep + j] =
				((uchar *)imageSLM->imageData)[i * imageSLM->widthStep + j];
		}
	}
}



void SLM::saveImageDesired(std::string name, std::string path)
{
	path = path + "\\" + name + ".bmp";

	cvSaveImage(path.c_str(), imageDesired);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////