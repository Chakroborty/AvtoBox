//---------------------------------------------------------------------------

#ifndef Adf4360H
#define Adf4360H
//---------------------------------------------------------------------------

#include <vcl.h>
//#include "UsbDefines.h"
#include <math.h>

//typedef void __fastcall(__closure *TWriteReg)(DWORD Data);

typedef void (__closure *TWritePll)(DWORD Addr, UINT32 Data);
typedef UINT32 (__closure *TReadPll)(DWORD Addr);

class TAdf4360
{
public:
	TAdf4360(double Freference);
    TAdf4360(TWritePll WriteReg, TReadPll ReadReg);
	~TAdf4360();

    __property double Freference = {read = ReadFref, write = WriteFref };
    __property double Frequency = {read = ReadFreq, write = WriteFreq };
    __property double Fpfd = {read = ReadFcomp, write = WriteFcomp };
    __property double Fstep = {read = ReadFstep, write = WriteFstep };
            
    __property  DWORD RCounter = {read = ReadR, write = WriteR};
    __property  DWORD ACounter = {read = ReadA, write = WriteA};
    __property  DWORD BCounter = {read = ReadB, write = WriteB};

    __property  DWORD RRegister = {read = ReadRReg, write = WriteRReg};
    __property  DWORD CRegister = {read = ReadCReg, write = WriteCReg};
    __property  DWORD NRegister = {read = ReadNReg, write = WriteNReg};

    __property DWORD PowerLevel = {read = ReadPwrLvl, write = WritePwrLvl };
    __property DWORD PowerDown = {read = ReadPwrDown, write = WritePwrDown };
    __property DWORD PdPolarity = {read = ReadPdPolarity, write = WritePdPolarity };
    __property DWORD CpGain = {read = ReadCpGain, write = WriteCpGain };
    __property DWORD MuteTilLd = {read = ReadMuteTilLd, write = WriteMuteTilLd };
    __property DWORD OutputPower = {read = ReadOutPwr, write = WriteOutPwr };
    __property DWORD Muxout = {read = ReadMuxout, write = WriteMuxout };
    __property DWORD CurrentSetting = {read = ReadCurSet, write = WriteCurSet };
    __property DWORD CounterReset = {read = ReadCurSet, write = WriteCurSet };
    __property DWORD CpThreeState = {read = ReadCpThreeState, write = WriteCpThreeState };
    __property DWORD Prescaler = {read = ReadPresc, write = WritePresc };
    __property DWORD DivideOutput = {read = ReadDivide, write = WriteDivide };
    __property DWORD BandSelectClock = {read = ReadBand, write = WriteBand };

    __property bool LockDetect = {read = ReadLockDetect};

    void CalculateRegisters();
//	__property  TWriteReg WriteRegister  = {read = FWriteReg, write = FWriteReg};
    void Load();
    void LoadControl();
    void LoadRdivider();
	void LoadNdivider();

protected:
    double ReadFref() { return Fref; }
    void WriteFref(double newFref) { Fref = newFref; }

    double ReadFreq() { return Freq; }
    void WriteFreq(double newFreq);// { Freq = newFreq; }

    double ReadFcomp() { return Fcomp; }
    void WriteFcomp(double newFreq) { Fcomp = newFreq; }

    double ReadFstep() { return Step; }
    void WriteFstep(double newFreq) { Step = newFreq; }

    DWORD ReadR() { return R; }
    void WriteR(DWORD newR) { R = newR; }

    DWORD ReadA() { return A; }
    void WriteA(DWORD newA) {A = newA; }

    DWORD ReadB() { return B; }
    void WriteB(DWORD newB) { B = newB; }

    DWORD ReadPwrLvl() { return PwrLvl; }
    void WritePwrLvl(DWORD newPowerLevel) { PwrLvl = newPowerLevel; }

    DWORD ReadPwrDown() { return PwrDown; }
    void WritePwrDown(DWORD newPwrDown) { PwrDown = newPwrDown; }

    DWORD ReadPdPolarity() { return PdPolar; }
    void WritePdPolarity(DWORD newPdPolarity) { PdPolar = newPdPolarity; }

    DWORD ReadCpGain() { return Gain; }
    void WriteCpGain(DWORD newGain) { Gain = newGain; }

    DWORD ReadMuteTilLd() { return Mute; }
    void WriteMuteTilLd(DWORD newMute) { Mute = newMute; }

    DWORD ReadOutPwr() { return OutPwr; }
    void WriteOutPwr(DWORD newOutPwr) { OutPwr = newOutPwr; }

    DWORD ReadMuxout() { return MuxMode; }
    void WriteMuxout(DWORD newMuxMode) { MuxMode = newMuxMode; }

    DWORD ReadCurSet() { return CurSet; }
    void WriteCurSet(DWORD newCurSet) { CurSet = newCurSet; }

    DWORD ReadCntReset() { return CntReset; }
    void WriteCntReset(DWORD newCntReset) { CntReset = newCntReset; }

    DWORD ReadCpThreeState() { return CpThreeSt; }
    void WriteCpThreeState(DWORD newCpThreeSt) { CpThreeSt = newCpThreeSt; }

    DWORD ReadPresc() { return Presc; }
    void WritePresc(DWORD newPresc) { Presc = newPresc; }

    DWORD ReadDivide() { return Divide; }
    void WriteDivide(DWORD newDivide) { Divide = newDivide; }

    DWORD ReadBand() { return Band; }
    void WriteBand(DWORD newBand) { Band = newBand; }

    DWORD ReadRReg() { return RReg; }
    void WriteRReg(DWORD newRReg) { RReg = newRReg; }

    DWORD ReadCReg() { return CReg; }
    void WriteCReg(DWORD newCReg) { CReg = newCReg; }

    DWORD ReadNReg() { return NReg; }
    void WriteNReg(DWORD newNReg) { NReg = newNReg; }

    bool WaitXfer();

    bool ReadLockDetect();

private:
	const int CB_R;
	const int CB_N;
	const int CB_C;

    double Fref;
    double Fcomp;
    double Freq;
    double Step;

    DWORD R;
    DWORD A;
    DWORD B;

    DWORD PwrLvl;
    DWORD PdPolar;
    DWORD Gain;
    DWORD Mute;
    DWORD OutPwr;
    DWORD MuxMode;
    DWORD CurSet;
    DWORD CntReset;
    DWORD CpThreeSt;
    DWORD PwrDown;
    DWORD Presc;
    DWORD Divide;
    DWORD Band;

    DWORD RReg;
    DWORD CReg;
    DWORD NReg;

//    TWriteReg FWriteReg;

    TWritePll WriteDword;
    TReadPll ReadDword;

};

#endif


