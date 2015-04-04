///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef WINVER_M
#define WINVER_M

#define WINVER	0x0500	//使某些所用标识符被声明

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HIGHGUI_H
#define HIGHGUI_H

#include "highgui.h"

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SLM_C
#define SLM_C

class SLM
{
private:
	IplImage *imageSLM;	//SLM上加载的相位图像
	IplImage *imageVisible;	//观察SLM上加载相位的图像

private:
	int leftPM;	//调相左起点
	int bottomPM;	//调相下起点
	int heightPM;	//调相高度
	int widthPM;	//调相宽度

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	SLM(int height, int width);	//初始化SLM
								/*
								 *	参数(int height, int width)为SLM调相范围的高度和宽度
								 */

private:
	void createWindow();	//创建SLM相关窗口
	void createImageSLM();	//创建SLM上加载的相位图像
	void setRangePM(int height, int width);	//设置SLM的调相范围
											/*
											 *	参数(int height, int width)为调相范围的高度和宽度
											 */
	void createImageVisible();	//创建观察SLM上加载相位的图像
	void initializePhase();	//初始化SLM上的相位图为零

	friend BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);	//EnumDisplayMonitors的回调函数

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	void getRangePM(int &height, int &width);	//返回SLM的调相范围
												/*
												 *	参数(int height, int width)为调相范围的高度和宽度
												 */

public:
	int getPhase(int x, int y);	//返回指定坐标的相位
								/*	
								 *	参数(int x, int y)为返回相位的横坐标和纵坐标
								 */

public:
	void setPhase(int x, int y, int value, int height = 1, int width = 1);	//设置指定区域的相位
																			/*	
																			 *	参数(int x, int y)为区域起点的横坐标和纵坐标
																			 *	参数(int value)为设置相位的值
																			 *	参数(int height = 1, int width = 1)为区域大小
																			 */

public:
	void showImage();	//显示SLM相关图像

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	~SLM();	//关闭SLM

private:
	void destroyWindow();	//销毁SLM相关窗口
	void releaseImage();	//释放SLM相关图像资源
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////