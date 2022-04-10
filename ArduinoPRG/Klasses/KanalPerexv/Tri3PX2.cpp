//---------------------------------------------------------------------------


#pragma hdrstop

#include "Tri3PX2.h"
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
 Tri3PX2::Tri3PX2(int ADR)
 { BL_NumModul = ADR<<28;
   MKanal  = new KanalCRPU(1,1,30);
  // MKanal2  = new KanalCRPU(2,1);
 }
 Tri3PX2::~Tri3PX2()
  {

  }
//---------------------------------------------------------------------------
void Tri3PX2::SeFriq(int Mod,int Kanal,double Fin,bool Ampl,int DB1,int DB2){
			switch (Mod)
   { case 0:
	 BL_NumModul = AdresModul::Obsh;Modul_All = true;break;
	 case 1:
	 BL_NumModul = AdresModul::Modul1;Modul_All = false;break;
	 case 2:
	 BL_NumModul = AdresModul::Modul2;Modul_All = false;break;
	 case 3:
	 BL_NumModul = AdresModul::Modul3;Modul_All = false;break;
	 case 4:
	 BL_NumModul = AdresModul::Modul4;Modul_All = false;break;
	 case 5:
	 BL_NumModul = AdresModul::Modul5;Modul_All = false;break;
	 case 6:
	 BL_NumModul = AdresModul::Modul6;Modul_All = false;break;
	 case 7:
	 BL_NumModul = AdresModul::Obsh;Modul_All = false;break;

	 default : BL_NumModul = AdresModul::Obsh;break;

   }
	 MKanal->WriteFregIN(Fin,Kanal);
	 MKanal->ATT1_SET(DB1);
	 MKanal->ATT2_SET(DB2);
	 MKanal->AmplifSET(Ampl);


}
int Tri3PX2::LoadKL_K1(int tip)
{
	return  BL_NumModul + MKanal->LoadKL(tip);
}
//---------------------------------------------------------------------------
void Tri3PX2::Set_ATT1_K1(double dB)
{
	MKanal->ATT1_SET(dB);
}
void Tri3PX2::Set_ATT2_K1(double dB)
{
	MKanal->ATT2_SET(dB);
}
int Tri3PX2::LoadATT_K1(int tip)
{
	return  BL_NumModul + MKanal->LoadATT(tip);
}

//---------------------------------------------------------------------------
DWORD Tri3PX2::LoadGET1_H(){
  return  MKanal->LoadGET1H();
}
DWORD Tri3PX2::LoadGET1_L(int REG)
{
  return  BL_NumModul + MKanal->LoadGET1(REG);
}
//---------------------------------------------------------------------------
DWORD Tri3PX2::LoadGET2_H(void){
  return  MKanal->LoadGET2H();
}
DWORD Tri3PX2::LoadGET2_L(int REG)
{
  return  BL_NumModul + MKanal->LoadGET2(REG);
}







#pragma package(smart_init)

