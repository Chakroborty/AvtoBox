//---------------------------------------------------------------------------


#pragma hdrstop
//#include "Test3DG1.h"
//#include "Unit1.h"
#include "BL3DG1C.h"
#include "Rpu16PX.h"
//---------------------------------------------------------------------------
	BL3DG1::BL3DG1(bool Isp830)
	{   Ispol830 = Isp830;

		ModulPX2 = new Tri3PX2(0xD); // Tri3PX2::AdresModul::Obsh
		ModulFCH2_830 = new MFC2Perexv830();
		ModulFCH2PX = new MFC2Perexv();
		ModulFCH1PX = new MFC1Perexv();

		ModulDG2 = new Tri3DG2(0xD);
		ModulFCH1 = new MFC1DG();
		ModulFCH2 = new MFC2DG();
		ModulFCHG =	new MFCG();
		Modul3DG10 = new Tri3DG10(0xD);
		DeviceManager = new UsbDeviceManager;   /* TODO -cUSB : USB Device VID PID в UsbDefines.h*/
		DeviceManager->OnAddDevice = DeviceConnected;
		DeviceManager->OnRemoveDevice = DeviceRemoved;
		DeviceUSB = NULL;
		MFCH_DG = 1; //0 - PX

	}
	BL3DG1::~BL3DG1()
	{

	}

DWORDLONG __fastcall  BL3DG1::SendDATA_SPI_USB(DWORD DATH,DWORD DATL)
{ /*---------- Прогрузка SendDATA_SPI_USB  ----------*/

	if (DeviceUSB == NULL)
		return 0;
 DWORDLONG res=0;
 DWORD retDH;
 DWORD retDL;
 DWORD dwData, dwAddr, dwStatus;
 dwData=0;
 DeviceUSB->WriteDword(0,DATH);
 Application->ProcessMessages();
 DeviceUSB->WriteDword(1,DATL);
 Application->ProcessMessages();
 Form1->WaitSPI_Timer->Enabled=TRUE;
 Wait_SPI=FALSE;
 while((dwData && 0x80000000)==0) //wait rdy SPI
 {
  dwStatus=DeviceUSB->ReadDword(2,dwData);
  if(Wait_SPI)
  {
   ShowMessage("Таймаут SPI");break;
  }
  Application->ProcessMessages();
 }
  Form1->WaitSPI_Timer->Enabled=FALSE;
  res=0;
  dwStatus=DeviceUSB->ReadDword(0,retDH);
  Application->ProcessMessages();
  dwStatus=DeviceUSB->ReadDword(1,retDL);
  Application->ProcessMessages();
  //res=retDH;
  res=retDL;
  res=(res<<32)|retDH;
 return res;
}

void __fastcall BL3DG1::DeviceConnected(TRpu16 *newDevice)
{

int iNumber = DeviceManager->Devices->IndexOf(newDevice);
	DeviceUSB = (TRpu16*)DeviceManager->Devices->Items[iNumber];
		Sleep(200);
			/*
			if (DeviceUSB = NULL)
			return;
			*/

	Form1->StatusBar1->Panels->Items[0]->Text = "3Дж1 " + IntToStr((int)Form1->Stend->VstendeBL3DG1->ReadBlokSN());

}
//---------------------------------------------------------------------------

void __fastcall BL3DG1::DeviceRemoved(TRpu16 *oldDevice)
{

	Form1->StatusBar1->Panels->Items[0]->Text = "USB ОЖИДАНИЕ";
	DeviceUSB = NULL;

}

