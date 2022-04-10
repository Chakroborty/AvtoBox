//---------------------------------------------------------------------------


#pragma hdrstop
#include <math.h>
#include "HMC830.h"
#include "BitsU.h"


//---------------------------------------------------------------------------
 HMC830::HMC830(double F,int I,int N,double Ref)
 {
	//FregSIN = F;
	R = 1;
	Nref = N;
	Xtal = Ref; //МГерц


	Reg00 = 1<<5;
	Reg01 = 0x2;

	Reg050 = BIN24(00000000,00001011,10001000);//0xF88;
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
	CurSetH = I<<7;
	CurSetL = I;
	//---------------------------------ШУМ-10--------
	Lmagn9 = 0x7F;//1111111  
	L_Dir_UP = 1;   
	L_Dir_DN = 0;
	//HiKcp = 100;
	HiKcp = 1;
	//----------------------------------------------
	RegF=0x81;
	HMC830::SetFreq(F);


 }
 HMC830::~HMC830()
 {

 }
void HMC830::DIVOUTEN(int ENBL)
{

		switch(ENBL)
{
	case 0:
	//Reg050 &=~(1<<8);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:
	Reg050 &=~(1<<9);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:
//		Reg050 &=~(1<<10);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:
//		Reg050 &=~(1<<11);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:


	break;
	case 1:
//		Reg050 |=(1<<8); // Чтобы  записат ь  единицу  в  бит  N,   выполни:
	Reg050 |=(1<<9); // Чтобы  записат ь  единицу  в  бит  N,   выполни:
//		Reg050 |=(1<<10); // Чтобы  записат ь  единицу  в  бит  N,   выполни:
//		Reg050 |=(1<<11); // Чтобы  записат ь  единицу  в  бит  N,   выполни:



	break;

}
}
void HMC830::GAIN_RF(int GRF)
{
		if(GRF>=0 & GRF<4)
 {
	GainRF = GRF;
 }
 else
 {
	GainRF = 0;
 }

		switch(GainRF)
{
		case 0:
	Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
//	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
	Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
//	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:

		break;
		case 1:
//	Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
	Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
//	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
		break;
		case 2:
	Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
//	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
//	Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
		break;
		case 3:
//	Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
//	Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
		break;

	default:
	Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
//	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
	Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
//	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
	break;
}

}
void HMC830::Div_Gain(int DIvG)
{
		if(DIvG>=0 &DIvG <2)
 {
	GainDiv = DIvG;
 }
 else
 {
	GainDiv = 0;
 }
		switch(GainDiv)
{
					case 0:
		Reg050 &=~(1<<15);//Чтобы записать ноль в бит N, выполни:
	//	Reg050 |=(1<<15); //Чтобы записать единицу в бит N, выполни:

					break;
					case 1:
	//	Reg050 &=~(1<<15);//Чтобы записать ноль в бит N, выполни:
		Reg050 |=(1<<15); //Чтобы записать единицу в бит N, выполни:
					break;

					default:
	//	Reg050 &=~(1<<15);//Чтобы записать ноль в бит N, выполни:
		Reg050 |=(1<<15); //Чтобы записать единицу в бит N, выполни:
					break;
}



}
void HMC830::SetREF(double INREF, double INR)
{
R = floor(INR);
	
Xtal = INREF;

}
void HMC830::SetFreq(double fsint)
{   int a = 0;

if (fsint >= 1500 && fsint <= 3000)
  {
	FregSIN = fsint;//FreqAktual = freq;
	a = 1;
	Reg05 = BIN24(00000000,11100000,10010000); // regnum5::F1raz


  }
if (fsint >= 750 && fsint < 1500) //1035 fsint >= 25
  {
	FregSIN = fsint*2;// FreqAktual = freq*2;
	a = 1;
	Reg05 = BIN24(00000000,01100001,00010000);
	//Reg05 = BIN24(00000000,11100001,00010000);// Reg05 = (UInt32)regnum5.F1175;

  }
if (fsint >= 375 && fsint < 750) //1035 fsint >= 25
  {
	FregSIN = fsint*4;// FreqAktual = freq*2;
	a = 1;
	Reg05 = BIN24(00000000,11100010,00010000);// Reg05 = (UInt32)regnum5.F1175;

  }
if (fsint >= 187.5 && fsint < 375) //1035 fsint >= 25
  {
	FregSIN = fsint*8;// FreqAktual = freq*2;
	a = 1;
	Reg05 = BIN24(00000000,11100100,00010000);// Reg05 = (UInt32)regnum5.F1175;

  }
if (fsint >= 93.75 && fsint < 187.5) //1035 fsint >= 25      46,875      23,4375
  {
	FregSIN = fsint*16;// FreqAktual = freq*2;
	a = 1;
	Reg05 = BIN24(00000000,11101000,00010000);// Reg05 = (UInt32)regnum5.F1175;

  }

	if (fsint >= 46.875 && fsint < 93.75)
  {
	FregSIN = fsint*32;// FreqAktual = freq*2;
	a = 1;
	Reg05 = BIN24(00000000,11110000,00010000);// Reg05 = (UInt32)regnum5.F1175;

  }

if (fsint >= 23.4375 && fsint < 46.875) //1035 fsint >= 25      46,875
  {
	FregSIN = fsint*62;// FreqAktual = freq*2;
	 a = 1;
	 Reg05 = BIN24(00000000,11111111,00010000);// Reg05 = (UInt32)regnum5.F1175;

  }



if (a==0)
  {
	FregSIN = 2300;
	Reg05 = regnum5::F1raz;//Reg05 = (UInt32)regnum5.F2300;

  }

  Nakt = FregSIN*R/Xtal;
		if (Nakt<24)
  {
	  R = R*2;
	  Nakt = FregSIN*R/Xtal;
  }
  Nint = floor(Nakt);
  Nfrak = floor(0.5 + pow(2.0,24)*(Nakt - Nint));
  Reg02 = R;
  Reg03 = Nint;
  Reg04 = Nfrak;

  if (Nfrak == 0)
   {
	Reg06 = regnum6::integer;      //integer = 0x100  0100000000

	/*
		Lmagn9 = 0;//1011111
			L_Dir_UP = 0;
			L_Dir_DN = 1;
			HiKcp = 0;

	*/

   }
   else
   {
	Reg06 = regnum6::frak;   //frak = 0x17F  0101111111
//		Lmagn9 = 0;  // 0x7F
//		L_Dir_UP = 0;
//		L_Dir_DN = 1;
//		HiKcp = 0;
   }
}
long HMC830::RegLoad830(int Reg)
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
	SW_SW = 0X9<<24|HiKcp<<23|L_Dir_DN<<22|L_Dir_UP<<21|Lmagn9<<14|CurSetH|CurSetL;break;

	case 4:
	SW_SW = 0X5<<24|Reg050;break;       //4-9

	case 5:
	SW_SW = 0X5<<24|Reg05;break;

	case 6:
	SW_SW = 0X5<<24|Reg052;break;
	case 7:
	SW_SW = 0X5<<24|Reg053;break;

	case 8:
	SW_SW = 0X5<<24|Reg054;break;

	case 9:
	SW_SW = 0X5<<24|Reg055;break;

	case 10:
	SW_SW = 0X1<<24|Reg01;break											;

	case 11:
	SW_SW = 0X7<<24|Reg07;break;

	//**********************************************************************
	case 12:
	SW_SW = 0X8<<24|Reg08;break;

	case 13:
	SW_SW = 0XA<<24|RegA;break;

	case 14:
	SW_SW = 0XB<<24|RegB;break;

	case 15:
	SW_SW = 0XC<<24|RegC;break;

	case 16:
	SW_SW = 0XD<<24|RegD;break;

	//******************************************
	case 17:
	SW_SW = 0XF<<24|RegF;break;
	case 18:
	SW_SW = 0X3<<24|Reg03;break;
	case 19:
	SW_SW = 0X4<<24|Reg04;break;        //18,19


	default : SW_SW = Reg00;break;

}

