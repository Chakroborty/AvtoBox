//---------------------------------------------------------------------------


#pragma hdrstop

#include "Adf4001.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
TAdf4001::TAdf4001 (TWritePll WriteReg, TReadPll ReadReg) :
        WriteDword(WriteReg), ReadDword(ReadReg), CB_R(0), CB_N(1), CB_F(2), CB_I(3)
{
	Fref = 10.0;
    Fpfd = 10.0;
    Freq = 10.0;

	//  Биты управления загрузкой синтезатора
	AntiBLW = 0;
	Polarity = 1;
//    MuxMode = 1;                   //  digital lock detect
//    MuxMode = 2;                   // N divider
//    MuxMode = 3;                   // vcc
//    MuxMode = 4;                     // R divider
    MuxMode = 5;                   //  lock detect
//    MuxMode = 6;                   // SDO
//    MuxMode = 7;                   // gnd
	CurSet1 = 0;
	CurSet2 = 0;
	Reset = 1 << 2;
}

//---------------------------------------------------------------------------
TAdf4001::~TAdf4001()
{
}

//---------------------------------------------------------------------------
void TAdf4001::SetFref(double F)
{
	Fref = F;
}

//---------------------------------------------------------------------------
double TAdf4001::GetFd()
{
	return Freq/2;
}

//---------------------------------------------------------------------------
void TAdf4001::SetFpfd(double F)
{
	Fpfd = F;
}

//---------------------------------------------------------------------------
bool TAdf4001::SetFreq(double F)
{
	if (F < FSYNTHMIN || F > FSYNTHMAX)
	{
		return false;
	}
	Freq = F;

	return UpdateRegisters();
}

//---------------------------------------------------------------------------
bool TAdf4001::SetCurent(int Curr)
{
	CurSet1 = Curr;
	CurSet2 = Curr;

	return UpdateRegisters();
}

//---------------------------------------------------------------------------
void TAdf4001::CalculateRegisters()
{
	R = int(floor(Fref / Fpfd + 0.5));
	Fpfd = Fref / R;
	N = int(Freq / Fpfd);
	Freq = Fpfd * N;
}

//---------------------------------------------------------------------------
bool TAdf4001::UpdateRegisters()
{
	CalculateRegisters();
    Sleep(1);
	WriteDword(0x4008, (AntiBLW << 16) + (R << 2) + CB_R);
    Sleep(1);
	WriteDword(0x4008, (0 << 21) + (N << 8) + CB_N);
    Sleep(1);
	WriteDword(0x4008, (CurSet2 << 18) + (CurSet1 << 15) + (Polarity << 7) +
                       (MuxMode << 4) + CB_F);
    Sleep(1);                       

/*	WritePll(CurSet2 | CurSet1 | Polarity | MuxMode | Reset | CB_F);
	WritePll(AntiBLW + (R << 2) + CB_R);
	WritePll((0 << 21) + (N << 8) + CB_N);
	WritePll(CurSet2 | CurSet1 | Polarity | MuxMode | CB_F);*/
	Sleep(10);
//	return ReadMuxout();
    return true;
}
