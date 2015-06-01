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



#ifndef FSTREAM_H
#define FSTREAM_H

#include <fstream>

#endif





#ifndef SA_C
#define SA_C

class SimulatedAnnealing
{

/*
 *	Data members
 */

private:
	IplImage *imageCCD;
	IplImage *imageCurrent;
	IplImage *imageIdeal;
	IplImage *imageDesiredCCD;
	IplImage *imageDesiredCurrent;

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
	double duration;

private:
	MSG message;

private:
	std::ofstream *fileLog;
	std::ofstream *fileProcess;
	std::ofstream *fileResult;



/*
 *	Constructor
 */

public:
	SimulatedAnnealing(SLM *slm, CCD *ccd, ImageProcessing *IP, std::string name = "SA_File_Log", std::string path = "Log");

private:
	void openFileLog(std::string name = "SA_File_Log", std::string path = "Log");

	void connectHardware(SLM *slm, CCD *ccd);

	void includeIP(ImageProcessing *IP);

	void createImageCCD();

	void setRangePM();

	void setSeedRand();



/*
 *	Interface
 */

public:
	void createWindow();

public:
	void destroyWindow();

public:
	void openFileSA(std::string nameProcess = "SA_File_Process", std::string nameResult = "SA_File_Result", std::string path = "Output");

public:
	void closeFileSA();

public:
	void setModeIdeal(int margin, std::string name, std::string path = "LP");

public:
	void createImageSA();

public:
	void updateImageCurrent();

public:
	void updateImageDesired();

public:
	void showImageCCD();

public:
	void showImageCurrent();

public:
	void saveImageIdeal(std::string name = "SA_Image_Ideal", std::string path = "Output");

public:
	void saveImageDesired(std::string nameCCD = "CCD_Image_Desired", std::string nameSA = "SA_Image_Desired", std::string path = "Output");

public:
	void setPhaseInitial(std::string name, std::string path = "Phase");

public:
	void setParameterSA(double Ts, double Tt, double c, int cyc);

public:
	void runSA(int height, int width);

public:
	void snapShot();

public:
	void saveImageResult(std::string nameSLM = "SLM_Image_Desired", std::string nameCCD = "CCD_Image_Desired",
		std::string nameSA = "SA_Image_Desired", std::string nameIdeal = "SA_Image_Ideal", std::string path = "Output");

public:
	void saveFileResult();

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

	void createImageCurrent();

	void createImageDesired();

private:
	void runEventProcessing();



/*
 *	Destructor
 */

public:
	~SimulatedAnnealing();

private:
	void releaseImage();

	void closeFileLog();
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////