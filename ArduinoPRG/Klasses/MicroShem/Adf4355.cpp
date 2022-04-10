// ---------------------------------------------------------------------------

#pragma hdrstop
#include <math.h>
#include "Adf4355.h"
#include "Bits.h"
// ---------------------------------------------------------------------------
Adf4355::Adf4355(double F, int I, int N, bool Pol_PLUS, double Ref,int Dabl)
{


	/** **********Reg 0************* */
	
	AUTOCAL = 1;
	PRESCALER =1;//1-8/9
	Nint = 24;
	
	/** **********Reg 1************* */
	
	Nref = 200;
	FRAC1 = 0;
	//unsigned int Nfrak;
	//double Nfrak_prog;
	
	
	/** **********Reg 2************* */
	FRAC2  = 0;
	MOD2 = 20;
	
	
	/************Reg 3**************/
	SDLRES = 1;
	PHRES = 0;
	PHADJ = 0;
	PHVAL = 0;
	
	
	
	
	/************Reg 4**************/
	MUXOUT = 6;
	DOUBLER = 0;
	RDIV2DBB = 1;
	R = 1;
	DBUF = 1;
	
	CurSet = 3; // опорный ток0,925
	CP_CUR = 3;
	REF_MOD = 0; //0 SINGLE 1 DIFF
	MLOG = 1;//MUX LOGIC 0 1.8V 1 3.3V
	PDPOLAR = 1;
	POWDN = 0; //Setting DB6 to 1 performs a power-down. Setting DB6 to 0 returns the synthesizer to normal operation
	CPTHREE = 0; //Set DB5 to 0 for normal operation.
	COUNTRES = 0;//When DB4 is set to 1, the RF synthesizer N counter, R counter, and VCO band select are reset. For normal operation, set DB4 to 0.
	
	
	/************Reg 5**************/
	
	Reg05 = 0X5;//     RESERVED
	
	
	/************Reg 6**************/
	GBLED = 0;//Gated Bleed.  if set to 1, ensures bleed currents are not switched on until the digital lock detect asserts logic high.
	NEGBLED = 1; //negative bleed is recommended for most fractional-N applications because it improves the linearity of the charge pump
	FEDSEL = 0; /*When the divider is enabled and the feedback signal is taken from the output, the RF output signals of two separately
	configured PLLs are in phase.*/
	RFDIV = 0; //0÷1  6÷64
	CPBLEDCU = 0;//BLEED CURRENT
	MTLD = 0;   /*Когда D8 (Бит DB11) установлен в 1, ток поставки к выходному каскаду RF закрыт,
	пока устройство не достигает замка, как определено цифровым замком обнаруживают схему.*/
	RFOUTB = 0;//AUXRF
	RFOUTBPOW = 0;//RFAUXPOW
	RFOUTA = 1;
	RFPOW = 2;
	
	
	
	/**********Reg 7**************/
	LESYNC = 1;
	LDCCONT = 0;
	LOL = 1;
	LDPREC = 3;
	LDMOD = 0;
	
	
	/**********Reg 8**************/
	
	Reg08 = 0X8; //  RESERVED
	
	/************Reg 9**************/
	VCOBAND = ;  /*Determine the value of this clock by PFD/(band
	division × 16) such that the result is <150 kHz.*/
	TOUT = 1020;  /*set the timeout value for the VCO band select.*/
	ATL = 10;
	SYNLOCT = 5;
	/**********Reg 10**************/
	ADCDIV = 100;
	ADCCONV = 1;  /*It is recommended to enable this mode. Page 28 of 35 */
	ADCEN = 1; /*temperature dependent VTUNEcalibration. It is recommended to
	always use this function. */
	
	/**********Reg 11**************/
	
	Reg11 = 0x0061300B;  // RESERVED
	

	/**********Reg 12**************/
	RESCLOC = ;

	
	/*******************************/
	
		

	MAPALL();
	
	SetFreq(F,Ref);
}

