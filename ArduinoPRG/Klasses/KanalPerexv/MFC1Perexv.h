// ---------------------------------------------------------------------------
#include "HMC700.h"
#ifndef MFC1PerexvH
#define MFC1PerexvH

// ---------------------------------------------------------------------------
class MFC1Perexv
{
public:
	

	MFC1Perexv();
	~MFC1Perexv();


	double Fget1;
	int On_Of; // Переключатель питания мс

	void SetFreq(double fget);
	int SintLOAD_L(int Poz);
	int SintLOAD_H(void);
	int Kluch(void);

private:
	HMC700 *Sint1_HMC700;
		int AdrMod;

	enum AdrDev {
		Kontr_I2C = 0x1,
		Perekl = 0x4, // 875
		Sint = 0xB,
		Kontrol = 0xE

	};

};
#endif
