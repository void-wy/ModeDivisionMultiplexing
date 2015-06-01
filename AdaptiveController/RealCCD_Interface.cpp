///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "RealCCD.h"

#include "CGVidEx.h"





void RealCCD::createWindow()
{
	cvNamedWindow("Image_CCD");
}



void RealCCD::destroyWindow()
{
	cvDestroyWindow("Image_CCD");
}



IplImage * RealCCD::createImageCopy()
{
	return cvCreateImage(cvGetSize(imageCCD), IPL_DEPTH_8U, 1);
}



void RealCCD::updateImageCopy(IplImage *imageCopy)
{
	for(int i = 0; i < imageCopy->height; i++)
	{
		for(int j = 0; j < imageCopy->width; j++)
		{
			((uchar *)imageCopy->imageData)[i * imageCopy->widthStep + j] =
				((uchar *)imageCCD->imageData)[i * imageCCD->widthStep + j];
		}
	}
}



void RealCCD::releaseImageCopy(IplImage *imageCopy)
{
	cvReleaseImage(&imageCopy);
}



void RealCCD::snapShot()
{
	status = CGSnapShot(hcg, 0, 0, TRUE, 1);

	CG_VERIFY(status);

	if(CG_SUCCESS(status))
	{
		status = CGStaticMemLock(0, 768 * 576, &handle, (VOID **)&pStaticBuffer);

		if(CG_SUCCESS(status))
		{
			CGDataTransform(pImageBuffer, pStaticBuffer, 768, 576, 8, FALSE);
		}

		CGStaticMemUnlock(handle);
	}

	imageCCD->imageData = (char *)pImageBuffer;
}



void RealCCD::snapShot(IplImage *imageCopy)
{
	status = CGSnapShot(hcg, 0, 0, TRUE, 1);

	CG_VERIFY(status);

	if(CG_SUCCESS(status))
	{
		status = CGStaticMemLock(0, 768 * 576, &handle, (VOID **)&pStaticBuffer);

		if(CG_SUCCESS(status))
		{
			CGDataTransform(pImageBuffer, pStaticBuffer, 768, 576, 8, FALSE);
		}

		CGStaticMemUnlock(handle);
	}

	imageCopy->imageData = (char *)pImageBuffer;
}



void RealCCD::showImageCCD()
{
	cvShowImage("Image_CCD", imageCCD);

	runEventProcessing();
}



void RealCCD::updateImageDesired()
{
	for(int i = 0; i < imageDesired->height; i++)
	{
		for(int j = 0; j < imageDesired->width; j++)
		{
			((uchar *)imageDesired->imageData)[i * imageDesired->widthStep + j] =
				((uchar *)imageCCD->imageData)[i * imageCCD->widthStep + j];
		}
	}
}



void RealCCD::saveImageDesired(std::string name, std::string path)
{
	path = path + "\\" + name + ".bmp";

	cvSaveImage(path.c_str(), imageDesired);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////