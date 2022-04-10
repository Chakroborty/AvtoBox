//---------------------------------------------------------------------------
#include "HMC830.h"
#ifndef MFC2Perexv830H
#define MFC2Perexv830H
#include "BL3PX1.h"
//---------------------------------------------------------------------------
class MFC2Perexv830
{
	public:
	MFC2Perexv830();
   ~MFC2Perexv830();
	double Fget2;
	double Fsin2;

		int Sw_Ext_In; //ѕереключатель опорной частоты
    	int Sw_G;  //(hmc839)
    	int Sw_CE; //¬кл/выкл adf4001
		int Sw_F; //(adf4001)
		bool c;

	void SetFreq(double fget);
	DWORD Kluch(int i);
	int SintLOAD_L(int Poz);
	int SintLOAD_H(void);
	void OGvnutr(bool OG);
	DWORD ADF4001(int i);
  private:
	HMC830 *Sint2_HMC830;
    int AdrMod;
      enum AdrDev
		{
		Kontr_I2C = 0x1,
		Perekl = 0x4,
		GenOC = 0x5,
		Sint = 0xC,
		Kontrol = 0xE

		};
    int ADF4001RG0;
	int ADF4001RG1;
	int ADF4001RG2;
	int ADF4001RG3;

};


#endif
