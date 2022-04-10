//---------------------------------------------------------------------------
#include "HMC839.h"
#ifndef MFC2PerexvH
#define MFC2PerexvH
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------

class MFC2Perexv
{
	public:
	MFC2Perexv();
   ~MFC2Perexv();
	 double Fget2;
	double Fsin2;

		int Sw_Ext_In; //ѕереключатель опорной частоты
		int Sw_G;  //(hmc839)
		int Sw_CE; //¬кл/выкл adf4001
		int Sw_F; //(adf4001)
		bool c;
	void OGvnutr(bool OG);
	void SetFreq(double fget);
	DWORD Kluch(int i);
	int SintLOAD_L(int Poz);
	DWORD SintLOAD_H(void);

  private:
	HMC839 *Sint2_HMC839;
	int AdrMod;

	  enum AdrDev
		{
		Kontr_I2C = 0x1,
		Perekl = 0x4,
		GenOC = 0x5,
		Sint = 0xC,
		Kontrol = 0xE

		};
 //-----------------------ADF4001--------------------------
	int ADF4001RG0;
	int ADF4001RG1;
	int ADF4001RG2;
	int ADF4001RG3;
	protected:

};

#endif
