//---------------------------------------------------------------------------


#pragma hdrstop

#include "Tri3DG10.h"
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
 Tri3DG10::Tri3DG10(int ADR)
 { BL_NumModul = ADR<<28;
   MKanalDG10  = new KanalDG10(1,1,30);
  // MKanalDG102  = new KanalCRPU(2,1);
 }
 Tri3DG10::~Tri3DG10()
  {

  }
//---------------------------------------------------------------------------
void Tri3DG10::SetFriq(int Mod,int Kanal,double Fin,int DB1,int DB2)
{
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
	 MKanalDG10->WriteFregIN(Fin,Kanal);
	 MKanalDG10->ATT1_SET(DB1);
	 MKanalDG10->ATT2_SET(DB2);
	


}
int Tri3DG10::LoadKL_K1(int tip)
{   
	return  BL_NumModul + MKanalDG10->LoadKL(tip);
}
//---------------------------------------------------------------------------
void Tri3DG10::Set_ATT1_K1(int dB)
{
	MKanalDG10->ATT1_SET(dB);
}
void Tri3DG10::Set_ATT2_K1(int dB)
{
	MKanalDG10->ATT2_SET(dB);
}
int Tri3DG10::LoadATT_K1(int tip)
{
	return  BL_NumModul + MKanalDG10->LoadATT(tip);
}

//---------------------------------------------------------------------------
DWORD Tri3DG10::LoadGET1_H(){
  return  MKanalDG10->LoadGET1H();
}
DWORD Tri3DG10::LoadGET1_L(int REG)
{
  return  BL_NumModul;
}
//---------------------------------------------------------------------------
DWORD Tri3DG10::LoadGET2_H(void){
  return  MKanalDG10->LoadGET2H();
}
DWORD Tri3DG10::LoadGET2_L(int REG)
{
  return  BL_NumModul;
}







#pragma package(smart_init)

