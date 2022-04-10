//---------------------------------------------------------------------------


#pragma hdrstop

#include "MFC1Perexv.h"
//#include "HMC700.h"
 // class  HMC700;
//---------------------------------------------------------------------------
  MFC1Perexv::MFC1Perexv()
   { Sint1_HMC700 = new HMC700(2350,0x5,45,100);
	 Fget1 = 2300;
	 AdrMod = 0xD<<28;
	 On_Of = 1<<15;// Переключатель питания мс

   }
   MFC1Perexv::~MFC1Perexv()
   {

   }
   void MFC1Perexv::SetFreq(double fget)
  {       if (fget>1690&&fget<=3936)
		{
		 Fget1 = fget;
	 }
	 else
	 {
	   Fget1 = 2300;
     }
	 Sint1_HMC700->SetFreq(Fget1);
  }
   int MFC1Perexv::Kluch()
   {
	 return  AdrMod|0x4<<24|0x16<<16|On_Of;
   }
   int MFC1Perexv::SintLOAD_L(int Poz)
   {  int i;
			if (Poz>=0)
	  {  i = Poz;
	  }
		 int  SW_SW;

			switch (i)
	   {

		 case 0:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 1:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 2:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 3:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 4:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 5:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 6:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 7:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 8:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 9:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 10:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 11:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		  case 12:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 13:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 14:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;

		 case 15:

		 SW_SW = Sint1_HMC700->RegLoad700(i);break;



		 default : SW_SW = Sint1_HMC700->RegLoad700(0);break;

	   }

	return  SW_SW<<1;

   }
   int MFC1Perexv::SintLOAD_H()
   {
	return  AdrMod|MFC1Perexv::AdrDev::Sint<<24;
   }
#pragma package(smart_init)
