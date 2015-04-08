///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"





void main()
{
	SLM *slm = new SLM(400, 400);
	//CCD *ccd = new CCD();
	ImageProcessing *IP = new ImageProcessing();
	SimulatedAnnealing *SA = new SimulatedAnnealing(slm/*, ccd*/, IP);

	SA->setModeIdeal("11a", 15);
	SA->setParameterSA(10000000, 100, 0.95, 100);
	SA->run(200, 200);

	delete SA;
	delete IP;
	//delete ccd;
	delete slm;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////