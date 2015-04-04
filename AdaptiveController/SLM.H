///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef WINVER_M
#define WINVER_M

#define WINVER	0x0500	//ʹĳЩ���ñ�ʶ��������

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
	IplImage *imageSLM;	//SLM�ϼ��ص���λͼ��
	IplImage *imageVisible;	//�۲�SLM�ϼ�����λ��ͼ��

private:
	int leftPM;	//���������
	int bottomPM;	//���������
	int heightPM;	//����߶�
	int widthPM;	//�������

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	SLM(int height, int width);	//��ʼ��SLM
								/*
								 *	����(int height, int width)ΪSLM���෶Χ�ĸ߶ȺͿ���
								 */

private:
	void createWindow();	//����SLM��ش���
	void createImageSLM();	//����SLM�ϼ��ص���λͼ��
	void setRangePM(int height, int width);	//����SLM�ĵ��෶Χ
											/*
											 *	����(int height, int width)Ϊ���෶Χ�ĸ߶ȺͿ���
											 */
	void createImageVisible();	//�����۲�SLM�ϼ�����λ��ͼ��
	void initializePhase();	//��ʼ��SLM�ϵ���λͼΪ��

	friend BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);	//EnumDisplayMonitors�Ļص�����

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	void getRangePM(int &height, int &width);	//����SLM�ĵ��෶Χ
												/*
												 *	����(int height, int width)Ϊ���෶Χ�ĸ߶ȺͿ���
												 */

public:
	int getPhase(int x, int y);	//����ָ���������λ
								/*	
								 *	����(int x, int y)Ϊ������λ�ĺ������������
								 */

public:
	void setPhase(int x, int y, int value, int height = 1, int width = 1);	//����ָ���������λ
																			/*	
																			 *	����(int x, int y)Ϊ�������ĺ������������
																			 *	����(int value)Ϊ������λ��ֵ
																			 *	����(int height = 1, int width = 1)Ϊ�����С
																			 */

public:
	void showImage();	//��ʾSLM���ͼ��

///////////////////////////////////////////////////////////////////////////////////////////////////

public:
	~SLM();	//�ر�SLM

private:
	void destroyWindow();	//����SLM��ش���
	void releaseImage();	//�ͷ�SLM���ͼ����Դ
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////