// ---------------------------------------------------------------------------
#include "HMC830.h"
#include "LMX2594.h"
#include "MUXM15.h"
#include "MUXM20.h"
#include "MHMC394.h"
#include "FCHPERENOS.h"
#ifndef MFC1RRH
#define MFC1RRH

// ---------------------------------------------------------------------------
struct USTRMFC1RR
{
	unsigned int F394;
	unsigned int S15p;
	unsigned int S20p;
	unsigned int RSV;//Sint1_refsw UPR2
	unsigned int PDP;//Sint1_pdp UPR1
	unsigned int FMC830;//
	unsigned int SMX2594;//
	unsigned int I2CRSF;
	unsigned int I2CWIF;
	unsigned int I2CRIF;
	unsigned int I2CRR;
};

struct FRRDiap
{   double DFv;
	int DNSys;
};
/*F	Внутренняя частота синтезатора
M	Петлевой делитель UXM15P
K	Полярность фазового детектора (1-переключение на инверсную петлю)
OUT	Выходной делитель синтезатора LMX2594
N	N-делитель синтезатора LMX2594
CAP1	код CAP
VCO	Номер ядра VCO (1-7)
FOUT	Выходная частота синтезатора*/
struct FRRST 
{
	double F;
	double FVCO;
	int M;//Петлевой делитель UXM15P
	int K;//Полярность фазового детектора (1-переключение на инверсную петлю)
	int OUTM;//Выходной делитель синтезатора LMX2594
	int N;//N-делитель синтезатора LMX2594
	int CAP;//код CAP
	int VCO;//Номер ядра VCO (1-7)
};
// ---------------------------------------------------------------------------
class MMFC1RR
{
public:
     MMFC1RR(int FIN);
	~MMFC1RR();
	int AdrMod;
	double Fget1,F830;
	HMC394 *MXHMC394;
	UXM20 *MXUXM20;
	UXM15 *MXUXM15;
	FCHP *BFCHP;
	int N394; // Делитель Упр. перед Mix2
	int UXD15;			//Sint1_uxm15p
	int UXD20;			//Sint1_uxd20p
	int L;//L-бит включения авто-калибровки VCO.«1» - avtocal enable, «0» - avtocal disable
	int U;//U-бит направления авто-калибровки.«1»-up correction,«0» - down correction.
//-------------------------------------------------------------------------------------------
FRRDiap Polosa830[13];
FRRST   PLAN[268];
FRRST   POINT;
	int UPR2;		//Sint1_refsw UPR2
	int UPR1;		//Sint1_pdp UPR1
USTRMFC1RR DEVFC1R[3];
//-------------------------------------------------------------------------------------------
void SetAUTOCOR(int SL,int SU);
void SetUXM15(int div);
void SetUXD20(int div);
//-------------------------------------------------------------------------------------------

	int Cp; // Переключатель CP
	int NumDapazon;//Номер диапазона
	int Diapazon830;//Номер диапазона HMC830

	long SintLOAD_L(int dev,int Poz);
	long SintLOAD_H(int dev);
	int Kluch(int Num);
//------------------------------------------------------------------------------------------
	long SintLOAD_LMXLCR(int Poz);
	long SintLOAD_LFCCR(int Poz);
	int KluchM(int Num);
//------------------------------------------------------------------------------------------
	int pol2m,Div,DivADF,Pol1,Pol2,ADPOL;

	double Fz;//частота модуляции (HMC830)
	double Fop;// Частота опорная 5000+Fz
    void Set394(int div);
	double Initfreq(double Freq,int K1,int K2,double  NDel,int Ocn,int AR,int AN);
	double  SetFreq(double Fg4159,double fget,int Fas1,int Log);
	void AdrSet(int OBSH);
	HMC830 *Sint1_HMC830;
    LMX2594 *Sint1_LMX2594;

private:

	  	enum DIV394
	{
		OFF = 0,
		D2 = 0x8,
		D3 = 0x4,
		D4 = 0xC,
		D5 = 0x2,
		D6 = 0xA,
		D7 = 0x6,
		D8 = 0xE,
		D9 = 0x1,
		D10 = 0x9,
		D11 = 0x5

	};

	enum Adress
	{
		OBSH = 0xD<<28,
		MFC1 = 0x7<<28
	};

	enum AdrDev
	{
		Kontr_I2C = 0x1,
		Perekl = 0x4, // 875
		Sint = 0xB,
		Kontrol = 0xE,
		PLL1 = 0x8,//  ADF4159
		PLL2 = 0x7,//   HMC830

	};

};
#endif
