// ---------------------------------------------------------------------------

#pragma hdrstop
#include <math.h>
#include "ADF4153.h"

// ---------------------------------------------------------------------------
ADF4153::ADF4153(double F, int I, int N, bool Pol_PLUS, double Ref,
	double ssHag,int Dabl) {
	Xtal = Ref; // MГерц
	SHag = ssHag;
	/** **********Reg 0************* */

	FASTLOCK = 0;
	Nref = N;
	// Nakt;
	// Nint;
	// Nfrak;
	// Nfrak_prog;

	/** **********Reg 1************* */
	Load_CONTR = 0;
	MUXOUT = 1;
	PRESCALER = 1; // 1 8/9
	R = 1;
	// int MODUL;
	// double MOD_prog;
	/** **********Reg 2************* */
	Resinc = 0x1;
	DOUBLER = Dabl;
	CP_CUR = CurSet = I; // опорный ток
	if (Pol_PLUS) {
		Polarity = Polar::Polog;
	}
	else {
		Polarity = Polar::Otric;
	}

	LDP = 0;
	P_Dovn = 0;
	CP_Trist = 0;
	CounRes = 0;
	/** **********Reg 3************* */
	NoiseSpur = ModeSp::LNSM;
	SetFreq(F);
}

ADF4153::~ADF4153() {

}

// *********************************************************************************
void ADF4153::SetFreq(double fsint)
{
	if (fsint >= 1 && fsint <= 4000) {
		FregSIN = SHag * floor(fsint / SHag);
	}
	if (fsint > 1500) {

		PRESCALER = Del8_9;
	}
	else {
		PRESCALER = Del4_5;
	}
	Nakt = FregSIN * R / (Xtal * (DOUBLER + 1));
	Nint = floor(Nakt);
	MODUL = floor(0.5 + (Xtal * (DOUBLER + 1)) / (R * SHag));
	Nfrak = (FregSIN - Nint * (Xtal * (DOUBLER + 1)) / R) / SHag;
	IMODUL = MODUL;
	INfrak = Nfrak;

	Nfrak_prog = Nfrak / 5;
	MOD_prog = MODUL / 5;

	if ((Nfrak_prog - floor(Nfrak_prog)) == 0&&(MOD_prog - floor(MOD_prog)) == 0)
	/* TODO -cADF4153 : Оптимизация  frak mod */
	{
		INfrak = Nfrak_prog;
		IMODUL = MOD_prog;
	}
	else {
		Nfrak_prog = Nfrak / 4;
		MOD_prog = MODUL / 4;
		if ((Nfrak_prog - floor(Nfrak_prog)) == 0&&(MOD_prog - floor(MOD_prog)) == 0) {
			INfrak = Nfrak_prog;
			IMODUL = MOD_prog;
		}
		else {
			Nfrak_prog = Nfrak / 2;
			MOD_prog = MODUL / 2;
			if ((Nfrak_prog - floor(Nfrak_prog)) == 0&&(MOD_prog - floor(MOD_prog)) == 0) {
				INfrak = Nfrak_prog;
				IMODUL = MOD_prog;
			}
		}

	}



   //	CP_CUR = floor(0.3 + CurSet * Nakt / Nref);


				if(Nakt / Nref>1.2)
	{

		 CurSet  &= ~(1<<3);//Чтобы  записать  ноль  в  бит  N,   выполни:


	}
	else
	{
		 CurSet  |= (1<<3);//Чтобы  записать  единицу  в  бит  N,   выполни:
		 
	}



	/*
	if (CP_CUR <= 1) {
		CP_CUR = 1;
	}
	if (CP_CUR > 15) {
		CP_CUR = 15;
	}

	CP3 CP2 CP1 CP0 2.7kΩ 5.1kΩ 10kΩ
	0	0	0	 0	1.18 0.63 0.32
					2.46 1.25 0.64
					3.54 1.88 0.96
					4.72 2.50 1.28
					5.9  3.13 1.59
					7.08 3.75 1.92
					8.26 4.38 2.23
					9.45 5.00 2.55
					0.59 0.31 0.16
					1.23 0.63 0.32
					1.77 0.94 0.48
					2.36 1.25 0.64
					2.95 1.57 0.8
					3.54 1.88 0.96
					4.13 2.19 1.12
	1	1	 1	 1	4.73 2.50 1.28
	 */

}

int ADF4153::RegLoad4153(int Reg) {
	int SW_SW;
	switch(Reg) {
	case 0: // 1.  Write all zeros to the noise and spur register. This ensures that all test modes are cleared.

		SW_SW = 0x3;
		break;

	case 1: // 2.  Write again to the noise and spur register, this time
		SW_SW = Reg03 = NoiseSpur << 2 | 0x3; // selecting which noise and spur mode is required.
		break;
		/* TODO -csinz : sekvense */
		// 3.  Enable the counter reset in the control register by writing a
	case 2: // 1 to DB2; also select the required settings in the control
		CounRes = 1;  //register. If using the phase resync function, set the resync
		SW_SW = Reg02 = Resinc << 12 | DOUBLER << 11 | CP_CUR << 7 |
			Polarity << 6 | LDP << 5 | P_Dovn << 4 | CP_Trist << 3 |
			CounRes << 2 | 0X2; // bits to the required settings.
		break;

	case 3: // 4. Load the R divider register (with load control [DB23]set to 0).

		SW_SW = Reg01 = Load_CONTR << 24 | MUXOUT << 20 | PRESCALER << 18 |
			R << 14 | IMODUL << 2 | 0X1;
		break;
	case 4: // 5.  Load the N divider register.

		SW_SW = Reg00 = FASTLOCK << 24 | Nint << 14 | INfrak << 2;
		break;

	case 5: // 6.  Disable the counter reset by writing a 0 to DB2 in the control register.
		CounRes = 0;
		SW_SW = Reg02 = Resinc << 12 | DOUBLER << 11 | CP_CUR << 7 |
			Polarity << 6 | LDP << 5 | P_Dovn << 4 | CP_Trist << 3 |
			CounRes << 2 | 0X2;
		break;

	default:
		SW_SW = Reg00;
		break;
	}
	return SW_SW;
}
void ADF4153::SetPFD(int Cur)
{
			  if(Cur>=0&&Cur<8)
  {
		 CP_CUR = Cur;
  }
  else
  {
		 CP_CUR = 3;

  }
}

void ADF4153::SetDUB(int Dubl)
{
	DOUBLER = Dubl;
}
/*
//Reg 0

int FASTLOCK;
int Nref;
double Nakt;
double Nint;
int Nfrak;
double Nfrak_prog;

//Reg 1
int Load_CONTR;
int MUXOUT;
int PRESCALER;
double R;
int MODUL;
double MOD_prog;
//Reg 2****
int Resinc;
int DOUBLER;
int CP_CUR;
int CurSet; // опорный ток
int Polarity;
int LDP;
int P_Dovn;
int CP_Trist;
int CounRes;
//Reg 3
int NoiseSpur;
 */
void ADF4153::Operation1() {

}

#pragma package(smart_init)

