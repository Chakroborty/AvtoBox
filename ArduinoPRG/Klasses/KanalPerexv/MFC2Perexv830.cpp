//---------------------------------------------------------------------------


#pragma hdrstop
#include "HMC830.h"
#include "MFC2Perexv830.h"
#include "Unit1.h"
#include "UsbDeviceManager.h"
//---------------------------------------------------------------------------
  MFC2Perexv830::MFC2Perexv830()
   {
	 Fget2 = Fsin2 = 2300;
	 Sw_Ext_In = 0;// ѕереключатель опорной частоты
	 Sw_G = 0;  //(hmc839)
	 Sw_CE = 0; //¬кл/выкл adf4001
	 Sw_F = 0; //(adf4001)
	 Sint2_HMC830 = new HMC830(2300,0x7F,54,100);
	 AdrMod = 0xD<<28;//0xF<<28;
     ADF4001RG0 = 20;
	 ADF4001RG1 = 12800;
	 ADF4001RG2 = 516132;
	 ADF4001RG3 = 0;

   }
  MFC2Perexv830::~MFC2Perexv830()
   {

   }
  void MFC2Perexv830::SetFreq(double fget)
   {

              c = true;
			  Fget2 = fget;
					 if (fget>=2299 && fget<=2301)
						 { Fget2 = Fsin2 =fget;


            			   c = false;
						 }
            			   if (fget>=1174 && fget<=1176)
						 { Fget2 = Fsin2 =fget;
						   c = false;
            			 }
            			   if (fget>=874 && fget<=876)
						 {  Fget2 = Fsin2 =fget;
            			   c = false;
            			 }
            			   if (c)
            			   {
						   Fget2 = Fsin2 = 2300;
            			   Sw_G  = 0x100;
						   }




   //------------------------------------------------------------------------
	Sint2_HMC830->SetFreq(Fsin2) ;


   }
  DWORD MFC2Perexv830::Kluch(int i)

   {
	 DWORD  SW_SW=0;
		switch (i)
   {

	 case 0:

	 SW_SW = AdrMod|(0x4<<24)|(0x12<<16)|(Sw_Ext_In<<15);break;

	 case 1:

	 SW_SW = AdrMod|(0x4<<24)|(0x15<<16)|(Sw_F<<15);break;

	 case 2:

	 SW_SW = AdrMod|(0x4<<24)|(0x14<<16)|(Sw_CE<<15);break;

	 case 3:

	 SW_SW = AdrMod|(0x4<<24)|(0x13<<16)|(Sw_G<<15);break;

	 default : SW_SW = AdrMod|(0x4<<24)|(0x13<<16)|(Sw_G<<15);break;

   }
	return  SW_SW;
  }
  int MFC2Perexv830::SintLOAD_H(void)
  {
		return  AdrMod|MFC2Perexv830::AdrDev::Sint<<24;
  }
  int MFC2Perexv830::SintLOAD_L(int Poz)
   {  int i;
	  if (Poz>=0)
	  {  i = Poz;
	  }
		int  SW_SW;
		switch (i)
   {

	 case 0:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 1:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 2:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 3:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 4:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 5:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 6:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 7:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 8:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 9:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 10:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 11:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	  case 12:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 13:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 14:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 15:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 16:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 17:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 case 18:

	 SW_SW = Sint2_HMC830->RegLoad830(i);break;

	 default : SW_SW = Sint2_HMC830->RegLoad830(0);break;

   }

	return  SW_SW<<1;

   }
  void MFC2Perexv830::OGvnutr(bool OG){
	if (OG) {
	   Sw_Ext_In = 0; //ѕереключатель опорной частоты
	   Sw_CE = 0; //¬кл/выкл adf4001
	   Sw_F = 1; //(adf4001)

  } else {
	 Sw_Ext_In = 1; //ѕереключатель опорной частоты
	 Sw_CE = 1; //¬кл/выкл adf4001
	 Sw_F = 0; //(adf4001)
  }
}
DWORD MFC2Perexv830::ADF4001(int i)
   {
	 DWORD  SW_SW;
		switch (i)
   {

	 case 0:

	 SW_SW = (ADF4001RG3<<2|3)<<8;break;

	 case 1:

	 SW_SW = ((ADF4001RG2+1)<<2|2)<<8;break;

	 case 2:

	 SW_SW = (ADF4001RG0<<2|0)<<8;break;

	 case 3:
     SW_SW = (ADF4001RG1<<2|1)<<8;break;

	 case 4:
	 SW_SW = (ADF4001RG2<<2|2)<<8;break;
	 case 5:
	 SW_SW = AdrMod|(0x5<<24);break;

	 default : SW_SW = AdrMod|0x5<<24;break;

   }
	return  SW_SW;
  }
#pragma package(smart_init)
