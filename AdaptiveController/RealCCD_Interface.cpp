///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "RealCCD.h"

#include "CGVidEx.h"





IplImage * RealCCD::getImageCCD()
{
	return imageCCD;
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



void RealCCD::showImageCCD()
{
	cvShowImage("Image_CCD", imageCCD);

	cvWaitKey(1);
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