void BL3DG1::KanalInitial()
{

	for (i = 0; i < 7; i++) {SendDATA_SPI_USB( ModulDG2->LoadKL_K1(i),0); }
	for (i = 0; i < 16; i++) { SendDATA_SPI_USB( ModulPX2->LoadGET1_H(), ModulPX2->LoadGET1_L(i));}  //Прогр синтезатора 1

	//			if (Ispol830)
	//	{ for (i = 0; i < 19; i++)
	//		{
	//				SendDATA_SPI_USB( ModulFCH2_830->SintLOAD_H(),ModulFCH2_830->SintLOAD_L(i));
	//		}       for (i = 0; i < 4; i++)
	//		{
	//				SendDATA_SPI_USB(ModulFCH2_830->Kluch(i),0);
	//		}
	//
	//	}
	//	else
	//	{            for (i = 0; i < 18; i++)
	//		{
	//					SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(),ModulFCH2->SintLOAD_L(i));
	//		}       for (i = 0; i < 6; i++)
	//		{
	//					SendDATA_SPI_USB(ModulFCH2->Kluch(i),0);
	//		}
	//	}
	//	for (i = 0; i < 16; i++) { SendDATA_SPI_USB( ModulPX2->LoadGET2_H(), ModulPX2->LoadGET2_L(i));}  //Прогр синтезатора 2
	//for (i = 0; i < 7; i++) {SendDATA_SPI_USB( ModulPX2->LoadATT_K1(i),0); }    //Прогр всех ATT Sleep(10);

		if (ModulDG2->Modul_All)
	{

		ModulDG2->MKanal->KanalNum_B_Mod = 1;
		for (i = 0; i < 7; i++) { SendDATA_SPI_USB( ModulDG2->LoadKL_K1(i),0); }
		for (i = 0; i < 7; i++) { SendDATA_SPI_USB( ModulDG2->LoadATT_K1(i),0);Sleep(100); }    //Прогр всех ATT


		//for (i = 0; i < 16; i++) { SendDATA_SPI_USB( ModulPX2->LoadGET1_H(), ModulPX2->LoadGET1_L(i));}  Прогр синтезатора 1


		//for (i = 0; i < 16; i++) {SendDATA_SPI_USB( ModulPX2->LoadGET2_H(), ModulPX2->LoadGET2_L(i));} Прогр синтезатора 2

		ModulDG2->MKanal->KanalNum_B_Mod = 2;
		for (i = 0; i < 7; i++) { SendDATA_SPI_USB( ModulDG2->LoadKL_K1(i),0); }       /* TODO : Этого небыло ATT */
		for (i = 0; i < 7; i++) { SendDATA_SPI_USB( ModulDG2->LoadATT_K1(i),0); Sleep(100);}    //Прогр всех ATT

		//for (i = 0; i < 16; i++) { SendDATA_SPI_USB( ModulPX2->LoadGET1_H(), ModulPX2->LoadGET1_L(i));}  Прогр синтезатора 1
		//for (i = 0; i < 16; i++) {SendDATA_SPI_USB( ModulPX2->LoadGET2_H(), ModulPX2->LoadGET2_L(i));} Прогр синтезатора 2


	}


}
//**************************************FriqSET 3ДЖ2******************
void BL3DG1::FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal)
	{

					switch (Kanal)
		{

		  case 0:
		 ModulDG2->SeFriq(0,1,Fin1, Ampl, DB1, DB2);break;        //	void FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);
		  case 1:
		 ModulDG2->SeFriq(1,1,Fin1, Ampl, DB1, DB2);break;
		  case 2:
		 ModulDG2->SeFriq(1,2,Fin1, Ampl, DB1, DB2);break;
		  case 3:
		 ModulDG2->SeFriq(2,1,Fin1, Ampl, DB1, DB2);break;
		  case 4:
		 ModulDG2->SeFriq(2,2,Fin1, Ampl, DB1, DB2);break;
		  case 5:
		 ModulDG2->SeFriq(3,1,Fin1, Ampl, DB1, DB2);break;
		  case 6:
		 ModulDG2->SeFriq(3,2,Fin1, Ampl, DB1, DB2);break;
		  case 7:
		 ModulDG2->SeFriq(4,1,Fin1, Ampl, DB1, DB2);break;
		  case 8:
		 ModulDG2->SeFriq(4,2,Fin1, Ampl, DB1, DB2);break;
		  case 9:
		 ModulDG2->SeFriq(5,1,Fin1, Ampl, DB1, DB2);break;
		  case 10:
		 ModulDG2->SeFriq(5,2,Fin1, Ampl, DB1, DB2);break;
		  case 11:
		 ModulDG2->SeFriq(6,1,Fin1, Ampl, DB1, DB2);break;
		  case 12:
		 ModulDG2->SeFriq(6,2,Fin1, Ampl, DB1, DB2);break;
		  case 20:
		 ModulDG2->SeFriq(7,1,Fin1, Ampl, DB1, DB2);break;
		  case 21:
		 ModulDG2->SeFriq(7,2,Fin1, Ampl, DB1, DB2);break;

		 default : ModulDG2->SeFriq(0,2,Fin1, Ampl, DB1, DB2);break;
		}



//			MFCH1_FsetDG(ModulDG2->MKanal->FrGet1);
//			MFCH2_FsetDG(ModulDG2->MKanal->FrGet2,1);


//------------------------------------------------------------------------------
					switch(MFCH_DG)
		{
			case 0:
			MFCH1_FsetPX(ModulDG2->MKanal->FrGet1);
			MFCH2_FsetPX(ModulDG2->MKanal->FrGet2);
			break;
			case 1:

			MFCH1_FsetDG(ModulDG2->MKanal->FrGet1);
			MFCH2_FsetDG(ModulDG2->MKanal->FrGet2,1);
			break;


			default:MFCH1_FsetPX(ModulPX2->MKanal->FrGet1);
					MFCH2_FsetPX(ModulPX2->MKanal->FrGet2);break;

		}

//------------------------------------------------------------------------------
		 KanalInitial();

   }
 //*************************** МФЧ1 set ДЖ ПСИ********************** /
void BL3DG1::MFCH1_FsetDG(double Fg1)

{
		ModulFCH1->SetFreq(Fg1*2,Fg1*2,0,1);
		SendDATA_SPI_USB(ModulFCH1->Kluch(0),0);

//					for (i = 0; i < 16; i++)
//	{SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(3),ModulFCH1->SintLOAD_L(3,i));}
//ModulFCH1->
			for (i = 1; i < 10; i++)
	{
		 SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(3),ModulFCH1->SintLOAD_L(3,i)); //HMC830
		 Sleep(100);
	}
			for (i = 18; i < 20; i++)
	{
		 SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(3),ModulFCH1->SintLOAD_L(3,i)); //HMC830
		 Sleep(100);
	}
		  for (i = 10; i < 18; i++)
	{
		 SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(3),ModulFCH1->SintLOAD_L(3,i)); //HMC830
		 Sleep(100);
	}

			for (i = 0; i < 4; i++)
	{SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(2),ModulFCH1->SintLOAD_L(2,i));} //ADF4002

			for (i = 0; i < 11; i++)
	{SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(1),ModulFCH1->SintLOAD_L(1,i));} //ADF4159

/****************** МФЧ1 Переключение с ADF4159 на ADF4002 ***********/
		//MessageDlg("ADF4002 Включение!",  mtConfirmation, TMsgDlgButtons() << mbOK,  0);

		ModulFCH1->Sint1_ADF4002->CurSET(0);
			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(2),ModulFCH1->SintLOAD_L(2,i)); //ADF4002


		}

		//MessageDlg("Выключение ADF4159!",  mtConfirmation, TMsgDlgButtons() << mbOK,  0);
		ModulFCH1->Sint1_ADF4159->POWDN = 1;
		//SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);
			for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(1),ModulFCH1->SintLOAD_L(1,i)); //ADF4159

		}
		 

