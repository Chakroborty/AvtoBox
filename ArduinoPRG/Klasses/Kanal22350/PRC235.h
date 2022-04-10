// ---------------------------------------------------------------------------
#include "Kanal235.h"
#ifndef PRC235H
#define PRC235H
struct ADRPRC
	{
		unsigned int Att1;
		unsigned int Att2;
		unsigned int In_SW;
		unsigned int LNA_sw;
		unsigned int Conv_sw;
		unsigned int UsilPCH_sw;
		unsigned int Filtr_sw;
		unsigned int PwrOnUsil_sw;
		unsigned int Pres_Fil_sw;
		unsigned int Control_UI;
		unsigned int Control_T;
	};

// ---------------------------------------------------------------------------
class MPRC {
public:
	MPRC(int ADR);
	~MPRC();

	KanalRR *MKanal;
	bool Modul_All;
	long BL_NumModul;

	enum AdresModulPR {

		Modul1 = 0,//0x0,
		Modul2 = 0x8<<28,//0x1 << 28,
		Modul3 = 0x4<<28,//0x2 << 28,
		Modul4 = 0xC<<28,//0x3 << 28,
		Modul5 = 0x2<<28,//0x4 << 28,
		Modul6 = 0xA<<28,//0x5 << 28,       /* TODO -oPerv -cADR mod : мод7-8 */
		Modul7 = 0x6<<28,//0x5 << 28,
		Modul8 = 0xE<<28,
		MFCl = 0xE << 28,
		MFC2 = 0xF << 28,
		Obsh = 0xD << 28,
		SH_M1 = 0x3
	};

//0111  1110  E	0xE
//0110  0110  6	0x6
//0101  1010  A	0xA
//0100  0010  2	0x2
//0011  1100  C	0xC
//0010  0100  4	0x4
//0001  1000  8	0x8

//1 0					0
//2	1	0001  1000  8	0x8
//3	2	0010  0100  4	0x4
//4	3	0011  1100  C	0xC
//5	4	0100  0010  2	0x2
//6	5	0101  1010  A	0xA
//7	6	0110  0110  6	0x6
//8	7	0111  1110  E	0xE




	int LoadKL(int tip);
	int LoadATT(int tip);


	void Set_ATT1(double dB);
	void Set_ATT2(double dB);
	unsigned long LoadGET1_L(int REG);
	unsigned long LoadGET1_H(void);
	unsigned long LoadGET2_L(int REG);
	unsigned long LoadGET2_H(void);


void SetFriq(int Mod, int Kanal, double Fin, bool Ampl, int DB1,int DB2,int DB3,int DB4,int PARAM);

private:

};
#endif
