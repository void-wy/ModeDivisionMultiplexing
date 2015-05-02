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



#ifndef	STRING_H
#define	STRING_H

#include <string>

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



/*
 *	Constructor
 */

public:
	FakeCCD();

private:
	void createWindow();

	void createImageCCD();

	void createImageDesired();

	void initializeData();



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
	~FakeCCD();

private:
	void destroyWindow();

	void releaseImage();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////