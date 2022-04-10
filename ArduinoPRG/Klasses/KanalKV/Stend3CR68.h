// ---------------------------------------------------------------------------

#ifndef Stend3CR68H
#define Stend3CR68H
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "E5071BNetwAnalizer.h"
#include "Agilent8560.h"
#include "Agilent9030.h"
#include "RSFSU50.h"
#include "RSZVA50.h"
#include "HPE44XXB.h"
#include "MP_N6702A.h"
#include "Switch34980A.h"
#include "BL3Cr6.h"
#include "SMU200.h"
#include "visa.h"
#include "UsbDeviceManager.h"
// ---------------------------------------------------------------------------

class StendKV68
{ public:
	StendKV68(bool Blok3CR6,char* Ip);
	~StendKV68();

	E5071B *Vstende5071;
	Switch34980 *KOM34980;
	HPE4426B *AgE44XX;
	HPE4426B *AE4426;
	HPE4426B *Ag4425;

	Analiz8560 *An8560;
	Analiz9030 *An9030;
	PanZVA50 * RS_PanZVA50;
	FSU50 *RS_FSUP50;
	SMU200GEN *SMU200;
	N6702A *MP_N6702A;

/*============================= Конец Приборы  =============================*/
/*============================================================================
=                          			 Блок 3Чр68                              =
 ============================================================================*/
Bl3CR6   *VstendeBl3CR6;
void Sint_SetBLOK68(double Fnastr);
/*******************************************************/
void ATTUPC_SetBLOK68(double Db);
/******************************************************/
void AMPLUPC_SetBLOK68(int Ampl);
/******************************************************/
void  VX_SetBLOK68(bool Priem);
void  ATTPres_SetBLOK68(int Db);
void  FVC_SetBLOK68(int Fset);
void  PC_SetBLOK68(bool PC40);
/*******************************************************/


// UsbDeviceManager *DeviceManager;
// UKV3CR6I8* DeviceUSB;
// void __fastcall DeviceConnected(UKV3CR6I8 *newDevice);
// void __fastcall DeviceRemoved(UKV3CR6I8 *oldDevice);
/*================================  Конец Блок 3Чр68  ==========================*/



	void SelektKanalCr68(int Kanal);
    void  SetAnaliz(double F);
	void Set5071_Perenos(double StartIN, double StopIN, double Fnastr, double Fpc, double Pow);
	double Set5071_Perenos28(double Fnastr, double Fpc, bool InvSp, double Pow);
	double Set5071_PerenosBW(double Fnastr, double Fpc,bool InvSp, double Pow,double Pos,double Span);
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
	void Stend_PrAdress(int An, int Gen,int ANLAN, AnsiString AdrAN,
		int GENLAN, AnsiString AdrGEN,
		int GEN1LAN,AnsiString AdrGEN1,int GEN2LAN, AnsiString AdrGEN2,
		int SWLAN, AnsiString AdrSW,
		int PANLAN,	AnsiString AdrPan,
		int BPLAN,	AnsiString AdrBP,  AnsiString Ip);
	float MarkerZapros(int NumTRASE, int NumMARK);
	double IP1(double Lstart, double Lmax, double Fin, double Fout, int Kanal,int Com);
	double Sens(double Lin, double Lan, double Fin, int Kanal,int Com);
	double SensATT(double Lin, double Lan, double Fin, int Kanal);
	float CHenalPOW(double BW, double Centr, int Kanal);
	double GeinAnGen(double FrGen, int ATT, int ATT1, int Kanal);
	double GeinAnGen(double FrGen,bool Com,int ATT,int ATT1, int Kanal,bool Shirokaia,int Comm);
	double GeinPanoram(double FrGen,int ATT, int Kanal,int PC,int Com);
	double PowAn(double FrAn, int Kanal);
	double PowAn10(double FrAn, int Kanal);
	double Friq(void);
	void GetSet();
	void SelektKanal(int Kanal);
	int analiz, get, i;
	bool jgut;
	int TCom,TKanal;

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
