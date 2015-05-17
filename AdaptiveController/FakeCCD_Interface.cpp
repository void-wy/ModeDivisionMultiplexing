///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "FakeCCD.h"

#include "cv.h"





IplImage * FakeCCD::getImageCCD()
{
	return imageCCD;
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



void FakeCCD::showImageCCD()
{
	cvShowImage("Image_CCD", imageCCD);

	eventProcessing();
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