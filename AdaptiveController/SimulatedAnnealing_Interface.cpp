///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void SimulatedAnnealing::setModeIdeal(char *name, int margin)
{
	setRangeSpot(margin);	//����CCD�Ĺ�߷�Χ
							/*
							 *	����(int margin)Ϊ�߾��С
							 */

	createImageIdeal(name, margin);	//���������Ŀ��ͼ��
								/*
								 *	����(int margin)Ϊ�߾��С
								 */

	showImage();	//��ʾ�����Ŀ��ͼ��
}

//����SA�Ĳ���
/*
 *	����(double TsSA)Ϊ������ʼ�¶ȵ�ֵ
 *	����(double TtSA)Ϊ������ֹ�¶ȵ�ֵ
 *	����(double cSA)Ϊ���ý��·��ȵ�ֵ
 *	����(int cycSA)Ϊ����ѭ��������ֵ
 */
void SimulatedAnnealing::setParameterSA(double TsSA, double TtSA, double cSA, int cycSA)
{
	Ts = TsSA;
	Tt = TtSA;
	c = cSA;
	cyc = cycSA;
	BoltzmannConstant = 1.3806488e-23;

	correlation = 0;
	DRN = 0;
	PRN = 0;
	TN = 0;

	cout << "Ts : " << Ts << endl;
	cout << "Tt : " << Tt << endl;
	cout << "c : " << c << endl;
	cout << "cyc : " << cyc << endl;
	cout << "BoltzmannConstant : " << BoltzmannConstant << endl;

	cout << "correlation : " << correlation << endl;
	cout << "DRN : " << DRN << endl;
	cout << "PRN : " << PRN << endl;
	cout << "TN : " << TN << endl;

	cout << endl;
}

//ִ��SA
void SimulatedAnnealing::run(int height, int width)
{
	int x, y;
	double tempCorrelation;

	while(1)
	{
		if(100 == TN)
		{
			break;
		}

		if(Ts > Tt)
		{
			for(int i = 0; i < cyc; i++)
			{
				x = (rand() % (heightPM / height)) * height;
				y = (rand() % (widthPM / width)) * width;

				slm->setPhase(x, y, 127^slm->getPhase(x, y), height, width);
				slm->showImage();

				//ccd->snapShot();
				//ccd->showImage();

				tempCorrelation = getCorrelation();

				//TN
				TN += 1;

				if(tempCorrelation > correlation)
				{
					correlation = tempCorrelation;

					cout << tempCorrelation << endl;

					//DRN
					DRN += 1;
				}
				else if(exp((tempCorrelation - correlation) / (BoltzmannConstant * Ts)) > rand() / (double)RAND_MAX)
				{
					correlation = tempCorrelation;

					//PRN
					PRN += 1;
				}
				else
				{
					slm->setPhase(x, y, 127^slm->getPhase(x, y), height, width);
				}
			}

			Ts = c * Ts;
		}
		else
		{
			break;
		}
	}

	cout << "TN : " << TN << endl;
	cout << "DRN : " << DRN << endl;
	cout << "PRN : " << PRN << endl;
	cout << correlation << endl;
}

//������ض�
double SimulatedAnnealing::getCorrelation()
{
	int cdIdeal, cdCurrent;

	double sumNumerator = 0, sumDenominator1 = 0, sumDenominator2 = 0;

	for(int i = 0; i < imageIdeal->height; i++)
	{
		for(int j = 0; j < imageIdeal->width; j++)
		{
			cdIdeal = i * imageIdeal->widthStep + j;
			cdCurrent = (i + bottomSpot) * imageCurrent->widthStep + j + leftSpot;

			sumNumerator += ((uchar *)imageIdeal->imageData)[cdIdeal] * ((uchar *)imageCurrent->imageData)[cdCurrent];
			sumDenominator1 += ((uchar *)imageIdeal->imageData)[cdIdeal] * ((uchar *)imageIdeal->imageData)[cdIdeal];
			sumDenominator2 += ((uchar *)imageCurrent->imageData)[cdCurrent] * ((uchar *)imageCurrent->imageData)[cdCurrent];
		}
	}

	return (sumNumerator * sumNumerator) / (sumDenominator1 * sumDenominator2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////