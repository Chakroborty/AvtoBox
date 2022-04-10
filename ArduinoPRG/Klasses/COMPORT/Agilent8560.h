#ifndef Agilent8560H
#define Agilent8560H
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>

class Analiz8560 {
public:
	Analiz8560(int Adr, char* Ip);
	~Analiz8560();
	char* PriborLoad();
	void GPIB_Set(AnsiString Adr, AnsiString Ip);
	long AVG(int D);
	long AnSpanSet(double Fset, double SP, double BW, double RL);
	char* GetGPIB();
    int Pinitial();
	long MkrPeak();

	long MkDelta(bool Enabl, double Del);

	long SetMarker(bool Del, int Delta, bool Pik, int Count);
	double FMark();
	char* Result();
	AnsiString Zapt(AnsiString str);
	char* CHPWRBW(double Chnl);

	int Lan_GPIB;
	double Fmark, Rmark;
protected:
	void Control(int K, int Pred, int& Com);

	char* GPIB;
	char ipAdres[100];
	int Gadr;

	double Fmin;
	double Fmax;
	double CentrF;
	double RL;
	double Span;
	double RBW;
	int Coun;
	ViSession defaultRM, vi; // Declares a variable of type ViSession
	ViByte buffer[256]; // for instrument communication
	char rezult[256];
	ViStatus status;
	ViUInt32 retCnt;
	/**
	 * <url>element://model:project::Exsampl/design:node:::v5xdh04ocnpjfllyr_n:0w1acwyuhaj5cv2tl_n:mrb4r99gwrhiuu39j_n</url>
	 */
	int DELTA;
	//bool AVG;


};
#endif /* #ifndef PribH */
