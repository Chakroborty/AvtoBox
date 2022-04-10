//---------------------------------------------------------------------------


#pragma hdrstop

#include "PRC235.h"

//---------------------------------------------------------------------------
 MPRC::MPRC(int ADR)
{
	BL_NumModul = ADR<<28;
	MKanal  = new KanalRR(1,1,30);
}
 MPRC::~MPRC()
{

}
//---------------------------------------------------------------------------
void MPRC::SetFriq(int Mod,int Kanal,double Fin,bool Ampl,int DB1,int DB2,int DB3,int DB4,int PARAM)
{
			switch (Mod)
   { case 0:
	 BL_NumModul = AdresModulPR::Obsh;Modul_All = true;break;
	 case 1:
	 BL_NumModul = AdresModulPR::Modul1;Modul_All = false;break;
	 case 2:
	 BL_NumModul = AdresModulPR::Modul2;Modul_All = false;break;
	 case 3:
	 BL_NumModul = AdresModulPR::Modul3;Modul_All = false;break;
	 case 4:
	 BL_NumModul = AdresModulPR::Modul4;Modul_All = false;break;
	 case 5:
	 BL_NumModul = AdresModulPR::Modul5;Modul_All = false;break;
	 case 6:
	 BL_NumModul = AdresModulPR::Modul6;Modul_All = false;break;
	 case 7:
	 BL_NumModul = AdresModulPR::Modul7;Modul_All = false;break;
	 case 8:
	 BL_NumModul = AdresModulPR::Modul8;Modul_All = false;break;

	 case 9:
	 BL_NumModul = AdresModulPR::Obsh;Modul_All = false;break;

	 default : BL_NumModul = AdresModulPR::Obsh;break;

   }

		MKanal->WriteFregIN(Fin,Kanal,PARAM);
        MKanal->AmplifSET(Ampl);
		MKanal->ATT1_SET(DB1);
		MKanal->ATT2_SET(DB2);
		MKanal->ATT3_SET(DB3);
		MKanal->ATT4_SET(DB4);
}
int MPRC::LoadKL(int tip)
{
	return  BL_NumModul + MKanal->LoadKL(tip);
}
//---------------------------------------------------------------------------
void MPRC::Set_ATT1(double dB)
{
	MKanal->ATT1_SET(dB);
}
void MPRC::Set_ATT2(double dB)
{
	MKanal->ATT2_SET(dB);
}
int MPRC::LoadATT(int tip)
{
	return  BL_NumModul + MKanal->LoadATT(tip);
}

//---------------------------------------------------------------------------
unsigned long MPRC::LoadGET1_H()
{
  return  MKanal->LoadGET1H();
}
unsigned long MPRC::LoadGET1_L(int REG)
{
  return  BL_NumModul + MKanal->LoadGET1(REG);
}
//---------------------------------------------------------------------------
unsigned long MPRC::LoadGET2_H(void)
{
  return  MKanal->LoadGET2H();
}
unsigned long MPRC::LoadGET2_L(int REG)
{
  return  BL_NumModul + MKanal->LoadGET2(REG);
}







#pragma package(smart_init)

