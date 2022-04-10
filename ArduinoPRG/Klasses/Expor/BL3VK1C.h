// ---------------------------------------------------------------------------
#include "Tri3PX2.h"
#include "Tri3VK6.h"
#include "MFC1VK.h"
#include "MFC2VK.h"
#include "MFCGDG.h"
#include "MFC2Perexv.h"
#include "MFC2Perexv830.h"
#include "Tri3DG10.h"
#include "UsbDeviceManager.h"
#include "Rpu16PX.h"
//#include "Test3DG1.h"
#include "Unit1.h"
#ifndef BL3VK1CH
#define BL3VK1CH

// ---------------------------------------------------------------------------
class MFC2Perexv830;
class MFC1Perexv;
class MFC2Perexv;
class BL3VK1
{
	public:
	BL3VK1(bool Isp830);
	~BL3VK1();

	UsbDeviceManager *DeviceManager;
	TRpu16* DeviceUSB;

	Tri3PX2 *ModulPX2;
	MFC1Perexv *ModulFCH1PX;
	MFC2Perexv *ModulFCH2PX;
	MFC2Perexv830 *ModulFCH2_830;

	Tri3VK6 *ModulVK6;
	MFC1VK *ModulFCH1;
	MFC2VK *ModulFCH2;


	void __fastcall DeviceConnected(TRpu16 *newDevice);
	void __fastcall DeviceRemoved(TRpu16 *oldDevice);
	DWORDLONG __fastcall SendDATA_SPI_USB(DWORD DATH, DWORD DATL);

	bool Wait_SPI;
	bool Ispol830;
	int MFCH_DG;    //1 - DG 0- PX
	int blTupe;     //0 - 3Vk1 1- 3Vk11
	int ReadSN_Ver(int SelectedModul);
	void __fastcall WriteSN_Ver(int SelectedModul,DWORD ver,DWORD num);
	void  BL3VK1::WriteBlokSN(DWORD ValSN);
	DWORD BL3VK1::ReadBlokSN();

	void FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);
	void FriqSETTST(double Fin1,bool Ampl,int DB1,int DB2,int Kanal,int Slp1,int Slp2, int mod);
/*----------  Настройка ДЖ  ----------*/
	
	void MFCH1_Fset3(double Fg4159,double Fg1,int Fas1,int Fas2);
	void MFCH2_Fset(double Fg1);
	void MFCH1_Fset(double Fg1);
	void MFCH1_Fset1(double Fg4159,double Fg1,int Log);
	void MFCH1_Fset2(int  Pol);
	void MFCH2_Fset1(int Cur);
	void MFCH2_Fset2(int Cur);
	void MFCH2_Fset3(double Fg1,int Fas1,int Fas2);
	/*****************ПСИ ДЖ********************************************/
	void MFCH1_FsetDG(double Fg1);
	void MFCH2_FsetDG(double Fg1,int Fas1);

	

	/*---------  ПСИ  ----------*/
	void MFCH1_FsetPX(double Fg1);
	void MFCH2_FsetPX(double Fg1);
	

	void MFCH2_Sinc(double Fg1);
	void ATT1Set(double dB);
	void ATT2Set(double dB);
	void AmplON(bool ON);
	double Geterodin1();
	double Geterodin2();
	void KanalInitial();
	void TestInitial(int SL1, int SL2, int mod);
	void MFCH2_830_Sint2(unsigned long &, unsigned long &, int i);
	double FriqOUT(void);
	//MFC2Perexv *ModulFCH2;
	/**-------------------3Дж10-----------------------**/
	void FriqSET10(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);

	void MFCH2_OGvnutr(bool OG);
	void MFCH2DG_OGvnutr(bool OG);
 	void KanalInitial10();
	protected:
	void __fastcall SPI_InitI2c(void);
	BYTE SPI_ReadBytePower(BYTE ModulADr,BYTE Addr,bool by_way);
	void SPI_WriteBytePower(BYTE ModulADr,BYTE Addr, BYTE Data,bool by_way);
	BYTE __fastcall SPI_ReadBytePowerEeprom(BYTE ModulADr,WORD Addr,bool by_way);
	BYTE __fastcall SPI_I2C_WaitRdy(BYTE ModulADr,bool by_way);
	BYTE __fastcall SPI_I2C_GetStatus(BYTE ModulADr,bool by_way);
	BYTE __fastcall SPI_I2C_rdByte(BYTE ModulADr,BYTE CMD,BYTE adr,bool by_way);
	bool __fastcall SPI_I2C_wrByte(BYTE ModulADr,BYTE CMD,BYTE D,BYTE adr,bool by_way);
	/********************************************************************************/

	void __fastcall SPI_WriteBytePowerEeprom(BYTE ModulADr,BYTE D,WORD Addr,bool by_way);
	void __fastcall SPI_WritePagePowerEeprom(BYTE ModulADr,WORD Addr, PBYTE Data, BYTE Size,bool by_way);
	void __fastcall SPI_EraseBlockPowerEeprom(BYTE ModulADr,WORD Addr,bool by_way);
	void __fastcall SPI_ErasePageWriteBytePowerEeprom(BYTE ModulADr,WORD Addr, BYTE Data,bool by_way);
	private:




	int i, j;
};
#endif
