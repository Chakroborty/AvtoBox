//---------------------------------------------------------------------------

#pragma hdrstop
#include "Bits.h"

#include "SRCHTBL.h"
//---------------------------------------------------------------------------

MSRCH::MSRCH()
{
	//|П1 |П2 |П3  |П4  |П9  |П10 |П11 |П12 |П13 |П14 |
	//|П5 |П6 |П7  |П8  |    |    |    |    |    |
	/*_____________________________|______________________*/
	 //O1VCO1_8_10 = BIN16(00001000,00010110); //681   0x281 0x2801
	//                                0101 0010 0010  0x0522
	 //O1VCO2_8_10  = BIN16(00000100,10010110); //692
	//                             10 0101 0001 0001  0x2511
	 //O2VCO1_12_15 = BIN16(00001000,00101001); //941
	//                             00 1010 0010 0010  0xA22
	 //O2VCO2_12_15 = BIN16(00000100,10101001); //952 1001 0101 0010  00000100,10101001
	//
	 //O1VCO3_10_12 = BIN16(00000010,00100110); //544 0101 0100 0100  00000010,00101010
	//
	 //O1VCO4_10_12 = BIN16(00000001,01101010); //568 0101 0110 1000
	//
	 //O2VCO3_15_18 = BIN16(00000010,00010101); //A94 1010 1001 0100 00000010,10010101
	//
	 //O2VCO4_15_18 = BIN16(00000001,01010101); //AA8 1010 1010 1000 00000001,01010101


		O1VCO1_8_10  = BIN16(00001000,00010110); //681   0x281 0x2801
	//                                0101 0010 0010  0x0522
		O1VCO2_8_10  = BIN16(00000100,10010110); //692
	//                             10 0101 0001 0001  0x2511
		O2VCO1_12_15 = BIN16(00001000,00100101); //941
	//                             00 1010  0010 0010  0xA22
		O2VCO2_12_15 = BIN16(00000100,10100101); //952 1001 0101 0010  00000100,10101001
	//
		O1VCO3_10_12 = BIN16(00000010,00101010); //544 0101 0100 0100  00000010,00101010
	//
		O1VCO4_10_12 = BIN16(00000001,01101010); //568 0101 0110 1000
	//
		O2VCO3_15_18 = BIN16(00000010,00011001); //? A94 1010 1001 0100 00000010,10010101
	//
		O2VCO4_15_18 = BIN16(00000001,01011001); //AA8 1010 1010 1000 00000001,01010101
pSetupPacket = new BYTE[SETUP_PKT_SIZE];
pData = new BYTE[MAX_PKT_SIZE];
 COMPorTT = new MSerial();
}
MSRCH::~MSRCH()
{
	
}
int MSRCH::Reverse(int x)
{
  int Rez = 0;
  Rez|=(x&1);
  for(int i = 0; i<11;i++)
  {
	Rez =  Rez<<1;
	x = x>>1;
	Rez|=(x&1);



  }
	
  return Rez;
}

unsigned short MSRCH::WRITESV64(DWORD ADR, DWORD FB)
{
	pSetupPacket [0] = 0;
	pSetupPacket [1] = ADR&0xFF;
	pSetupPacket [2] = FB>>8&0xFF;
	pSetupPacket [3] = FB&0xFF;
	
//COMPorTT->OpenPP(Data8Bit, NonParity, OneStopBit);
COMPorTT->Write(pSetupPacket,4);
//COMPorTT->Close();
}
unsigned short MSRCH::SRCHWRITEALL(int VAL)
{
	
COMPorTT->OpenPP(Data8Bit, NonParity, OneStopBit);
WRITESV64(0x7, VAL);
// WRITESV64(0x7, 0);
// WRITESV64(0x5, 0);
// WRITESV64(0x0, 0);
// WRITESV64(0x4, 0);

COMPorTT->Close();
}

unsigned short MSRCH::READSV32(BYTE &DATA)
{
	COMPorTT->Read(pData,4);
	DATA = (pData[3]<<24 | pData[2]<<16 | pData[1]<<8 | pData[0]);
}

int MSRCH::REGIMST(int Reg)
{
	return 0xa92;
}
int MSRCH::REGIMVAL(int Reg)
{ int reve;
  int FBute;
  FBute = Reg&0xC00;
  FBute = FBute>>6|FBute>>10;

  reve = (Reg<<6 )& 0xFF00;




	return reve|FBute;
}
#pragma package(smart_init)

