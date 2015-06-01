///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "RealCCD.h"





RealCCD::RealCCD(std::string name, std::string path)
{
	openFileLog(name, path);

	createImageCCD();

	createImageDesired();

	initializeICC();
}



void RealCCD::openFileLog(std::string name, std::string path)
{
	path = path + "\\" + name;

	fileLog = new std::ofstream();

	fileLog->open(path.c_str());

	fileLog->precision(10);
}



void RealCCD::createImageCCD()
{
	imageCCD = cvCreateImageHeader(cvSize(768, 576), IPL_DEPTH_8U, 1);
}



void RealCCD::createImageDesired()
{
	imageDesired = cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
}



void RealCCD::initializeICC()
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