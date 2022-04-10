// ---------------------------------------------------------------------------

#pragma hdrstop
#include <math.h>
#include "CADF4002.h"

// ---------------------------------------------------------------------------
ADF4002::ADF4002(int I, int PN, bool Pol_PLUS, double Ref)
{
	Xtal = Ref; // MГерц

	/** **********Reg 0************* */
	LDP = 0;
	TMB = 0;
	ABP = 0;;

	R = 1;
	/** **********Reg 1************* */
	CP_GAIN = 0;
	Nref = PN;
	N = PN;
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
	MUXOUT = 2; //N делитель
	//MUXOUT = 1; //DIGITAL LOCK DETECT

	PD2 = 0;
	CounRes = 0;
	MAP00();
	MAP01();
	MAP02();
	MAP03();


}

ADF4002::~ADF4002()
{

}

// *********************************************************************************
void ADF4002::SetFreq(double fsint)
{





}

int ADF4002::RegLoad4002(int Reg)
{
	unsigned int SW_SW;
    SW_SW = 0;
	switch(Reg)
  {
	case 0:SW_SW = Reg03;break;
	case 1:SW_SW = Reg02;break;
	case 2:SW_SW = Reg00;break;
	case 3:SW_SW = Reg01;break;
	default:SW_SW = Reg03;break;
  }

	return SW_SW;
}

/**
 * [ADF4002::ParamSET description]
 * @param Pol  [Полярность ФД]
 * @param Cur  [Ток ФД]
 * @param Rdiv [R делитель опоры]
 * @param Ndiv [N делитель RF]
 */
void ADF4002::ParamSET(int Pol, int Cur, int Rdiv, int Ndiv)
{   /*----------  Процедура ParamSET ----------*/

		N = Ndiv;
		R = Rdiv;
		Polarity = Pol;

		  if (Cur>7)
		{
			CurSet = 0;
			CP_Trist = 1;
		} else
		{
			CurSet = Cur;
			CP_Trist = 0;
		}
	  MAP00();
	  MAP01();
	  MAP02();
	  MAP03();

}
void ADF4002::CurSET(int Cur)
{
	   if (Cur>7)
		{
			//CurSet = 0;
			CP_Trist = 1;
		} else
		{
			//CurSet = Cur;
			CP_Trist = 0;
		}
	   MAP00();
	   MAP01();
	   MAP02();
	   MAP03();
}
void ADF4002::MAP00()
{
	Reg00 = LDP<<20|TMB<<18|ABP<<16|R<<2;

}
void ADF4002::MAP01()
{
	Reg01 = CP_GAIN<<21|N<<8|A_COUNT<<2|1;
}
void ADF4002::MAP02()
{
	Reg02 = PD2<<21|CurSet<<18|CurSet<<15|T_OUT<<11|FASTLOCK<<9|CP_Trist<<8|Polarity<<7|MUXOUT<<4|PD1<<3|CounRes<<2|2;
}
void ADF4002::MAP03()
{
	Reg03 = PD2<<21|CurSet<<18|CurSet<<15|T_OUT<<11|FASTLOCK<<9|CP_Trist<<8|Polarity<<7|MUXOUT<<4|PD1<<3|CounRes<<2|3;
}

#pragma package(smart_init)


