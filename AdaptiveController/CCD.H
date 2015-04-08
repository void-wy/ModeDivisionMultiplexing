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



#ifndef CGVIDEO_H
#define CGVIDEO_H

#include "CGVideo.h"

#endif





#ifndef CCD_C
#define CCD_C

class CCD
{

/*
 *	Data members
 */

private:
	IplImage *imageCCD;

private:
	CGSTATUS status;
	HCG hcg;
	BYTE *pImageBuffer;
	BYTE *pStaticBuffer;
	HANDLE handle;



/*
 *	Constructor
 */

public:
	CCD();

private:
	void createWindow();

	void createImageCCD();

	void initializeICC();



/*
 *	Interface
 */

public:
	IplImage * getImageCCD();

public:
	void snapShot();

public:
	void showImage();



/*
 *	Utility
 */



/*
 *	Destructor
 */

public:
	~CCD();

private:
	void finalizeICC();

	void destroyWindow();

	void releaseImage();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////