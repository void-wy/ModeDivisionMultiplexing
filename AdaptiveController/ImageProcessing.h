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
	void resizeImage(IplImage *imageCurrent, IplImage *imageIdeal);

public:
	void findContour(IplImage *image, int &left, int &right, int &top, int &bottom);

public:
	double getCorrelation(IplImage *imageCurrent, IplImage *imageIdeal);

public:
	int getMaxValue(IplImage *image);

public:
	int getMinValue(IplImage *image);

public:
	double getMean(IplImage *image);

public:
	double getVariance(IplImage *image);

public:
	void setNormalization(IplImage *image, int maxValueIdeal = 255, int minValueIdeal = 0);

public:
	void setMedianFiltering(IplImage *imageCurrent, IplImage *imageIdeal);



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