Adf4355::~Adf4355()
{

}
void Adf4355::MAP00()
{
   Reg00 =  AUTOCAL << 21 | PRESCALER << 20| Nint << 4 | 0X0;
}
void Adf4355::MAP01()
{
   Reg01 = FRAC1<<4 | 0X1;
}
void Adf4355::MAP02()
{
   Reg02 =  FRAC2<<18|MOD2<<24|0X2;
}
void Adf4355::MAP03()
{
   Reg03 =  SDLRES<<30|PHRES<<29|PHADJ<<28|PHVAL<<4|0X3;
}
void Adf4355::MAP04()
{
   Reg04 = MUXOUT<<27|DOUBLER<<26|RDIV2DBB<<25|R<<15|DBUF<<14|
	 CP_CUR<<10|REF_MOD<<9|MLOG<<8|PDPOLAR<<7|POWDN<<6|CPTHREE<<5|COUNTRES<<4|0X4;

}
void Adf4355::MAP05()
{
   Reg05 = 5;   //RESERVED
}
void Adf4355::MAP06()
{
   Reg06 = GBLED<<30|NEGBLED<<29|FEDSEL<<24|RFDIV<<21|CPBLEDCU<<13|MTLD<<11|
		 RFOUTB<<9|RFOUTBPOW<<7|RFOUT<<6|RFPOW<<4|0X6;
}
void Adf4355::MAP07()
{
   Reg07 =  LESYNC << 25| LDCCONT<< 8 |LOL << 7 |LDPREC << 5|LDMOD << 4|0X7;
}
void Adf4355::MAP08()
{
   Reg08 = 8;
}
void Adf4355::MAP09()
{
   Reg09 =  VCOBAND<< 24| TOUT << 14|ATL<< 9|SYNLOCT<< 4|0X9;
}
void Adf4355::MAP10()
{
   Reg10 = ADCDIV<< 6| ADCCONV << 5|ADCEN<< 4|10;
}
void Adf4355::MAP11()
{
   Reg11 = 11;
}
void Adf4355::MAP12()
{
   Reg12 =  = RESCLOC<< 16|12;
}






void Adf4355::MAPALL()
{
	MAP00();
	MAP01();
	MAP02();
	MAP03();
	MAP04();
	MAP05();
	MAP06();
	MAP07();
	MAP08();
	MAP09();
	MAP10();
	MAP11();
	MAP12();
}
void Adf4355::MAPFRIQ()
{
	MAP00();
	MAP01();
	MAP02();
	MAP04();

}

// *********************************************************************************
/**
 * [Adf4355::SetFreq description]
 * @param fsint [description]
 * @param Fref  [description]
 */
void Adf4355::SetFreq(double fsint,double Fref)
{   Xtal =  Fref;
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
		  if (Xtal/R>110)
   {
	   R=R+1;
   }
	Fpfd = Xtal*(1+DOUBLER)/(R*(1+RDIV2DBB));

	Nakt = FregSIN/Fpfd;

		if (Nakt<23)
	{
	  R = R*2;
	  Fpfd = Xtal*(1+DOUBLER)/(R*(1+RDIV2DBB));
	  Nakt = FregSIN*Fpfd;
	}
	Nint = floor(Nakt);
	Nfrak = pow(2,24)*(Nakt - Nint);
	FRAC1 = floor(Nfrak); 

	/*
	 	*	Calculate MOD2 based on the channel spacing (fCHSP) by
		*	MOD2 = fPFD/GCD(fPFD, fCHSP)  (4)
		*	where:
		*	GCD(fPFD, fCHSP) is the greatest common divider of the PFD 
		*	frequency and the channel spacing frequency.
		*	fCHSP is the desired channel spacing frequency.
		*	7.  Calculate FRAC2 by the following equation: 
		*	FRAC2= [(N− INT) × 2^24 − FRAC1)] × MOD2  (5) 
		* 	The FRAC2 and MOD2 fraction results in outputs with zero 
		*  	frequency error for channel spacings when 
		*	fPFD/GCD(fPFD/fCHSP) < 16,383  (6) 
		* 	where: 
		*  	fPFDis the frequency of the phase frequency detector. 
		*   GCD is a greatest common denominator function. 
		*   fCHSPis the desired channel spacing frequency. 
		*		
	 */

	
	MOD2 = fPFD/GCD(fPFD, fCHSP);
	FRAC2 = (Nfrak - FRAC1)*MOD2; //  [(N− INT) × 2^24− FRAC1)] × MOD2
	//FRAKLSB = Nfrak & 0x1FFF; 13 bit LSB

	MAPFREQ();





	CP_CUR = floor(0.3 + CurSet * Nakt / Nref);
	if (CP_CUR <= 1)
	{
		CP_CUR = 1;
	}
	if (CP_CUR > 15)
	{
		CP_CUR = 15;
	}
   MAP02();

}
// *********************************************************************************
void Adf4355::PARAMSEt4159(int CPTri)
{
	 CPTHREE = CPTri;
	 MAP03();
}
// *********************************************************************************
long Adf4355::RegLoad4159
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



#pragma package(smart_init)


