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





#ifndef FAKECCD_C
#define FAKECCD_C

class FakeCCD
{

/*
 *	Data members
 */

private:
	IplImage *imageCCD;
	IplImage *imageDesired;

private:
	char name[3];
	int num;



/*
 *	Constructor
 */

public:
	FakeCCD();

private:
	void createWindow();

	void createImageCCD(std::string name = "Blank", std::string path = "FakeCCD");

	void createImageDesired();

	void initializeNum();



/*
 *	Interface
 */

public:
	IplImage * getImageCCD();

public:
	void snapShot(int numMax = 10, std::string path = "FakeCCD");

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