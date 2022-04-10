//---------------------------------------------------------------------------


#pragma hdrstop

#include "KanalDGUKV.h"
#include <math.h>
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
 KanalDGUKV::KanalDGUKV(int Mod_kanalNum, int Blok_kanalNum, double Polosa)
	{   KanalNum_B_Blok = Blok_kanalNum;
		KanalNum_B_Mod = Mod_kanalNum;
		PolosaPC2 =  Polosa;
		KanalNum_B_Mod = Mod_kanalNum;
		AmpSET = false;
		AMP_SW1_Kluch = KluchAmplSW1::SW1_15_25;
		AMP_SW2_Kluch = KluchAmplSW2::SW2_32_50;
		LNA = KluchAmplSW3::SW3_LNA_Off;
		AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_105_3200;
	    //AMP_SW3_Kluch = AMP_POn_Kluch |  AMP_SW3_Bolshe105;

		PC1_Kluch = KluchPC1::PC1_105_175_OB;
		PC2_Kluch = KluchPC2::PC2_105_175_OB;
		Pres_UPR_Kluch = KluchPrec::Pr_105_175;
		AMP_POn_Kluch = 1<<15;
		//AMP_SW3_Kluch
		GET1 = new HMC700(2350,0x5,48,100);
		GET2 = new HMC700(2300,0x5,48,100);
		FrGet1 = 2565;
        FrGet1 = 2300;
	}
 KanalDGUKV::~KanalDGUKV()
	{
		//Freal = 10;
	}
 void KanalDGUKV::AmplifSET(bool Amplif)
 {   AmpSET = Amplif;
	 if (FregIN>=99)
	 {
		 if (Amplif)
			 {
				  LNA =  KluchAmplSW3::SW3_LNA_ON;
			 }
			  else
			 {
				  LNA =  KluchAmplSW3::SW3_LNA_Off;
			 }
	 }
	 else
	 {
	  LNA =  KluchAmplSW3::SW3_LNA_Off;
	  AmpSET = false;
	 }
 }

 void KanalDGUKV::WriteFregIN(double freqCR, int Kanal)
{      if (Kanal==1||Kanal==2)
	{
			KanalNum_B_Mod = Kanal;
	} else
	   {
			KanalNum_B_Mod = 1;
	   }
		 Freal = freqCR;
		 FregIN = floor(0.5 + freqCR/0.5);
		 FregIN =  FregIN * 0.5;

		if (Freal>=100)
		{
				FsSperenosom();
		}
		else {   AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_32_105;
				 PC2_Kluch = KluchPC2::PC2_32_105;

					if (Freal <= 50)
				{
				AMP_SW2_Kluch =  KluchAmplSW2::SW2_32_50;
 				}
				if (Freal > 70 )
				{
				AMP_SW2_Kluch =  KluchAmplSW2::SW2_70_105;
				}
				if (Freal > 50 && Freal <= 70)
				{
				AMP_SW2_Kluch =  KluchAmplSW2::SW2_50_70;
				}
				  FsigPC1 = Freal;//Fpc140 = FsigPC1;

				  
		}
     KanalDGUKV::WriteFrPC1(FsigPC1);

}
 void KanalDGUKV::FsBolshe1830()
		 {
		  Fpc1 = 735;
		  FrGet1 = FregIN + Fpc1;//2 * floor(0.5 + (FregIN + Fpc1) / 2);
		  PC1_Kluch = KluchPC1::PC1_1815_3200; //Pc1_kluch_PCH1 = (UInt32)PC1UPR.pc1_735;
		  FsigPC1 =  FrGet1 - Freal;
		  //KanalDGUKV::WriteFrPC1(FsigPC1);

				if (Freal <= 2040)
				{
				Pres_UPR_Kluch = KluchPrec::Pr_1830_2040;
				}
				if (Freal > 2040 && Freal <= 2320)
				{
				Pres_UPR_Kluch = KluchPrec::Pr_2040_2320;
				}
				if (Freal > 2320 && Freal <= 2600)
				{
				Pres_UPR_Kluch =  KluchPrec::Pr_2320_2600;
				}
				if (Freal > 2600 && Freal <= 2880)
				{
				Pres_UPR_Kluch =  KluchPrec::Pr_2600_2880;
				}
				if (Freal > 2880 && Freal <= 3230)
				{
				Pres_UPR_Kluch =  KluchPrec::Pr_2880_3230;
				}

		 }
 void KanalDGUKV::FsMenshe1215()
		 {
		 Fpc1 = 2440;
		 FrGet1 = FregIN + Fpc1;//2 * floor(0.5 + (FregIN + Fpc1) / 2);
		 FsigPC1 =  FrGet1 - Freal;
		 PC1_Kluch = KluchPC1::PC1_105_1215;


				if (Freal > 825 && Freal <= 1215)
				{
				Pres_UPR_Kluch =  KluchPrec::Pr_805_1215;
				}
				if (Freal > 525 && Freal <= 825)
				{
				Pres_UPR_Kluch =  KluchPrec::Pr_525_805;
				}
				if (Freal > 315 && Freal <= 525)
				{
				Pres_UPR_Kluch =  KluchPrec::Pr_315_525;
				}
				if (Freal > 175 && Freal <= 315)
				{
				Pres_UPR_Kluch =  KluchPrec::Pr_175_315;
				}
				if (Freal > 99.9 && Freal <= 175)
				{
				if (PolosaPC2==70)
				{
				 PC1_Kluch = KluchPC1::PC1_105_175_OB;
				 PC2_Kluch = KluchPC2::PC2_105_175_OB;
				 FsigPC1 = Freal;
				}
				Pres_UPR_Kluch =  KluchPrec::Pr_105_175;
				}
				//KanalDGUKV::WriteFrPC1(FsigPC1);
		 }
 void KanalDGUKV::FsBolshe1215()
 {          Fpc1 = 1035;
			FrGet1 = FregIN + Fpc1;//2 * floor(0.5 + (FregIN + Fpc1) / 2);
			FsigPC1 =  FrGet1 - Freal;
			PC1_Kluch = KluchPC1::PC1_1215_1815;
			//KanalDGUKV::WriteFrPC1(FsigPC1);



			if (Freal <= 1410)
			{
				Pres_UPR_Kluch =  KluchPrec::Pr_1215_1410;
			}
			if (Freal > 1410 && Freal <= 1620)
			{
				Pres_UPR_Kluch =  KluchPrec::Pr_1410_1620;
			}
			if (Freal > 1620 && Freal <= 1830)
			{
				Pres_UPR_Kluch =  KluchPrec::Pr_1620_1830;
			}
			if (Freal > 1830 && Freal <= 2040)
			{
				Pres_UPR_Kluch = KluchPrec::Pr_1830_2040;
			}


		 }
 void KanalDGUKV::PC1_2440 ()
 {              PC1_Kluch = KluchPC1::PC1_105_1215;
				PC2_Kluch = KluchPC2::PC2_105_1215;
				FrGet2 = (floor((FsigPC1 - 140) * 2))/2; //0.5*Math.Floor((fget1 - FAktual - 140) * 2)
				Fsint2 = FrGet2;					     //Fsint2 = Fget2;
				FsigPC2 = FsigPC1 - FrGet2; 			 //Fpc140 = fsigPC1 - Fget2;
 }
 void KanalDGUKV::WriteFrPC1(double freqPC1)
 {     FsigPC1 = freqPC1;

 if ( freqPC1>=2439 && freqPC1<=2441)
			 {
							  KanalDGUKV::PC1_2440();
									//FsPC2Menshe1215();
									//Get2_pitKluch175 = (UInt32)Kommutator.vkl;//Управление ВХ2 ВКЛ
									//Pc2_kluch105 = (UInt32)Kommutator.vikl;//Управление ВХ3 ВЫКЛ(в 1 отсутствует )
									//Get2_div_kluch = (UInt32)PC2DEL.delit;//Для версии 2 и 3(в 1 два бита c Pc2_kluch105 )
									//FrGet2 = (floor((FsigPC1 - 140) * 2))/2; 0.5*Math.Floor((fget1 - FAktual - 140) * 2)
									//Fsint2 = FrGet2;
									//FsigPC2 = FsigPC1 - FrGet2;
									 }
								   //	else
									// {
										//FsPC1TUP();
										//Get2_pitKluch175 = (UInt32)Kommutator.vikl;//Управление ВХ2 ВКЛ
										//Pc2_kluch105 = (UInt32)Kommutator.vikl;//Управление ВХ3 ВЫКЛ(в 1 отсутствует )
										//Get2_div_kluch = (UInt32)PC2DEL.fund35;
										//FsigPC1 = 150;
									 //	FsigPC2 = FsigPC1;//Fpc140 = FsigPC1;
									// }
									if ( freqPC1>32 && freqPC1<=99.8)
										{
										PC2_Kluch = KluchPC2::PC2_32_105;//Pc2In105();
										//Get2_pitKluch175 = (UInt32)Kommutator.vikl;//Управление ВХ2 ВКЛ
										//Pc2_kluch105 = (UInt32)Kommutator.vkl;//Управление ВХ3 ВЫКЛ(в 1 отсутствует )
										FsigPC2 = FsigPC1;//Fpc140 = FsigPC1;
										}
									 if ( freqPC1>99.8 && freqPC1<=175)
									 {
										 if (PolosaPC2==70)
										 {
										 PC1_Kluch = KluchPC1::PC1_105_175_OB;
										 PC2_Kluch = KluchPC2::PC2_105_175_OB;
										 //Pc2In175();
										 //Get2_pitKluch175 = (UInt32)Kommutator.vikl;//Управление ВХ2 ВКЛ
										 //Pc2_kluch105 = (UInt32)Kommutator.vikl;//Управление ВХ3 ВЫКЛ(в 1 отсутствует )
										 FsigPC2 = FsigPC1;//Fpc140 = FsigPC1;
										 }
										 else
										 {
										 KanalDGUKV::PC1_2440();
										 }

									 }
									 if (( freqPC1>=733 && freqPC1<=737)||( freqPC1>=1033 && freqPC1<=1037))
									 {
									   	PC2_Kluch = KluchPC2::PC2_1215_1815;
										//FsPC2Bolshe1215();
										//Get2_pitKluch175 = (UInt32)Kommutator.vkl;//Управление ВХ2 ВКЛ
										//Pc2_kluch105 = (UInt32)Kommutator.vikl;//Управление ВХ3 ВЫКЛ(в 1 отсутствует )
										//Get2_div_kluch = (UInt32)PC2DEL.fund35;//Для версии 2 и 3(в 1 два бита c Pc2_kluch105 )
										Fsint2 = floor((FsigPC1 + 140) * 2);//0.5*floor((fget1 - FAktual - 140) * 2)
										FrGet2 = Fsint2/2;//Fget2 = Fsint2 / 2;
										FsigPC2 = FrGet2 - FsigPC1;//Fpc140 = Fget2 - FsigPC1;

									 }

 }
 void KanalDGUKV::FsSperenosom()
			  {
			  KanalDGUKV::AmplifSET(AmpSET);

			  AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_105_3200;
								/*	private void FSbolshe105() {
								USIL_kluch_diapazon = (UInt32)Usil_FilKOM.KV105__3200;
								Pres_AT1_db = Ukv_ATT1;
								Usil_AT3_db = (UInt32)ATT_dB.att_31_5;
								Usil_AT4_db = (UInt32)ATT_dB.att_31_5;
								}        */
		if (Freal>1830)
			  {
				FsBolshe1830();
			  }
			  else
			  {
				  if (Freal<1215)
				  {
					FsMenshe1215();
				  }
				   else
				  {
					FsBolshe1215();
				  }
			  }
			//  KanalDGUKV::WriteFrPC1(FsigPC1);
			  }
 int KanalDGUKV::LoadKL(int div)
{    int i;
	 int  SW_SW;
 if (div >= 0 && div < 8)
   {
	 i = div;

   }
   else
   {
	i = 0;
   }
	switch (i)
   {
	 case 0:
	 if (KanalNum_B_Mod==1)
	 SW_SW = AdrRegPX2::Ch1_Amp_POn + AMP_POn_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_POn + AMP_POn_Kluch;
	 break;
	 case 1:
	 if (KanalNum_B_Mod==1)
	 SW_SW = AdrRegPX2::Ch1_Amp_Sw2 + AMP_SW2_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_Sw2 + AMP_SW2_Kluch;break;
	 case 2:
	 if (KanalNum_B_Mod==1)
	 SW_SW = AdrRegPX2::Ch1_Amp_Sw3 + LNA+AMP_SW3_Bolshe105;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_Sw3 + LNA+AMP_SW3_Bolshe105;break;
	 case 3:
	 if (KanalNum_B_Mod==1)
	 SW_SW = AdrRegPX2::Ch1_Amp_Sw1 + AMP_SW1_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_Sw1 + AMP_SW1_Kluch;break;
	 case 4:
	 if (KanalNum_B_Mod==1)
	 SW_SW =  AdrRegPX2::Ch1_Pres_UPR + Pres_UPR_Kluch;
	 else
	 SW_SW =  AdrRegPX2::Ch2_Pres_UPR + Pres_UPR_Kluch;break;
	 case 5:
	 if (KanalNum_B_Mod==1)
	 SW_SW = AdrRegPX2::Ch1_Pch1_Sw  + PC1_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Pch1_Sw  + PC1_Kluch;break;
	 case 6:
	 if (KanalNum_B_Mod==1)
	 SW_SW = AdrRegPX2::Ch1_Pch2_Sw  + PC2_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Pch2_Sw  + PC2_Kluch;break;

	 default : SW_SW = AdrRegPX2::Ch1_Pch2_Sw  + PC2_Kluch;break;

   }
   SW_SW = TipUstrPX2::TipPerekl + SW_SW;
	return  SW_SW;
}
 void KanalDGUKV::ATT1_SET(double DB)
{
	/*
	   int i;
		 int  ATT_AT;
  */
 if (DB >= 0 && DB <= 63)
   {
	Pres_Att = Amp_Att3 = 	Amp_Att1 = ATT_pervi = (int)(DB) <<14;
   }
   else
   {
	Pres_Att = Amp_Att3 = 	Amp_Att1 = ATT_pervi = 30 <<14;
   }
}
 int KanalDGUKV::LoadATT(int div)
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
	 ATT_db = AdrRegATT::Ch1_Amp_Att1 + Amp_Att1;break;
	 case 1:
	 ATT_db = AdrRegATT::Ch1_Amp_Att2 + Amp_Att2;break;
	 case 2:
	 ATT_db = AdrRegATT::Ch1_Amp_Att3 + Amp_Att3;break;
	 case 3:
	 ATT_db = AdrRegATT::Ch1_Amp_Att4 + Amp_Att4;break;
	 case 4:
	 ATT_db = AdrRegATT::Ch1_Pres_Att + Pres_Att;break;
	 case 5:
	 ATT_db = AdrRegATT::Ch1_Pch1_Att1 + Pch1_Att1;break;
	 case 6:
	 ATT_db = AdrRegATT::Ch1_Pch1_Att2 + Pch1_Att2;break;
	 default : ATT_db = AdrRegATT::Ch2_Pch1_Att2 + Pch1_Att2;break;

   }


	 else
		switch (i)
   {
	 case 0:
	 ATT_db = AdrRegATT::Ch2_Amp_Att1 + Amp_Att1;break;
	 case 1:
	 ATT_db = AdrRegATT::Ch2_Amp_Att2 + Amp_Att2;break;
	 case 2:
	 ATT_db = AdrRegATT::Ch2_Amp_Att3 + Amp_Att3;break;
	 case 3:
	 ATT_db = AdrRegATT::Ch2_Amp_Att4 + Amp_Att4;break;
	 case 4:
	 ATT_db = AdrRegATT::Ch2_Pres_Att + Pres_Att;break;
	 case 5:
	 ATT_db = AdrRegATT::Ch2_Pch1_Att1 + Pch1_Att1;break;
	 case 6:
	 ATT_db = AdrRegATT::Ch2_Pch1_Att2 + Pch1_Att2;break;
	 default : ATT_db = AdrRegATT::Ch2_Pch1_Att2 + Pch1_Att2;break;

   }


  //****************************************************************

   ATT_db = TipUstrPX2::TipATT + ATT_db;
	return  ATT_db;
}
 void KanalDGUKV::ATT2_SET(double DB)
	   {
   if (DB >= 0 && DB <= 63)
   {
	Pch1_Att1 = Pch1_Att2 = Amp_Att2 = 	Amp_Att4 = ATT_vtoroi = (int)(DB) <<14;
   }
   else
   {
	Pch1_Att1 = Pch1_Att2 = Amp_Att2 = 	Amp_Att4 = ATT_vtoroi = 15 <<14;
   }
	   }

