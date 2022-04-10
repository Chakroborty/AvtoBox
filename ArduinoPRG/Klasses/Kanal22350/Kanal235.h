// ---------------------------------------------------------------------------

#ifndef Kanal235H
#define Kanal235H
//#include "HMC700.h"
 struct ADRDev
	{
		unsigned int Pres_Att1;
		unsigned int Pres_Att2;
		unsigned int Pres_Att3;
		unsigned int Pch2_Att4;
		unsigned int Pres_Band_LNA;
		unsigned int Pres_Fil;
		unsigned int Pch1_Sw;
		unsigned int Pch2_Sw;
		unsigned int Pres_RF;
		unsigned int Pres_Out1;
		unsigned int Pres_Out2;
		unsigned int Pch1_RF;
		unsigned int Pch1_Out;
		unsigned int Pch1_LO;
		unsigned int Pch2_RF;
		unsigned int Pch2_Out;
		unsigned int Pch2_LO;
	};
    	struct UPRLNA
	{
		int UPR;
		int RNG;
	};

// ---------------------------------------------------------------------------

class KanalRR {
public:
	KanalRR(int Mod_kanalNum, int Blok_kanalNum, double Polosa);
	~KanalRR();
	void WriteFregIN(double freqCR, int Kanal,int PRNS);
	// ********************************************************************************


	int DIAPAZON[2][13];

	UPRLNA LNAMATRIX[2][2];
	int PC2INMATRIX[2][2];
	int i;
	int LoadKL(int sw);
	// ********************************************************************************
	//HMC700 *GET1;
	//HMC700 *GET2;
	// ********************************************************************************
	int KanalNum_B_Blok;
	int KanalNum_B_Mod;//0-Канал1  1-Канал2
	// ********************************************************************************
	double FrGet2;
	double FregIN;
	double FPCH1;
	double FrGet1;
	// ********************************************************************************
	int PC1_Kluch;
	int PC2_Kluch;
	int PRES;
	int Pres_UPR_Kluch;
	int AMP_POn_Kluch;
	bool AmpSET;
	int LNAD;
    int LNA;
	int PCH3035;
	int CTRLIN;
	/****************************************************************************/
	//int AMP_SW1_Kluch;
	//int AMP_SW2_Kluch;
	//int AMP_SW3_Kluch;
	//int AMP_SW3_Bolshe105;
	// ********************************************************************************
	void AmplifSET(int Amplif);
	void PRESELSET(int PRES);
	void PERENOS(int PRES);
	void PC2INSET(int PC);
	void ATT1_SET(double DB);
	void ATT2_SET(double DB);
	void ATT3_SET(double DB);
	void ATT4_SET(double DB);

	int LoadATT(int div);

	unsigned long LoadGET1H();
	unsigned long LoadGET2H();

	unsigned long LoadGET1(int Reg);
	unsigned long LoadGET2(int Reg);
	// ********************************************************************************
    double FreqFout();
	ADRDev NKanal[4];

protected:

	double Freal;
	int ATT_pervi;
	int ATT_vtoroi;
	int Amp_Att1;
	int Amp_Att2;
	int Amp_Att3;
	int Pch2_Att4;

	// ********************************************************************************
private:
	double fregCR;
	double freqPC1;
	// double FrGet1;
	double Fsint2;

	double Fpc1;
	double FsigPC1;
	double FsigPC2;
	double PolosaPC2;

	// ********************************************************************************
	// enum AdresModul {
//
		// Modul1 = 0,//0x0,
		// Modul2 = 0x8<<28,//0x1 << 28,
		// Modul3 = 0x4<<28,//0x2 << 28,
		// Modul4 = 0xC<<28,//0x3 << 28,
		// Modul5 = 0x2<<28,//0x4 << 28,
		// Modul6 = 0xA<<28,//0x5 << 28,
		// Modul7 = 0x6<<28,//0x5 << 28,
		// Modul8 = 0xE<<28,
		// Obsh = 0xD << 28

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

	//};
};

#endif
