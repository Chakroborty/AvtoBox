// ---------------------------------------------------------------------------
#include "KanalCRPU.h"
#ifndef Tri3PX2H
#define Tri3PX2H
#include "UsbDeviceManager.h"

// ---------------------------------------------------------------------------
class Tri3PX2 {
public:
	Tri3PX2(int ADR);
	~Tri3PX2();

	KanalCRPU *MKanal;
	bool Modul_All;
	long BL_NumModul;

	enum AdresModul {

		Modul1 = 0x0, Modul2 = 0x1 << 28, Modul3 = 0x2 << 28, Modul4 =
			0x3 << 28, Modul5 = 0x4 << 28, Modul6 = 0x5 << 28, MFCl = 0xE << 28,
		MFC2 = 0xF << 28, Obsh = 0xD << 28
	};

	enum ATT_K1 {
		Ch1_Amp_Att1 = 0x3000000, Ch1_Amp_Att2 = 0x3010000, Ch1_Amp_Att3 =
			0x3020000, Ch1_Amp_Att4 = 0x3030000, Ch1_Pres_Att = 0x3080000,
		Ch1_Pch1_Att1 = 0x30A0000, Ch1_Pch1_Att2 = 0x30B0000
	};

	enum ATT_K2 {
		Ch2_Amp_Att1 = 0x3040000, Ch2_Amp_Att2 = 0x3050000, Ch2_Amp_Att3 =
			0x3060000, Ch2_Amp_Att4 = 0x3070000, Ch2_Pres_Att = 0x3090000,
		Ch2_Pch1_Att1 = 0x30C0000, Ch2_Pch1_Att2 = 0x30D0000
	};

	enum KLUCH_K1 {
		Ch1_Amp_POn = 0x4000000, Ch1_Amp_SW2 = 0x4020000, Ch1_Amp_SW3 =
			0x4040000, Ch1_Amp_SW1 = 0x4060000, Ch1_Pres_UPR012 = 0x4080000,
		Ch1_Pch1_Sw = 0x40e0000, Ch1_Pch2_Sw = 0x4100000

	};

	enum KLUCH_K2 {
		Ch2_Amp_POn = 0x4010000, Ch2_Amp_SW2 = 0x4030000, Ch2_Amp_SW3 =
			0x4050000, Ch2_Amp_SW1 = 0x4070000, Ch2_Pres_UPR012 = 0x4090000,
		Ch2_Pch1_Sw = 0x40f0000, Ch2_Pch2_Sw = 0x4110000
	};


	int LoadKL_K1(int tip);


	int LoadATT_K1(int tip);


	void Set_ATT1_K1(double dB);
	void Set_ATT2_K1(double dB);
	DWORD LoadGET1_L(int REG);
	DWORD LoadGET1_H(void);
	DWORD LoadGET2_L(int REG);
	DWORD LoadGET2_H(void);


	void Tri3PX2::SeFriq(int Mod, int Kanal, double Fin, bool Ampl, int DB1,
		int DB2);

private:

};
#endif
