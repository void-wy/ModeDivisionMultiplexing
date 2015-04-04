///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SLM_H
#define SLM_H

#include "SLM.H"

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CCD_H
#define CCD_H

#include "CCD.H"

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DIP_H
#define DIP_H

#include "ImageProcessing.h"

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SA_C
#define SA_C

class SimulatedAnnealing
{
private:
	IplImage *imageCurrent;	//当前CCD拍摄的图像
	IplImage *imageIdeal;	//理想的目标图像

private:
	SLM *slm;	//控制SLM硬件的对象指针
	CCD *ccd;	//控制CCD硬件的对象指针

private:
	ImageProcessing *IP;

private:
	int heightPM;
	int widthPM;

private:
	int leftSpot;	//光斑的左起点
	int bottomSpot;	//光斑的下起点
	int heightSpot;	//光斑的高度
	int widthSpot;	//光斑的宽度

private:
	double Ts;	//SA的起始温度
	double Tt;	//SA的终止温度
	double c;	//SA的降温幅度
	int cyc;	//SA同一温度的循环次数
	double BoltzmannConstant;	//玻尔兹曼常量

private:
	double correlation;	//当前相关度
	int DRN;	//SA中直接接受的次数
	int PRN;	//SA中条件接受的次数
	int TN;		//SA中总共的次数

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	SimulatedAnnealing(SLM *slmSA/*, CCD *ccdSA*/, ImageProcessing *IP_SA);	//初始化SA

private:
	void connectHardware(SLM *slmSA/*, CCD *ccdSA*/);	//连接硬件
	void includeIP(ImageProcessing *IP_SA);
	void getImageCurrent();	//获取当前图像
	void setRangePM();	//设置SLM的调相范围
	void createWindow();	//创建SA相关窗口
	void setSeedRand();	//设置随机数种子

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	void setModeIdeal(char *name, int margin);

private:
	void setRangeSpot(int margin);	//设置CCD的光斑范围
									/*
									 *	参数(int margin)为边距大小
									 */
	void createImageIdeal(char *name, int margin);	//创建理想的目标图像
										/*
										 *	参数(int margin)为边距大小
										 */
	void showImage();	//显示理想的目标图像

public:
	void setParameterSA(double TsSA, double TtSA, double cSA, int cycSA);	//设置SA的参数
																			/*
																			 *	参数(double TsSA)为设置起始温度的值
																			 *	参数(double TtSA)为设置终止温度的值
																			 *	参数(double cSA)为设置降温幅度的值
																			 *	参数(int cycSA)为设置循环次数的值
																			 */

public:
	void run(int height, int width);	//执行SA

public:
	double getCorrelation();	//计算相关度

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	~SimulatedAnnealing();	//完成SA

private:
	void destroyWindow();	//销毁SA相关窗口
	void releaseImage();	//释放SA相关图像资源
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////