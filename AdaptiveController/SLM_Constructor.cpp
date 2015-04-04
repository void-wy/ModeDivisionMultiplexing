///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//��ʼ��SLM
/*
 *	����(int height, int width)ΪSLM���෶Χ�ĸ߶ȺͿ��
 */
SLM::SLM(int height, int width)
{
	createWindow();	//����SLM��ش���

	createImageSLM();	//����SLM�ϼ��ص���λͼ��

	setRangePM(height, width);	//����SLM�ĵ��෶Χ
								/*
								 *	����(int height, int width)Ϊ���෶Χ�ĸ߶ȺͿ��
								 */

	createImageVisible();	//�����۲�SLM�ϼ�����λ��ͼ��

	initializePhase();	//��ʼ��SLM�ϵ���λͼΪ��

	showImage();	//��ʾSLM���ͼ��
}

//����SLM��ش���
void SLM::createWindow()
{
	cvNamedWindow("Image_SLM", 0);
	cvNamedWindow("Image_Visible");
}

//����SLM�ϼ��ص���λͼ��
void SLM::createImageSLM()
{
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)this);	//������ʾ�豸
}

//����SLM�ĵ��෶Χ
/*
 *	����(int height, int width)Ϊ���෶Χ�ĸ߶ȺͿ��
 */
void SLM::setRangePM(int height, int width)
{
	leftPM = imageSLM->width / 2 - width / 2;
	bottomPM = imageSLM->height / 2 - height / 2;
	heightPM = height;
	widthPM = width;

	cout << "leftPM : " << leftPM << endl;
	cout << "bottomPM : " << bottomPM << endl;
	cout << "heightPM : " << heightPM << endl;
	cout << "widthPM : " << widthPM << endl;

	cout << endl;
}

//�����۲�SLM�ϼ�����λ��ͼ��
void SLM::createImageVisible()
{
	imageVisible = cvCreateImage(cvSize(widthPM, heightPM), IPL_DEPTH_8U, 1);
}

//��ʼ��SLM�ϵ���λͼΪ��
void SLM::initializePhase()
{
	int i, j;

	for(i = 0; i < imageSLM->height; i++)
	{
		for(j = 0; j < imageSLM->width; j++)
		{
			((uchar *)imageSLM->imageData)[i * imageSLM->widthStep + j] = 0;
		}
	}

	for(i = 0; i < imageVisible->height; i++)
	{
		for(j = 0; j < imageVisible->width; j++)
		{
			((uchar *)imageVisible->imageData)[i * imageVisible->widthStep + j] = 0;
		}
	}
}

//EnumDisplayMonitors�Ļص�����
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	HWND hwnd = ::GetParent((HWND)cvGetWindowHandle("Image_SLM"));

	SetWindowLong(hwnd, GWL_STYLE, 0);

	if(lprcMonitor->left != 0 || lprcMonitor->top != 0)
	{
		int width = lprcMonitor->right - lprcMonitor->left;
		int height = lprcMonitor->bottom - lprcMonitor->top;

		SetWindowPos(hwnd, HWND_TOPMOST, lprcMonitor->left, lprcMonitor->top, width, height, SWP_SHOWWINDOW);

		cout << "MonitorLeft  : " << lprcMonitor->left << "\t" << "MonitorRight  : " << lprcMonitor->right << endl;
		cout << "MonitorTop   : " << lprcMonitor->top << "\t" << "MonitorBottom : " << lprcMonitor->bottom << endl;
		cout << "MonitorWidth : " << width << "\t" << "MonitorHeight : " << height << endl;

		cout << endl;

		((SLM *)dwData)->imageSLM = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////