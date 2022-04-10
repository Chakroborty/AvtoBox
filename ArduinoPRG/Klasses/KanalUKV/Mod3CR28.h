// ---------------------------------------------------------------------------
#include "Kanal009.h"
#ifndef Mod3CR28H
#define Mod3CR28H
#include "UsbDeviceManager.h"

// ---------------------------------------------------------------------------
class Mod3CR28 {
public:
	Mod3CR28(int ADR);
	~Mod3CR28();

	Kanal009 *MKanal;
	bool Modul_All;
	DWORD BL_Kanal;
    bool MPeleng;
	enum Adres {
		Kanal1 = 0x0,
		Kanal2 = 0x1 << 28,
		Kanal3 = 0x2 << 28,
		Kanal4 = 0x3 << 28,
		Obsh = 0x9 << 28
	};

	enum ATT{
		Att1 = 0x3000000,
		Att2 = 0x3010000,

	};


	enum KLUCH{
		Ch1_Amp_POn = 0x4000000,
		Ch1_Amp_SW2 = 0x4020000,
		Ch1_Amp_SW3 = 0x4040000,
		Ch1_Amp_SW1 = 0x4060000,
		Ch1_Pres_UPR012 = 0x4080000,
		Ch1_Pch1_Sw = 0x40e0000,
		Ch1_Pch2_Sw = 0x4100000

	};

	

	/**
	 * <url>element://model:project::Test3PX1/design:node:::3a9pve1675ekz5ofn_n:uhdju1h2ina2y67wn_n</url>
	 */
	int LoadKL();
    bool  Inversia();
	/**
	 * <url>element://model:project::Test3PX1/design:node:::e7s0lm29znhhyd2yj_n:uhdju1h2ina2y67wn_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::2a0jlr6gxai_n:uhdju1h2ina2y67wn_n</url>
	 */
	int LoadATT(int tip);

	/**
	 * <url>element://model:project::Test3PX1/design:node:::e7s0lm29znhhyd2yj_n:uhdju1h2ina2y67wn_n</url>
	 */
	void Set_ATT1(double dB);
	void Set_ATT2(double dB);
	DWORD LoadGET1(int REG);

	DWORD LoadGET2(int REG);
	void Ispolnenie(bool Peleng);

	/**
	 * <url>element://model:project::Test3PX1/design:node:::uhdju1h2ina2y67wn_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::zl54etpuk6s8uejyg_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::rp8asjz0rdt_n:uhdju1h2ina2y67wn_n</url>
	 * <url>element://model:project::Project3CR25/design:node:::8c3dtfwga0l_n</url>
	 */
void Mod3CR28::SeFriq( int Kanal, double Fin,int DB1,int DB2,bool Shrokaia,bool Peleng);

private:

};
#endif
