///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////
/*

#include "SimulatedAnnealing.h"

#include "RealCCD.h"

#include "FakeCCD.h"





void main()
{
	SLM *slm = new SLM(400, 400);

	//RealCCD *ccd = new RealCCD();

	FakeCCD *ccd = new FakeCCD();

	ImageProcessing *IP = new ImageProcessing();

	SimulatedAnnealing *SA = new SimulatedAnnealing(slm, ccd, IP);



	slm->createWindow();

	SA->createWindow();



	SA->openFileSA();

	SA->setModeIdeal(15, "11a");

	SA->createImageSA();

	SA->setPhaseInitial("01-11a");

	SA->setParameterSA(10000000, 100, 0.95, 100);

	SA->startClock();

	SA->runSA(200, 200);

	SA->finishClock();

	SA->saveImageResult();

	SA->saveFileResult();

	SA->closeFileSA();



	SA->destroyWindow();

	slm->destroyWindow();



	delete SA;
	delete IP;
	delete ccd;
	delete slm;
}

*/
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////