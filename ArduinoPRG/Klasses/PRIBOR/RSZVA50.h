#ifndef RSZVA50H
#define RSZVA50H
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
class PanZVA50 {
public:
	PanZVA50(int Adr, char* Ip);
	~PanZVA50();
	char* PriborLoad();
	void GPIB_Set(AnsiString Adr, AnsiString Ip);

	long AnSpanSet(double Fset, double SP, double BW, double RL);
	char* GetGPIB();

	int Lan_GPIB;
	void IP_Set(AnsiString Ip);
	char* GetIPlok();

	long MkrPeak(int n);

	long MkDelta(double Del);

	long SetMarker(bool Del, int Delta, bool Pik, int Count);
	double FMark();
	char* Result(int n);
	AnsiString Zapt(AnsiString str);
	char* CHPWRBW(double Chnl);
	void DataRet(double *Data, double *Freq, int point);
protected:
	int Control(int K, int Pred, int& Com);

	char* GPIB;
	char ipAdres[100];
	char ipLok[100];
	int Gadr;
	AnsiString Slovo;
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
	int DELTA;
	bool AVG;

	double Fmark;
};
#endif /* #ifndef PribH */
