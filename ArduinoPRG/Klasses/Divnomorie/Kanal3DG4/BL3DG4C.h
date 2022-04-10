// ---------------------------------------------------------------------------
#include "Tri3PX2.h"
#include "Tri3DG2.h"
#include "MFC1DG.h"
#include "MFC2DG.h"
#include "MFCGDG.h"
#include "Tri3DG10.h"
//#include "MFC2Perexv.h"
//#include "MFC2Perexv830.h"
#include "UsbDeviceManager.h"
#include "Rpu16PX.h"
//#include "Test3DG1.h"
#include "Unit1.h"
#ifndef BL3DG4CH
#define BL3DG4CH

// ---------------------------------------------------------------------------
class MFC2Perexv830;
class MFC1Perexv;
class MFC2Perexv;
class BL3DG4
{
	public:
	BL3DG4(bool Isp830);
	~BL3DG4();

	UsbDeviceManager *DeviceManager;
	TRpu16* DeviceUSB;

	Tri3PX2 *ModulPX2;
	MFC1Perexv *ModulFCH1PX;
	MFC2Perexv *ModulFCH2PX;
	MFC2Perexv830 *ModulFCH2_830;
	Tri3DG10 *Modul3DG10;
	Tri3DG2 *ModulDG2;
	MFC1DG *ModulFCH1;
	MFC2DG *ModulFCH2;
	MFCG *ModulFCHG;

	void __fastcall DeviceConnected(TRpu16 *newDevice);
	void __fastcall DeviceRemoved(TRpu16 *oldDevice);
	DWORDLONG __fastcall SendDATA_SPI_USB(DWORD DATH, DWORD DATL);

	bool Wait_SPI;
//	bool Ispol830;
	int blTupe;     //0 - 3Дж4 1-SHASSI
	int MFCH_DG;    //1 - DG 0- PX
	int ReadSN_Ver(int SelectedModul);
	void __fastcall WriteSN_Ver(int SelectedModul,DWORD ver,DWORD num);
	void  BL3DG4::WriteBlokSN(DWORD ValSN);
	DWORD BL3DG4::ReadBlokSN();

	void FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);
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
	/* --------------------Прогрузка 3Дж10 -----------------------------*/
	void FriqSET10(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);
	double LOADGET1();
	/* --------------------Прогрузка МФЧГ -----------------------------*/
	void MFCHG_Fset2(int Cur);
	void MFCHG_Fset5(int Cur,int Pol);
	void MFCHG_Fset12(int Cur,int Pol);

    /************************ Синхронизация МФЧГR ***************/
	void MFCHG_OGvnutr(int OG);
    void MFCHG_Sinc(double Fg1);
	/*=================  End of Прогрузка МФЧГ  ==================*/
	
	/*---------  ПСИ  ----------*/
	void MFCHG_Fset3(double Fg4159, int Inic);
	void MFCHG_FsetINDEX(double Fg4159);
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
    void KanalInitial10();
	void MFCH2_830_Sint2(unsigned long &, unsigned long &, int i);
	double FriqOUT(void);
	//MFC2Perexv *ModulFCH2;


	void MFCH2_OGvnutr(bool OG);
	void MFCH2DG_OGvnutr(bool OG);

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
