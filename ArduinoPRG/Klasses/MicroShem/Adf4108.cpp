// ---------------------------------------------------------------------------

#pragma hdrstop
#include <math.h>
#include "Adf4108.h"

// ---------------------------------------------------------------------------
ADF4108::ADF4108(double F, int I, int N, bool Pol_PLUS, double Ref,
	double ssHag,int Dabl)
{
	Xtal = Ref; // MГерц

	/** **********Reg 0************* */
	LDP = 0;
	TMB = 0;
	ABP = 0;;
	Nref = 5;
	/** **********Reg 1************* */
	CP_GAIN = 1;
	B_COUNT = 15;
	A_COUNT = 0;
	/** **********Reg 2************* */
	PRESCALER = 1;
	PD1 =0;

	CurSet = 5; // опорный ток
	T_OUT = 0;
	FASTLOCK = 0;
	CP_Trist = 0;
		if (Pol_PLUS)
	{
		Polarity = Polar::Polog;
	}
	else
	{
		Polarity = Polar::Otric;
	}
	MUXOUT = 2;

	PD2 = 0;
	CounRes = 0;






}

ADF4108::~ADF4108()
{

}

// *********************************************************************************
void ADF4108::SetFreq(double fsint)
{





}

int ADF4108::RegLoad4108(int Reg)
{
	unsigned int SW_SW;
    SW_SW = 0;
	switch(Reg)
  {
	case 0:

   SW_SW = PRESCALER<<22|PD2<<21|CurSet<<18|CurSet<<15|T_OUT<<11|FASTLOCK<<9|CP_Trist<<8|Polarity<<7|MUXOUT<<4|PD1<<3|CounRes<<2|3;

	break;

	case 1:
   SW_SW = LDP<<20|TMB<<18|ABP<<16|Nref<<2;
	break;
	case 2:
   SW_SW = CP_GAIN<<21|B_COUNT<<8|A_COUNT<<2|1;
	break;
	case 3:
   SW_SW =  PRESCALER<<22|PD2<<21|CurSet<<18|CurSet<<15|T_OUT<<11|FASTLOCK<<9|CP_Trist<<8|Polarity<<7|MUXOUT<<4|PD1<<3|CounRes<<2|2;
	break;

	default:
   SW_SW =  PRESCALER<<22|PD2<<21|CurSet<<18|CurSet<<15|T_OUT<<11|FASTLOCK<<9|CP_Trist<<8|Polarity<<7|MUXOUT<<4|PD1<<3|CounRes<<2|3;
	break;
  }
	   SW_SW = SW_SW;
	return SW_SW;
}


void ADF4108::ParamSET(int Pol, int Cur,int Pres,int A,int B, int R)
{       Nref = R;
		Polarity = Pol;

				if (Cur>7)
		{   CurSet = 0;
			CP_Trist = 1;
		} else
		{   CurSet = Cur;
			CP_Trist = 0;
		}
		PRESCALER = Pres;
		A_COUNT = A;
		B_COUNT = B;

}
#pragma package(smart_init)


