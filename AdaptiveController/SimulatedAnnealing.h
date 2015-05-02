///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SLM_H
#define SLM_H

#include "SLM.H"

#endif



#ifndef CCD_H
#define CCD_H

#include "CCD.H"

#endif



#ifndef DIP_H
#define DIP_H

#include "ImageProcessing.h"

#endif



#ifndef	TIME_H
#define	TIME_H

#include <time.h>

#endif



#ifndef	STRING_H
#define	STRING_H

#include <string>

#endif





#ifndef SA_C
#define SA_C

class SimulatedAnnealing
{

/*
 *	Data members
 */

private:
	IplImage *imageCurrent;
	IplImage *imageIdeal;

private:
	SLM *slm;
	CCD *ccd;

private:
	ImageProcessing *IP;

private:
	int heightPM;
	int widthPM;

private:
	int leftSpot;
	int bottomSpot;
	int heightSpot;
	int widthSpot;

private:
	double Ts;
	double Tt;
	double c;
	int cyc;
	double BoltzmannConstant;

private:
	int DRN;
	int PRN;
	int TN;
	double correlationBest;

private:
	clock_t start;
	clock_t finish;
	double duration;



/*
 *	Constructor
 */

public:
	SimulatedAnnealing(SLM *slm, CCD *ccd, ImageProcessing *IP);

private:
	void connectHardware(SLM *slm, CCD *ccd);

	void includeIP(ImageProcessing *IP);

	void getImageCurrent();

	void setRangePM();

	void createWindow();

	void setSeedRand();



/*
 *	Interface
 */

public:
	void setModeIdeal(int margin, std::string name, std::string path = "LP");

public:
	void setPhaseInitial(std::string name, std::string path = "Phase");

public:
	void setParameterSA(double Ts, double Tt, double c, int cyc);

public:
	void run(int height, int width);

public:
	void noiseSolution(int noiseMaxValue);

public:
	double getCorrelation();

public:
	void saveResult(std::string nameSLM = "SLM_Image_Desired", std::string nameCCD = "CCD_Image_Desired",
		std::string nameSA = "SimulatedAnnealing", std::string path = "Output");

public:
	void startClock();

public:
	double finishClock();



/*
 *	Utility
 */

private:
	void setRangeSpot(int margin);

	void createImageIdeal(int margin, std::string name, std::string path = "LP");

	void showImageIdeal();



/*
 *	Destructor
 */

public:
	~SimulatedAnnealing();

private:
	void destroyWindow();

	void releaseImage();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////