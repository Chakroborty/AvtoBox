//---------------------------------------------------------------------------


#pragma hdrstop

#include "HMC700.h"
#include <math.h>
//---------------------------------------------------------------------------


  HMC700::HMC700(double F,int I,int N,double Ref)
  {

	Nref = N;
	Nakt = N;
	R = 2;
	Xtal = Ref; //MÃåðö
	CurRef = CurSet = I;

	Reg00 = 1;
	Reg01 = 0x101;


	Reg05 = 0;

	Reg06 = 0x842C87;
	Reg07 = 0x180400;
	Reg08 = 0x31DF;   //int CpEn;   Reg 08h Analog EN Register


	Reg09ost=0x201;
	RegA=0;
	RegB=0x78; //     Reg 0Bh PFD Register
	RegC = 0;
	RegD = 0;
	RegE = 0;
	RegF = 0;
	SetFreq(F);
  }
  HMC700::~HMC700()
  {


  }

  int HMC700::RegLoad700(int Reg)
  {
		 int  SW_SW;
         SW_SW = 0;
		switch (Reg)
   {

	 case 0:

	 SW_SW = Reg00;break;

	 case 1:

	 SW_SW = 0X1<<24|Reg01;break;//

	 case 2:

	 SW_SW = 0X2<<24|Reg02;break;//

	 case 3:

	SW_SW = 0X3<<24|Reg03;break;

	 case 4:

	 SW_SW = 0X4<<24|Reg04;break;

	 case 5:

	 SW_SW = 0X5<<24|Reg05;break; //

	 case 6:

	 SW_SW = 0X6<<24|Reg06;break;//

	 case 7:

	 SW_SW = 0X7<<24|Reg07;break;//

	 case 8:

	 SW_SW = 0X8<<24|Reg08;break;//

	 case 9:

	 SW_SW = 0X9<<24|CurSet<<21|CurSet<<18|Reg09ost;break;
	 case 10:

	 SW_SW = 0XA<<24|RegA;break;//

	 case 11:

	  SW_SW = 0XB<<24|RegB;break;   // RegB

	  case 12:

	 SW_SW = 0XC<<24|RegC;break;

	 case 13:

	 SW_SW = 0XD<<24|RegD;break;

	 case 14:

	 SW_SW = 0XE<<24|RegE;break;

	 case 15:
	 SW_SW = 0XF<<24|RegF;break;



	 default : SW_SW = Reg00;break;

   }

	return  SW_SW;
  }
  void HMC700::SetFreq(double fsint)
  {  R = 1;
   if (fsint>=1 && fsint<=8000)
   {
	   FregSIN = fsint;
   }
	  Nakt = FregSIN*R/Xtal;
	  if (Nakt<36)
	  {
		R= R+1;
		Nakt = FregSIN*R/Xtal;
	  }
			/*
		  if (Nakt>74)
			  {
			  if (R>1) {
					R= R-1;
				}
				Nakt = FregSIN*R/Xtal;
			  }
	  */
	   CurSet = floor(0.3 + CurRef * Nakt/Nref);
			  if (CurSet<1) {
		   CurSet = 1;
	   }
			  if (CurSet>7) {
		   CurSet = 7;
	   }
	Reg02 = R;
	Reg03 = Nint = floor(Nakt);
	Reg04 = Nfrak = floor(0.5 + pow(2.0,24)*(Nakt - Nint));//


  }
  void HMC700::SetDFreq(double Fsint,double Fop)
  {               if (Fsint>Fop)
		{    Fdiv = Fsint-Fop;
			 Polarity = 0;

		} else
		{    Fdiv = Fop - Fsint;
			 Polarity = 1;
		}
         	switch(Polarity)
		{case 0:RegB &=~(1<<4);break; //     Reg 0Bh PFD Register
		 case 1:RegB |=(1<<4);break; //     Reg 0Bh PFD Register
		}
//  If the VCO input is above 4GHz then the 8GHz fixed RF divide-by-2 should be used, “Reg 08h”[19] = 1. In this case the
//total division range is restricted to even numbers over the range 2*(2^19-5) (1,048,566) to 40.

			while (Fdiv/R >80)
		{         if (R==1)
			{
				 R=2;
			} else
			{
				 R=R+2;
			}
		}
         //Divide by 2 for operation > 4GHz, “Reg 08h”[19] = 1, < 4GHz = 0
			switch(R)
			{case 1:CurSet = 3;break;
			 case 2:CurSet = 5;break;
			 case 4:CurSet = 10;break;
			 case 8:CurSet = 15;break;
			 default: CurSet = 8;break;
			}

	Nakt = Fop*R/Fdiv;
	Reg02 = R;
	Reg03 = Nint = floor(Nakt);
	Reg04 = Nfrak = floor(0.5 + pow(2.0,24)*(Nakt - Nint));//
  }
  void HMC700::ParamSet(int Pol,int Cur,int CP)
  {

		CpEn = CP;
		switch(CpEn)
		{case 0:CurSet = 0;
				RegB &=~(1<<5);
				RegB &=~(1<<6);break;//int CpEn;   Reg 08h Analog EN Register
		 case 1:CurSet = Cur;
				RegB |=(1<<5);
				RegB |=(1<<6);break;//int CpEn;   Reg 08h Analog EN Register
		}
						if (Cur==0)
		{
				CurSet = 0;
				RegB &=~(1<<5);
				RegB &=~(1<<6);
		} else
		{

		}

		Polarity = Pol;
		switch(Polarity)
		{case 0:RegB &=~(1<<4);break; //     Reg 0Bh PFD Register
		 case 1:RegB |=(1<<4);break; //     Reg 0Bh PFD Register

		}

	//int CpEn;   Reg 08h Analog EN Register
	// Polarity;Reg 0Bh PFD Register

  }
double HMC700::GetR()
{
  return R;
}
double HMC700::GetN()
{
   return Nint;
}
double HMC700::GetFrak()
{
   return Nfrak;
}
double HMC700::GetPFD()
{
   return Fdiv/R;
}

  #pragma package(smart_init)
