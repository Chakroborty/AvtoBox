//---------------------------------------------------------------------------

#ifndef SRCHtblH
#define SRCHtblH
#include "MSERIAL.h"
#include "Bits.h"
#define SETUP_PKT_SIZE         4
#define MAX_PKT_SIZE           4
class MSRCH
  {

	public:// User declarations
	MSRCH();
	~MSRCH();
	   //int O1VCO1_8_10;
	   
PBYTE pSetupPacket;
PBYTE pData;
//---------------------------------------------------------------------------
int O1VCO1_8_10 ;
int O1VCO2_8_10 ;
int O2VCO1_12_15;
int O2VCO2_12_15;
int O1VCO3_10_12;
int O1VCO4_10_12;
int O2VCO3_15_18;
int O2VCO4_15_18;
	int Reverse(int x);
	int REGIMST(int Reg);
	int REGIMVAL(int Reg);
	unsigned short WRITESV64(DWORD ADR, DWORD FB);
	unsigned short READSV32(BYTE &DATA);
	unsigned short SRCHWRITEALL(int VAL);
	MSerial* COMPorTT;

	private:	// User declarations
		

  } ;
//---------------------------------------------------------------------------
#endif
