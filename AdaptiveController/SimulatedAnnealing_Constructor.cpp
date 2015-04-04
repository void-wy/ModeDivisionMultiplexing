///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"

#include <time.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//初始化SA
SimulatedAnnealing::SimulatedAnnealing(SLM *slmSA/*, CCD *ccdSA*/, ImageProcessing *IP_SA)
{
	connectHardware(slmSA/*, ccdSA*/);	//连接硬件

	includeIP(IP_SA);

	//getImageCurrent();	//获取当前图像

	//ccd->snapShot();	//采集一帧图像
	//ccd->showImage();	//显示CCD拍摄的图像

	setRangePM();	//设置SLM的调相范围

	createWindow();	//创建SA相关窗口

	setSeedRand();	//设置随机数种子
}

//连接硬件
void SimulatedAnnealing::connectHardware(SLM *slmSA/*, CCD *ccdSA*/)
{
	slm = slmSA;
	//ccd = ccdSA;
}

void SimulatedAnnealing::includeIP(ImageProcessing *IP_SA)
{
	IP = IP_SA;
}

//获取当前图像
void SimulatedAnnealing::getImageCurrent()
{
	imageCurrent = ccd->getImageCCD();
}

//设置SLM的调相范围
void SimulatedAnnealing::setRangePM()
{
	slm->getRangePM(heightPM, widthPM);	//返回SLM的调相范围
										/*
										 *	参数(int height, int width)为调相范围的高度和宽度
										 */
}

//创建SA相关窗口
void SimulatedAnnealing::createWindow()
{
	cvNamedWindow("Image_Ideal");
}

//设置随机数种子
void SimulatedAnnealing::setSeedRand()
{
	srand((unsigned)time(NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////