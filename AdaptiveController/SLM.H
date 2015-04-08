///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef WINVER_M
#define WINVER_M

#define WINVER	0x0500

#endif



#ifndef HIGHGUI_H
#define HIGHGUI_H

#include "highgui.h"

#endif





#ifndef SLM_C
#define SLM_C

class SLM
{

/*
 *	Data members
 */

private:
	IplImage *imageSLM;
	IplImage *imageVisible;

private:
	int leftPM;
	int bottomPM;
	int heightPM;
	int widthPM;



/*
 *	Constructor
 */

public:
	SLM(int height, int width);

private:
	void createWindow();

	void createImageSLM();

	void setRangePM(int height, int width);

	void createImageVisible();

	void initializePhase();

	//	A callback function that is called by the EnumDisplayMonitors function.
	friend BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);



/*
 *	Interface
 */

public:
	void getRangePM(int &height, int &width);

public:
	int getPhase(int x, int y);

public:
	void setPhase(int x, int y, int value, int height = 1, int width = 1);

public:
	void showImage();



/*
 *	Utility
 */



/*
 *	Destructor
 */

public:
	~SLM();

private:
	void destroyWindow();

	void releaseImage();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////