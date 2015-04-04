///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ImageProcessing.h"

#include "cv.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//得到指定图像中的光斑轮廓
/*
 *	参数(IplImage * &image)为得到光斑轮廓的图像
 *	参数(int &left, int &right, int &top, int &bottom)为轮廓的最左点、最右点、最上点和最下点
 */
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