double KanalDGUKV::FreqFout(){
return FsigPC2;
}
//--------------------------------------------------------------
DWORD KanalDGUKV::LoadGET1H(){
  DWORD SW = 0;
	if (true) {
	   SW = TipUstrPX2::Fc1_Ch1;
  } else {
	   SW = TipUstrPX2::Fc1_Ch2;
  }

}
DWORD KanalDGUKV::LoadGET2H(){
if (KanalNum_B_Mod) {
	TipUstrPX2::Fc2_Ch1;

}   else {
	TipUstrPX2::Fc2_Ch2;
  }

}
//--------------------------------------------------------------
DWORD KanalDGUKV::LoadGET1(int Reg){
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
/*
    	switch (i)
	   {
    	 case 0:
    	 SW_SW =GET1->RegLoad700(i); break;
    	 case 1:
    	 SW_SW =GET1->RegLoad700(i);break;
		 default:SW_SW =GET1->RegLoad700(i);break;
	   }
*/
	return  GET1->RegLoad700(i);
}
DWORD KanalDGUKV::LoadGET2(int Reg){
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
/*
    	switch (i)
	   {
    	 case 0:
    	 SW_SW =GET1->RegLoad700(i); break;
    	 case 1:
    	 SW_SW =GET1->RegLoad700(i);break;
		 default:SW_SW =GET1->RegLoad700(i);break;
	   }
*/
	return  GET2->RegLoad700(i);
}
#pragma package(smart_init)
