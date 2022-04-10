#ifndef AgilentFFH
#define AgilentFFH
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
class AnalizFFox
{
	public:
		AnalizFFox(int Adr, char* Ip);
		~AnalizFFox();
		char* PriborLoad();
		char* Comand(AnsiString Com,int RET);
		void GPIB_Set(AnsiString Adr, AnsiString Ip);
		void IP_Set(AnsiString Ip);
		void Reset(void);
		long AnSpanSet(float Fset, double SP, double BW, double RL);
		char* GetGPIB();
		char* GetIPlok();
		long DataRet(double *Data, double *Freq, int point);
		long MkrPeak(int n);
		void fieldfoxtest( int Meas,double *Data,long Number_Points_ff, long Measurement_avg_ff, long Background_avg_ff, double Start_Fq_ff, double Stop_Fq_ff);
        void Wite(int Msec);
		long MkDelta(int num,bool Enabl,double Del);
		ViReal32 adTraceArray[32768];
		long SetMarker(bool Del, int Delta, bool Pik, int Count);
		double FMark();
		double Sens(double Lin,double Fin, double SP, double BW,double Ofs);
		char* Result(int n);
		AnsiString Zapt(AnsiString str);
		AnsiString Slovo;
		char* CHPWRBW(double Chnl);
		long lOpc;
		ViSession FieldFox;
	protected:
		int Control(int K, int Pred, int& Com);

		char GPIB[10];
		char ipAdres[100];
		char ipLok[100];
		int Gadr;
		int Lan_GPIB;

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

		char saSetup[200];
		ViChar cResult[1024];
		unsigned long lBytesRetrieved;
		char sBuffer[80];
		char dummyvar;
		long lNumberPoints;
		long lNumberBytes;
		FILE *fTraceFile;


		int DELTA;
		bool AVG;

		double Fmark;
};
#endif /* #ifndef PribH */
