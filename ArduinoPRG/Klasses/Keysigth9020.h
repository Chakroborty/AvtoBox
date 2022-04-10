#ifndef KEYSIGTH9020H
#define KEYSIGTH9020H
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
class Analiz9020
{
	public:
		Analiz9020(int Adr, char* Ip, int LAN);
		~Analiz9020();
		char* PriborLoad();
		void GPIB_Set(AnsiString Adr, AnsiString Ip);
		void IP_Set(AnsiString Ip);
		long AnSpanSet(double Fset, double SP, double BW, double RL);
		char* GetGPIB();
		char* GetIPlok();
		void Wite(int Msec);
        void Reset();
		long MkrPeak(int n);
		long MarkerCent(int N); //установка маркера в центр
		long MkDelta(int num,bool Enabl,double Del);
		void DataRet(double *Data, double *Freq, int point);
		long SetMarker(bool Del, int Delta, bool Pik, int Count);
		long Spurs(int Line);
		double FMark();
		double Spur[50];
		long SavPath(AnsiString MPath);
		long Screen(AnsiString FName);
		void DispLINE(int LEV,int ENbl);
		double Sens(double Lin,double Fin, double SP, double BW,double Ofs);
		char* Result(int n);
		AnsiString Zapt(AnsiString str);
		char* CHPWRBW(double Chnl);
		int Lan_GPIB;
		double PeakF,PeakP;
        double CentrF;
	protected:
		int Control(int K, int Pred, int& Com);
		double RazborStr (int poz, char* str);
		char GPIB[10];
		char ipAdres[100];
		char ipLok[100];
		int Gadr;


		double Fmin;
		double Fmax;

		double RL;
		double Span;
		double RBW;
		int Coun;
		ViSession defaultRM, vi; // Declares a variable of type ViSession
		ViByte buffer[32768]; // for instrument communication
		char rezult[256];
		ViStatus status;
		ViUInt32 retCnt;
		AnsiString DataPath;
		unsigned long byteret;
		long lNumberBytes;
    	long lNumberPoints;
		int DELTA;
		bool AVG;
        long lOpc;
		double Fmark,Pmark;
};
#endif /* #ifndef PribH */