/*=====  End of Переключение   с ADF4159 на ADF4002 ===========*/

}
//*************************** МФЧ2 set ДЖ настр********************
void BL3DG1::MFCH2_Fset(double Fg1)
  {     ModulFCH2->SetFreq(Fg1,1,false);    //UPR=1 синхр внутр
		//ModulFCH2_830->SetFreq(Fg1);
		//	SendDATA_SPI_USB(ModulFCH2->Kluch(2),0);
		SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);


					for (i = 1; i < 10; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
				for (i = 18; i < 20; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
			  for (i = 10; i < 18; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}

			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(2),ModulFCH2->SintLOAD_L(2,i)); //ADF4002
		}
			for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(1),ModulFCH2->SintLOAD_L(1,i)); //ADF4159
		}

			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(4),ModulFCH2->SintLOAD_L(4,i)); //ADF4002
		}

			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(5),ModulFCH2->SintLOAD_L(5,i)); //ADF4002
		}
		//SendDATA_SPI_USB(ModulFCH2->Kluch(2),0);
	}
void BL3DG1::MFCH2_Fset1(int Cur)
{
	ModulFCH2->Sint2_ADF4002->CurSET(Cur);
	 for (i = 0; i < 4; i++)
	 {
		SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(2),ModulFCH2->SintLOAD_L(2,i));
	 }

}
void BL3DG1::MFCH2_Fset2(int Cur)
  {
		  if(Cur>15)
		  {
	  		ModulFCH2->Sint2_ADF4159->PARAMSEt4159(1,Cur);
		  }
		  else
		  {
		  	ModulFCH2->Sint2_ADF4159->PARAMSEt4159(0,Cur);
		  }
  	
		 SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);
		 for (i = 0; i < 11; i++)
		 {
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(1),ModulFCH2->SintLOAD_L(1,i)); //МФЧ2 ADF4159
		 }
		//SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(1),ModulFCH2->SintLOAD_L(1,8)); //МФЧ2 ADF4159


  }
void BL3DG1::MFCH2_Fset3(double Fg1, int Fas1,int Fas2)
  {
		ModulFCH2->Sint2_HMC830->SetFreq(Fg1);



		SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);


				for (i = 1; i < 10; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
				for (i = 18; i < 20; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
			  for (i = 10; i < 18; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}


		

  }
//*************************************АТТ 3ПХ2****************
void BL3DG1::ATT1Set(double dB)
 {
	 ModulDG2->Set_ATT1_K1(dB);
	 for (i = 0; i < 7; i++) {SendDATA_SPI_USB( ModulDG2->LoadATT_K1(i),0); }    //Прогр всех ATT Sleep(10);
 /*	 KanalInitial();
 */

 }
void BL3DG1::ATT2Set(double dB)
 {
	 ModulDG2->Set_ATT2_K1(dB);
	 for (i = 0; i < 7; i++) {SendDATA_SPI_USB( ModulDG2->LoadATT_K1(i),0); }    //Прогр всех ATT Sleep(10);
/*	 KanalInitial();
*/
 }
void BL3DG1::AmplON(bool ON)
 {   ModulDG2->MKanal->AmplifSET(ON);
	 KanalInitial();

 }


  //************************************МФЧ1*******************
void BL3DG1::MFCH1_Fset(double Fg1)
{
               //выбор МФЧ1
}

void BL3DG1::MFCH1_Fset3(double Fg4159,double Fg1, int Fas1,int Fas2)
{
		ModulFCH1->Sint1_HMC830->SetFreq(Fg1);
		SendDATA_SPI_USB(ModulFCH1->Kluch(0),0);

				for (i = 1; i < 10; i++)
		{
			 SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(3),ModulFCH1->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
				for (i = 18; i < 20; i++)
		{
			 SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(3),ModulFCH1->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
			  for (i = 10; i < 18; i++)
		{
			 SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(3),ModulFCH1->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}


}
void BL3DG1::MFCH1_Fset1(double Fg4159,double Fg1,int Log)
  { /*----------  Subsection MFCH1_Fset1  ----------*/

			ModulFCH1->SetFreq(Fg4159,Fg1,1,Log);
			//ModulFCH1->Sint1_ADF4159->SetFreq(Fg4159,Fg1);

			for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(1),ModulFCH1->SintLOAD_L(1,i)); //ADF4159
		}

  }
void BL3DG1::MFCH1_Fset2(int  Pol)
  {
		   //	ModulFCH1->
			//SetFreq(Fg4159,Fg1,1,1);

			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCH1->SintLOAD_H(2),ModulFCH1->SintLOAD_L(2,i)); //ADF4002
		}

  }
double BL3DG1::Geterodin1()
  {
	   return ModulFCH1->Fget1;
  }

//*************************** МФЧ1 set ПХ ПСИ**********************
void BL3DG1::MFCH1_FsetPX(double Fg1)
{
		ModulFCH1PX->SetFreq(Fg1);
		SendDATA_SPI_USB(ModulFCH1PX->Kluch(),0);

					for (i = 0; i < 16; i++)
{SendDATA_SPI_USB( ModulFCH1PX->SintLOAD_H(),ModulFCH1PX->SintLOAD_L(i));}

}

