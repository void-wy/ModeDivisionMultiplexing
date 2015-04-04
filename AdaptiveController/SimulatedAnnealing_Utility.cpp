///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"

#include "cv.h"

#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//设置CCD的光斑范围
/*
 *	参数(int margin)为边距大小
 */
void SimulatedAnnealing::setRangeSpot(int margin)
{
	int left, right, top, bottom;

	//Test
	imageCurrent = cvLoadImage("CCD_Test.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	IP->findContour(imageCurrent, left, right, top, bottom);	//得到指定图像中的光斑轮廓
															/*
															 *	参数(IplImage * &image)为得到光斑轮廓的图像
															 *	参数(int &left, int &right, int &top, int &bottom)为轮廓的最左点、最右点、最上点和最下点
															 */

	leftSpot = left - margin;
	bottomSpot = bottom - margin;
	heightSpot = top - bottom + 2 * margin;
	widthSpot = right - left + 2 * margin;

	cout << "leftSpot : " << leftSpot << endl;
	cout << "bottomSpot : " << bottomSpot << endl;
	cout << "heightSpot : " << heightSpot << endl;
	cout << "widthSpot : " << widthSpot << endl;

	cout << endl;
}

//创建理想的目标图像
/*
 *	参数(int margin)为边距大小
 */
void SimulatedAnnealing::createImageIdeal(char *name, int margin)
{
	int left, right, top, bottom;

	string path = name;

	path = "LP\\" + path + ".jpg";

	IplImage *imageOriginalIdeal = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

	IP->findContour(imageOriginalIdeal, left, right, top, bottom);	//得到指定图像中的光斑轮廓
																/*
																 *	参数(IplImage * &image)为得到光斑轮廓的图像
																 *	参数(int &left, int &right, int &top, int &bottom)为轮廓的最左点、最右点、最上点和最下点
																 */

	int width = ((double)(widthSpot - 2 * margin) / (right - left)) * imageOriginalIdeal->width;
	int height = ((double)(heightSpot - 2 * margin) / (top - bottom)) * imageOriginalIdeal->height;

	IplImage *imageOriginalResize = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

	cvResize(imageOriginalIdeal, imageOriginalResize);

	IP->findContour(imageOriginalResize, left, right, top, bottom);	//得到指定图像中的光斑轮廓
																/*
																 *	参数(IplImage * &image)为得到光斑轮廓的图像
																 *	参数(int &left, int &right, int &top, int &bottom)为轮廓的最左点、最右点、最上点和最下点
																 */

	imageIdeal = cvCreateImage(cvSize(widthSpot, heightSpot), IPL_DEPTH_8U, 1);

	for(int i = 0; i < imageIdeal->height; i++)
	{
		for(int j = 0; j < imageIdeal->width; j++)
		{
			((uchar *)imageIdeal->imageData)[i * imageIdeal->widthStep + j] = ((uchar *)imageOriginalResize->imageData)[(bottom - margin + i) * imageOriginalResize->widthStep + (left - margin + j)];
		}
	}

	cvReleaseImage(&imageOriginalIdeal);
	cvReleaseImage(&imageOriginalResize);
}

//显示理想的目标图像
void SimulatedAnnealing::showImage()
{
	cvShowImage("Image_Ideal", imageIdeal);

	cvWaitKey(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////