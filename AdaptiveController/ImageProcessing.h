///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HIGHGUI_H
#define HIGHGUI_H

#include "highgui.h"

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef IP_C
#define IP_C

class ImageProcessing
{
public:
	ImageProcessing();

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	void findContour(IplImage *image, int &left, int &right, int &top, int &bottom);	//得到指定图像中的光斑轮廓
																						/*
																						 *	参数(IplImage * &image)为得到光斑轮廓的图像
																						 *	参数(int &left, int &right, int &top, int &bottom)为轮廓的最左点、最右点、最上点和最下点
																						 */

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	~ImageProcessing();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////