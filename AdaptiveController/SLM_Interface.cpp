///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"





void SLM::getRangePM(int &height, int &width)
{
	height = heightPM;
	width = widthPM;
}



int SLM::getPhase(int x, int y)
{
	return ((uchar *)imageSLM->imageData)[(bottomPM + x) * imageSLM->widthStep + leftPM + y];
}



void SLM::setPhase(int x, int y, int value, int height, int width)
{
	for(int i = x; i < x + height; i++)
	{
		for(int j = y; j < y + width; j++)
		{
			((uchar *)imageSLM->imageData)[(bottomPM + i) * imageSLM->widthStep + leftPM + j] = value;
			((uchar *)imageVisible->imageData)[i * imageVisible->widthStep + j] = value;
		}
	}
}



void SLM::showImage()
{
	cvShowImage("Image_SLM", imageSLM);

	cvWaitKey(1);

	cvShowImage("Image_Visible", imageVisible);

	cvWaitKey(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////