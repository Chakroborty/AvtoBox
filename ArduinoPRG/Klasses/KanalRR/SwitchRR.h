// ---------------------------------------------------------------------------

#ifndef SwitchRRH
#define SwitchRRH
#include "HMC700.h"
#include "TADT7310.h"
 struct ADRSW
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
		unsigned int Control_T;
		unsigned int Control_R;

		unsigned int SR;// регистр
		unsigned int FSR;// регистр
		unsigned int NVCR;// регистр
		unsigned int VCR ;// регистр
		unsigned int EVCR;// регистр
		unsigned int WriteFregIN;//Write Enable operation
		unsigned int ClearFSt;
		unsigned int Write1b;//Write 1 byte to flash memory 
		unsigned int Read5b;//Read 5 byte from flash memory
		unsigned int BulkEr;
		unsigned int Rflash;
		unsigned int ReadST;  
	};
 struct LNA
	{
		int UPR;
		int RNG;
	};
// ---------------------------------------------------------------------------
class CSwitchRR {
public:
	CSwitchRR(int Mod_kanalNum);
	~CSwitchRR();
	void WriteFregIN(double freqCR, int Kanal);
	// ********************************************************************************
	ADT7310 *MADT7310;
	int AdrMod;
	int DIAPAZON[2][13];

	LNA LNAMATRIX[2][2];
	ADRSW ASW[3];
	int i;
	int LoadATT(int div);
	int LoadKL(int sw);
	// ********************************************************************************

	// ********************************************************************************
	int KanalNum_B_Blok;
	int KanalNum_B_Mod;
	// ********************************************************************************
	double FrGet2;
	double FregIN;
	double FrGet1;
	// ********************************************************************************


	// ********************************************************************************
	void AmplifSET(int Amplif);
	void PRESELSET(int PRES);
	void ATT1_SET(double DB);
	void ATT2_SET(double DB);
	void ATT3_SET(double DB);
	void ATT4_SET(double DB);
	int SRCOM();
	

	
	// ********************************************************************************
    
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
