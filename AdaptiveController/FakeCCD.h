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



#ifndef CCD_H
#define CCD_H

#include "CCD.H"

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





#ifndef FAKECCD_C
#define FAKECCD_C

class FakeCCD : public CCD
{

/*
 *	Data members
 */

private:
	IplImage *imageCCD;
	IplImage *imageDesired;

private:
	std::string directory;
	std::string name;
	int numMax;
	int num;

private:
	MSG message;

private:
	std::ofstream *fileLog;



/*
 *	Constructor
 */

public:
	FakeCCD(std::string name = "CCD_File_Log", std::string path = "Log");

private:
	void openFileLog(std::string name = "CCD_File_Log", std::string path = "Log");

	void initializeData();

	void createImage(int flag = AC_IMAGE_ALL);



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
	void showImage();

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
	~FakeCCD();

private:
	void releaseImage(int flag = AC_IMAGE_ALL);

	void closeFileLog();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////