///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"

#include <time.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//��ʼ��SA
SimulatedAnnealing::SimulatedAnnealing(SLM *slmSA/*, CCD *ccdSA*/, ImageProcessing *IP_SA)
{
	connectHardware(slmSA/*, ccdSA*/);	//����Ӳ��

	includeIP(IP_SA);

	//getImageCurrent();	//��ȡ��ǰͼ��

	//ccd->snapShot();	//�ɼ�һ֡ͼ��
	//ccd->showImage();	//��ʾCCD�����ͼ��

	setRangePM();	//����SLM�ĵ��෶Χ

	createWindow();	//����SA��ش���

	setSeedRand();	//�������������
}

//����Ӳ��
void SimulatedAnnealing::connectHardware(SLM *slmSA/*, CCD *ccdSA*/)
{
	slm = slmSA;
	//ccd = ccdSA;
}

void SimulatedAnnealing::includeIP(ImageProcessing *IP_SA)
{
	IP = IP_SA;
}

//��ȡ��ǰͼ��
void SimulatedAnnealing::getImageCurrent()
{
	imageCurrent = ccd->getImageCCD();
}

//����SLM�ĵ��෶Χ
void SimulatedAnnealing::setRangePM()
{
	slm->getRangePM(heightPM, widthPM);	//����SLM�ĵ��෶Χ
										/*
										 *	����(int height, int width)Ϊ���෶Χ�ĸ߶ȺͿ��
										 */
}

//����SA��ش���
void SimulatedAnnealing::createWindow()
{
	cvNamedWindow("Image_Ideal");
}

//�������������
void SimulatedAnnealing::setSeedRand()
{
	srand((unsigned)time(NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////