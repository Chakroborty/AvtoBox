#ifndef MP_N6702AH
#define MP_N6702AH
#include "visa.h"
//#include "StendUSBGPIB.h"
//#include "USBGPIB.h"

#include <stdio.h>
#include <string.h>
#include <vcl.h>

  class N6702A
{
public:
	N6702A(int Adr, char* Ip,int Mode);
	~N6702A();
   //	ADAPTgpib * AdapterGPIB;
	void GPIB_Set(AnsiString Adr, AnsiString Ip);
    long SET_METER(int Kanal);
	long BP_SET(double Vset, double Cur,int Kanal);
	char* GetGPIB();
	AnsiString  Zapt(AnsiString str);
    int Lan_GPIB;
	void GPIBLAN_Set(bool LG);
	void IP_Set(AnsiString Ip);
	char* PriborLoad();
	double Volt;
	int N6702A::STATUS(int Kanal);
	double Pow,Rez,V1,V2,V3,V4;
	long OPENOUT(bool Swich,bool Normal,int Kanal);
	bool PowStat;
	double MeasureVolt(int Kanal);
	double MeasureAmper(int Kanal);
	int Stat1,Stat2,Stat3,Stat4;
	long Comand(AnsiString Com,char *Rez);
	char* GetIPlok();
	long ResetGroup();
	long SetGroup(int GR, int Kan1, int Kan2);
protected:

	void Control(int K, int Pred, int& Com);
	void ControlV(double K, double& Com);
	char GPIB[10];  //
	char ipAdres[100]; //
	int Gadr;

	char ipLok[100];


	double Vmin;
	double Vmax;



	ViSession defaultRM, vi; // Declares a variable of type ViSession
	ViByte buffer[256]; // for instrument communication
	char rezult[256];
	ViStatus status;
	ViUInt32 retCnt;
	bool USB;
private:



};
#endif /* #ifndef SwitchH */
