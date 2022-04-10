//---------------------------------------------------------------------------


#pragma hdrstop

#include "KanalCRPU.h"
#include <math.h>
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
 KanalCRPU::KanalCRPU(int Mod_kanalNum, int Blok_kanalNum, double Polosa)
	{   KanalNum_B_Blok = Blok_kanalNum;
		KanalNum_B_Mod = Mod_kanalNum;
		PolosaPC2 =  Polosa;
		KanalNum_B_Mod = Mod_kanalNum;
		AmpSET = false;
		Ispoln = 1;
		AMP_SW1_Kluch = KluchAmplSW1::SW1_15_25;
		AMP_SW2_Kluch = KluchAmplSW2::SW2_32_50;
		LNA = KluchAmplSW3::SW3_LNA_Off;
		AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_105_3200;
	   //	AMP_SW3_Kluch = AMP_POn_Kluch |  AMP_SW3_Bolshe105;

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
 KanalCRPU::~KanalCRPU()
	{
		//Freal = 10;
	}
 void KanalCRPU::AmplifSET(bool Amplif)
 {   AmpSET = Amplif;
	 if (FregIN>=105)
	 {
					if (Amplif)
		 {
					switch(Ispoln)
			  {
				case 0:LNA =  KluchAmplSW3::SW3_LNA_ONOKP;break;
				case 1:LNA =  KluchAmplSW3::SW3_LNA_ON;break;
			  }
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

void KanalCRPU::WriteFregIN(double freqCR, int Kanal)
{      if (Kanal>=0&Kanal<=1)
	{
			KanalNum_B_Mod = Kanal;
	} else
	{
		KanalNum_B_Mod = 0;
	}
		 Freal = freqCR;
		 FregIN = floor(0.5 + freqCR/0.5);
		 FregIN =  FregIN * 0.5;

		if (Freal>105)
		{


				FsSperenosom();
				  


		}
		else
		{   //AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_32_105;

               	switch(Ispoln)
			  {
				case 0:AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_32_105OKP;break;
				case 1:AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_32_105;break;
			  }


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

				   /*	private void FsMenshe105() {

								Usil_AT3_db = Ukv_ATT1;
								Usil_AT4_db = Ukv_ATT2;
								FsigPC1 =  fsig;

							}
			1-2,5 ÌÃö	216 -	1000010110
			2,5-5 ÌÃö	206 -	1000000110
			5-9 ÌÃö	    21À -	1000011010
			9-16 ÌÃö	20À -	1000001010
			16-32 ÌÃö	212 -	1000010010
			1-32 ÌÃö	202 -	1000000010
			32-50 ÌÃö	2À1 -	1010100001
			50-70 ÌÃö	2Ñ1 -	1011000001
			70-105 ÌÃö	311 -	1100010001
			 Ï×1
			 105-175	   0X0F;
			 175-1215	   0X74;
			 1215-1830	   0X71;
			 1830-3200	   0X7A;
			 Ï×2
			 105-175	   0X1;
			 175-1215	   0XC;
			 1215-1830	   0XA;
			 1830-3200	   0XA;

							 */
		}
	 KanalCRPU::WriteFrPC1(FsigPC1);

}
 void KanalCRPU::FsBolshe1830()
		 {
		  Fpc1 = 735;
		  //FrGet1 = 2 * floor(0.5 + (FregIN + Fpc1) / 2);
		  FrGet1 = FregIN + Fpc1;
		  PC1_Kluch = KluchPC1::PC1_1815_3200; //Pc1_kluch_PCH1 = (UInt32)PC1UPR.pc1_735;
		  FsigPC1 =  FrGet1 - Freal;
		  //KanalCRPU::WriteFrPC1(FsigPC1);

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
 void KanalCRPU::FsMenshe1215()
		 {
		 Fpc1 = 2440;
		 //FrGet1 = 2 * floor(0.5 + (FregIN + Fpc1) / 2);
		 FrGet1 = FregIN + Fpc1;
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
				if (Freal > 105 && Freal <= 175)
				{
				if (PolosaPC2==70)
				{
				 PC1_Kluch = KluchPC1::PC1_105_175_OB;
				 PC2_Kluch = KluchPC2::PC2_105_175_OB;
				 FsigPC1 = Freal;
				}
				Pres_UPR_Kluch =  KluchPrec::Pr_105_175;
				}
				//KanalCRPU::WriteFrPC1(FsigPC1);
		 }
 void KanalCRPU::FsBolshe1215()
 {          Fpc1 = 1035;
			//FrGet1 = 2 * floor(0.5 + (FregIN + Fpc1) / 2);
            FrGet1 = FregIN + Fpc1;
			FsigPC1 =  FrGet1 - Freal;
			PC1_Kluch = KluchPC1::PC1_1215_1815;
			//KanalCRPU::WriteFrPC1(FsigPC1);



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
 void KanalCRPU::PC1_2440 ()
 {              PC1_Kluch = KluchPC1::PC1_105_1215;
				PC2_Kluch = KluchPC2::PC2_105_1215;
				FrGet2 = (floor((FsigPC1 - 140) * 2))/2; //0.5*Math.Floor((fget1 - FAktual - 140) * 2)
				Fsint2 = FrGet2;					     //Fsint2 = Fget2;
				FsigPC2 = FsigPC1 - FrGet2; 			 //Fpc140 = fsigPC1 - Fget2;
 }
 void KanalCRPU::WriteFrPC1(double freqPC1)
 {     FsigPC1 = freqPC1;

 if ( freqPC1>=2439 && freqPC1<=2441)
			 {
							  KanalCRPU::PC1_2440();
									//FsPC2Menshe1215();
									//Get2_pitKluch175 = (UInt32)Kommutator.vkl;//Óïðàâëåíèå ÂÕ2 ÂÊË
									//Pc2_kluch105 = (UInt32)Kommutator.vikl;//Óïðàâëåíèå ÂÕ3 ÂÛÊË(â 1 îòñóòñòâóåò )
									//Get2_div_kluch = (UInt32)PC2DEL.delit;//Äëÿ âåðñèè 2 è 3(â 1 äâà áèòà c Pc2_kluch105 )
									//FrGet2 = (floor((FsigPC1 - 140) * 2))/2; 0.5*Math.Floor((fget1 - FAktual - 140) * 2)
									//Fsint2 = FrGet2;
									//FsigPC2 = FsigPC1 - FrGet2;
			 }
								   //	else
									// {
										//FsPC1TUP();
										//Get2_pitKluch175 = (UInt32)Kommutator.vikl;//Óïðàâëåíèå ÂÕ2 ÂÊË
										//Pc2_kluch105 = (UInt32)Kommutator.vikl;//Óïðàâëåíèå ÂÕ3 ÂÛÊË(â 1 îòñóòñòâóåò )
										//Get2_div_kluch = (UInt32)PC2DEL.fund35;
										//FsigPC1 = 150;
									 //	FsigPC2 = FsigPC1;//Fpc140 = FsigPC1;
									// }
									if ( freqPC1>32 && freqPC1<=105)
										{
										PC2_Kluch = KluchPC2::PC2_32_105;//Pc2In105();
										//Get2_pitKluch175 = (UInt32)Kommutator.vikl;//Óïðàâëåíèå ÂÕ2 ÂÊË
										//Pc2_kluch105 = (UInt32)Kommutator.vkl;//Óïðàâëåíèå ÂÕ3 ÂÛÊË(â 1 îòñóòñòâóåò )
										FsigPC2 = FsigPC1;//Fpc140 = FsigPC1;
										}
									 if ( freqPC1>105 && freqPC1<=175)
									 {
										 if (PolosaPC2==70)
										 {
										 PC1_Kluch = KluchPC1::PC1_105_175_OB;
										 PC2_Kluch = KluchPC2::PC2_105_175_OB;
										 //Pc2In175();
										 //Get2_pitKluch175 = (UInt32)Kommutator.vikl;//Óïðàâëåíèå ÂÕ2 ÂÊË
										 //Pc2_kluch105 = (UInt32)Kommutator.vikl;//Óïðàâëåíèå ÂÕ3 ÂÛÊË(â 1 îòñóòñòâóåò )
										 FsigPC2 = FsigPC1;//Fpc140 = FsigPC1;
										 }
										 else
										 {
										 KanalCRPU::PC1_2440();
										 }

									 }
									 if (( freqPC1>=733 && freqPC1<=737)||( freqPC1>=1033 && freqPC1<=1037))
									 {
										PC2_Kluch = KluchPC2::PC2_1215_1815;
										//FsPC2Bolshe1215();
										//Get2_pitKluch175 = (UInt32)Kommutator.vkl;//Óïðàâëåíèå ÂÕ2 ÂÊË
										//Pc2_kluch105 = (UInt32)Kommutator.vikl;//Óïðàâëåíèå ÂÕ3 ÂÛÊË(â 1 îòñóòñòâóåò )
										//Get2_div_kluch = (UInt32)PC2DEL.fund35;//Äëÿ âåðñèè 2 è 3(â 1 äâà áèòà c Pc2_kluch105 )
										Fsint2 = floor((FsigPC1 + 140) * 2);//0.5*floor((fget1 - FAktual - 140) * 2)
										FrGet2 = Fsint2/2;//Fget2 = Fsint2 / 2;
										FsigPC2 = FrGet2 - FsigPC1;//Fpc140 = Fget2 - FsigPC1;

									 }

 }
 void KanalCRPU::FsSperenosom()
{
	KanalCRPU::AmplifSET(AmpSET);
//	AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_105_3200;

			switch(Ispoln)
  {
	case 0: AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_105_3200OKP; break;
	case 1: AMP_SW3_Bolshe105 = KluchAmplSW3::SW3_105_3200; break;
  }

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
	//  KanalCRPU::WriteFrPC1(FsigPC1);
}
 int KanalCRPU::LoadKL(int div)
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
	 if (KanalNum_B_Mod==0)
	 SW_SW = AdrRegPX2::Ch1_Amp_POn + AMP_POn_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_POn + AMP_POn_Kluch;break;
	case 1:
	 if (KanalNum_B_Mod==0)
	 SW_SW = AdrRegPX2::Ch1_Amp_Sw2 + AMP_SW2_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_Sw2 + AMP_SW2_Kluch;break;
	case 2:
	 if (KanalNum_B_Mod==0)
	 SW_SW = AdrRegPX2::Ch1_Amp_Sw3 + LNA+AMP_SW3_Bolshe105;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_Sw3 + LNA+AMP_SW3_Bolshe105;break;
	case 3:
	 if (KanalNum_B_Mod==0)
	 SW_SW = AdrRegPX2::Ch1_Amp_Sw1 + AMP_SW1_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Amp_Sw1 + AMP_SW1_Kluch;break;
	case 4:
	 if (KanalNum_B_Mod==0)
	 SW_SW =  AdrRegPX2::Ch1_Pres_UPR + Pres_UPR_Kluch;
	 else
	 SW_SW =  AdrRegPX2::Ch2_Pres_UPR + Pres_UPR_Kluch;break;
	case 5:
	 if (KanalNum_B_Mod==0)
	 SW_SW = AdrRegPX2::Ch1_Pch1_Sw  + PC1_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Pch1_Sw  + PC1_Kluch;break;
	case 6:
	 if (KanalNum_B_Mod==0)
	 SW_SW = AdrRegPX2::Ch1_Pch2_Sw  + PC2_Kluch;
	 else
	 SW_SW = AdrRegPX2::Ch2_Pch2_Sw  + PC2_Kluch;break;

	 default : SW_SW = AdrRegPX2::Ch1_Pch2_Sw  + PC2_Kluch;break;

   }
   SW_SW = TipUstrPX2::TipPerekl + SW_SW;
	return  SW_SW;
}
 void KanalCRPU::ATT1_SET(double DB)
{
	/*
	   int i;
		 int  ATT_AT;
  */
 if (DB >= 0 && DB <= 63)
   {
		Pres_Att =  (int)(DB) <<14;

		Amp_Att1 = Pres_Att;
		Amp_Att3 = Pres_Att;
		//Amp_Att2 = Pres_Att;Äîáàâëåííà    /* TODO : Ââîä  âñåõ ATT1 */
		ATT_pervi = Pres_Att;
   }
   else
   {
		Pres_Att = Amp_Att3 = 	Amp_Att1 = ATT_pervi = 30 <<14;
   }
}
 int KanalCRPU::LoadATT(int div)
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

   if (KanalNum_B_Mod==0)
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
 void KanalCRPU::ATT2_SET(double DB)
	   {
		   if (DB >= 0 && DB <= 63)
		   {
			
			ATT_vtoroi = (int)(DB) <<14;
			Pch1_Att1 =   ATT_vtoroi;
			Pch1_Att2 =  ATT_vtoroi;
			Amp_Att2 =   ATT_vtoroi;
			Amp_Att4 =  ATT_vtoroi;
		   }
		   else
		   {
			Pch1_Att1 = Pch1_Att2 = Amp_Att2 = 	Amp_Att4 = ATT_vtoroi = 15 <<14;
		   }
	   }

double KanalCRPU::FreqFout(){
return FsigPC2;
}
//--------------------------------------------------------------
DWORD KanalCRPU::LoadGET1H(){
  DWORD SW = 0;
	if (true) {
	   SW = TipUstrPX2::Fc1_Ch1;
  } else {
	   SW = TipUstrPX2::Fc1_Ch2;
  }

}
DWORD KanalCRPU::LoadGET2H(){
	if (KanalNum_B_Mod)
	{
		TipUstrPX2::Fc2_Ch1;

	}   else
	{
		TipUstrPX2::Fc2_Ch2;
	}

}
//--------------------------------------------------------------
DWORD KanalCRPU::LoadGET1(int Reg){
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
DWORD KanalCRPU::LoadGET2(int Reg){
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
