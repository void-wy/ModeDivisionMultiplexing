///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"





SimulatedAnnealing::SimulatedAnnealing(SLM *slm, /*Test*/ FakeCCD *ccd, ImageProcessing *IP)
{
	connectHardware(slm, ccd);

	includeIP(IP);

	getImageCurrent();

	ccd->snapShot();
	ccd->showImageCCD();

	setRangePM();

	createWindow();

	setSeedRand();
}



void SimulatedAnnealing::connectHardware(SLM *slm, /*Test*/ FakeCCD *ccd)
{
	this->slm = slm;
	this->ccd = ccd;
}



void SimulatedAnnealing::includeIP(ImageProcessing *IP)
{
	this->IP = IP;
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