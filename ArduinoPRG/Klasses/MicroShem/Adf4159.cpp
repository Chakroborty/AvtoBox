// ---------------------------------------------------------------------------

#pragma hdrstop
#include <math.h>
#include "Adf4159.h"

// ---------------------------------------------------------------------------
ADF4159::ADF4159(double F, int I, int N, bool Pol_PLUS, double Ref,int Dabl)
{


	Ramp = 0;
	MUXOUT = 1;
	Nref = N;

	/** **********Reg 1************* */
	PHADJ = 0;
	//FRAKLSB; 13 bit LSB
	PHASE = 0;

	/** **********Reg 2************* */
	CSR = 0;
	CP_CUR = I;
	CurSet = I; // опорный ток
	//PRESCALER;
	RDIV2DBB = 0;
	DOUBLER = Dabl;
	R = 1;
	CLKDIV = 1;

	/** **********Reg 3************* */
	NBLDCUR = 0;
	NBLEN = 0;
	LOL = 0;
	NSEL = 0;
	SDRESET = 0;
	RAMPMOD = 0;
	PSK = 0;
	FSK = 0;
	LDP = 0;
	PDPOLAR = 0;  /* TODO -oPerv : Polar 4159 */
	POWDN = 0;
	CPTHREE = 0;
	COUNTRES = 0;


	/** **********Reg 4************* */
	LESEL = 0;
	MMODE = 0;  //Σ-Δ MODULATOR MODE     NORMAL OPERATION 000000   DISABLED WHEN FRAC = 0  0 1 1 1 0
	RAMPST = 0;
	CLKDMODE = 0;
	CLKDIVVALUE = 0;
	CLKDIVSEL = 0;

	/************Reg 5**************/
	TXINV = 0;
	TXCLK = 0;
	PRAMP = 0;
	INR = 0;
	FSKR = 0;
	DUALR = 0;
	DEVSEL = 0;
	DEVOFW = 0;
	DEVW = 0;

	/************Reg 6**************/
	STEPS = 0;
	STEPW = 0;

	/************Reg 7**************/
	TXDTRIGDEL = 0;
	TRIDEL = 0;
	SFULTRI = 0;
	TXDATTR = 0;
	FASTR = 0;
	RDELFL = 0;
	RDELAY = 0;
	DCLKSEL = 0;
	DSTARTEN = 0;
	DSTARTW = 0;


	MAP00();
	MAP01();
	MAP02();
	MAP03();
	MAP04();
	MAP05();
	MAP06();
	MAP07();
	SetFreq(F,Ref,true);
}

