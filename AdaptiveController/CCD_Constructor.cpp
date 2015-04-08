///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "CCD.H"





CCD::CCD()
{
	createWindow();

	createImageCCD();

	initializeICC();
}



void CCD::createWindow()
{
	cvNamedWindow("Image_CCD");
}



void CCD::createImageCCD()
{
	imageCCD = cvCreateImageHeader(cvSize(768, 576), IPL_DEPTH_8U, 1);
}



void CCD::initializeICC()
{
	hcg = NULL;
	status = CG_OK;

	status = BeginCGCard(1, &hcg);

	CG_VERIFY(status);

	CGSetVideoStandard(hcg, PAL);
	CGSetScanMode(hcg, FRAME);
	CGSelectCryOSC(hcg, CRY_OSC_35M);
	CGSetVideoFormat(hcg, ALL8BIT);

	VIDEO_SOURCE source;

	source.type = COMPOSITE_VIDEO;
	source.nIndex = 0;

	CGSetVideoSource(hcg, source);
	CGSetInputWindow(hcg, 0, 0, 768, 576);
	CGSetOutputWindow(hcg, 0, 0, 768, 576);

	pImageBuffer = new BYTE[768 * 576];
	pStaticBuffer = NULL;
	handle = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////