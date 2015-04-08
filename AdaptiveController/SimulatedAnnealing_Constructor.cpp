///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"

#include <time.h>





SimulatedAnnealing::SimulatedAnnealing(SLM *slmSA/*, CCD *ccdSA*/, ImageProcessing *IP_SA)
{
	connectHardware(slmSA/*, ccdSA*/);

	includeIP(IP_SA);

	//getImageCurrent();

	//ccd->snapShot();
	//ccd->showImage();

	setRangePM();

	createWindow();

	setSeedRand();
}



void SimulatedAnnealing::connectHardware(SLM *slmSA/*, CCD *ccdSA*/)
{
	slm = slmSA;
	//ccd = ccdSA;
}



void SimulatedAnnealing::includeIP(ImageProcessing *IP_SA)
{
	IP = IP_SA;
}



void SimulatedAnnealing::getImageCurrent()
{
	imageCurrent = ccd->getImageCCD();
}



void SimulatedAnnealing::setRangePM()
{
	slm->getRangePM(heightPM, widthPM);
}



void SimulatedAnnealing::createWindow()
{
	cvNamedWindow("Image_Ideal");
}



void SimulatedAnnealing::setSeedRand()
{
	srand((unsigned)time(NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////