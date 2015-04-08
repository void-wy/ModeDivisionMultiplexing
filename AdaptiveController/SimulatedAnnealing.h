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
	double correlation;
	int DRN;
	int PRN;
	int TN;



/*
 *	Constructor
 */

public:
	SimulatedAnnealing(SLM *slmSA/*, CCD *ccdSA*/, ImageProcessing *IP_SA);

private:
	void connectHardware(SLM *slmSA/*, CCD *ccdSA*/);

	void includeIP(ImageProcessing *IP_SA);

	void getImageCurrent();

	void setRangePM();

	void createWindow();

	void setSeedRand();



/*
 *	Interface
 */

public:
	void setModeIdeal(char *name, int margin);

public:
	void setParameterSA(double TsSA, double TtSA, double cSA, int cycSA);

public:
	void run(int height, int width);

public:
	double getCorrelation();



/*
 *	Utility
 */

private:
	void setRangeSpot(int margin);

	void createImageIdeal(char *name, int margin);

	void showImage();



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