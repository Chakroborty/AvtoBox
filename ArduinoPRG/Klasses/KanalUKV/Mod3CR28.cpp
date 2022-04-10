//---------------------------------------------------------------------------


#pragma hdrstop

#include "Mod3CR28.h"
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
 Mod3CR28::Mod3CR28(int ADR)
 { BL_Kanal = ADR<<28;
   MKanal  = new Kanal009(8,true);
   MPeleng = true;
  // MKanal2  = new KanalCRPU(2,1);
 }
 Mod3CR28::~Mod3CR28()
  {

  }
//---------------------------------------------------------------------------
void Mod3CR28::SeFriq(int Kanal, double Fin,int DB1,int DB2,bool Shirokaia,bool Peleng){
			switch (Kanal)
   { case 0:
	 BL_Kanal = Adres::Obsh;Modul_All = true;break;
	 case 1:
	 BL_Kanal = Adres::Kanal1;Modul_All = false;break;
	 case 2:
	 BL_Kanal = Adres::Kanal2;Modul_All = false;break;
	 case 3:
	 BL_Kanal = Adres::Kanal3;Modul_All = false;break;
	 case 4:
	 BL_Kanal = Adres::Kanal4;Modul_All = false;break;


	 default : BL_Kanal = Adres::Obsh; Modul_All = true;break;

   }

	 MKanal->WriteFregIN(Fin,Kanal,Shirokaia);
	 Ispolnenie(Peleng);

	 MKanal->ATT1_SET(DB1);
	 MKanal->ATT2_SET(DB2);



}
void Mod3CR28::Ispolnenie(bool Peleng){
		  MPeleng = Peleng;
		  if (Peleng) {                                           /* TODO -cad : sint */
		 MKanal->SynthExt = 1;
		 MKanal->SynthOff = 1;
	 } else {
		 MKanal->SynthExt = 0;
		 MKanal->SynthOff = 0;
	 }
}
int Mod3CR28::LoadKL()
{
	return  BL_Kanal + MKanal->LoadKL();
}
//---------------------------------------------------------------------------
void Mod3CR28::Set_ATT1(double dB)
{
	MKanal->ATT1_SET(dB);
}
void Mod3CR28::Set_ATT2(double dB)
{
	MKanal->ATT2_SET(dB);
}
int Mod3CR28::LoadATT(int tip)
{
	return  BL_Kanal + MKanal->LoadATT(tip);
}
DWORD Mod3CR28::LoadGET1(int REG){

 return  BL_Kanal + MKanal->LoadGET1(REG);
}

DWORD Mod3CR28::LoadGET2(int REG){
 return  BL_Kanal + MKanal->LoadGET2(REG);
	}
bool  Mod3CR28::Inversia(){
  return  MKanal->InvSP;
}
#pragma package(smart_init)

