//---------------------------------------------------------------------------

#ifndef SMU200H
#define SMU200H
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
class SMU200GEN
{
	public:
		SMU200GEN(int Adr, char* Ip);
		~SMU200GEN();
		char* PriborLoad();
		void GPIB_Set(AnsiString Adr, AnsiString Ip);
void IP_Set(AnsiString Ip);
		long GenSetA(double Fset, double Pow, bool OutOn);
		long GenSetB(double Fset, double Pow, bool OutOn);
		char* GetGPIB();
char* GetIPlok();
		AnsiString  Zapt(AnsiString str);
		int Lan_GPIB;
	protected:


		void Control(int K, int Pred, int& Com);
		void ControlFA(double K, double& Com);
		void ControlFB(double K, double& Com);
		char GPIB[10];

		char ipAdres[100];
		char ipLok[100];
		int Gadr;

		double AFmin;
		double AFmax;

		double BFmin;
		double BFmax;

		double AFreq;
		double BFreq;


		double Pow;

		bool PowStat;

		ViSession defaultRM, vi; // Declares a variable of type ViSession
		ViByte buffer[256]; // for instrument communication
		char rezult[256];
		ViStatus status;
		ViUInt32 retCnt;
};





//---------------------------------------------------------------------------
#endif
