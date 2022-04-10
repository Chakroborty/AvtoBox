//---------------------------------------------------------------------------


#pragma hdrstop

#include "hmc839.h"
#include <math.h>
//---------------------------------------------------------------------------
 HMC839::HMC839(double F,int I,int N,double Ref)
 {
	//FregSIN = F;
	R = 1;
	Nref = N;
	Xtal = Ref; //ֳּונצ

	HMC839::SetFreq(F);
	Reg00 = 1<<5;
	Reg01 = 0x2;
	Reg02 = 0x1;
	Reg03 = 0x24;
	Reg04 = 0;

	Reg05 = regnum5::F2300;
	Reg052 = 0xAB95;
	Reg053 = 0xD11D;
	Reg054 = 0x5;

	Reg06=0x202F4A;
	Reg07=0x10D;
	Reg08=0x41BEFF;
	CurSet = I;
	Lmagn9 = 0x5F;//1011111
	L_Dir_UP = 0;
	L_Dir_DN = 1;
	HiKcp = 1;

	   //110101111110000001000000
	RegA=0x1105;
	RegB=0x78061;
	RegC=0x0;
	RegD = 0;

    RegF=0x81;



 }
 HMC839::~HMC839()
 {

 }
 void HMC839::SetFreq(double fsint)
 {   int a = 0;

  if (fsint >= 2100 && fsint <= 2410)
	  {
		FregSIN = fsint;//FreqAktual = freq;
		 a = 1;
		 Reg05 = regnum5::F2300;//Reg05 = (UInt32)regnum5.F2300;
								//Sw_g = 0x80;
		 Reg052 = 0xAB95;		//Reg052 = 0xAB95;

	  }
 if (fsint >= 1050 && fsint <= 1205) //1035
	  {
		FregSIN = fsint*2;// FreqAktual = freq*2;
		 a = 1;
		 Reg05 = regnum5::F1175;// Reg05 = (UInt32)regnum5.F1175;
		 Reg052 = 0xAB95;		// Reg052 = 0xAB95;
		 // Sw_g = 0x80;
	  }
 if (fsint >= 4200 && fsint <= 4820) //875
	  {
		FregSIN = fsint/2;		//FreqAktual = (freq*5)/2;
		 a = 1;
		 Reg05 = regnum5::F4200; //Reg05 = (UInt32)regnum5.F875;
		 Reg052 = 0xA395;		//Reg052 = 0xA395;
								//Sw_g = 0;
	  }

  if (a==0)
	  {
		FregSIN = 2300;
		 Reg05 = regnum5::F2300;//Reg05 = (UInt32)regnum5.F2300;
								//Sw_g = 0x80;
		 Reg052 = 0xAB95;		//Reg052 = 0xAB95;

	  }

	  Nakt = FregSIN*R/Xtal;
			if (Nakt<20) {
		  R = R*2;
		  Nakt = FregSIN*R/Xtal;
	  }
	  Nint = floor(Nakt);
	  //Nfrak = floor(0.5 + pow(2,24)*(Nakt - Nint));
	   Nfrak = floor(0.5 + pow(2.0,24)*(Nakt - Nint));
	  Reg02 = R;
	  Reg03 = Nint;
	  Reg04 = Nfrak;

	 /*          	set {
					freq = value;
							FreqAktual = (freq*5)/2;
							Reg05 = (UInt32)regnum5.F875;
							Reg052 = 0xA395;
							Sw_g = 0;
					 if (freq>1172)
					 {
						 FreqAktual = freq*2;
						 Reg05 = (UInt32)regnum5.F1175;
						 Reg052 = 0xAB95;
						 Sw_g = 0x80;
					 }
					 if (freq>2297)
					 {
						 FreqAktual = freq;
						 Reg05 = (UInt32)regnum5.F2300;
						 Sw_g = 0x80;
						 Reg052 = 0xAB95;
					 }
						NRasch = (freqAktual * refDiv) / xtal;
						Nint = Math.Floor(nRasch);
						Nfrak = Math.Round((decimal)Math.Pow(2, 24)*(nRasch - nint));
				} */
			}
 int HMC839::RegLoad839(int Reg)
  {
     	 int  SW_SW;
		switch (Reg)
   {

	 case 0:

	 SW_SW = Reg00;break;

	 case 1:

	 SW_SW = 0X2<<24|Reg02;break;

	 case 2:

	 SW_SW = 0X6<<24|Reg06;break;

	 case 3:

	 SW_SW = 0X9<<24|HiKcp<<23|L_Dir_DN<<22|L_Dir_UP<<21|Lmagn9<<14|CurSet<<7|CurSet;break;

	 case 4:

	 SW_SW = 0X5<<24|Reg05;break;

	 case 5:

	 SW_SW = 0X5<<24|Reg052;break;


	 case 6:

	 SW_SW = 0X5<<24|Reg053;break;

	 case 7:

	 SW_SW = 0X5<<24|Reg054;break;

	 case 8:
	 SW_SW = 0X1<<24|Reg01;break;

	 case 9:
	 SW_SW = 0X7<<24|Reg07;break;

 //**********************************************************************
	 case 10:
	 SW_SW = 0X8<<24|Reg08;break;


	 case 11:
	 SW_SW = 0XA<<24|RegA;break;


	  case 12:

	 SW_SW = 0XB<<24|RegB;break;

	 case 13:
	 SW_SW = 0XC<<24|RegC;break;


	 case 14:
	SW_SW = 0XD<<24|RegD;break;


	 case 15:
	  SW_SW = 0XF<<24|RegF;break;


//******************************************
	 case 16:
	SW_SW = 0X3<<24|Reg03;break;


	 case 17:
	SW_SW = 0X4<<24|Reg04;break;


	 default :  SW_SW = 0X3<<24|Reg03;break;

   }

	return  SW_SW;
  }

#pragma package(smart_init)
