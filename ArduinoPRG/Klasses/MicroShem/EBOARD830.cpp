//---------------------------------------------------------------------------

#pragma hdrstop
#include "BOARD830.h"
#include "EBOARD830.h"

#include "BOARD830.h"//#include "Rpu16PX.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
HMC830BR::HMC830BR()
{
	DeviceManager = new UsbDeviceManager;   /* TODO -cUSB : USB Device VID PID в UsbDefines.h*/
	MXHMC830 = new HMC830(2600,7,52,50);
	DeviceManager->OnAddDevice = DeviceConnected;
	DeviceManager->OnRemoveDevice = DeviceRemoved;
	DeviceUSB = NULL;

}
 HMC830BR::~HMC830BR(){
 }
void __fastcall HMC830BR::DeviceConnected(TBOARD830 *newDevice)
{

int iNumber = DeviceManager->Devices->IndexOf(newDevice);
 DeviceUSB = (TBOARD830*)DeviceManager->Devices->Items[iNumber];
  Sleep(200);
   /*
   if (DeviceUSB = NULL)
   return;
   */

 Form1->StatusBar1->Panels->Items[0]->Text = "BOARD HMC830";

}
void __fastcall HMC830BR::DeviceRemoved(TBOARD830 *oldDevice)
{

 Form1->StatusBar1->Panels->Items[0]->Text = "USB ОЖИДАНИЕ";
 DeviceUSB = NULL;

}
DWORDLONG __fastcall  HMC830BR::SendDATA_SPI_USB(DWORD DATH,DWORD DATL)
{ /*---------- Прогрузка SendDATA_SPI_USB  ----------*/

	if (DeviceUSB == NULL)
		return 0;
	DWORDLONG res=0;
   //	DWORD retDH;
	//DWORD retDL;
	DWORD dwData, dwAddr, dwStatus;
	dwData = DATH<<24|DATL;

	Application->ProcessMessages();
	//DeviceUSB->WriteDword(DATH,DATL);
	DeviceUSB->WriteDwordADR(dwData);

	//	Form1->WaitSPI_Timer->Enabled=TRUE;
	//	Wait_SPI=FALSE;
	//	while((dwData && 0x80000000)==0) //wait rdy SPI
	//	{
	//		dwStatus=DeviceUSB->ReadDword(2,dwData);
	//		if(Wait_SPI)
	//		{
	//			ShowMessage("Таймаут SPI");break;
	//		}
	//			Application->ProcessMessages();
	//		}
	//	Form1->WaitSPI_Timer->Enabled=FALSE;
	// res=0;
	// dwStatus=DeviceUSB->ReadDword(0,retDH);
	// Application->ProcessMessages();
	// dwStatus=DeviceUSB->ReadDword(1,retDL);
	// Application->ProcessMessages();
	// //res=retDH;
	// res=retDL;
	// res=(res<<32)|retDH;
 return res;
}
 DWORDLONG __fastcall  HMC830BR::SendDATA_SPI_USB(DWORD DAT)
{ /*---------- Прогрузка SendDATA_SPI_USB  ----------*/

	if (DeviceUSB == NULL)
		return 0;
	DWORDLONG res=0;
//	DWORD retDH;
//	DWORD retDL;
//	DWORD dwData, dwAddr, dwStatus;
//	dwData=0;

	Application->ProcessMessages();
	DeviceUSB->WriteDwordADR(DAT);


  //	Form1->WaitSPI_Timer->Enabled=TRUE;
  //	Wait_SPI=FALSE;
//	while((dwData && 0x80000000)==0) //wait rdy SPI
//	{
//		dwStatus=DeviceUSB->ReadDword(2,dwData);
//		if(Wait_SPI)
//		{
//			ShowMessage("Таймаут SPI");break;
//		}
//			Application->ProcessMessages();
//		}
  //	Form1->WaitSPI_Timer->Enabled=FALSE;
	// res=0;
	// dwStatus=DeviceUSB->ReadDword(0,retDH);
	// Application->ProcessMessages();
	// dwStatus=DeviceUSB->ReadDword(1,retDL);
	// Application->ProcessMessages();
	// //res=retDH;
	// res=retDL;
	// res=(res<<32)|retDH;
 return res;
}


long HMC830BR::REGNoAdres(int REG)
{
   return MXHMC830->RegLoad830(REG);//<<1
}

#pragma package(smart_init)
