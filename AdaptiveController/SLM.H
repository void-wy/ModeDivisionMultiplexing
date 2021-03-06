///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MACROS_H
#define MACROS_H

#include "Macros.h"

#endif



#ifndef HIGHGUI_H
#define HIGHGUI_H

#include "highgui.h"

#endif



#ifndef	STRING_H
#define	STRING_H

#include <string>

#endif



#ifndef FSTREAM_H
#define FSTREAM_H

#include <fstream>

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
	IplImage *imageDesired;

private:
	int leftPM;
	int bottomPM;
	int heightPM;
	int widthPM;

private:
	MSG message;

private:
	std::ofstream *fileLog;



/*
 *	Constructor
 */

public:
	SLM(int height, int width, std::string name = "SLM_File_Log", std::string path = "Log");

private:
	void openFileLog(std::string name = "SLM_File_Log", std::string path = "Log");

	void initializeSLM();

	void setRangePM(int height, int width);

	void createImage(int flag = AC_IMAGE_ALL);

	void initializePhase();

	//	A callback function that is called by the EnumDisplayMonitors function.
	friend BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);



/*
 *	Interface
 */

public:
	void createWindow();

public:
	void destroyWindow();

public:
	IplImage * createImageCopy();

public:
	void updateImageCopy(IplImage *imageCopy);

public:
	void releaseImageCopy(IplImage *imageCopy);

public:
	void getRangePM(int &height, int &width);

public:
	int getPhase(int x, int y);

public:
	void setPhase(std::string name = "Blank", std::string path = "Phase");

public:
	void setPhase(IplImage *imageCopy);

public:
	void setPhase(int x, int y, int value, int height = 1, int width = 1);

public:
	void loadPhase();

public:
	void showImage();

public:
	void updateImageDesired();

public:
	void saveImageDesired(std::string name = "SLM_Image_Desired", std::string path = "Output");



/*
 *	Utility
 */

private:
	void runEventProcessing();



/*
 *	Destructor
 */

public:
	~SLM();

private:
	void releaseImage(int flag = AC_IMAGE_ALL);

	void finalizeSLM();

	void closeFileLog();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////