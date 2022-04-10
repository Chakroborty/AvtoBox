//---------------------------------------------------------------------------

#pragma hdrstop
//#include "Test3Cr5.h"
#include "BL3Cr6.h"
//---------------------------------------------------------------------------
   Bl3CR6::Bl3CR6(bool BlCR6)
	{
		NG = 0;
		Typ3CR6 = BlCR6;
		if (Typ3CR6)
		{
			KanalKV  = new Mod3CR5(16,false);
		}
		else
		{
			KanalKV  = new Mod3CR5(0,true);
		}
		DeviceManager = new UsbDeviceManager(BlCR6);   /* TODO -cUSB : USB Device VID PID в UsbDefines.h*/
		DeviceManager->OnAddDevice = DeviceConnected;
		DeviceManager->OnRemoveDevice = DeviceRemoved;



	}
   Bl3CR6::~Bl3CR6()
   {

   }

//---------------------------------------------------------------------------

void __fastcall Bl3CR6::DeviceConnected(UKV3CR6I8 *newDevice)
{

int iNumber = DeviceManager->Devices->IndexOf(newDevice);
DeviceUSB = (UKV3CR6I8*)DeviceManager->Devices->Items[iNumber];
/*Form1->Button1->Enabled = true;
Form1->Button2->Enabled = true;
Form1->Button3->Enabled = true;
Form1->Button4->Enabled = true;
  Form1->ComboBox1->Enabled = true;
	Form3->Button2->Enabled=true;
	Form3->Button1->Enabled=true;
	Form3->Button3->Enabled=true;
	Form3->Button6->Enabled=true;
	Form3->Button5->Enabled=true;
*/


}
//---------------------------------------------------------------------------

void __fastcall Bl3CR6::DeviceRemoved(UKV3CR6I8 *oldDevice)
{
/*Form1->Button1->Enabled = false;
Form1->Button2->Enabled = false;
Form1->Button3->Enabled = false;
Form1->Button4->Enabled = false;


   Form1->ComboBox1->Enabled = false;
    Form3->Button2->Enabled=false;
    Form3->Button1->Enabled=false;
    Form3->Button3->Enabled=false;
	Form3->Button6->Enabled=false;
	Form3->Button5->Enabled=false;
*/


}



 bool Bl3CR6::GetBlTyp3CR6()
 {
   return  Typ3CR6;
 }
 void Bl3CR6::SetFriq(int Kanal,int Clbr,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC)
 {
  KanalKV->SetVX(Clbr ,Nois);	//WaidPC = 1  узкая полоса Clbr = 1 вход ант.
  KanalKV->SetATT_Pres(ATTpr); 	//15 Включает усилитель
  KanalKV->SetFVC(Pres);    	// 8,15,0
  KanalKV->SetATT_UPC(ATT);
  KanalKV->SetAmpl_UPC(AmpUPC);
  KanalKV->SetFriq(Fset,Kanal);
  KanalKV->SetPC(WaidPC);
  SetALL(true,true,true,true);
 }
void Bl3CR6::SetALL(bool Fset, bool ATTset, bool VGAset, bool KLset)
{
 /*  int b = KanalKV->Load_sint(5);

 */
 	if (DeviceUSB==NULL) { 	return ; }


 DWORD  dwStatus;


		if ( KLset)
	{
	   Sleep(300);
	  if (!Typ3CR6)
	  {
		dwStatus=DeviceUSB->WriteDword(0,KanalKV->LoadKL(),0,0,0);

	  } else
	  {
		dwStatus=DeviceUSB->WriteDword(1,KanalKV->LoadKL(),0,0,0);

	  }
	}



		if (VGAset)
	{
	  if (!Typ3CR6)
	  {
		dwStatus=DeviceUSB->WriteDword(0,KanalKV->LoadAmpl_UPC(),0,0,0);
	  } else
	  {
		dwStatus=DeviceUSB->WriteDword(1,KanalKV->LoadAmpl_UPC(),0, 0,0);

	  }
	}


  		if (Fset)
	{
		  if (!Typ3CR6)
		 {
			   //	dwStatus=DeviceUSB->WriteDword(4,KanalKV->Load_sint(0),KanalKV->Load_sint(1),KanalKV->Load_sint(3),KanalKV->Load_sint(4));
			   //	dwStatus=DeviceUSB->WriteDword(2,KanalKV->Load_sint(4),KanalKV->Load_sint(5),0,0);
				dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(0),0,0,0);
				dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(1),0,0,0);

				dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(3),0,0,0);
				dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(4),0,0,0);
				dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(4),0,0,0);

				dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(5),0,0,0);

				 //	dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(5),0,0,0);


		 } else
		 {
				dwStatus=DeviceUSB->WriteDword(4,KanalKV->Load_sint(0),KanalKV->Load_sint(1),KanalKV->Load_sint(3),KanalKV->Load_sint(4));
				dwStatus=DeviceUSB->WriteDword(2,KanalKV->Load_sint(4),KanalKV->Load_sint(5),0,0);

					// dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(0),0,0,0);
					// dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(1),0,0,0);
					// dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(2),0,0,0);
					// dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(3),0,0,0);
					// dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(4),0,0,0);
					// dwStatus=DeviceUSB->WriteDword(0,KanalKV->Load_sint(5),0,0,0);


		 }
	}
  
	if (ATTset)
	{
	  if (!Typ3CR6)
	  {
			dwStatus=DeviceUSB->WriteDword(0,KanalKV->LoadATT_UPC(),0,0,0);
	  } else
	  {
			dwStatus=DeviceUSB->WriteDword(1,KanalKV->LoadATT_UPC(),0,0,0);
	  }
	}



}
/*************************************************************/
void Bl3CR6::SetATT_UPC(double Db)
{
   KanalKV->SetATT_UPC(Db);
   SetALL(false, true, false, false);
}
/*************************************************************/
void Bl3CR6::SetAMPL_UPC(int Db)
{
	KanalKV->SetAmpl_UPC(Db);
	SetALL(false, false, true, false);
}

/*************************************************************/
void Bl3CR6::SetPC(bool PC40)
{
	KanalKV->SetPC(PC40);
	SetALL(false, false, false, true);
}


void Bl3CR6::SetFVC(int F)
{
	KanalKV->SetFVC(F);
	SetALL(false, false, false, true);
}
void Bl3CR6::SetATT_Pres(int Db)
{
	KanalKV->SetATT_Pres(Db);
	SetALL(false, false, false, true);
}
void Bl3CR6::SetVX(bool Priem,int DB)
{   KanalKV->SetVX(Priem, DB);
	SetALL(false, false, false, true);

}
#pragma package(smart_init)
