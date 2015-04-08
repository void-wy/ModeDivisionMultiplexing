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

	int first = 1;

	for(int i = 0; i < imageBinary->height; i++)
	{
		for(int j = 0; j < imageBinary->width; j++)
		{
			if(((uchar *)imageBinary->imageData)[i * imageBinary->widthStep + j]  == 255)
			{
				if(first == 0)
				{
					if(left > j)
					{
						left = j;
					}

					if(right < j)
					{
						right = j;
					}

					if(top < i)
					{
						top = i;
					}

					if(bottom > i)
					{
						bottom = i;
					}
				}
				else
				{
					left = j;
					right = j;
					top = i;
					bottom = i;

					first = 0;
				}
			}
		}
	}

	cvReleaseImage(&imageBinary);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////