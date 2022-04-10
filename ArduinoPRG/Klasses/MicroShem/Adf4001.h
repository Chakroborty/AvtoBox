//---------------------------------------------------------------------------

#ifndef Adf4001H
#define Adf4001H
//---------------------------------------------------------------------------

#include <vcl.h>
//#include "UsbDefines.h"
#include <math.h>

#define FSYNTHMIN   9
#define FSYNTHMAX   11

typedef void (__closure *TWritePll)(DWORD Addr, UINT32 Data);
typedef UINT32 (__closure *TReadPll)(DWORD Addr);

class TAdf4001
{
private:
	const int CB_R;
	const int CB_N;
	const int CB_F;
	const int CB_I;

	DWORD Nreg;
	DWORD Rreg;
	DWORD Ireg;
	DWORD Freg;
	DWORD Polarity;
	DWORD MuxMode;
	DWORD AntiBLW;
	DWORD CurSet1;
	DWORD CurSet2;
	DWORD Reset;

protected:
	double Fpfd;
	double Fref;
	double Freq;
	DWORD N;
	DWORD R;
	void CalculateRegisters();
	bool UpdateRegisters();
public:
	TAdf4001(TWritePll WriteReg, TReadPll ReadReg);
	~TAdf4001();
	void SetFref(double F);
	void SetFpfd(double F);
	bool SetFreq(double F);
	bool SetCurent(int Curr);
	double GetFd();
    TWritePll WriteDword;
    TReadPll ReadDword;
//	virtual void WritePll(DWORD) = 0;
//	virtual bool ReadMuxout() = 0;
};

#endif
