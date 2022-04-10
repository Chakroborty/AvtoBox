//---------------------------------------------------------------------------


#pragma hdrstop

#include "Adf4360.h"

//---------------------------------------------------------------------------

TAdf4360::TAdf4360(double Freference) : Fref(Freference), CB_C(0), CB_R(1), CB_N(2)
{
	//MuxMode = 5;                  //  analog lock detect
//    MuxMode = 1;                    //  digital lock detect
    MuxMode = 4;                    //  digital lock detect
	CntReset = 0;
    CpThreeSt = 0;
    PwrDown = 0;
	PdPolar = 0;
	CurSet = 0;
    Presc = 0;
    OutPwr = 0;
    CpThreeSt = 0;
    Mute = 0;
    Gain = 0;
    Divide = 1;
    Band = 0;
    PwrLvl = 0;
}
//---------------------------------------------------------------------------

TAdf4360::TAdf4360(TWritePll WriteReg, TReadPll ReadReg) :
        WriteDword(WriteReg), ReadDword(ReadReg), CB_C(0), CB_R(1), CB_N(2)
{

//    MuxMode = 3;                  //  1
    MuxMode = 5;                  //  analog lock detect
//    MuxMode = 1;                    //  digital lock detect
//    MuxMode = 4;                    //  R
//    MuxMode = 2;                    //  N
	CntReset = 0;
    CpThreeSt = 0;
    PwrDown = 0;
	PdPolar = 1;
	CurSet = 0;
    Presc = 0;
    OutPwr = 0;
    CpThreeSt = 0;
    Mute = 0;
    Gain = 0;
    Divide = 1;
    Band = 0;
    PwrLvl = 0;
}
//---------------------------------------------------------------------------

TAdf4360::~TAdf4360()
{
}
//---------------------------------------------------------------------------

void TAdf4360::WriteFreq(double newFreq)
{
    Freq = newFreq;
    CalculateRegisters();
}
//---------------------------------------------------------------------------

void TAdf4360::CalculateRegisters()
{
    // Делитель опоры
    R =  floor(Fref / Fcomp + 0.5);
    Fcomp = Fref / R;
	int N = int(Freq / Fpfd);
    div_t x;
    DWORD P = 8;
    x = div(N, P);
    B = x.quot;
    A = N - B * P;

	// Control register
	CReg = Presc << 22 | PwrDown << 20 | CurSet << 17 | CurSet << 14 |
        PwrLvl << 12 | Mute << 11 | Gain << 10 | CpThreeSt << 9 |
        PdPolar << 8 | MuxMode << 5 | CntReset << 4 | OutPwr << 2 | CB_C;

	NReg = Divide << 22 | Gain << 21 | B << 8 | A << 2 | CB_N;

	RReg = Band << 20 | R << 2 | CB_R;

	Load();
}
//---------------------------------------------------------------------------

void TAdf4360::Load()
{
    WaitXfer();
    WriteDword(0x4004, RReg);
    WaitXfer();
    WriteDword(0x4004, CReg);
    WaitXfer();
    WriteDword(0x4004, NReg);
//    WriteRegister(RReg);
//    WriteRegister(CReg);
//    WriteRegister(NReg);
}
//---------------------------------------------------------------------------

void TAdf4360::LoadControl()
{
    WriteDword(0x4004, CReg);
//	WriteRegister(CReg);
}
//---------------------------------------------------------------------------

void TAdf4360::LoadRdivider()
{
    WriteDword(0x4004, RReg);
//	WriteRegister(RReg);
}
//---------------------------------------------------------------------------

void TAdf4360::LoadNdivider()
{
    WriteDword(0x4004, NReg);
//	WriteRegister(NReg);
}
//---------------------------------------------------------------------------

bool TAdf4360::WaitXfer()
{
DWORD res, cyc = 0;
    do
    {
        res = ReadDword(0x4004);
        cyc++;
        if (cyc > 10000)
        {
            break;
        }
    }
    while (!(res & 0x80000000));

    if (cyc > 10000)
        return false;
    else
        return true;
}
//---------------------------------------------------------------------------

bool TAdf4360::ReadLockDetect()
{
DWORD res;
    res = ReadDword(0x4004) & 0x01000000;
    return res ? true : false;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
