///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CCD_H
#define CCD_H

#include "CCD.H"

#endif



#ifndef HIGHGUI_H
#define HIGHGUI_H

#include "highgui.h"

#endif



#ifndef CGVIDEO_H
#define CGVIDEO_H

#include "CGVideo.h"

#endif



#ifndef	STRING_H
#define	STRING_H

#include <string>

#endif



#ifndef FSTREAM_H
#define FSTREAM_H

#include <fstream>

#endif





#ifndef REALCCD_C
#define REALCCD_C

class RealCCD : public CCD
{

/*
 *	Data members
 */

private:
	IplImage *imageCCD;
	IplImage *imageDesired;

private:
	CGSTATUS status;
	HCG hcg;
	BYTE *pImageBuffer;
	BYTE *pStaticBuffer;
	HANDLE handle;

private:
	MSG message;

private:
	std::ofstream *fileLog;



/*
 *	Constructor
 */

public:
	RealCCD(std::string name = "CCD_File_Log", std::string path = "Log");

private:
	void openFileLog(std::string name = "CCD_File_Log", std::string path = "Log");

	void createImageCCD();

	void createImageDesired();

	void initializeICC();



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
	void snapShot();

public:
	void snapShot(IplImage *imageCopy);

public:
	void showImageCCD();

public:
	void updateImageDesired();

public:
	void saveImageDesired(std::string name = "CCD_Image_Desired", std::string path = "Output");



/*
 *	Utility
 */

private:
	void runEventProcessing();



/*
 *	Destructor
 */

public:
	~RealCCD();

private:
	void finalizeICC();

	void releaseImage();

	void closeFileLog();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////