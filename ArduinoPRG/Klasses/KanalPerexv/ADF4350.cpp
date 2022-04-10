//---------------------------------------------------------------------------


#pragma hdrstop
 #include <math.h>
#include "ADF4350.h"

//---------------------------------------------------------------------------
 ADF4350::ADF4350(double F,int I,int N,double Ref)
 {
	//FregSIN = F;
	R = 1;
	Nref = N;
	Xtal = Ref; //ֳּונצ


	Reg00 = 1<<5;
	Reg01 = 0x2;


	Reg05 = regnum5::F1raz;
	Reg052 = 0x2818;
	Reg053 = 0x60A0;
	Reg054 = 0x1628;
	Reg055 = 0x0;
	Reg06=regnum6::integer;


	Reg07 = 0x14D; //10000101001101   14D
	Reg08 = 0xC1BEFF;

	RegA = 0x2046; //0 1 01 00 011 100
	RegB = 0x78061;
	RegC = 0;
	RegD = 0;

	RegF = 0x81;
	CurSet = I;
	Lmagn9 = 0x5F;//1011111
	L_Dir_UP = 0;
	L_Dir_DN = 1;
	HiKcp = 1;
    RegF=0x81;
	ADF4350::SetFreq(F);


 }
 ADF4350::~ADF4350()
 {

 }
 void ADF4350::SetFreq(double fsint)
 {   int a = 0;

  if (fsint >= 1500 && fsint <= 3000)
	  {
		FregSIN = fsint;//FreqAktual = freq;
		 a = 1;
		 Reg05 = regnum5::F1raz;


	  }
 if (fsint >= 750 && fsint < 1500) //1035 fsint >= 25
	  {
		FregSIN = fsint*2;// FreqAktual = freq*2;
		 a = 1;
		 Reg05 = regnum5::F2raz;// Reg05 = (UInt32)regnum5.F1175;

	  }


  if (a==0)
	  {
		FregSIN = 2300;
		 Reg05 = regnum5::F1raz;//Reg05 = (UInt32)regnum5.F2300;

	  }

	  Nakt = FregSIN*R/Xtal;
			if (Nakt<20) {
		  R = R*2;
		  Nakt = FregSIN*R/Xtal;
	  }
	  Nint = floor(Nakt);
	  Nfrak = floor(0.5 + pow(2,24)*(Nakt - Nint));
	  Reg02 = R;
	  Reg03 = Nint;
	  Reg04 = Nfrak;

	  if (Nfrak == 0)
	   {
		Reg06 = regnum6::integer;      //integer = 0x100  0100000000

		Lmagn9 = 0;//1011111
		L_Dir_UP = 0;
		L_Dir_DN = 1;
		HiKcp = 0;


	   }
	   else
	   {
		Reg06 = regnum6::frak;   //frak = 0x17F  0101111111
		Lmagn9 = 0;  // 0x7F
		L_Dir_UP = 0;
		L_Dir_DN = 1;
		HiKcp = 0;
	   }
			}
 int ADF4350::RegLoad830(int Reg)
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
	 SW_SW = 0X5<<24|Reg055;break;
	 case 9:
	SW_SW = 0X1<<24|Reg01;break											;

	 case 10:
	SW_SW = 0X7<<24|Reg07;break;

 //**********************************************************************
	 case 11:
	 SW_SW = 0X8<<24|Reg08;break;
	   case 12:
	 SW_SW = 0XA<<24|RegA;break;
	 case 13:
	  SW_SW = 0XB<<24|RegB;break;

	 case 14:
	 SW_SW = 0XC<<24|RegC;break;
	 case 15:
	 SW_SW = 0XD<<24|RegD;break;







//******************************************
	 case 16:
	SW_SW = 0XF<<24|RegF;break;


	 case 17:

   SW_SW = 0X3<<24|Reg03;break;

	 case 18:

   SW_SW = 0X4<<24|Reg04;break;

	 default : SW_SW = Reg00;break;

   }

	return  SW_SW;
  }
 void ADF4350::SetFreq(double F,int I,double PFD,double Ref){
   R = Ref/PFD;
   Xtal = Ref; //ֳּונצ
   CurSet = I;
 SetFreq(F);
 }
#pragma package(smart_init)
