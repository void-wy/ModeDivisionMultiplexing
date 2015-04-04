///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//初始化SLM
/*
 *	参数(int height, int width)为SLM调相范围的高度和宽度
 */
SLM::SLM(int height, int width)
{
	createWindow();	//创建SLM相关窗口

	createImageSLM();	//创建SLM上加载的相位图像

	setRangePM(height, width);	//设置SLM的调相范围
								/*
								 *	参数(int height, int width)为调相范围的高度和宽度
								 */

	createImageVisible();	//创建观察SLM上加载相位的图像

	initializePhase();	//初始化SLM上的相位图为零

	showImage();	//显示SLM相关图像
}

//创建SLM相关窗口
void SLM::createWindow()
{
	cvNamedWindow("Image_SLM", 0);
	cvNamedWindow("Image_Visible");
}

//创建SLM上加载的相位图像
void SLM::createImageSLM()
{
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)this);	//遍历显示设备
}

//设置SLM的调相范围
/*
 *	参数(int height, int width)为调相范围的高度和宽度
 */
void SLM::setRangePM(int height, int width)
{
	leftPM = imageSLM->width / 2 - width / 2;
	bottomPM = imageSLM->height / 2 - height / 2;
	heightPM = height;
	widthPM = width;

	cout << "leftPM : " << leftPM << endl;
	cout << "bottomPM : " << bottomPM << endl;
	cout << "heightPM : " << heightPM << endl;
	cout << "widthPM : " << widthPM << endl;

	cout << endl;
}

//创建观察SLM上加载相位的图像
void SLM::createImageVisible()
{
	imageVisible = cvCreateImage(cvSize(widthPM, heightPM), IPL_DEPTH_8U, 1);
}

//初始化SLM上的相位图为零
void SLM::initializePhase()
{
	int i, j;

	for(i = 0; i < imageSLM->height; i++)
	{
		for(j = 0; j < imageSLM->width; j++)
		{
			((uchar *)imageSLM->imageData)[i * imageSLM->widthStep + j] = 0;
		}
	}

	for(i = 0; i < imageVisible->height; i++)
	{
		for(j = 0; j < imageVisible->width; j++)
		{
			((uchar *)imageVisible->imageData)[i * imageVisible->widthStep + j] = 0;
		}
	}
}

//EnumDisplayMonitors的回调函数
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	HWND hwnd = ::GetParent((HWND)cvGetWindowHandle("Image_SLM"));

	SetWindowLong(hwnd, GWL_STYLE, 0);

	if(lprcMonitor->left != 0 || lprcMonitor->top != 0)
	{
		int width = lprcMonitor->right - lprcMonitor->left;
		int height = lprcMonitor->bottom - lprcMonitor->top;

		SetWindowPos(hwnd, HWND_TOPMOST, lprcMonitor->left, lprcMonitor->top, width, height, SWP_SHOWWINDOW);

		cout << "MonitorLeft  : " << lprcMonitor->left << "\t" << "MonitorRight  : " << lprcMonitor->right << endl;
		cout << "MonitorTop   : " << lprcMonitor->top << "\t" << "MonitorBottom : " << lprcMonitor->bottom << endl;
		cout << "MonitorWidth : " << width << "\t" << "MonitorHeight : " << height << endl;

		cout << endl;

		((SLM *)dwData)->imageSLM = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////