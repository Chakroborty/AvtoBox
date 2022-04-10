// ---------------------------------------------------------------------------

#ifndef StendPRH
#define StendPRH
#include <stdio.h>
#include <math.h>
#include <string.h>

/* Анализатор цепей */
#include "E5071BNetwAnalizer.h"
#include "RSZVA50.h"
/* Коммутатор */
#include "Switch34980A.h"
/* Генераторы */
#include "HPE44XXB.h"
#include "AGN5183A.h"
#include "SMU200.h"
#include "KLSMF100A.h"
/* Анализатор спектра */
#include "Agilent8560.h"
#include "Agilent9030.h"
#include "Keysigth9020.h"
#include "RSFSU50.h"
#include "RSFSL18.h"
#include "AgilentE4407.h"

/* Источник питания */
#include "MP_N6702A.h"
/*Блок*/
//#include "BLRPU16.h"
#include "VirtBlock.h"
/*=====  End of   ======*/
//#include "EBOARD830.h"
#include "visa.h"
//#include "UsbDeviceManager.h"
// ---------------------------------------------------------------------------

class StendPRibor {
public:
	//StendPRibor(char* Ip, IBLock* Block);
	StendPRibor(char* Ip);
	~StendPRibor();
	/*Анализатор цепей*/
	E5071B *Vstende5071;
	PanZVA50 * RS_PanZVA50;
	/*Коммутатор*/
  	Switch34980 *KOM34980;
	/* Генераторы */

	HPE4426B *AgE44XX;
	HPE4426B *AE4426;
	HPE4426B *Ag4425;
	SMU200GEN *SMU200;
	N5183A *NN5183;
	SMF100A *RSSMF100A;
	/* Анализатор спектра */

	Analiz8560 *An8560;
	Analiz9030 *An9030;
	FSL18 *RS_FSL;
	FSU50 *RS_FSUP50;
    AnalizE4407 *AnE4407;
    Analiz9020 *Key9020;
	/* Источник питания */

	N6702A *MP_N6702A;
	/*Блок*/
	  //	HMC830BR* BR830;
	//BlRPU16 *VstendeBlRPU16;//TRpu16   *VstendeBlRPU16;
	IBLock  *StBlock;
	/*=====  End of   ======*/

	double CTbl[4];

	void SetAnaliz(double F);
	double Set5071_Perenos(double Fnastr, double Fpc, bool InvSp, double Pow);
	void Set5071_NoPerenos(double Fstr, double Fstop, double Pow, int Var);
	void Pribor5071_IzmLoad();
	void Pribor5071_MarkLoad();
	void Pribor5071_LimitLoad();
	void Stend_LimitLoad(double PowGen, double RefL, double RefL10M,
		double Span, double RBW,double VFOFC);
	void Stend_LimitRet(double &Pow, double &Ref, double &Ref10M, double &Sp,
		double &RB);
	void DataRet(double *Data, double *Freq, int point);
	void SendBlokALL(void);

	float RazborStr(int poz, char* str);
	void Stend_PrAdress(int An, int Get1, int Get2, int ANLAN, AnsiString AdrAN,
		int GENLAN, AnsiString AdrGEN, int GEN1LAN, AnsiString AdrGEN1,
		int GEN2LAN, AnsiString AdrGEN2,
		int SWLAN, AnsiString AdrSW,
        int PANLAN, AnsiString AdrPan, int BPLAN, AnsiString AdrBP,
		AnsiString Ip);
	float MarkerZapros(int NumTRASE, int NumMARK);
	float CHenalPOW(double BW, double Centr, int Kanal);
	double Friq(void);
	void SETGet1(double Friq1);
	void SETGet2(double Friq2);
	void GetSet();
	void SelektKanal(int Kanal);
/************************************************************************************************/

	void ALLAnInit();
	void ALLAnSpanSet(double FrAn,double Span,double RBW,double RefL);
	double ALLAnPeak(int Num);
	double ALLAnSENS(double Fan,double Lan);
	void ALLAnDELTA(double Fan,double Lan);
	double ALLAnRESULT(void);

/************************************************************************************************/
	int analiz, get1,get2, i,TCom,get;
	bool jgut;
	double GeinAnGen16(double FrGen,double FrAn,int Kanal);
/**************************************************************************************************/
   bool ChekCon();
   double GeinAnGen(double FrGen,double FrAn, int Kanal);
   double GeinAnGen(double FrGen,double FrAn,int ATT1,int ATT2,int PRES,int Kanal,int PARAM);
   double SIP1(double Lstart, double Lmax, double Fin, double Fout, int Kanal);
   double Sens(double Lin, double Lan, double Fin,double Fan, int Kanal);
   double PowAn(double FrAn,double RefL, int Kanal);

protected:
	ViSession defaultRM, vi; // Declares a variable of type ViSession
	ViByte buffer[256]; // for instrument communication
	char rezult[256];
	ViStatus status;
	ViUInt32 retCnt;

	double FrGen;
	double PowGen, Meas;
	double FrAn;
	double RefL;
	double RBW;
	double Span;
    double Fofs;
	double RefL10M;

};
#endif
