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





#ifndef IP_C
#define IP_C

class ImageProcessing
{

/*
 *	Data members
 */



/*
 *	Constructor
 */

public:
	ImageProcessing();



/*
 *	Interface
 */

public:
	void findContour(IplImage *image, int &left, int &right, int &top, int &bottom);



/*
 *	Utility
 */



/*
 *	Destructor
 */

public:
	~ImageProcessing();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////