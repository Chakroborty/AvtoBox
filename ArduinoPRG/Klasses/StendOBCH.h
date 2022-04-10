// ---------------------------------------------------------------------------

#ifndef StendOBCHH
#define StendOBCHH
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "E5071BNetwAnalizer.h"
#include "Agilent8560.h"
#include "Agilent9030.h"
#include "RSFSU50.h"
#include "HPE44XXB.h"
#include "Switch34980A.h"
#include "BL3Cr6.h"
#include "SMU200.h"
#include "visa.h"
#include "UsbDeviceManager.h"
// ---------------------------------------------------------------------------
class BL3PX1;

/**
 * <url>element://model:project::Test3PX1/design:node:::gt5tv1m0ylg_n:tejjyk0ckko_n</url>
 */
class Stend3CR5 {
public:
	Stend3CR5(bool BL3CR6,char* Ip);
	~Stend3CR5();

	E5071B *Vstende5071;
	Bl3CR6 *VstendeBl3CR6;
	Switch34980 *KOM34980;
	HPE4426B *AgE44XX;
	HPE4426B *AE4426;
	HPE4426B *Ag4425;

	Analiz8560 *An8560;
	Analiz9030 *An9030;
	FSU50 *RS_FSUP50;
	SMU200GEN *SMU200;

	double Set5071_Perenos(double Fnastr, double Fpc, bool InvSp, double Pow,double Span);
	void Set5071_NoPerenos(double Fstr, double Fstop, double Pow, int Var);
	void Pribor5071_IzmLoad();
	void Pribor5071_MarkLoad();
	void Pribor5071_LimitLoad();
	void Stend_LimitLoad(double PowGen, double RefL, double RefL10M,
		double Span, double RBW);
	void Stend_LimitRet(double &Pow, double &Ref, double &Ref10M, double &Sp,
		double &RB);
	void DataRet(double *Data, double *Freq, int point);
	void SendBlokALL(void);
	bool ChekCon(double FrGen, int Kanal);
	float RazborStr(int poz, char* str);
	void Stend_PrAdress(int An, int Gen, AnsiString AdrAN, AnsiString AdrGEN,
		AnsiString AdrGEN1, AnsiString AdrGEN2, AnsiString AdrSW,
		AnsiString AdrPan, AnsiString AdrDUalGen, AnsiString Ip);
	float MarkerZapros(int NumTRASE, int NumMARK);
	double IP1(double Lstart, double Lmax, double Fin, double Fout, int Kanal);
	double Sens(double Lin, double Lan, double Fin, int Kanal);
	double SensATT(double Lin, double Lan, double Fin, int Kanal);
	float CHenalPOW(double BW, double Centr, int Kanal);
	double GeinAnGen(double FrGen, int ATT, int ATT1, int Kanal);
	double GeinPanoram(double FrGen,int ATT, int Kanal,int PC,int OSNAST);
	double PowAn(double FrAn, int Kanal);
	double PowAn10(double FrAn, int Kanal);
	double Friq(void);

	int analiz, get, i;
	bool jgut;

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
	double RefL10M;
	double Rez;
};
#endif
