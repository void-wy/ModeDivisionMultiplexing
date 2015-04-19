///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ImageProcessing.h"

#include "cv.h"





void ImageProcessing::findContour(IplImage *image, int &left, int &right, int &top, int &bottom)
{
	IplImage *imageBinary = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);

	cvThreshold(image, imageBinary, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	left = imageBinary->width;
	right = -1;
	top = -1;
	bottom = imageBinary->height;

	for(int i = 0; i < imageBinary->height; i++)
	{
		for(int j = 0; j < imageBinary->width; j++)
		{
			if(((uchar *)imageBinary->imageData)[i * imageBinary->widthStep + j]  == 255)
			{
				if(left > j)
				{
					left = j;
				}
				else if(right < j)
				{
					right = j;
				}

				if(top < i)
				{
					top = i;
				}
				else if(bottom > i)
				{
					bottom = i;
				}
			}
		}
	}

	cvReleaseImage(&imageBinary);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////