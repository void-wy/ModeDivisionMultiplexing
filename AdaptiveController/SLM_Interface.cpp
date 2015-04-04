///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//返回SLM的调相范围
/*
 *	参数(int height, int width)为调相范围的高度和宽度
 */
void SLM::getRangePM(int &height, int &width)
{
	height = heightPM;
	width = widthPM;
}

//返回指定坐标的相位
/*	
 *	参数(int x, int y)为返回相位的横坐标和纵坐标
 */
int SLM::getPhase(int x, int y)
{
	return ((uchar *)imageSLM->imageData)[(bottomPM + x) * imageSLM->widthStep + leftPM + y];
}

//设置指定区域的相位
/*	
 *	参数(int x, int y)为区域起点的横坐标和纵坐标
 *	参数(int value)为设置相位的值
 *	参数(int height = 1, int width = 1)为区域大小
 */
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

//显示SLM相关图像
void SLM::showImage()
{
	cvShowImage("Image_SLM", imageSLM);

	cvWaitKey(1);

	cvShowImage("Image_Visible", imageVisible);

	cvWaitKey(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////