//---------------------------------------------------------------------------


#pragma hdrstop
#include "Test3CRUKV.h"
#include "BL3CR27.h"
#include "Rpu3CR27.h"
#define ADR_CMD          2
//---------------------------------------------------------------------------
	BL3CR27::BL3CR27(int BL3CRXX)
	{  BLtip =  BL3CRXX;

		switch (BL3CRXX)
   {
	 case 19:
	  ADR0 = 8;

	  break;
	 case 25:
	 ADR0 = 0;
	  ADR1 = 1;
	  ADR2 = 2;
	  ADR3 = 3;break;
	 case 27:
	  ADR0 = 8;
	  ADR1 = 8;
	  ADR2 = 0;
	  ADR3 = 1;
	  ADR4 = 2;
	  ADR5 = 3;
	  break;



   }
	 ModulCR28 = new Mod3CR28(0x8); // Tri3PX2::AdresModul::Obsh;
	 ModulFCH = new MFCUKV02();


DeviceManager = new UsbDeviceManager;   /* TODO -cUSB : USB Device VID PID в UsbDefines.h*/
DeviceManager->OnAddDevice = DeviceConnected;
DeviceManager->OnRemoveDevice = DeviceRemoved;



	}
	BL3CR27::~BL3CR27()
	{

	}


void __fastcall BL3CR27::DeviceConnected(TRpu3CR27 *newDevice)
{

int iNumber = DeviceManager->Devices->IndexOf(newDevice);
DeviceUSB = (TRpu3CR27*)DeviceManager->Devices->Items[iNumber];
 Sleep(200);
	//DeviceUSB->LoadFpga("USB2LVDS.bit");

		if (DeviceUSB->LoadFpga("USB2LVDS.bit"))
			 ShowMessage(DeviceUSB->ErrMsg);


Form1->StatusBar1->Panels->Items[0]->Text = "3Чр25 " ;

}
//---------------------------------------------------------------------------

void __fastcall BL3CR27::DeviceRemoved(TRpu3CR27 *oldDevice)
{

Form1->StatusBar1->Panels->Items[0]->Text = "USB ОЖИДАНИЕ";
DeviceUSB = NULL;

}

void BL3CR27::KanalInitial(){
		  SendDATA_USB(ModulCR28->LoadKL());
				if ( ModulCR28->MKanal->TIp28) {
				Sleep(300);
				for (i = 0; i < 7; i++)
				{ 	SendDATA_USB( ModulCR28->LoadGET1(i));} //Прогр синтезатора 1   //Прогр всех ATT
				for (i = 0; i < 7; i++)
				{   SendDATA_USB( ModulCR28->LoadGET2(i));}   //Прогр синтезатора 2
			}
			Sleep(300);
			ModulFCH->LoadGET1(i);
				for (i = 0; i < 7; i++)
				{ 	SendDATA_USB( ModulCR28->LoadGET1(i));} //Прогр синтезатора 1   //Прогр всех ATT
				for (i = 0; i < 7; i++)
				{   SendDATA_USB( ModulCR28->LoadGET2(i));}   //Прогр синтезатора 2
			for (i = 0; i < 2; i++) {
			SendDATA_USB( ModulCR28->LoadATT(i)); }    //Прогр всех ATT



}



//**************************************3ПХ2******************
void BL3CR27::FriqSET(double Fin1,int DB1,int DB2,int Kanal,bool Shrokaia,bool Peleng)
	{         ModulCR28->SeFriq(Kanal,Fin1,DB1, DB2,Shrokaia,Peleng);
			  OGvnutr(1);
			  KanalInitial();


   }

 void BL3CR27::Ispolnenie(bool Peleng){
  ModulCR28->Ispolnenie(Peleng);
  KanalInitial();
 }

//*************************************АТТ 3ПХ2****************
 void BL3CR27::ATT1Set(double dB)
 {
	 ModulCR28->Set_ATT1(dB);
	 KanalInitial();



 }
 void BL3CR27::ATT2Set(double dB)
 {
	ModulCR28->Set_ATT2(dB);
	 KanalInitial();

 }
void BL3CR27::Polosa(bool Shirokaia)
 {   ModulCR28->MKanal->Polosa(Shirokaia);
	 KanalInitial();

 }


  //************************************МФЧ1*******************
 

 double BL3CR27::Geterodin1()
  {
	   return ModulCR28->MKanal->FrGet1;// ModulFCH1->Fget1;
  }
  //***********************************МФЧ2********************

 void BL3CR27::OGvnutr(bool OG){
	if ( OG) {
	ModulCR28->MKanal->RefExt = 0;
	ModulFCH->RefExt =0;
  } else {
	ModulCR28->MKanal->RefExt = 1;
   	ModulFCH->RefExt =1;
  }

 }
double BL3CR27::FriqOUT(void){
	 return ModulCR28->MKanal->Freal;// ModulPX2->MKanal->FreqFout();
}
void BL3CR27::MFCInitial(){
		  SendDATA_USB(ModulFCH->Kluch());

		  Sleep(300);
		  for (i = 0; i < 6; i++)
		  { 	SendDATA_USB( ModulFCH->LoadGET1(i));} //Прогр синтезатора 1   //Прогр всех ATT
		  for (i = 0; i < 6; i++)
		  {   SendDATA_USB( ModulFCH->LoadGET2(i));}   //Прогр синтезатора 2

}
void BL3CR27::MFCH_F1set(double Fg1)
  {   ModulFCH->SetFreq(Fg1);
	 // OGvnutr(1);
	  MFCInitial();
  }
void BL3CR27::MFCH_F2set(double Fg2)
  {   ModulFCH->SetFreq2(Fg2);
	  //OGvnutr(1);
	  MFCInitial();
  }
double BL3CR27::MFCG1OUT(void){

	 return ModulFCH->Fget1;// ModulPX2->MKanal->FreqFout();
}
double BL3CR27::MFCG2OUT(void){

	 return ModulFCH->Fget2;// ModulPX2->MKanal->FreqFout();
}
 double BL3CR27::Geterodin2()
  {
	   return ModulCR28->MKanal->FrGet2;//ModulFCH2->Fget2;
  }
 DWORDLONG __fastcall BL3CR27::SendDATA_USB(DWORD DwData){

  if (DeviceUSB == NULL) {
      return 0;
 }
  return DeviceUSB->WriteDword(2,DwData);
 }


#pragma package(smart_init)
