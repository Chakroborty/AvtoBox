//---------------------------------------------------------------------------


#pragma hdrstop
 #include <math.h>
#include "MAX2870.h"

//---------------------------------------------------------------------------
 MAX2870::MAX2870(double F,int I,int N,double Ref)
 {

	Xtal = Ref; //ֳּונצ




//  regnum0
	NF = 0;
	Nint = 100;
	Nfrak = 0;

//  regnum1
	CPOC = 0;
	CPL = 1;
	CPT = 0;
	P = 4095;
	Nmod = 4095;


// regnum2
	LDS = 0;
	SDN = 2;
	MUX = 6;
	DBR = 0;// Reference Doubler Mode  Sets reference doubler mode.  0 = Disable reference doubler  1 = Enable reference double
	RDIV2 = 0;
	R = 4;
	REG4DB = 0;
	CP = 15;
	LDF = 0;
	LDP = 0;
	PDP = 1;
	SHDN = 0;
	TRI = 0;
	RST = 0;


// regnum3

	VCO = 63;           //Manual selection of VCO and VCO sub-band when VAS is disabled.
	VAS_SHDN = 0;  //0 = VAS enabled
	RETUNE = 1;
	CDM  = 0;
	CDIV = 0;

// regnum4
	Res4=24;
	BS_MSBs = 1;
	FB = 1;           //Manual selection of VCO and VCO sub-band when VAS is disabled.
	DIVA = 1;
	BS = 244;
	Res42 = 0;
	BDIV  = 1;
	RFB_EN = 1;
	BPWR = 2;
	RFA_EN = 0;
	APWR = 3;


 //	regnum5


		F01 = 0;           //Manual selection of VCO and VCO sub-band when VAS is disabled.
		LD = 0;
		MUX5 = 0;






	MAX2870::SetFreq(F);


 }
 MAX2870::~MAX2870()
 {

 }
 double MAX2870::SetFreq(double fsint)
 {

		if (fsint >= 3000 && fsint <= 6000)
	{
		FregSIN = fsint;
		 DIVA = 0;
	}
		if (fsint >= 1500 && fsint < 3000)
	{
		FregSIN = fsint;
		 DIVA = 1;
	}

	   if (fsint >= 750 && fsint < 1500)
	{
		FregSIN = fsint;
		 DIVA = 2;
	}

	   if (fsint >= 375 && fsint < 750)
   {	FregSIN = fsint;
		 DIVA = 3;
   }
		if (fsint >= 187.5375 && fsint < 375)
   {	FregSIN = fsint;
		 DIVA = 4;
   }
		if (fsint >= 93.75 && fsint < 187.5)
   {	FregSIN = fsint;
		 DIVA = 5;
   }
		
		 if (fsint >= 46.875 && fsint < 93.75)
   {	FregSIN = fsint;
		 DIVA = 6;
   }
		  if (fsint >= 23.5 && fsint < 46.875)
   {	FregSIN = fsint;
		 DIVA = 7;
   }
	  Pfd = Xtal/ R;
	  Divison = Pfd/Nmod;
	  Nakt = floor(fsint/Divison+0.5);
	  FregSIN = Divison*Nakt;

	  Nint = floor(Nakt/Nmod);
	  Nfrak =Nakt-Nint*Nmod;




	  Nakt = FregSIN*R/Xtal;
			if (Nakt<20)
	  {

		  Nakt = FregSIN*R/Xtal;
	  }



	  if (Nfrak == 0)
	   {




	   }
	   else
	   {



	   }
	   return  FregSIN ;

 }
int MAX2870::RegLoad2870(int Reg)
  {
		 SW_SW = 0;

		switch (Reg)
   {

	case 0:

		SW_SW =  NF<<31|Nint<<15|Nfrak<<3;break;

	case 1:

		SW_SW =  CPOC<<31|CPL<<29|CPT<<27|P<<15|Nmod<<3|1;break;

	case 2:

		SW_SW =  LDS<<31|SDN<<29|MUX<<26|DBR<<25|RDIV2<<24|R<<14;

		SW_SW = SW_SW|REG4DB<<13|CP<<9|LDF<<8|LDP<<7|PDP<<6|SHDN<<5;

		SW_SW = SW_SW|TRI<<4|RST<<3|2;break;
	case 3:
		SW_SW =  VCO<<26|VAS_SHDN<<25|RETUNE<<24|CDM<<15|CDIV<<3|3;break;

	case 4:

		SW_SW = Res4<<26|BS_MSBs<<24|Res42<<10|FB<<23|DIVA<<20|BS<<12|BDIV<<9|RFB_EN<<8|BPWR<<6;
		SW_SW = SW_SW|RFA_EN<<5|APWR<<3|4;break;

	case 5:

		SW_SW =  F01<<24|LD<<22|MUX5<<18|5;break;



	default : SW_SW =NF<<31|Nint<<15|Nfrak<<3;break;

   }

	return  SW_SW;
  }

 void MAX2870::SetParam(int Pol,int Icp,int PowA,int PowB,int ADIV )
 {


		if (PowB==4)
	{
		RFB_EN=0;
	}   else
	{   RFB_EN = 1;
		BPWR  = PowB;
	}
			if (PowA==4)
	{
		 RFA_EN=0;
	}   else
	{
		RFA_EN = 1;
		APWR  = PowA;
	}
	/******************************CP*********************************/
				if (Icp==16)
		{  TRI =1;

		} else
		{   TRI =0;
			CP =  Icp;
		}
	/*******************************POL*****************************/
				PDP = Pol;
	/*******************************DIVA*****************************/
			 DIVA = ADIV;

 }
 void MAX2870::SetFreq(double F,int I,double PFD,double Ref)
 {
	//R = Ref/PFD;
	Xtal = Ref; //ֳּונצ
	CurSet = I;
	SetFreq(F);
 }
#pragma package(smart_init)
