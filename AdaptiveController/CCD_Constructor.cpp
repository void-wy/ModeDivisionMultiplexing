///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "CCD.H"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//��ʼ��CCD
CCD::CCD()
{
	createWindow();	//����CCD��ش���

	createImageCCD();	//����CCD�����ͼ��

	initializeICC();	//��ʼ��ICC
}

//����CCD��ش���
void CCD::createWindow()
{
	cvNamedWindow("Image_CCD");
}

//����CCD�����ͼ��
void CCD::createImageCCD()
{
	imageCCD = cvCreateImageHeader(cvSize(768, 576), IPL_DEPTH_8U, 1);
}

//��ʼ��ICC
void CCD::initializeICC()
{
	hcg = NULL;
	status = CG_OK;

	status = BeginCGCard(1, &hcg);

	CG_VERIFY(status);

	CGSetVideoStandard(hcg, PAL);	//������Ƶ��ʽ
	CGSetScanMode(hcg, FRAME);	//����ɨ��ģʽ
	CGSelectCryOSC(hcg, CRY_OSC_35M);	//���þ���
	CGSetVideoFormat(hcg, ALL8BIT);	//������Ƶ��ʽ

	VIDEO_SOURCE source;

	source.type = COMPOSITE_VIDEO;
	source.nIndex = 0;

	CGSetVideoSource(hcg, source);	//������ƵԴ·
	CGSetInputWindow(hcg, 0, 0, 768, 576);	//������Ƶ���봰��
	CGSetOutputWindow(hcg, 0, 0, 768, 576);	//������Ƶ�������

	pImageBuffer = new BYTE[768 * 576];
	pStaticBuffer = NULL;
	handle = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////