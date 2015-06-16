///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HIGHGUI_H
#define HIGHGUI_H

#include "highgui.h"

#endif



#ifndef	STRING_H
#define	STRING_H

#include <string>

#endif





#ifndef CCD_C
#define CCD_C

class CCD
{
public:
	virtual void createWindow() = 0;

public:
	virtual void destroyWindow() = 0;

public:
	virtual IplImage * createImageCopy() = 0;

public:
	virtual void updateImageCopy(IplImage *imageCopy) = 0;

public:
	virtual void releaseImageCopy(IplImage *imageCopy) = 0;

public:
	virtual void snapShot() = 0;

public:
	virtual void snapShot(IplImage *imageCopy) = 0;

public:
	virtual void showImage() = 0;

public:
	virtual void updateImageDesired() = 0;

public:
	virtual void saveImageDesired(std::string name = "CCD_Image_Desired", std::string path = "Output") = 0;
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////