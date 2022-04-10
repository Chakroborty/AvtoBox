// ---------------------------------------------------------------------------
#include "KanalDG10.h"
#ifndef Tri3DG10H
#define Tri3DG10H
#include "UsbDeviceManager.h"

// ---------------------------------------------------------------------------
class Tri3DG10 {
public:
	Tri3DG10(int ADR);
	~Tri3DG10();

	KanalDG10 *MKanalDG10;
	bool Modul_All;
	long BL_NumModul;

	enum AdresModul {                  //Адрес_3ДЖ10

		Modul1 = 0x0,
		Modul2 = 0x1 << 28,
		Modul3 = 0x2 << 28,
		Modul4 = 0x3 << 28,
		Modul5 = 0x4 << 28,
		Modul6 = 0x5 << 28,
		MFCl = 0xE << 28,
		MFC2 = 0xF << 28,
		Obsh = 0xD << 28,
		SH_M2 = 0x5
	};

	
	

	enum KLUCH_K1 {
		HMC939K1 = 0x4000000,
		HMC274K1 = 0x4010000,
		SWK1 = 0x4020000
	};

	enum KLUCH_K2 {
		HMC939 = 0x4100000, 
		HMC274 = 0x4110000, 
		SW = 0x4120000 
	};

	enum PRESOUT
	{
	D3_6 =	0,		//0	0	0	Диапазон 3-6 ГГц – вх1
	D6_10= 0X1,		//0	0	1	Диапазон 6-10 ГГц – вх2
	D10_12= 0X2,	//0	1	0	Диапазон 10-12 ГГц – вх3
	D12_16= 0X3,	//0	1	1	Диапазон 12-16 ГГц – вх4
	D16_18= 0x4 	//1	0	0	Диапазон 16-18 ГГц – вх5
	};//Упр1.3(3)	Упр1.2(4)	Упр1.1(5)	
	enum PRES
	{//Упр1(8)	Упр2.1(4)	Упр2.2(6)
		PR3_4 = 0X7,//1	1	1	Диапазон 3-4 ГГц – вх1	
		PR4_6 = 0X5,//1	0	1	Диапазон 4-6 ГГц – вх1
		PR6_8 = 0X6,//1	1	0	Диапазон 6-8 ГГц – вх2
		PR8_10 = 0X4,//1	0	0	Диапазон 8-10 ГГц – вх2
		PR10_12 = 0X3,//0	1	1	Диапазон 10-12 ГГц – вх2
		PR12_14 = 0X1,//0	0	1	Диапазон 12-14 ГГц – вх2
		PR14_16 = 0X2,//0	1	0	Диапазон 14-16 ГГц – вх2
		PR16_18 = 0 //0	0	0	Диапазон 16-18 ГГц – вх2
		

	};


	int LoadKL_K1(int tip);

	
	int LoadATT_K1(int tip);

	
	void Set_ATT1_K1(int dB);
	void Set_ATT2_K1(int dB);
	DWORD LoadGET1_L(int REG);
	DWORD LoadGET1_H(void);
	DWORD LoadGET2_L(int REG);
	DWORD LoadGET2_H(void);

	
	void Tri3DG10::SetFriq(int Mod, int Kanal, double Fin, int DB1,int DB2);

private:

};
#endif
