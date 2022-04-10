//---------------------------------------------------------------------------


#pragma hdrstop

#include "Kanal009.h"
#include <math.h>
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
 Kanal009::Kanal009(int Blok_kanalNum, bool CR28)
	{   KanalNum_B_Blok = Blok_kanalNum;
		ATT_pervi = 0;
        ATT_vtoroi = 0;
		TIp28 = CR28;
		RefExt = 0;
		Filter = 1;
        SynthExt = 0;
		GET1 = new ADF4153(1700,7,170,false,10,2,1);
		Sint2 = new ADF4153(1600,4,160,true,10,0.2,1);
	}
 Kanal009::~Kanal009()
	{
		//Freal = 10;
	}


 void Kanal009::WriteFregIN(double freqCR, int Kanal,bool Shirokaia)
{
// Установка частоты
	if (freqCR>=20&&freqCR<=3200) {

		  Freal = freqCR;
	 } else {
		 Freal = 200;
	 }

  FregIN =  0.5 * floor(0.5 + Freal * 2);


	if (Freal < 1200)
	{ GetNo = 1;
	  Band = KluchPC1::PC1_200;
	  FrGet1 = 2*floor(0.5+(FregIN+1670)/2);
	  FsigPC1 = FrGet1 - Freal;
	  InvSP = true;
	if (Freal >= 720)
		Presel = KluchPrec::Pr_720_1200 ;
	  else
		if (Freal >= 430)
		  Presel = KluchPrec::Pr_430_720 ;
		else
		  if (Freal >= 255)
			Presel = KluchPrec::Pr_255_430;
		  else
			if (Freal >= 156)
			  Presel = KluchPrec::Pr_156_255;
			else
			  if (Freal >= 93)
				Presel = KluchPrec::Pr_93_156;
			  else
				if (Freal >= 56)
				  Presel = KluchPrec::Pr_56_93;
				else
				  if (Freal >= 33)
					Presel = KluchPrec::Pr_33_56;
				  else
					Presel = KluchPrec::Pr_20_33;
	}
	else
	{
	  GetNo = 2;
	  Band = KluchPC1::PC1_2000;
	  FrGet1 = 2*floor(0.5+(FregIN+470)/2);
	  FsigPC1 = FrGet1 - Freal;
	  if (Freal >= 2800){
		Presel = KluchPrec::Pr_2800_3200;
		FrGet1 = 2*floor(0.5+(FregIN - 470)/2);
		FsigPC1 =  Freal - FrGet1;
		InvSP = false;}
	  else
		if (Freal >= 2400){
		  Presel = 	KluchPrec::Pr_2400_2800;
		  FrGet1 = 2*floor(0.5+(FregIN - 470)/2);
		  FsigPC1 = Freal - FrGet1;
		  InvSP = false;}
		else
		  if (Freal >= 2000)
			Presel = KluchPrec::Pr_2000_2400;
		  else
			if (Freal >= 1600)
			  Presel = KluchPrec::Pr_1600_2000;
			else
			  Presel = KluchPrec::Pr_1200_1600;
	}

		 GET1->SetFreq(FrGet1);
		 WriteFrPC1(FsigPC1,Shirokaia);

}

void Kanal009::Polosa(bool Shrokaia){
		if (Shrokaia) {
			Filter = 0;
	   }
	   else{
		  Filter = 1;
	   }
}


 void Kanal009::WriteFrPC1(double freqPC1,bool Shrokaia)
 {     FsigPC1 = freqPC1;
	Polosa(Shrokaia);
 if ( freqPC1>=1669 && freqPC1<=1671)
			 { FrGet2 = 0.2*floor((FsigPC1 - 70) * 5);//FRF1-FC-FПЧ2
			   Fsint2 = FrGet2;//Fget2 = Fsint2 / 2;
			   FsigPC2 = FrGet2 - FsigPC1;//Fpc140 = Fget2 - FsigPC1;
			   Band = KluchPC1::PC1_200;
			 }
			 else
			 { FrGet2 = 0.2*floor((FsigPC1 - 70) * 5);//FRF1-FC-FПЧ2
			   Fsint2 = FrGet2*4;//Fget2 = Fsint2
			   FsigPC2 = FrGet2 - FsigPC1;//Fpc140 = Fget2 - FsigPC1;
			   Band = KluchPC1::PC1_2000;
			 }
	   Sint2->SetFreq(Fsint2);
 }
 int Kanal009::LoadKL()
{
  SW_SW =  UstrCR28::OTHER<<24 | RefExt<<8 | SynthExt<<7 | SynthOff<<6 | Filter<<5 | Band<<4 | Presel;
  return  SW_SW;
}
 void Kanal009::ATT1_SET(double DB)
{

 if (DB >= 0 && DB <= 63)
   {
ATT_pervi = (int)(DB);
   }
   else
   {
ATT_pervi = 30 ;
   }
}
 int Kanal009::LoadATT(int div)
{    int i;
	 int  ATT_db;
 if (div >= 0 && div < 2)
   {
	 i = div;

   }
   else
   {
	i = 0;
   }
 	switch (i){

	case 0:
	SW_SW =	UstrCR28::ATT1<<24|ATT_pervi<<1;
	 break;
	case 1:
	SW_SW =UstrCR28::ATT2<<24|ATT_vtoroi<<1;
	break;
	default :	SW_SW =	UstrCR28::ATT2<<24|ATT_vtoroi<<1;
	break;
	}



																		 /* TODO -cLoad : ATT */
  return SW_SW;
	// ATT_vtoroi dwReceiverNumber<<28 | ((AttNum-1)? ATT_MODE2 : ATT_MODE1)<<24 | ((AttNum-1)? Att2 : Att1);



}
 void Kanal009::ATT2_SET(double DB)
	   {
   if (DB >= 0 && DB <= 63)
   {
	ATT_vtoroi = (int)(DB);
   }
   else
   {
ATT_vtoroi = 15 ;
   }
	   }

double Kanal009::FreqFout(){
return FsigPC2;
}
//--------------------------------------------------------------
DWORD Kanal009::LoadGET1(int Reg){


 if (Reg >= 0 && Reg < 16)
   {
	 i = Reg;

   }
   else
   {
	i = 0;
   }

	SW_SW =UstrCR28::Sin1<<24|GET1->RegLoad4153(Reg);

	return  SW_SW;
}
DWORD Kanal009::LoadGET2(int Reg){
  int i;
  DWORD  SW_SW;
 if (Reg >= 0 && Reg < 16)
   {
	 i = Reg;

   }
   else
   {
	i = 0;
   }
SW_SW =UstrCR28::Sin2<<24|Sint2->RegLoad4153(Reg);

	return  SW_SW;
}
#pragma package(smart_init)
