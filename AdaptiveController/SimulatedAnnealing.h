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
	IplImage *imageCurrent;	//��ǰCCD�����ͼ��
	IplImage *imageIdeal;	//�����Ŀ��ͼ��

private:
	SLM *slm;	//����SLMӲ���Ķ���ָ��
	CCD *ccd;	//����CCDӲ���Ķ���ָ��

private:
	ImageProcessing *IP;

private:
	int heightPM;
	int widthPM;

private:
	int leftSpot;	//��ߵ������
	int bottomSpot;	//��ߵ������
	int heightSpot;	//��ߵĸ߶�
	int widthSpot;	//��ߵĿ��

private:
	double Ts;	//SA����ʼ�¶�
	double Tt;	//SA����ֹ�¶�
	double c;	//SA�Ľ��·���
	int cyc;	//SAͬһ�¶ȵ�ѭ������
	double BoltzmannConstant;	//������������

private:
	double correlation;	//��ǰ��ض�
	int DRN;	//SA��ֱ�ӽ��ܵĴ���
	int PRN;	//SA���������ܵĴ���
	int TN;		//SA���ܹ��Ĵ���

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	SimulatedAnnealing(SLM *slmSA/*, CCD *ccdSA*/, ImageProcessing *IP_SA);	//��ʼ��SA

private:
	void connectHardware(SLM *slmSA/*, CCD *ccdSA*/);	//����Ӳ��
	void includeIP(ImageProcessing *IP_SA);
	void getImageCurrent();	//��ȡ��ǰͼ��
	void setRangePM();	//����SLM�ĵ��෶Χ
	void createWindow();	//����SA��ش���
	void setSeedRand();	//�������������

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	void setModeIdeal(char *name, int margin);

private:
	void setRangeSpot(int margin);	//����CCD�Ĺ�߷�Χ
									/*
									 *	����(int margin)Ϊ�߾��С
									 */
	void createImageIdeal(char *name, int margin);	//���������Ŀ��ͼ��
										/*
										 *	����(int margin)Ϊ�߾��С
										 */
	void showImage();	//��ʾ�����Ŀ��ͼ��

public:
	void setParameterSA(double TsSA, double TtSA, double cSA, int cycSA);	//����SA�Ĳ���
																			/*
																			 *	����(double TsSA)Ϊ������ʼ�¶ȵ�ֵ
																			 *	����(double TtSA)Ϊ������ֹ�¶ȵ�ֵ
																			 *	����(double cSA)Ϊ���ý��·��ȵ�ֵ
																			 *	����(int cycSA)Ϊ����ѭ��������ֵ
																			 */

public:
	void run(int height, int width);	//ִ��SA

public:
	double getCorrelation();	//������ض�

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	~SimulatedAnnealing();	//���SA

private:
	void destroyWindow();	//����SA��ش���
	void releaseImage();	//�ͷ�SA���ͼ����Դ
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////