//*************************** МФЧ2 set ПХ ПСИ**********************
void BL3DG1::MFCH2_FsetPX(double Fg1)
  {     ModulFCH2PX->SetFreq(Fg1);
		ModulFCH2_830->SetFreq(Fg1);
			  if (ModulFCH2_830->Sw_Ext_In)
		{
			  MFCH2_OGvnutr(false);
		}   else
		{
			  MFCH2_OGvnutr(true);
		}

		if (Ispol830)
	{ 		for (i = 0; i < 19; i++)
		{  SendDATA_SPI_USB( ModulFCH2_830->SintLOAD_H(),ModulFCH2_830->SintLOAD_L(i)); }
			for (i = 0; i < 4; i++)
		{  SendDATA_SPI_USB(ModulFCH2_830->Kluch(i),0);}

	}
		else
	{           for (i = 0; i < 18; i++)
		{   SendDATA_SPI_USB( ModulFCH2PX->SintLOAD_H(),ModulFCH2PX->SintLOAD_L(i));}
			for (i = 0; i < 6; i++)
		{ SendDATA_SPI_USB(ModulFCH2PX->Kluch(i),0); }
	}
  }
//*************************** МФЧ2 set ДЖ ПСИ**********************
void BL3DG1::MFCH2_FsetDG(double Fg1,int Fas1)
  {     ModulFCH2->SetFreq(Fg1,1,false);    //UPR=1 синхр внутр
		SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);


					for (i = 1; i < 10; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
				for (i = 18; i < 20; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
			  for (i = 10; i < 18; i++)
		{
			 SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(3),ModulFCH2->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}

			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(2),ModulFCH2->SintLOAD_L(2,i)); //ADF4002
		}
			for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(1),ModulFCH2->SintLOAD_L(1,i)); //ADF4159
		}

/****************** МФЧ2 Переключение с ADF4159 на ADF4002 ***********/
		

		ModulFCH2->Sint2_ADF4002->CurSET(0);
			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(2),ModulFCH2->SintLOAD_L(2,i)); //ADF4002


		}

		//MessageDlg("ADF4002 включена!",  mtConfirmation, TMsgDlgButtons() << mbOK,  0);
		ModulFCH2->Sint2_ADF4159->POWDN = Fas1;
		//SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);
			for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(1),ModulFCH2->SintLOAD_L(1,i)); //ADF4159

		}


/*=====  End of Переключение   с ADF4159 на ADF4002 ===========*/


		// 	for (i = 0; i < 4; i++)
		// {
		// 	SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(4),ModulFCH2->SintLOAD_L(4,i)); //ADF4002
		// }

		// 	for (i = 0; i < 4; i++)
		// {
		// 	SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(5),ModulFCH2->SintLOAD_L(5,i)); //ADF4002
		// }

  }

//**************************************FriqSET 3ДЖ10******************
void BL3DG1::FriqSET10(double Fin1,bool Ampl,int DB1,int DB2,int Kanal)
	{

					switch (Kanal)
		{

		  case 0:

		 Modul3DG10->SetFriq(0,1,Fin1, DB1, DB2);break;        //	void FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);
		  case 1:
		 Modul3DG10->SetFriq(1,1,Fin1, DB1, DB2);break;
		  case 2:
		 Modul3DG10->SetFriq(1,2,Fin1, DB1, DB2);break;
		  case 3:
		 Modul3DG10->SetFriq(2,1,Fin1, DB1, DB2);break;
		  case 4:
		 Modul3DG10->SetFriq(2,2,Fin1, DB1, DB2);break;
		  case 5:
		 Modul3DG10->SetFriq(3,1,Fin1, DB1, DB2);break;
		  case 6:
		 Modul3DG10->SetFriq(3,2,Fin1, DB1, DB2);break;
		  case 7:
		 Modul3DG10->SetFriq(4,1,Fin1, DB1, DB2);break;
		  case 8:
		 Modul3DG10->SetFriq(4,2,Fin1, DB1, DB2);break;
		  case 9:
		 Modul3DG10->SetFriq(5,1,Fin1, DB1, DB2);break;
		  case 10:
		 Modul3DG10->SetFriq(5,2,Fin1, DB1, DB2);break;
		  case 11:
		 Modul3DG10->SetFriq(6,1,Fin1, DB1, DB2);break;
		  case 12:
		 Modul3DG10->SetFriq(6,2,Fin1, DB1, DB2);break;
		  case 20:
		 Modul3DG10->SetFriq(7,1,Fin1, DB1, DB2);break;
		  case 21:
		 Modul3DG10->SetFriq(7,2,Fin1, DB1, DB2);break;

		 default : Modul3DG10->SetFriq(0,2,Fin1, DB1, DB2);break;
		}




//------------------------------------------------------------------------------
		 KanalInitial10();

   }
void BL3DG1::KanalInitial10()
{
		Modul3DG10->MKanalDG10->KanalNum_B_Mod = 1;
		i = 0;
		for (i = 0; i < 3; i++)
		{ SendDATA_SPI_USB(	Modul3DG10->LoadKL_K1(i),0); }

		Modul3DG10->MKanalDG10->KanalNum_B_Mod = 2;
		i = 0;
		for (i = 0; i < 3; i++)
		{ SendDATA_SPI_USB(	Modul3DG10->LoadKL_K1(i),0); }


}

