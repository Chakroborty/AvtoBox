// ---------------------------------------------------------------------------
#ifndef BL3PX1H
#define BL3PX1H
#include "Tri3PX2.h"
#include "MFC1Perexv.h"
#include "MFC2Perexv.h"
#include "MFC2Perexv830.h"
#include "UsbDeviceManager.h"
#include "Rpu16PX.h"

//#include "Unit1.h"

// ---------------------------------------------------------------------------
class MFC2Perexv830;

class BL3PX1
{
public:
	BL3PX1(bool Isp830);
	~BL3PX1();

	UsbDeviceManager *DeviceManager;
	TRpu16* DeviceUSB;

	void __fastcall DeviceConnected(TRpu16 *newDevice);
	void __fastcall DeviceRemoved(TRpu16 *oldDevice);
	DWORDLONG __fastcall SendDATA_SPI_USB(DWORD DATH, DWORD DATL);

	bool Wait_SPI;
	bool Ispol830;
	int ReadSN_Ver(int SelectedModul);
	void __fastcall WriteSN_Ver(int SelectedModul,DWORD ver,DWORD num);
	void  BL3PX1::WriteBlokSN(DWORD ValSN);
	DWORD BL3PX1::ReadBlokSN();
	/**
	 * <url>element://model:project::Test3PX1/design:node:::hf6wo2i0tjfob27hg_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::uhdju1h2ina2y67wn_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::zl54etpuk6s8uejyg_n</url>
	 */
	void FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);

	
	/**
	 * <url>element://model:project::Test3PX1/design:node:::st71xwsdy70vuu0rf_n</url>
	 */
	void MFCH1_Fset(double Fg1);
    void MFCH1_Rset(int R);
	/**
	 * <url>element://model:project::Test3PX1/design:node:::fzr217fsa1k4x56rq_n</url>
	 * <url>element://model:project::Test3PX1/design:node:::0u80tcl1kws_n</url>
	 */
	void MFCH2_Fset(double Fg1);
	void ATT1Set(double dB);
	void ATT2Set(double dB);
	void AmplON(bool ON);
	double Geterodin1();
	double Geterodin2();
	void KanalInitial();
	void MFCH2_830_Sint2(unsigned long &, unsigned long &, int i);
	double FriqOUT(void);
	MFC2Perexv *ModulFCH2;
	MFC2Perexv830 *ModulFCH2_830;
	/**
	 * <url>element://model:project::Test3PX1/design:node:::wvgprtcur20pp2t0j_n</url>
	 */
	void MFCH2_OGvnutr(bool OG);
	Tri3PX2 *ModulPX2;
	MFC1Perexv *ModulFCH1;
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
