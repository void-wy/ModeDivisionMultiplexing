///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"





SLM::SLM(int height, int width, std::string name, std::string path)
{
	openFileLog(name, path);

	initializeSLM();

	setRangePM(height, width);

	createImage();

	initializePhase();
}



void SLM::openFileLog(std::string name, std::string path)
{
	path = path + "\\" + name;

	fileLog = new std::ofstream();

	fileLog->open(path.c_str());

	fileLog->precision(10);
}



void SLM::initializeSLM()
{
	cvNamedWindow("Image_SLM", 0);

	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)this);
}



void SLM::setRangePM(int height, int width)
{
	leftPM = imageSLM->width / 2 - width / 2;
	bottomPM = imageSLM->height / 2 - height / 2;
	heightPM = height;
	widthPM = width;

	*fileLog << "leftPM : " << leftPM << std::endl;
	*fileLog << "bottomPM : " << bottomPM << std::endl;
	*fileLog << "heightPM : " << heightPM << std::endl;
	*fileLog << "widthPM : " << widthPM << std::endl;
}



void SLM::createImage(int flag)
{
	switch(flag)
	{
	case AC_IMAGE_ALL:
		{
			imageVisible = cvCreateImage(cvSize(widthPM, heightPM), IPL_DEPTH_8U, 1);
			imageDesired = cvCreateImage(cvGetSize(imageSLM), IPL_DEPTH_8U, 1);
		}

		break;

	case AC_IMAGE_VISIBLE:
		{
			imageVisible = cvCreateImage(cvSize(widthPM, heightPM), IPL_DEPTH_8U, 1);
		}

		break;

	case AC_IMAGE_DESIRED:
		{
			imageDesired = cvCreateImage(cvGetSize(imageSLM), IPL_DEPTH_8U, 1);
		}

		break;

	default:
		break;
	}
}



void SLM::initializePhase()
{
	setPhase();

	loadPhase();
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

		*((SLM *)dwData)->fileLog << "MonitorLeft  : " << lprcMonitor->left << "\t" << "MonitorRight  : " << lprcMonitor->right << std::endl;
		*((SLM *)dwData)->fileLog << "MonitorTop   : " << lprcMonitor->top << "\t" << "MonitorBottom : " << lprcMonitor->bottom << std::endl;
		*((SLM *)dwData)->fileLog << "MonitorWidth : " << width << "\t" << "MonitorHeight : " << height << std::endl;

		((SLM *)dwData)->imageSLM = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////