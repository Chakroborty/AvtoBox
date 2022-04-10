//---------------------------------------------------------------------------

#ifndef EBOARD830H
#define EBOARD830H
#include "HMC830.h"
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------

 class HMC830BR{
  public:
  HMC830BR();
  ~HMC830BR();
	UsbDeviceManager* DeviceManager;
	TBOARD830* DeviceUSB;
	HMC830*  MXHMC830;
	void __fastcall DeviceConnected(TBOARD830 *newDevice);
	void __fastcall DeviceRemoved(TBOARD830 *oldDevice);
	DWORDLONG __fastcall SendDATA_SPI_USB(DWORD DATH, DWORD DATL);
	DWORDLONG __fastcall SendDATA_SPI_USB(DWORD DAT);
	long REGNoAdres(int REG);
 };



#endif
