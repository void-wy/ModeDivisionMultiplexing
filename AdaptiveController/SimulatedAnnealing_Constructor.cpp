///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimulatedAnnealing.h"





SimulatedAnnealing::SimulatedAnnealing(SLM *slm, CCD *ccd, ImageProcessing *IP, std::string name, std::string path)
{
	openFileLog(name, path);

	connectHardware(slm, ccd);

	includeIP(IP);

	createImageCCD();

	setRangePM();

	setSeedRand();
}



void SimulatedAnnealing::openFileLog(std::string name, std::string path)
{
	path = path + "\\" + name;

	fileLog = new std::ofstream();

	fileLog->open(path.c_str());

	fileLog->precision(10);
}



void SimulatedAnnealing::connectHardware(SLM *slm, CCD *ccd)
{
	this->slm = slm;
	this->ccd = ccd;
}



void SimulatedAnnealing::includeIP(ImageProcessing *IP)
{
	this->IP = IP;
}



void SimulatedAnnealing::createImageCCD()
{
	imageCCD = ccd->createImageCopy();
}



void SimulatedAnnealing::setRangePM()
{
	slm->getRangePM(heightPM, widthPM);
}



void SimulatedAnnealing::setSeedRand()
{
	srand((unsigned)time(NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////