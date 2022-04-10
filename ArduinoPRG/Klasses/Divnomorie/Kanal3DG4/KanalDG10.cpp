//---------------------------------------------------------------------------


#pragma hdrstop

#include "KanalDG10.h"
#include <math.h>
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
 KanalDG10::KanalDG10(int Mod_kanalNum, int Blok_kanalNum, double Polosa)
	{   KanalNum_B_Blok = Blok_kanalNum;
		KanalNum_B_Mod = Mod_kanalNum;
		PolosaPC2 =  Polosa;
		KanalNum_B_Mod = Mod_kanalNum;
		AmpSET = false;
		AMP_SW1_Kluch = KluchAmplSW1::SW1_15_25;
		AMP_SW2_Kluch = KluchAmplSW2::SW2_32_50;
		LNA = KluchAmplSW3::SW3_LNA_Off;
		AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_105_3200;

		PC1_Kluch = KluchPC1::PC1_105_175_OB;
		PC2_Kluch = KluchPC2::PC2_105_175_OB;
		Pres_UPR_Kluch = KluchPrec::Pr_105_175;
		AMP_POn_Kluch = 1<<15;
		ATT_pervi =  UPR3_0;
		ATT_vtoroi = UPR2_0;
		FrGet1 = 2565;
		FrGet1 = 2300;
		PC4 = Nig;
        FsigPC2 = 140;
	}
 KanalDG10::~KanalDG10()
	{
		//Freal = 10;
	}
 
 void KanalDG10::WriteFregIN(double freqCR, int Kanal)
{      if (Kanal>=1&&Kanal<=2)
	{
			KanalNum_B_Mod = Kanal;
	} else
	   {
			KanalNum_B_Mod = 1;
	   }
		 Freal = freqCR;
		 FregIN = floor(0.5 + freqCR/0.5);
		 FregIN =  FregIN * 0.5;

		if (Freal>=10000)
	{
				if(Freal>=14000)
			{
				if(Freal>=16000)
					{
						upr221 = UPR2_1618;
						upr1311 = UPR1_1618;
						
					}
					else {
						upr221 = UPR2_1416;
						upr1311 = UPR1_1216;
						
					}

			}
			else
			{  if(Freal>=12000)
					{
						upr221 = UPR2_1214;
						upr1311 = UPR1_1216;
					}
					else {
						upr221 = UPR2_1012;
						upr1311 = UPR1_1012;
					}
			
			}
			upr25 = Nig1;

			FrGet1 = Freal - 2440;//2360
	}
	else {
			if(Freal>=6000)
			{
				if(Freal>=8000)
				{
					upr221 = UPR2_810;
					upr25 = VER1;		  // upr25 = Nig1;

					FrGet1 = Freal + 2440;//  Freal - 2440
				}
				else {
					upr221 = UPR2_68;
					upr25 = VER1;
					
					FrGet1 = Freal + 2440;//2360
				}
				upr1311 = UPR1_610;

			}
			else
			{
				if(Freal>=4000)
				{
					upr221 = UPR2_46;
				}
				else {
					upr221 = UPR2_34;
				}
				upr1311 = UPR1_36;
				upr25 = VER1;
				
				FrGet1 = Freal + 2440;//2360
			}

	}

}


 
 void KanalDG10::PC1_2440 ()
 {           			 //Fpc140 = fsigPC1 - Fget2;
 }


 int KanalDG10::LoadKL(int div)
{    int i;
	 int  SW_SW;
	 i = div;
					switch (i)
   {
	 case 0:

		 			switch(KanalNum_B_Mod)
		 {
			case 1:SW_SW = 0x4<<24|ATT_pervi;break;

			case 2:SW_SW = 0x4<<24|0x10<<16|ATT_pervi;break;
		 }
	 break;
	 case 1:
					switch(KanalNum_B_Mod)
		 {
			case 1:SW_SW = 0x4<<24|0x01<<16|ATT_vtoroi;break;

			case 2:SW_SW = 0x4<<24|0x11<<16|ATT_vtoroi;break;
		 }
	 break;
	 case 2:
					switch(KanalNum_B_Mod)
		 {
			case 1:SW_SW = 0x4<<24|0x02<<16|PC4<<7|upr25<<6|upr1311<<3|upr221;break;

			case 2:SW_SW = 0x4<<24|0x12<<16|PC4<<7|upr25<<6|upr1311<<3|upr221;break;
		 }

	 


	 break;
	 

	 default : SW_SW = 0x4<<24|0x12<<16|PC4<<7|upr25<<6|upr1311<<3|upr221;break;

   }
   
	return  SW_SW;
}
 void KanalDG10::ATT1_SET(int DB)
{


	  ATT_pervi =  (~DB)&31;


}
 int KanalDG10::LoadATT(int div)
{    int i;
	 int  ATT_db;
 if (div >= 0 && div < 8)
   {
	i = div;
   }
   else
   {
	i = 0;
   }



  //****************************************************************

   if (KanalNum_B_Mod==1)
		switch (i)
   {
	 case 0:
	// ATT_db = AdrRegATT::Ch1_Amp_Att1 + Amp_Att1;break;
	 case 1:
	// ATT_db = AdrRegATT::Ch1_Amp_Att2 + Amp_Att2;break;
	 case 2:
	// ATT_db = AdrRegATT::Ch1_Amp_Att3 + Amp_Att3;break;
	 case 3:
	// ATT_db = AdrRegATT::Ch1_Amp_Att4 + Amp_Att4;break;
	 case 4:
   //	 ATT_db = AdrRegATT::Ch1_Pres_Att + Pres_Att;break;
	 case 5:
	// ATT_db = AdrRegATT::Ch1_Pch1_Att1 + Pch1_Att1;break;
	 case 6:
	// ATT_db = AdrRegATT::Ch1_Pch1_Att2 + Pch1_Att2;break;
	 default : //ATT_db = AdrRegATT::Ch2_Pch1_Att2 + Pch1_Att2;
	 break;

   }


	 else
		switch (i)
   {
	 case 0:
	 //ATT_db = AdrRegATT::Ch2_Amp_Att1 + Amp_Att1;break;
	 case 1:
	// ATT_db = AdrRegATT::Ch2_Amp_Att2 + Amp_Att2;break;
	 case 2:
	// ATT_db = AdrRegATT::Ch2_Amp_Att3 + Amp_Att3;break;
	 case 3:
	// ATT_db = AdrRegATT::Ch2_Amp_Att4 + Amp_Att4;break;
	 case 4:
	// ATT_db = AdrRegATT::Ch2_Pres_Att + Pres_Att;break;
	 case 5:
	// ATT_db = AdrRegATT::Ch2_Pch1_Att1 + Pch1_Att1;break;
	 case 6:
	// ATT_db = AdrRegATT::Ch2_Pch1_Att2 + Pch1_Att2;break;
	 default : //ATT_db = AdrRegATT::Ch2_Pch1_Att2 + Pch1_Att2;
	 break;

   }


  //****************************************************************

//   ATT_db = TipUstrPX2::TipATT + ATT_db;
	return  ATT_db;
}
 void KanalDG10::ATT2_SET(int DB)
{

//	Имеется в виду, что 15=0Ь00001111,51 =0Ь00110011,85=0Ь01010101.
		ATT_vtoroi = ((DB>>2)&3)|((DB&3)<<2);
		ATT_vtoroi = ((ATT_vtoroi>>1)&5)|((ATT_vtoroi&5)<<1);
		ATT_vtoroi = (~ATT_vtoroi)&15;

}

double KanalDG10::FreqFout(){
return FsigPC2;
}
//--------------------------------------------------------------
DWORD KanalDG10::LoadGET1H(){
  DWORD SW = 0;
	if (true) {
	//   SW = TipUstrPX2::Fc1_Ch1;
  } else {
	//   SW = TipUstrPX2::Fc1_Ch2;
  }

}
DWORD KanalDG10::LoadGET2H(){
if (KanalNum_B_Mod) {
   //	TipUstrPX2::Fc2_Ch1;

	}   else {
	  //	TipUstrPX2::Fc2_Ch2;
	}

}
//--------------------------------------------------------------

#pragma package(smart_init)
