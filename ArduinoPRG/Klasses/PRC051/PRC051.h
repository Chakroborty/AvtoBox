// ---------------------------------------------------------------------------

#ifndef PRC051H
#define PRC051H
//#include "HMC700.h"
#include "LMX2594.h"
#include "FCHPERENOS.h"
 struct ADRSW
	{
		unsigned int Att1;
		unsigned int Att2;
		unsigned int In_SW;
		unsigned int LNA_sw;
		unsigned int Conv_sw;
		unsigned int UsilPCH_sw;
		unsigned int Filtr_sw;
		unsigned int refsw;
		unsigned int lptrf;
		unsigned int Pres_Fil_sw;
		unsigned int uxm15p;
		unsigned int sinth;
	};
 struct LNA
	{
		int UPR;
		int RNG;
	};
// ---------------------------------------------------------------------------
class PRC51 {
public:
	PRC51(int Mod_kanalNum);
	~PRC51();
	void WriteFregIN(double freqCR, int Kanal);
	// ********************************************************************************

	int AdrMod;
	int DIAPAZON[2][13];

	LNA LNAMATRIX[2][2];
	ADRSW ASW[3];
	int i;
	int LoadATT(int div);
	int LoadKL(int sw);
	long SintLOAD_L(int Poz);
	// ********************************************************************************
	LMX2594 *DLMX2594;
	FCHP    *FCHP2594;
	// ********************************************************************************
	int KanalNum_B_Blok;
	int KanalNum_B_Mod;
	// ********************************************************************************
	double FrGet2;
	double FregIN;
	double FrGet1;

	// ********************************************************************************
	void INSET(int IN);
	void AmplifSET(int Amplif);

	void PERENOS(int SW);
	void PRESELSET(int PRES);
	void ATT1_SET(double DB);
	void ATT2_SET(double DB);
	void SUPR1(int S);
	void SUPR2(int S);
	void SetUXM15(int div);
	// ********************************************************************************
	/*
		ooooo         ooooooo      o      ooooooooo
		 888        o888   888o   888      888    88o
		 888        888     888  8  88     888    888
		 888      o 888o   o888 8oooo88    888    888
		o888ooooo88   88ooo88 o88o  o888o o888ooo88

	*/

	long FCHLOAD_LMX(int Poz);
	// void PRC51FCHFRIQ(int NUM);
	long FCHLOADF(int Poz);
	long FCHLOAD_KL(int Poz);
    //*************************************************************************
    /*
	  ooooo oooo   oooo ooooo ooooooooooo oooo   oooo
	   888   8888o  88   888  88  888  88  8888o  88
	   888   88 888o88   888      888      88 888o88
	   888   88   8888   888      888      88   8888
	  o888o o88o    88  o888o    o888o    o88o    88
	*/
long FCHLOAD_LMXINIT(int Poz);
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
enum Adress
	{
		OBSH = 0xD<<28,
		SWadr = 0x7<<28
	};

};

#endif
