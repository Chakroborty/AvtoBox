// ---------------------------------------------------------------------------

#ifndef KanalVKUKVH
#define KanalVKUKVH
#include "HMC700.h"
#include "UsbDeviceManager.h"
// ---------------------------------------------------------------------------
class KanalVKUKV {
public:
	KanalVKUKV(int Mod_kanalNum, int Blok_kanalNum, double Polosa);
	~KanalVKUKV();
	void WriteFregIN(double freqCR, int Kanal);
	
	int LoadKL(int sw);
	// ********************************************************************************
	HMC700 *GET1;
	HMC700 *GET2;
	// ********************************************************************************
	int KanalNum_B_Blok;
	int KanalNum_B_Mod;
	// ********************************************************************************
	double FrGet2;
	double FregIN;
	double FrGet1;
	// ********************************************************************************
	int PC1_Kluch;
	int PC2_Kluch;
	int Pres_UPR_Kluch;
	int AMP_POn_Kluch;
	bool AmpSET;
    int LNA;
	void AmplifSET(bool Amplif);

	int AMP_SW1_Kluch;
	int AMP_SW2_Kluch;
	// int AMP_SW3_Kluch;
	int AMP_SW3_Bolshe105;
	// ********************************************************************************

	void ATT1_SET(double DB);
	
	int LoadATT(int div);
	void ATT2_SET(double DB);
	DWORD LoadGET1H();
	DWORD LoadGET2H();

	DWORD LoadGET1(int Reg);
	DWORD LoadGET2(int Reg);
	// ********************************************************************************
    double FreqFout();
protected:
	void FsMenshe1215(void);
	void FsBolshe1215(void);
	void FsBolshe1830(void);
	void FsSperenosom(void);
	void Obxod175(void);
	void WriteFrPC1(double freqPC1);
	void PC1_2440(void);

	double Freal;
	int ATT_pervi;
	int ATT_vtoroi;
	int Amp_Att1;
	int Amp_Att2;
	int Amp_Att3;
	int Amp_Att4;
	int Pres_Att;
	int Pch1_Att1;
	int Pch1_Att2;

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
	enum AdresModul {

		Modul1 = 0x0,
		Modul2 = 0x1 << 28,
		Modul3 = 0x2 << 28,
		Modul4 = 0x3 << 28,
		Modul5 = 0x4 << 28,
		Modul6 = 0x5 << 28,
		Obsh = 0xD << 28
	};

	enum EFpc1 {
		Pc1_735 = 735,
		Pc1_1035 = 1035,
		Pc1_2440 = 2440,
	};

	enum AdrRegPX2 {
		Ch1_Amp_POn = 0,
		Ch2_Amp_POn = 0x1 << 16,

		Ch1_Amp_Sw2 = 0x2 << 16,
		Ch2_Amp_Sw2 = 0x3 << 16,

		Ch1_Amp_Sw3 = 0x4 << 16,
		Ch2_Amp_Sw3 = 0x5 << 16,

		Ch1_Amp_Sw1 = 0x6 << 16,
		Ch2_Amp_Sw1 = 0x7 << 16,

		Ch1_Pres_UPR = 0x8 << 16,
		Ch2_Pres_UPR = 0x9 << 16,

		Ch1_Pch1_Sw = 0xE << 16,
		Ch2_Pch1_Sw = 0xF << 16,

		Ch1_Pch2_Sw = 0x10 << 16,
		Ch2_Pch2_Sw = 0x11 << 16




	};

	enum TipUstrPX2 {

		TipATT = 0x3 << 24,
		TipPerekl = 0x4 << 24,

		Fc1_Ch1 = 0x7 << 24,
		Fc2_Ch1 = 0x8 << 24,

		Fc1_Ch2 = 0x9 << 24,
		Fc2_Ch2 = 0xA << 24,

		Kontr_Mdul = 0xE << 24,

		Nul_USTR = 0x0
	};

	enum AdrRegATT {
		Ch1_Amp_Att1 = 0,
		Ch1_Amp_Att2 = 0x1<<20,
		Ch1_Amp_Att3 = 0x2<<20,
		Ch1_Amp_Att4 = 0x3<<20,
		Ch2_Amp_Att1 = 0x4<<20,
		Ch2_Amp_Att2 = 0x5<<20,
		Ch2_Amp_Att3 = 0x6<<20,
		Ch2_Amp_Att4 = 0x7<<20,
		Ch1_Pres_Att = 0x8<<20,
		Ch2_Pres_Att = 0x9<<20,
		Ch1_Pch1_Att1 = 0xA<<20,
		Ch1_Pch1_Att2 = 0xB<<20,
		Ch2_Pch1_Att1 = 0xC<<20,
		Ch2_Pch1_Att2 = 0xD<<20,
	};

	enum KluchPrec {
		Pr_105_175 = 0X194 << 7,
		Pr_175_315 = 0X10C << 7,
		Pr_315_525 = 0X2C << 7,
		Pr_525_805 = 0X64 << 7,
		Pr_805_1215 = 0X144 << 7,
		Pr_1215_1410 = 0XB4 << 7,
		Pr_1410_1620 = 0XDB << 7,
		Pr_1620_1830 = 0XDF << 7, //011011001
		Pr_1830_2040 = 0XD9 << 7,
		Pr_2040_2320 = 0XDD << 7, //011011101
		Pr_2320_2600 = 0XDA << 7, //011011010
		Pr_2600_2880 = 0XDE << 7, //011011110
		Pr_2880_3230 = 0XD8 << 7  //011011000
	};

	enum KluchPC2 {
		PC2_32_105 = 0x4 << 12,
		PC2_105_175_OB = 0x0 << 12,
		PC2_105_1215 = 0x9 << 12,
		PC2_1215_1815 = 0xA << 12,
		PC2_1815_3200 = 0xA << 12
	};
                                  // SSS SS SS
	enum KluchPC1 {               // 876 54 32    3px2_mfch_1_2.docx стр. 7
		PC1_32_105 = 0X58<< 9,     //101 10 00  0X58   было 0 38 68
        PC1_105_175_OB = 0X78<< 9, //101 10 00  0X58   было 0
		PC1_105_1215 = 0x78 << 9,  //111 10 00
		PC1_1215_1815 = 0x72 << 9, //111 00 10
		PC1_1815_3200 = 0x75 << 9  //111 01 01
	};

	enum KluchAmplSW2 {
		SW2_32_50 = 0x4 << 13, //
		SW2_50_70 = 0x2 << 13, //
		SW2_70_105 = 0x1 << 13 //
	};

	enum KluchAmplSW1 {
		SW1_15_32 = 0,
		SW1_15_25 = 0x5 << 13,
		SW1_25_5 = 0x4 << 13,
		SW1_5_9 = 0x3 << 13,
		SW1_9_16 = 0x2 << 13,
		SW1_16_32 = 0x1 << 13
	};

	enum KluchAmplSW3 {
		SW3_32_105 = 1 << 15,
		SW3_105_3200 = 0,
		SW3_LNA_ON = 1 << 14,
		SW3_LNA_Off = 0
	};

};

#endif
