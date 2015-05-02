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



/*
 *	Constructor
 */

public:
	RealCCD();

private:
	void createWindow();

	void createImageCCD();

	void createImageDesired();

	void initializeICC();



/*
 *	Interface
 */

public:
	IplImage * getImageCCD();

public:
	void snapShot();

public:
	void showImageCCD();

public:
	void updateImageDesired();

public:
	void saveImageDesired(std::string name = "CCD_Image_Desired", std::string path = "Output");



/*
 *	Utility
 */



/*
 *	Destructor
 */

public:
	~RealCCD();

private:
	void finalizeICC();

	void destroyWindow();

	void releaseImage();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////