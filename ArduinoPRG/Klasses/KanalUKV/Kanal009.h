// ---------------------------------------------------------------------------

#ifndef Kanal009H
#define Kanal009H
#include "ADF4153.h"
#include "UsbDeviceManager.h"

// ---------------------------------------------------------------------------
class Kanal009 {
public:
	Kanal009(int Blok_kanalNum, bool Perehv);
	~Kanal009();
	/**
	 * <url>element://model:project::Project3CR25/design:node:::u1xv9063dz2fckm2o_n</url>
	 */
	void WriteFregIN(double freqCR, int Kanal,bool Shirokaia);
	/**
	 * <url>element://model:project::Test3PX1/design:node:::bnq03y5ot69c907we_n:uhdju1h2ina2y67wn_n</url>
	 */
	int LoadKL();
	bool TIp28;
    bool InvSP;
	// ********************************************************************************
	ADF4153* GET1;
	ADF4153* Sint2;
	// ********************************************************************************
	int KanalNum_B_Blok;
	// ********************************************************************************
	double FrGet2;
	double FregIN;
	double FrGet1;
	double Freal;
	// ********************************************************************************
	int GetNo, Band, Presel, Att1, Att2, AttNum, Filter, SynthExt,
		SynthOff, RefExt;

	// ********************************************************************************

	void ATT1_SET(double DB);
	/**
	 * <url>element://model:project::Test3PX1/design:node:::5crob4xaecpjom8ct_n:uhdju1h2ina2y67wn_n</url>
	 */
	int LoadATT(int div);
	void ATT2_SET(double DB);
	DWORD LoadGET1(int Reg);
	DWORD LoadGET2(int Reg);
    void Polosa(bool Shrokaia);
	// ********************************************************************************
	double FreqFout();

protected:

	void WriteFrPC1(double freqPC1,bool Shrokaia);


	int ATT_pervi;
	int ATT_vtoroi;


	// ********************************************************************************
private:

	double Fsint2;
	double FsigPC1,FsigPC1R;
	double FsigPC2;
	DWORD SW_SW;
	int  i;







	enum UstrCR28
	{
   OTHER = 0,	// Режим параллельных данных (ключи, фильтры, ...)
   Sin1 =  1,
   Sin2 =  2,
   ATT1 =  3,
   ATT2 =  4  };



	enum KluchPrec {
		Pr_20_33 = 0,
		Pr_33_56 = 1,
		Pr_56_93 = 2,
		Pr_93_156 = 3,
		Pr_156_255 = 4,
		Pr_255_430 = 5,
		Pr_430_720 = 6,
		Pr_720_1200 = 7,
		Pr_1200_1600 = 8,

		Pr_1600_2000 = 9,
		Pr_2000_2400 = 10,
		Pr_2400_2800 = 11,
		Pr_2800_3200 = 12


		};

	enum KluchPC1 {
		PC1_200 = 0,
		PC1_2000 = 1

	};




};

#endif
