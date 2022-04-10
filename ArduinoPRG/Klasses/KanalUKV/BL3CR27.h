// ---------------------------------------------------------------------------
#include "Mod3CR28.h"
#include "MFCUKVCHR.h"

#include "UsbDeviceManager.h"
#include "Rpu3CR27.h"
#ifndef BL3CR27H
#define BL3CR27H
#include "Test3CRUKV.h"

// ---------------------------------------------------------------------------


class BL3CR27 {
public:
	BL3CR27(int BL3CRXX);
	~BL3CR27();

	UsbDeviceManager *DeviceManager;
	TRpu3CR27* DeviceUSB;
	int BLtip, ADR0, ADR1, ADR2, ADR3, ADR4, ADR5, ADR6, ADR7;

	void __fastcall DeviceConnected(TRpu3CR27 *newDevice);
	void __fastcall DeviceRemoved(TRpu3CR27 *oldDevice);
	DWORDLONG __fastcall SendDATA_USB(DWORD DwData);

	bool Wait_SPI;
	bool Ispol830;

	int ReadSN_Ver(int SelectedModul);
	void __fastcall WriteSN_Ver(int SelectedModul, DWORD ver, DWORD num);
	void WriteBlokSN(DWORD ValSN);
	DWORD ReadBlokSN();
	/**
	 * <url>element://model:project::Test3PX1/design:node:::hf6wo2i0tjfob27hg_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::uhdju1h2ina2y67wn_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::zl54etpuk6s8uejyg_n</url>
	 * <url>element://model:project::Project3CR25/design:node:::3tcqkfb2vi4ozpils_n</url>
	 */
	void FriqSET(double Fin1,int DB1,int DB2,int Kanal,bool Shrokaia,bool Peleng);

	/**
	 * <url>element://model:project::Test3PX1/design:node:::st71xwsdy70vuu0rf_n</url>
	 */
	void MFCH_F1set(double Fg1);
	void MFCH_F2set(double Fg2);
	/**
	 * <url>element://model:project::Test3PX1/design:node:::fzr217fsa1k4x56rq_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::0u80tcl1kws_n</url>
	 */

	void ATT1Set(double dB);
	void ATT2Set(double dB);
	void Polosa(bool Shirokaia);
	void Ispolnenie(bool Peleng);
	double Geterodin1();
	double Geterodin2();
	void KanalInitial();
	void MFCInitial();
	void MFCH2_830_Sint2(unsigned long &, unsigned long &, int i);
	double FriqOUT(void);
	double MFCG1OUT(void);
    double MFCG2OUT(void);
	/**
	 * <url>element://model:project::Test3PX1/design:node:::wvgprtcur20pp2t0j_n</url>
	 */
	void OGvnutr(bool OG);
    Mod3CR28 *ModulCR28;
	MFCUKV02 *ModulFCH;
protected:


private:
	

	 int i, j;
	 };
	 #endif

