///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SLM.H"





SLM::~SLM()
{
	destroyWindow();

	releaseImage();

	closeFileLog();
}



void SLM::destroyWindow()
{
	cvWaitKey(0);

	cvDestroyWindow("Image_SLM");
	cvDestroyWindow("Image_Visible");
}



void SLM::releaseImage()
{
	cvReleaseImage(&imageSLM);
	cvReleaseImage(&imageVisible);
	cvReleaseImage(&imageDesired);
}



void SLM::closeFileLog()
{
	fileLog->close();

	delete fileLog;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////