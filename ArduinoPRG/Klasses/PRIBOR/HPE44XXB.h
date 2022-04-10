#ifndef HPE44XXBH
#define HPE44XXBH
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
class HPE4426B {
public:
	HPE4426B(int Adr, char* Ip, int LAN);
	~HPE4426B();
	char* PriborLoad();
	void GPIB_Set(AnsiString Adr, AnsiString Ip);
	void IP_Set(AnsiString Ip);
	long GenSet(double Fset, double Pow, bool OutOn);
	char* GetGPIB();
	char* GetIPlok();
	AnsiString  Zapt(AnsiString str);
	int Lan_GPIB;
	long GenOUTONOFF( bool OutOn);
	protected:

	void Control(int K, int Pred, int& Com);
	void ControlF(double K, double& Com);
	char GPIB[10];

	char ipAdres[100];
	char ipLok[100];
	int Gadr;

	double Fmin;

	double Fmax;

	double Freq;

	double Pow;

	bool PowStat;

	ViSession defaultRM, vi; // Declares a variable of type ViSession
	ViByte buffer[256]; // for instrument communication
	char rezult[256];
	ViStatus status;
	ViUInt32 retCnt;
};
#endif /* #ifndef SwitchH */
