// ---------------------------------------------------------------------------

#ifndef BL3Cr6H
#define BL3Cr6H

#include "Mod3CR5.h"
#include "UsbDeviceManager.h"

/**
 * -------------------------------------------------------------------------
 */
class Bl3CR6 {
public: // User declarations
	Bl3CR6(bool BlCR6);
	~Bl3CR6();

	/***********************************************/
	 UsbDeviceManager *DeviceManager;
	 UKV3CR6I8* DeviceUSB;
	 void __fastcall DeviceConnected(UKV3CR6I8 *newDevice);
	 void __fastcall DeviceRemoved(UKV3CR6I8 *oldDevice);
	/********************************************************/
	void SetATT_UPC(double Db);
	void SetAMPL_UPC(int Db);

	/************************************************/
	void SetFriq(int Kanal,int Clbr,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC);
	void SetFVC(int Fset);
	void SetPC(bool PC40);
	void SetATT_Pres(int Db);
	void SetVX(bool Priem,int DB );
	void SetALL(bool Fset, bool ATTset, bool VGAset, bool KLset);

	/************************************************/
	 bool GetBlTyp3CR6(void);
	 enum NoiseG
	 {OTKL = 0,
	 LEV0 = 0X4,
	 LEV_10 = 0X4,
	 LEV_20 = 0X5,
	 LEV_30 = 0X3
	 };

	  Mod3CR5 *KanalKV;


	 private:	// User declarations

	 bool Typ3CR6;
	 int NG;
	 protected:

	 };

	 #endif