/**************************МФЧГ set ДЖ настр***********************/
void BL3DG1::MFCHG_Fset3(double Fg4159,double Fg1, int Fas1,int Fas2)
{
		//ModulFCHG->Sint1_HMC830->SetFreq(Fg1);
		ModulFCHG->SetFreq(Fg4159,12,0,1);
		ModulFCHG->CED86 = 2; //ADF5941_1  SendDATA_SPI_USB(ModulFCHG->Kluch(2),0);
		ModulFCHG->CED18 = 2; //ADF5941_2  SendDATA_SPI_USB(ModulFCHG->Kluch(1),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(0),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(1),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(2),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(3),0);
			for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(1),ModulFCHG->SintLOAD_L(1,i)); //МФЧГ ADF4159_1

		}
         for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(4),ModulFCHG->SintLOAD_L(4,i)); //МФЧГ ADF4159_2
		}
				for (i = 1; i < 10; i++)
		{
			 SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(3),ModulFCHG->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
				for (i = 18; i < 20; i++)
		{
			 SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(3),ModulFCHG->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}
			  for (i = 10; i < 18; i++)
		{
			 SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(3),ModulFCHG->SintLOAD_L(3,i)); //HMC830
			 Sleep(100);
		}

		

/*=====  End of Переключение на ADF4002_2  ======*/
  /*		MessageDlg("Выключение ADF4159_1!",  mtConfirmation, TMsgDlgButtons() << mbOK,  0); //
*/    	for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(2),ModulFCHG->SintLOAD_L(2,i)); //ADF4002


		}


		ModulFCHG->CED18 = 0; //ADF5941_2
		SendDATA_SPI_USB(ModulFCHG->Kluch(1),0);

/*==============================
=            Переключение на ADF4002_1            =
==============================*/
		/*MessageDlg("Выключение ADF4159_1!",  mtConfirmation, TMsgDlgButtons() << mbOK,  0); //
		ModulFCHG->Sint1_ADF4002->CurSET(0);*/
		
			for (i = 0; i < 4; i++)
		{
			SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(5),ModulFCHG->SintLOAD_L(5,i)); //ADF4002_2


		}

		/*ModulFCHG->Sint1_ADF4159->POWDN = 1;
		
			for (i = 0; i < 11; i++)
		{
			SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(1),ModulFCHG->SintLOAD_L(1,i)); //ADF4159

		}*/

		ModulFCHG->CED86 = 0; //ADF5941_1
		SendDATA_SPI_USB(ModulFCHG->Kluch(2),0);




}

void BL3DG1::MFCHG_Fset2(int Cur)
  {
		  if(Cur>15)
		  {
	  		ModulFCHG->Sint2_ADF4159->PARAMSEt4159(1,Cur);
		  }
		  else
		  {
		  	ModulFCHG->Sint2_ADF4159->PARAMSEt4159(0,Cur);
		  }

			SendDATA_SPI_USB(ModulFCHG->Kluch(0),0);
			SendDATA_SPI_USB(ModulFCHG->Kluch(1),0);
			SendDATA_SPI_USB(ModulFCHG->Kluch(2),0);
			SendDATA_SPI_USB(ModulFCHG->Kluch(3),0);

		 for (i = 0; i < 11; i++)
		 {
			SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(4),ModulFCHG->SintLOAD_L(4,i)); //МФЧ2 ADF4159
		 }
		//SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(1),ModulFCH2->SintLOAD_L(1,8)); //МФЧ2 ADF4159


  }
void BL3DG1::MFCHG_Fset12(int Cur,int Pol)
  {

		ModulFCHG->Sint1_ADF4002->ParamSET(Pol,Cur,1,1);
		SendDATA_SPI_USB(ModulFCHG->Kluch(0),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(1),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(2),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(3),0);


         for (i = 0; i < 4; i++)
	 {
		SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(2),ModulFCHG->SintLOAD_L(2,i));
	 }

  }
void BL3DG1::MFCHG_Fset5(int Cur,int Pol)
  {

		ModulFCHG->Sint2_ADF4002->ParamSET(Pol,Cur,1,1);
		SendDATA_SPI_USB(ModulFCHG->Kluch(0),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(1),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(2),0);
		SendDATA_SPI_USB(ModulFCHG->Kluch(3),0);


         for (i = 0; i < 4; i++)
	 {
		SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(5),ModulFCHG->SintLOAD_L(5,i));
	 }

  }

/************************ Синхронизация МФЧГ ***************/
void BL3DG1::MFCHG_OGvnutr(int OG)
{   ModulFCHG->OGvnutr(OG);

				if (OG)
		{
			SendDATA_SPI_USB(ModulFCHG->Kluch(0),0);
					for (i = 0; i < 4; i++)
			{
				SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(6),ModulFCHG->SintLOAD_L(6,i)); //ADF4002
			}
		} else
		{   SendDATA_SPI_USB(ModulFCHG->Kluch(0),0);

		}
}
void BL3DG1::MFCHG_Sinc(double Fg1)
{
		for (i = 0; i < 4; i++)
	{
		SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(6),ModulFCHG->SintLOAD_L(6,i)); //ADF4002_100
	}  
		for (i = 0; i < 4; i++)
	{
		SendDATA_SPI_USB( ModulFCHG->SintLOAD_H(7),ModulFCHG->SintLOAD_L(7,i)); //ADF4002_1000
	}


}
/*-------------------------------------------------------*/

