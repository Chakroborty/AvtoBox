//---------------------------------------------------------------------------

#pragma hdrstop

#include "DDSAD9910.h"
//---------------------------------------------------------------------------
AD9910::AD9910(int I, int PN, bool Pol_PLUS, double Ref)
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
		Polarity = 0;
	}
	else
	{
		Polarity = 1;
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

#pragma package(smart_init)
