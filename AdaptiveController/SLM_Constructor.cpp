///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"

#include <iostream>





SLM::SLM(int height, int width)
{
	createWindow();

	createImageSLM();

	setRangePM(height, width);

	createImageVisible();

	createImageDesired();

	initializePhase();
}



void SLM::createWindow()
{
	cvNamedWindow("Image_SLM", 0);
	cvNamedWindow("Image_Visible");
}



void SLM::createImageSLM()
{
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)this);
}



void SLM::setRangePM(int height, int width)
{
	leftPM = imageSLM->width / 2 - width / 2;
	bottomPM = imageSLM->height / 2 - height / 2;
	heightPM = height;
	widthPM = width;

	std::cout << "leftPM : " << leftPM << std::endl;
	std::cout << "bottomPM : " << bottomPM << std::endl;
	std::cout << "heightPM : " << heightPM << std::endl;
	std::cout << "widthPM : " << widthPM << std::endl;

	std::cout << std::endl;
}



void SLM::createImageVisible()
{
	imageVisible = cvCreateImage(cvSize(widthPM, heightPM), IPL_DEPTH_8U, 1);
}



void SLM::createImageDesired()
{
	imageDesired = cvCreateImage(cvGetSize(imageSLM), IPL_DEPTH_8U, 1);
}



void SLM::initializePhase()
{
	setPhase();

	loadPhase();

	showImageVisible();
}



//	A callback function that is called by the EnumDisplayMonitors function.
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	HWND hwnd = ::GetParent((HWND)cvGetWindowHandle("Image_SLM"));

	SetWindowLong(hwnd, GWL_STYLE, 0);

	if(lprcMonitor->left != 0 || lprcMonitor->top != 0)
	{
		int width = lprcMonitor->right - lprcMonitor->left;
		int height = lprcMonitor->bottom - lprcMonitor->top;

		SetWindowPos(hwnd, HWND_TOPMOST, lprcMonitor->left, lprcMonitor->top, width, height, SWP_SHOWWINDOW);

		std::cout << "MonitorLeft  : " << lprcMonitor->left << "\t" << "MonitorRight  : " << lprcMonitor->right << std::endl;
		std::cout << "MonitorTop   : " << lprcMonitor->top << "\t" << "MonitorBottom : " << lprcMonitor->bottom << std::endl;
		std::cout << "MonitorWidth : " << width << "\t" << "MonitorHeight : " << height << std::endl;

		std::cout << std::endl;

		((SLM *)dwData)->imageSLM = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////