void BL3DG1::MFCH2_Sinc(double Fg1)
{
		for (i = 0; i < 4; i++)
	{
		SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(4),ModulFCH2->SintLOAD_L(4,i)); //ADF4002
	}  
		for (i = 0; i < 4; i++)
	{
		SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(5),ModulFCH2->SintLOAD_L(5,i)); //ADF4002
	}


}
void BL3DG1::MFCH2_OGvnutr(bool OG)
{
	 //ModulFCH2->OGvnutr(OG);
	 ModulFCH2_830->OGvnutr(OG);
	 for (i = 0; i < 4; i++)
	 {
		SendDATA_SPI_USB(ModulFCH2_830->Kluch(i),0);
	 }
	 if (ModulFCH2_830->Sw_Ext_In)
	{
	 for (i = 0; i < 5; i++)
	 {
		SendDATA_SPI_USB(ModulFCH2_830->ADF4001(5),ModulFCH2_830->ADF4001(i));   //
	 }
	}

}
void BL3DG1::MFCH2DG_OGvnutr(bool OG)
{   ModulFCH2->OGvnutr(OG);

				if (OG)
		{
			SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);
					for (i = 0; i < 4; i++)
			{
				SendDATA_SPI_USB( ModulFCH2->SintLOAD_H(5),ModulFCH2->SintLOAD_L(5,i)); //ADF4002
			}
		} else
		{   SendDATA_SPI_USB(ModulFCH2->Kluch(0),0);


		}
}
double BL3DG1::FriqOUT(void)
{
	return ModulDG2->MKanal->FreqFout();
}

double BL3DG1::Geterodin2()
{
	return ModulFCH2->Fget2;
}
 //************************************Blok********************

int BL3DG1::ReadSN_Ver(int SelectedModul)
{
  if(DeviceUSB==NULL)
  {
	   return 0;
  }
  SPI_InitI2c();

  BYTE Data[8];

  SPI_WriteBytePower(SelectedModul,0x90,0x01,true);
  SPI_WriteBytePower(SelectedModul,0x93,0x01,true);
  Sleep(1000);
  //Version

  //Data[7]=SPI_ReadBytePowerEeprom(ModulPX2->BL_NumModul,0xfbff,true);//ReadBytePowerEeprom(0xfbff);
 // Data[6]=SPI_ReadBytePowerEeprom(ModulPX2->BL_NumModul,0xfbfe,true);//ReadBytePowerEeprom(0xfbfe);
  //Data[5]=SPI_ReadBytePowerEeprom(ModulPX2->BL_NumModul,0xfbfd,true);//ReadBytePowerEeprom(0xfbfd);
  //Data[4]=SPI_ReadBytePowerEeprom(ModulPX2->BL_NumModul,0xfbfc,true);//ReadBytePowerEeprom(0xfbfc);
  //SerNumber
  Data[3]=SPI_ReadBytePowerEeprom(SelectedModul,0xfbfb,true);//ReadBytePowerEeprom(0xfbfb);
  Data[2]=SPI_ReadBytePowerEeprom(SelectedModul,0xfbfa,true);//ReadBytePowerEeprom(0xfbfa);
  Data[1]=SPI_ReadBytePowerEeprom(SelectedModul,0xfbf9,true);//ReadBytePowerEeprom(0xfbf9);
  Data[0]=SPI_ReadBytePowerEeprom(SelectedModul,0xfbf8,true);//ReadBytePowerEeprom(0xfbf8);

  SPI_WriteBytePower(SelectedModul,0x93,0x01,true);

  DWORD SN=(Data[3]<<24)|(Data[2]<<16)|(Data[1]<<8)|Data[0];
  //DWORD VER=(Data[7]<<24)|(Data[6]<<16)|(Data[5]<<8)|Data[4];
  return (int)SN;
  //Edit95->Text=IntToStr((int)VER);
  //Edit94->Text="0x"+IntToHex((int)SN,8);
  //Edit95->Text="0x"+IntToHex((int)VER,8);


}
 //-------- SPI_ReadBytePowerEeprom
BYTE __fastcall BL3DG1::SPI_ReadBytePowerEeprom(BYTE ModulADr,WORD Addr,bool by_way)
{
   BYTE AddrLo=Addr;
   BYTE AddrHi=Addr>>8;
   DWORD DWtx=0;
   DWORDLONG RxDat=0;
   BYTE RxByte=0;
   BYTE CMD=0x14;
   //сбросим I2C
   //DWtx=(ModulADr<<28)|(0x1<<24)|(0x4<<20)|((0x40)<<12)|0x800;//set stop
   //RxDat=SendDATA_SPI_USB(DWtx,0);

   //отправим команду
   DWtx=(ModulADr<<28)|(0x13<<20)|((CMD<<1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return 0x0;}

   //отправим  адрес Hi
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrHi<<12)|0x800;//--Запись в TxReg=AddrHi
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return 0x1;}

	//отправим  адрес Lo
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrLo<<12)|0x800;//--Запись в TxReg=AddrLo
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=stop+wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return 0x2;}

   DWtx=(ModulADr<<28)|(0x1<<24)|(0x4<<20)|((0x40)<<12)|0x800;//set stop
   RxDat=SendDATA_SPI_USB(DWtx,0);

   //снова отправим команду со стартом
   DWtx=(ModulADr<<28)|(0x13<<20)|(((CMD<<1)|1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=1
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return 0x3;}

	//считаем  байт
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x28<<12)|0x800;//set  Read & noACK=1
   SendDATA_SPI_USB(DWtx,0);

   DWtx=(ModulADr<<28)|(0x13<<20)|(0x00<<12)|0x000;///read Rx Reg
   RxByte=(BYTE)SendDATA_SPI_USB(DWtx,0);

   DWtx=(ModulADr<<28)|(0x1<<24)|(0x4<<20)|((0x40)<<12)|0x800;//set stop
   RxDat=SendDATA_SPI_USB(DWtx,0);


  //DWtx=(ModulADr<<28)|(0x13<<20)|(0x00<<12)|0x000;///read Rx Reg
   //RxByte=(BYTE)SendDATA_SPI_USB(DWtx,0);


   return RxByte;

}
BYTE __fastcall BL3DG1::SPI_I2C_WaitRdy(BYTE ModulADr,bool by_way)
	{

	  //Sleep(10);//вместо цикла ожидания, пока
	  return (BYTE)SPI_I2C_GetStatus(ModulADr,by_way);
	}
