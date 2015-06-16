///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ImageProcessing.h"

#include "cv.h"





void ImageProcessing::resizeImage(IplImage *imageCurrent, IplImage *imageIdeal)
{
	cvResize(imageCurrent, imageIdeal);
}



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



double ImageProcessing::getCorrelation(IplImage *imageCurrent, IplImage *imageIdeal)
{
	double sumNumerator = 0, sumDenominator1 = 0, sumDenominator2 = 0;

	for(int i = 0; i < imageIdeal->height; i++)
	{
		for(int j = 0; j < imageIdeal->width; j++)
		{
			sumNumerator += ((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep + j]
				* ((uchar *)imageCurrent->imageData)[i * imageCurrent->widthStep + j];
			sumDenominator1 += ((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep + j]
				* ((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep + j];
			sumDenominator2 += ((uchar *)imageCurrent->imageData)[i * imageCurrent->widthStep + j]
				* ((uchar *)imageCurrent->imageData)[i * imageCurrent->widthStep + j];
		}
	}

	return (sumNumerator * sumNumerator) / (sumDenominator1 * sumDenominator2);
}



int ImageProcessing::getMaxValue(IplImage *image)
{
	int max = 0;

	for(int i = 0; i < image->height; i++)
	{
		for(int j = 0; j < image->width; j++)
		{
			if(max < ((uchar *)image->imageData)[i * image->widthStep + j])
			{
				max = ((uchar *)image->imageData)[i * image->widthStep + j];
			}
		}
	}

	return max;
}



int ImageProcessing::getMinValue(IplImage *image)
{
	int min = 255;

	for(int i = 0; i < image->height; i++)
	{
		for(int j = 0; j < image->width; j++)
		{
			if(min > ((uchar *)image->imageData)[i * image->widthStep + j])
			{
				min = ((uchar *)image->imageData)[i * image->widthStep + j];
			}
		}
	}

	return min;
}



double ImageProcessing::getMean(IplImage *image)
{
	double sum = 0;

	for(int i = 0; i < image->height; i++)
	{
		for(int j = 0; j < image->width; j++)
		{
			sum += ((uchar *)image->imageData)[i * image->widthStep + j];
		}
	}

	return sum / (image->height * image->width);
}



double ImageProcessing::getVariance(IplImage *image)
{
	double mean = getMean(image);

	double sum = 0;

	for(int i = 0; i < image->height; i++)
	{
		for(int j = 0; j < image->width; j++)
		{
			sum += (((uchar *)image->imageData)[i * image->widthStep + j] - mean)
				* (((uchar *)image->imageData)[i * image->widthStep + j] - mean);
		}
	}

	return sum / (image->height * image->width);
}



void ImageProcessing::setNormalization(IplImage *image, int maxValueIdeal, int minValueIdeal)
{
	int i, j;

	int maxValueCurrent = 0;
	int minValueCurrent = 255;

	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			if(maxValueCurrent < ((uchar *)image->imageData)[i * image->widthStep + j])
			{
				maxValueCurrent = ((uchar *)image->imageData)[i * image->widthStep + j];
			}

			if(minValueCurrent > ((uchar *)image->imageData)[i * image->widthStep + j])
			{
				minValueCurrent = ((uchar *)image->imageData)[i * image->widthStep + j];
			}
		}
	}

	double range = maxValueCurrent - minValueCurrent;

	if(0 == range)
	{
		return;
	}

	double ratio = (maxValueIdeal - minValueIdeal) / range;

	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			((uchar *)image->imageData)[i * image->widthStep + j] =
				ratio * (((uchar *)image->imageData)[i * image->widthStep + j] - minValueCurrent) + minValueIdeal;
		}
	}
}



void ImageProcessing::setMedianFiltering(IplImage *imageCurrent, IplImage *imageIdeal)
{
	uchar sort[9];
	uchar temp;

	int i, j;
	int m, n;
	int k;
	int min;

	for(i = 0; i < imageIdeal->height; i++)
	{
		((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep] = ((uchar *)imageCurrent->imageData)[i * imageCurrent->widthStep];
		((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep + imageIdeal->width - 1] =
			((uchar *)imageCurrent->imageData)[i * imageCurrent->widthStep + imageCurrent->width - 1];
	}

	for(j = 1; j < imageIdeal->width - 1; j++)
	{
		((uchar *)imageIdeal->imageData)[j] = ((uchar *)imageCurrent->imageData)[j];
		((uchar *)imageIdeal->imageData)[(imageIdeal->height - 1) * imageIdeal->widthStep + j] =
			((uchar *)imageCurrent->imageData)[(imageCurrent->height - 1) * imageCurrent->widthStep + j];
	}

	for(i = 0; i < imageIdeal->height; i++)
	{
		for(j = 0; j < imageIdeal->width; j++)
		{
			k = 0;

			for(m = i - 1; m < i + 2; m++)
			{
				for(n = j - 1; n < j + 2; n++)
				{
					sort[k] = ((uchar *)imageCurrent->imageData)[m * imageCurrent->widthStep + n];

					k++;
				}
			}

			for(m = 0; m < 5; m++)
			{
				min = m;

				for(n = m + 1; n < 9; n++)
				{
					if(sort[n] < sort[min])
					{
						min = n;
					}
				}

				temp = sort[m];
				sort[m] = sort[min];
				sort[min] = temp;
			}

			((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep + j] = sort[4];
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////