ADF4159::~ADF4159()
{

}
void ADF4159::MAP00()
{
   Reg00 = Ramp<<31|MUXOUT<<27|Nint<<15|FRAC<<3| 0X0;
}
void ADF4159::MAP01()
{
   Reg01 = PHADJ<<28|FRAKLSB<<15|PHASE<<3|0X1;
}
void ADF4159::MAP02()
{
   Reg02 = CSR<<28|CP_CUR<<24|PRESCALER<<22|RDIV2DBB<<21|
   DOUBLER<<20|R<<15|CLKDIV<<3|0X2;
}
void ADF4159::MAP03()
{
   Reg03 = NBLDCUR<<22|NBLEN<<21|LOL<<16|NSEL<<15|SDRESET<<14|RAMPMOD<<10|
   PSK<<9|FSK<<8|LDP<<7|PDPOLAR<<6|POWDN<<5|CPTHREE<<4|COUNTRES<<3|0X3;
}
void ADF4159::MAP04()
{
   Reg04 = LESEL<<31|MMODE<<26 |RAMPST<<21|CLKDMODE<<19|
		 CLKDIVVALUE<<7|CLKDIVSEL<<6|0X4;

}
void ADF4159::MAP05()
{
   Reg05 = TXINV<<30|TXCLK<<29|PRAMP<<28|INR<<26|FSKR<<26|
   DUALR<<24|DEVSEL<< 23|DEVOFW<<19|DEVW<< 3|0X5;
}
void ADF4159::MAP06()
{
   Reg06 = STEPS<<23|STEPW<<3|0X6;
}
void ADF4159::MAP07()
{
   Reg07 = TXDTRIGDEL<<23|TRIDEL<<22|SFULTRI<<21|TXDATTR<<20|FASTR<<19|RDELFL<<18|
   RDELAY<<17|DCLKSEL<<16|DSTARTEN<<15|DSTARTW<<3| 0X7;
}
// *********************************************************************************
void ADF4159::SetFreq(double fsint,double Fref,bool OptI)
{   Xtal =  Fref;

	POWDN = 0;
	if (fsint >= 1 && fsint <= 12000)
	{
		FregSIN = fsint;
	}
	if (fsint > 8000)
	{

		PRESCALER = Del8_9;
	}
	else
	{
		PRESCALER = Del4_5;
	}
			while (Xtal/R>110)
			{
			  R=R*2;
			}
//		  if (Xtal/R>110)
//   {
//	   R=R+1;
//   }
	Fpfd = Xtal*(1+DOUBLER)/(R*(1+RDIV2DBB));
	Nakt = FregSIN/Fpfd;
		if (Nakt<23)
	{
	  R = R*2;
	  Fpfd = Xtal*(1+DOUBLER)/(R*(1+RDIV2DBB));
	  Nakt = FregSIN/Fpfd;
	}
	Nint = floor(Nakt);
	Nfrak = floor(0.5 + pow(2.0,25)*(Nakt - Nint));

	FRAC =   (Nfrak >> 13) & 0xFFF;;
	FRAKLSB = Nfrak & 0x1FFF; //13 bit LSB
//	switch (Nfrak)
//	{  case 0:  MMODE = 14;break;      //Выключение дробности
//	   default: MMODE = 0;break;
//	}
	MAP04();
	MAP00();
	MAP01();


		if(OptI)
	{
			CP_CUR = floor(0.3 + CurSet * Nakt / Nref);
		if (CP_CUR <= 0)
		{
			CP_CUR = 0;
		}
		if (CP_CUR > 15)
		{
			CP_CUR = 15;
		}

	}


   MAP02();
   MAP03();

}
// *********************************************************************************
void ADF4159::PARAMSEt4159(int CPTri,int Cur)
{
		if (Cur <= 1)
	{
		CP_CUR = 1;
	}else
	{
			if (Cur > 15)

		{
			CP_CUR = 15;
		}else
		{
			CP_CUR = Cur;
		}

	}
	MAP02();


	CPTHREE = CPTri;
	MAP03();
}


void ADF4159::NRSEt4159(int PR,int PN,int PNF,int PREs)
{
	 Nint = PN;

	 R = PR;
	 Nfrak = PNF;
//	 if (PNF==0) {
//	 FRAC =   (Nfrak >> 13) & 0xFFF;;
//	 FRAKLSB = Nfrak & 0x1FFF; //13 bit LSB
//	 MMODE = 0XE;
//	 } else{
//     MMODE = 0;
//	 FRAC =   (Nfrak >> 13) & 0xFFF;;
//	 FRAKLSB = Nfrak & 0x1FFF; //13 bit LSB
//	 }
			switch (PREs)
			 {
		case 0: PRESCALER = Del4_5;      break;
		case 1: PRESCALER = Del8_9;      break;
		default: PRESCALER = Del4_5;      break;

			}

		MAP00();
		MAP01();
		MAP02();
		MAP03();
		MAP04();
}
// *********************************************************************************
long ADF4159::RegLoad4159
(int Reg)
{
   unsigned	int SW_SW;
	switch(Reg)
	{
	case 0:
		SW_SW = Reg07;
		break;
	case 1:
		STEPS = 0;
		MAP06();
		SW_SW = Reg06;
		break;

	case 2:
		STEPS = 1;
		MAP06();
		SW_SW = Reg06;
		break;
	case 3:
		DEVSEL =0;
		MAP05();
		SW_SW = Reg05;
		break;
	case 4:
		DEVSEL =1;
		MAP05();
		SW_SW = Reg05;
		break;
	case 5:
		CLKDIVSEL = 0;
		MAP04();
		SW_SW = Reg04;
		break;
	case 6:
		CLKDIVSEL = 1;
		MAP04();
		SW_SW = Reg04;
		break;
	case 7:
		MAP03();
		SW_SW = Reg03;
		break;
	case 8:
		SW_SW = Reg02;
		break;
	
	case 9:
		SW_SW = Reg01;
		break;
	case 10:
		SW_SW = Reg00;
		break;
	default:
		SW_SW = Reg00;
		break;
	}
	return SW_SW;
}

void ADF4159::Operation1() {

}

#pragma package(smart_init)


