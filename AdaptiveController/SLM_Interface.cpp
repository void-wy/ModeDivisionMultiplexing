///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//����SLM�ĵ��෶Χ
/*
 *	����(int height, int width)Ϊ���෶Χ�ĸ߶ȺͿ��
 */
void SLM::getRangePM(int &height, int &width)
{
	height = heightPM;
	width = widthPM;
}

//����ָ���������λ
/*	
 *	����(int x, int y)Ϊ������λ�ĺ������������
 */
int SLM::getPhase(int x, int y)
{
	return ((uchar *)imageSLM->imageData)[(bottomPM + x) * imageSLM->widthStep + leftPM + y];
}

//����ָ���������λ
/*	
 *	����(int x, int y)Ϊ�������ĺ������������
 *	����(int value)Ϊ������λ��ֵ
 *	����(int height = 1, int width = 1)Ϊ�����С
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

//��ʾSLM���ͼ��
void SLM::showImage()
{
	cvShowImage("Image_SLM", imageSLM);

	cvWaitKey(1);

	cvShowImage("Image_Visible", imageVisible);

	cvWaitKey(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////