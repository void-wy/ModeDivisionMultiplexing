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



void ImageProcessing::setNormalization(IplImage *image)
{
	int max = getMaxValue(image);
	int min = getMinValue(image);

	int range = max - min;

	if(0 == range)
	{
		return;
	}

	double ratio = 255 / range;

	for(int i = 0; i < image->height; i++)
	{
		for(int j = 0; j < image->width; j++)
		{
			((uchar *)image->imageData)[i * image->widthStep + j] =
				ratio * (((uchar *)image->imageData)[i * image->widthStep + j] - min);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////