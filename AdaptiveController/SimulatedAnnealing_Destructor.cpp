///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//���SA
SimulatedAnnealing::~SimulatedAnnealing()
{
	destroyWindow();

	releaseImage();
}

//����SA��ش���
void SimulatedAnnealing::destroyWindow()
{
	cvWaitKey(0);

	cvDestroyWindow("Image_Ideal");
}

//�ͷ�SA���ͼ����Դ
void SimulatedAnnealing::releaseImage()
{
	cvReleaseImage(&imageIdeal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////