return  SW_SW;
}
long HMC830::RGLoad830STR(int Reg)
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
	SW_SW = 0X9<<24|HiKcp<<23|L_Dir_DN<<22|L_Dir_UP<<21|Lmagn9<<14|CurSetH|CurSetL;break;

	case 4:
	SW_SW = 0X5<<24|Reg050;break;       //4-9

	case 5:
	SW_SW = 0X5<<24|Reg05;break;

	case 6:
	SW_SW = 0X5<<24|Reg052;break;
	case 7:
	SW_SW = 0X5<<24|Reg053;break;

	case 8:
	SW_SW = 0X5<<24|Reg054;break;

	case 9:
	SW_SW = 0X5<<24|Reg055;break;

	case 10:
	SW_SW = 0X3<<24|Reg03;break;
	case 11:
	SW_SW = 0X4<<24|Reg04;break;        //18,19


	case 12:
	SW_SW = 0X1<<24|Reg01;break											;

	case 13:
	SW_SW = 0X7<<24|Reg07;break;

	//**********************************************************************
	case 14:
	SW_SW = 0X8<<24|Reg08;break;

	case 15:
	SW_SW = 0XA<<24|RegA;break;

	case 16:
	SW_SW = 0XB<<24|RegB;break;

	case 17:
	SW_SW = 0XC<<24|RegC;break;

	case 18:
	SW_SW = 0XD<<24|RegD;break;

	//******************************************
	case 19:
	SW_SW = 0XF<<24|RegF;break;
	
	default : SW_SW = Reg00;break;

}

return  SW_SW;
}
void HMC830::SetBIT09(int Offset,int UP,int DN,int MHiKCP)
 {
		if (Offset>=0 && Offset<128)
	{
		Lmagn9 = Offset;
	} else
	{
	   Lmagn9 = 0;
	}
	L_Dir_UP = UP;
	L_Dir_DN = DN;
	HiKcp = MHiKCP;
 }

 void HMC830::CURSet(int IH, int IL)
 {    CurSetH = IH<<7;
      CurSetL = IL;
 }
#pragma package(smart_init)
