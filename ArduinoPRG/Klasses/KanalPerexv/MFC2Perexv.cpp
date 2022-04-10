//---------------------------------------------------------------------------


#pragma hdrstop
#include "HMC839.h"
#include "MFC2Perexv.h"

//---------------------------------------------------------------------------
   MFC2Perexv::MFC2Perexv()
   {
	 Fget2 = 2300;
	 Fsin2 = 2300;
	 Sw_Ext_In = 0;// ѕереключатель опорной частоты
	 Sw_G = 0;  //(hmc839)
	 Sw_CE = 0; //¬кл/выкл adf4001
	 Sw_F = 0; //(adf4001)
	 Sint2_HMC839 = new HMC839(2300,0x40,54,100);
	 AdrMod = 0xD<<28;//0xF<<28;

	 ADF4001RG0 = 20;
	 ADF4001RG1 = 12800;
	 ADF4001RG2 = 516132;
	 ADF4001RG3 = 0;


   }
   MFC2Perexv::~MFC2Perexv()
   {

   }
  void MFC2Perexv::SetFreq(double fget)
   {

              c = true;
			  Fget2 = fget;
					 if (fget>=2299 && fget<=2301)
						 { Fget2 = fget;
            			   Fsin2 = fget;
						   Sw_G  = 1;
            			   c = false;
						 }
            			   if (fget>=1174 && fget<=1176)
						 { Fget2 = fget;
						   Fsin2 = fget;
						   Sw_G  = 1;
						   c = false;
            			 }
            			   if (fget>=874 && fget<=876)
						 {  Fget2 = fget;
            			   Fsin2 = fget*5;
						   Sw_G  = 0x0;
            			   c = false;
						 }
            			   if (c)
            			   {
						   Fget2 = Fsin2 = 2300;
						   Sw_G  = 1;
						   }




   //------------------------------------------------------------------------
	Sint2_HMC839->SetFreq(Fsin2) ;
   }
  DWORD MFC2Perexv::Kluch(int i)

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
	 SW_SW = AdrMod|(0x4<<24)|(0x13<<16)|(1<<15);break;

	 case 4:
	 SW_SW = AdrMod|(0x4<<24)|(0x13<<16)|(0<<15);break;

	 case 5:
	 SW_SW = AdrMod|(0x4<<24)|(0x13<<16)|(Sw_G<<15);break;

	 default : SW_SW = AdrMod|(0x4<<24)|(0x13<<16)|(Sw_G<<15);break;

   }
	return  SW_SW;
  }
  DWORD  MFC2Perexv::SintLOAD_H(void)
  {
  return  AdrMod|MFC2Perexv::AdrDev::Sint<<24;
  }
  int MFC2Perexv::SintLOAD_L(int Poz)
   {  int i;
	  if (Poz>=0)
	  {  i = Poz;
	  }
		int  SW_SW;
		switch (i)
   {

	 case 0:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 1:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 2:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 3:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 4:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 5:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 6:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 7:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 8:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 9:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 10:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 11:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	  case 12:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 13:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 14:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 15:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 16:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;

	 case 17:

	 SW_SW = Sint2_HMC839->RegLoad839(i);break;


	 default : SW_SW = Sint2_HMC839->RegLoad839(16);break;

   }

	return  SW_SW<<1;

   }
  void MFC2Perexv::OGvnutr(bool OG){
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

#pragma package(smart_init)