BYTE __fastcall BL3DG1::SPI_I2C_GetStatus(BYTE ModulADr,bool by_way)
	 {
	  DWORD CMD=(ModulADr<<28)|(0x14<<20);
	  DWORDLONG RxDat=0;
	  RxDat=SendDATA_SPI_USB(CMD,0);
	  //Edit88->Text=IntToHex((int)RxDat,4);
	  return (BYTE)RxDat;
	 }


BYTE BL3DG1::SPI_ReadBytePower(BYTE ModulADr,BYTE Addr,bool by_way)
	{
	 return (BYTE)SPI_I2C_rdByte(ModulADr,0x14,Addr,by_way);
	}
void BL3DG1::SPI_WriteBytePower(BYTE ModulADr,BYTE Addr, BYTE Data,bool by_way)
	{
	 SPI_I2C_wrByte(ModulADr,0x14,Data,Addr,by_way);
	}

BYTE __fastcall BL3DG1::SPI_I2C_rdByte(BYTE ModulADr,BYTE CMD,BYTE adr,bool by_way)
	{
	 //чтение байта по адресу регистра на I2C
 //by_way=TRUE-USB, FALSE-PCI_E
   DWORD DWtx=0;
   DWORDLONG RxDat=0;
   BYTE RXByte;
   //сбросим I2C
   DWtx=(ModulADr<<28)|(0x1<<24)|(0x4<<20)|((0x40)<<12)|0x800;//set stop
   RxDat=SendDATA_SPI_USB(DWtx,0);

   //отправим команду
   DWtx=(ModulADr<<28)|(0x13<<20)|((CMD<<1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return 0xff;}

   //отправим  адрес
   DWtx=(ModulADr<<28)|(0x13<<20)|(adr<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return 0xff;}

   //снова отправим команду со стартом
   DWtx=(ModulADr<<28)|(0x13<<20)|(((CMD<<1)|1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=1
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);


	//считаем  байт
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x68<<12)|0x800;//set  Read & noACK=1 & stop
   SendDATA_SPI_USB(DWtx,0);




   DWtx=(ModulADr<<28)|(0x13<<20)|(0x00<<12)|0x000;///read Rx Reg
   RXByte=(BYTE)SendDATA_SPI_USB(DWtx,0);

   //сбросим I2C
   DWtx=(ModulADr<<28)|(0x1<<24)|(0x4<<20)|((0x40)<<12)|0x800;//set stop
   RxDat=SendDATA_SPI_USB(DWtx,0);
   return RXByte;


	}
//---------------------------------------------------------------------------
bool __fastcall BL3DG1::SPI_I2C_wrByte(BYTE ModulADr,BYTE CMD,BYTE D,BYTE adr,bool by_way)
{
 //Запись байта по адресу регистра на I2C
 //by_way=TRUE-USB, FALSE-PCI_E
 DWORD DWtx=0;

   //сбросим I2C
   DWtx=(ModulADr<<28)|(0x14<<20)|((40)<<12)|0x800;//set stop
   SendDATA_SPI_USB(DWtx,0);

   //отправим команду
   DWtx=(ModulADr<<28)|(0x13<<20)|((CMD<<1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return false;}

   //отправим  адрес
   DWtx=(ModulADr<<28)|(0x13<<20)|(adr<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return false;}
	//отправим  байт
   DWtx=(ModulADr<<28)|(0x13<<20)|(D<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return false;}

   //сбросим I2C
   DWtx=(ModulADr<<28)|(0x14<<20)|((40)<<12)|0x800;//set stop
   SendDATA_SPI_USB(DWtx,0);
   return true;
}




//--------SPI_WriteBytePowerEeprom
void __fastcall BL3DG1::SPI_WriteBytePowerEeprom(BYTE ModulADr,BYTE D,WORD Addr,bool by_way)
{
 if ((Addr < WORD(0xF800)) || (Addr > (0xFC00)))
		return;
 DWORD DWtx=0;
 BYTE CMD=0x14;
 BYTE AddrHi=Addr>>8;
 BYTE AddrLo=Addr;
   //сбросим I2C
   //DWtx=(ModulADr<<28)|(0x14<<20)|((40)<<12)|0x800;//set stop
   //SendDATA_SPI(DWtx,0,by_way);

   //отправим команду
   DWtx=(ModulADr<<28)|(0x13<<20)|((CMD<<1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return;}

   //отправим  адрес Hi
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrHi<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}
	//отправим  адрес Lo
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrLo<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

	//отправим  байт
   DWtx=(ModulADr<<28)|(0x13<<20)|(D<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return;}


   DWtx=(ModulADr<<28)|(0x14<<20)|((40)<<12)|0x800;//set stop
   SendDATA_SPI_USB(DWtx,0);

}

void __fastcall BL3DG1::SPI_ErasePageWriteBytePowerEeprom(BYTE ModulADr,WORD Addr, BYTE Data,bool by_way)
{
 BYTE CMD=0x14;
 BYTE AddrHi=Addr>>8;
 BYTE AddrLo=Addr;

 DWORD DWtx=(ModulADr<<28)|(0x13<<20)|((CMD<<1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

   //отправим  адрес Hi
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrHi<<12)|0x800;//--Запись в TxReg=AddrHi
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

	//отправим  адрес Lo
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrLo<<12)|0x800;//--Запись в TxReg=AddrLo
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

   DWtx=(ModulADr<<28)|(0x14<<20)|(0x40<<12)|0x800;//Запись в CR=stop
   SendDATA_SPI_USB(DWtx,0);



   DWtx=(ModulADr<<28)|(0x13<<20)|((CMD<<1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);

   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

	DWtx=(ModulADr<<28)|(0x13<<20)|(0xfe<<12)|0x800;//--Запись в TxReg=0xFE
   SendDATA_SPI_USB(DWtx,0);

   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=stop+wr
   SendDATA_SPI_USB(DWtx,0);

   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

   DWtx=(ModulADr<<28)|(0x14<<20)|(0x40<<12)|0x800;//Запись в CR=stop
   SendDATA_SPI_USB(DWtx,0);

	Sleep(30);

   DWtx=(ModulADr<<28)|(0x13<<20)|((CMD<<1)<<12)|0x800;//--Запись в TxReg=cmd  slave устройства на I2C +бит w=0
   SendDATA_SPI_USB(DWtx,0);

   DWtx=(ModulADr<<28)|(0x14<<20)|(0x90<<12)|0x800;//Запись в CR=start+wr
   SendDATA_SPI_USB(DWtx,0);

   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

   //отправим  адрес Hi
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrHi<<12)|0x800;//--Запись в TxReg=AddrHi
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

	//отправим  адрес Lo
   DWtx=(ModulADr<<28)|(0x13<<20)|(AddrLo<<12)|0x800;//--Запись в TxReg=AddrLo
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

	//отправим  байт
   DWtx=(ModulADr<<28)|(0x13<<20)|(Data<<12)|0x800;//--Запись в TxReg=AddrLo
   SendDATA_SPI_USB(DWtx,0);
   DWtx=(ModulADr<<28)|(0x14<<20)|(0x10<<12)|0x800;//Запись в CR=wr
   SendDATA_SPI_USB(DWtx,0);
   if(((BYTE)SPI_I2C_WaitRdy(ModulADr,by_way)&0x80)!=0) {ShowMessage("No Slave ACK");return ;}

   DWtx=(ModulADr<<28)|(0x14<<20)|(0x40<<12)|0x800;//Запись в CR=stop
   SendDATA_SPI_USB(DWtx,0);
}

void __fastcall BL3DG1::SPI_EraseBlockPowerEeprom(BYTE ModulADr,WORD Addr,bool by_way)
{

 if ((Addr < 0xF800) || (Addr > 0xFC00))
		return;
 SPI_WriteBytePower(0xd,0x90,0x05,by_way);
 SPI_ErasePageWriteBytePowerEeprom(ModulADr,Addr,0xff,by_way);
 SPI_WriteBytePower(0xd,0x90,0x01,by_way);
}


void __fastcall BL3DG1::SPI_WritePagePowerEeprom(BYTE ModulADr,WORD Addr, PBYTE Data, BYTE Size,bool by_way)
{

 if (Addr < 0xF800 || Addr > 0xFC00)
        return;
	if (!Data)
        return;
	if (Size == 0 || Size > 32)
        return;
	//EraseBlockPowerEeprom(Addr);
	SPI_EraseBlockPowerEeprom(ModulADr,Addr,by_way);
	DWORD i;

    for (i = 0 ; i < Size; i++)
    {
	   // WriteBytePowerEeprom(Addr + i, Data[i]);
	   SPI_WriteBytePowerEeprom(ModulADr,Data[i],Addr+i,by_way);
	}

}

void __fastcall BL3DG1::WriteSN_Ver(int SelectedModul,DWORD ver,DWORD num)
{
if(DeviceUSB==NULL)
  {
	  ShowMessage("Нет подключенных устройств!!!");
	  return;
  }
  SPI_InitI2c();
 bool by_way=true;
  BYTE Data[32];




  SPI_WriteBytePower(SelectedModul,0x90,0x01,by_way);//Разрешаем обновление регистров
  SPI_WriteBytePower(SelectedModul,0x93,0x01,by_way); //останавливаем SE

  //Version
  Data[31]=ver>>24;
  Data[30]=ver>>16;
  Data[29]=ver>>8;
  Data[28]=ver;


  //SerNumber
  Data[27]=num>>24;
  Data[26]=num>>16;
  Data[25]=num>>8;
  Data[24]=num;


 SPI_WritePagePowerEeprom(SelectedModul,0xfbe0, Data, 32,by_way);//fbe0


//WritePagePowerEeprom(WORD(0xfbe0), Data, 32);



  //SPI_WriteBytePower(SelectedModul,0x90,0x01,by_way);//разрешаем обновление регистров
  SPI_WriteBytePower(SelectedModul,0xD8,0x01,by_way);//перезагружаем RAM
  //SPI_WriteBytePower(SelectedModul,0x93,0x01,by_way);//запускаем SE
}
void  BL3DG1::WriteBlokSN(DWORD ValSN){
if (DeviceUSB == NULL)
		return ;
	 DeviceUSB->WriteSN(ValSN);
}
DWORD BL3DG1::ReadBlokSN(){
if (DeviceUSB == NULL)
		return 0;
 return DeviceUSB->ReadSN();
}
void __fastcall BL3DG1::SPI_InitI2c()
{
//Инициализация модуля I2C в модулях мфч1,мфч2,3пх2
//by_way=TRUE-USB, FALSE-PCI_E
   SendDATA_SPI_USB(0xD1000400,0); // reset i2c core
   SendDATA_SPI_USB(0xD1005800,0); // set PRERlo
   SendDATA_SPI_USB(0xD1100800,0); // set PRERhi
   SendDATA_SPI_USB(0xD1280800,0); //Control register: set  I2C core enable bit

}
#pragma package(smart_init)
