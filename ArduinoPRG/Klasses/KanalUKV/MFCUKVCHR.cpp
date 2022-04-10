//---------------------------------------------------------------------------


#pragma hdrstop
 #include "UsbDeviceManager.h"
#include "MFCUKVCHR.h"

//---------------------------------------------------------------------------
  MFCUKV02::MFCUKV02()
   {
	 Fget1 = 2300;
	 AdrMod = 0x9 << 28;
	 Band = 0;
	 RefExt = 1;// Переключатель опорной частоты
	 Sint1_ADF4153 = new ADF4153(1700,7,170,false,10,2,1);
	 Sint2_ADF4153 = new ADF4153(1600,4,160,true,10,0.2,1);


   }
   MFCUKV02::~MFCUKV02()
   {

   }
   void MFCUKV02::SetFreq(double fget)
  {       if (fget>=1670&&fget<=2920)
		{
		 Fget1 = 2*floor(fget/2+0.5);

		 if (Fget1>2920) {
		 Fget1 =  2920;
		 }
		 if (Fget1<1670) {
		 Fget1 =  1670;
		 }
	 }
	 else
	 {
	   Fget1 = 1690;
	 }
	 Sint1_ADF4153->SetFreq(Fget1);

  }
   void MFCUKV02::SetFreq2(double fget)
 {   if (fget>=1599&&fget<=1601)
	 {   Band =0;
		 Fget2 = 0.2*floor(fget*5);
		  if (Fget2<1599)
		  {
			Fget2 = 1599;
		  }
         Fsint2 = Fget2;
	 }
	 else
	 {
	   if (fget>=399&&fget<=401)
	   { Band = 1;
		 Fget2 = 0.2*floor(fget*5);
		 if (Fget2<399)
		 {
            Fget2=399;
         }

	   } else
	   {
		 Fget2 = 400;
	   }
	   Fsint2 = Fget2*4;
	 }
 
	Sint2_ADF4153->SetFreq(Fsint2);
  }

   int MFCUKV02::Kluch()
   {
  SW_SW =  Ustr::OTHER<<24 | RefExt<<8| Band<<4;
  SW_SW = AdrMod + SW_SW ;
  return  SW_SW;
   }
   int MFCUKV02::LoadGET1(int Reg)
  { int i;
  if (Reg >= 0 && Reg < 16)
   {
	 i = Reg;

   }
   else
   {
	i = 0;
   }

	SW_SW =Ustr::Sin1<<24|Sint1_ADF4153->RegLoad4153(i);
	SW_SW = AdrMod + SW_SW ;
	return  SW_SW;

   }
   int MFCUKV02::LoadGET2(int Reg)
   {
	 int i;
  DWORD  SW_SW;
 if (Reg >= 0 && Reg < 16)
   {
	 i = Reg;

   }
   else
   {
	i = 0;
   }
SW_SW =Ustr::Sin2<<24|Sint2_ADF4153->RegLoad4153(Reg);
		SW_SW = AdrMod + SW_SW ;
	return  SW_SW;
   }
#pragma package(smart_init)
