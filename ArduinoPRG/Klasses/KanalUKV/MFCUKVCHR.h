// ---------------------------------------------------------------------------
#include "ADF4153.h"
#ifndef MFCUKVCHRH
#define MFCUKVCHRH
 #include <math.h>
// ---------------------------------------------------------------------------
class MFCUKV02 {
public:
	double Fget1;
	double Fget2,Fsint2;


	MFCUKV02();
	~MFCUKV02();
	/**
	 * <url>element://model:project::Test3PX1/design:node:::rqb4yht5xnt_n</url>
	 */
	void SetFreq(double fget);
	void SetFreq2(double fget);
	int LoadGET1(int Reg);
	int LoadGET2(int Reg);
	int Kluch(void);
	int RefExt;

private:
	ADF4153 *Sint1_ADF4153;
	ADF4153 *Sint2_ADF4153;
	int AdrMod,Band;
	DWORD SW_SW;
	enum AdrDev {
		Kontr_I2C = 0x1, Perekl = 0x4, // 875
			Sint = 0xB, Kontrol = 0xE

	};

		enum Ustr
	{
   OTHER = 0,	// Режим параллельных данных (ключи, фильтры, ...)
   Sin1 =  1,
   Sin2 =  2,
   ATT1 =  3,
   ATT2 =  4  };

};
#endif
