//---------------------------------------------------------------------------

#ifndef FCHPERENOSH
#define FCHPERENOSH
#include "LMX2594.h"
#include "MUXM15.h"
#include "MUXM20.h"
//---------------------------------------------------------------------------
struct STATE
	{
		double FVCO;
		double FOUT;
		int NPLL;
		int SUM;
		int uxm15p;
		int OUTDIV;
		int VCO;
		int CAP;
	};
//--------------------------------------------------------------------------
class FCHP
{
public:
FCHP();
~FCHP();
int PUXM15;
int PUXM20;
int UPR1;//(CP: op || RC)
int UPR2;//(REF100 ext/int)
int FINE;
int TL;
int TU;
LMX2594 *PLMX2594;
UXM20 *MXUXM20;
UXM15 *MXUXM15;
STATE FNUM[12];
void SETF(int NUM); //  установка ПРЕСЕТ
void SETDF(int DXM15,int POL, int LOOP, int NOUT, int NPLL, int CAP, int VCO);
int SETUMX15(int NUM);
int SETUMX20(int NUM);
void SETFINE(int ZN);
void SETAUTO(int ZL,int ZU);



/*
	dP                                dP
	88                                88
	88        .d8888b. .d8888b. .d888b88
	88        88'  `88 88'  `88 88'  `88
	88        88.  .88 88.  .88 88.  .88
	88888888P `88888P' `88888P8 `88888P8
*/

long LOAD_F(int NUM);
long LoadINITLMX2594(int NUM);

};

#endif
