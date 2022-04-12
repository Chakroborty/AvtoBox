//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "BL3CR37.h"
#include "UdpClient.h"
#include "UdpServer.h"

using namespace LightNetwork;



//---------------------------------------------------------------------------
BL3CR37::BL3CR37()
{
	PRC = new MPRC(0);
	MFC1 = new MMFC1RR(0);
	MFC1->AdrMod = 1<<28;
	MFC11 = new MMFC1RR(0);
    MFC11->AdrMod = 1<<28;
	MFC2 = new MMFC1RR(0);
	MFC2->AdrMod = 9<<28;

}
BL3CR37::~BL3CR37()
{

}
char *BL3CR37::SENDLAN(int ADR,int data,bool Read)
{   return 0;
	UdpClient udpClient;
	bool result = udpClient.Connect(HostADR,UDP_038_PORT);

	if (!result)
	{
		ShowMessage("Connection failed");
		return "";
	}
	NetworkStreamUdp *stream = udpClient.Stream();

	UdpServer udpServer;
	result = udpServer.Bind("192.168.1.100",UDP_038_PORTR);
    		if (!result)
	{
		ShowMessage("Connection failed");
		return "";
	}
	NetworkStreamUdp *streamCell = udpServer.Stream();

	char buf[8];
	// запись                       // TODO : buf не заполняется
	buf[0] = data&0xFF;
	buf[1] = data>>8&0xFF;
	buf[2] = data>>16&0xFF;
	buf[3] = data>>24&0xFF;
	buf[4] = ADR&0xFF;
	buf[5] = ADR>>8&0xFF;
	buf[6] = ADR>>16&0xFF;
	buf[7] = ADR>>24&0xFF;
//
	long long writeBytes = stream->Write(buf, 8);
	if (writeBytes < 0)
	{
		std::string errStr = stream->ErrorString();
		ShowMessage(UnicodeString(errStr.c_str()));
        return "";
	}
			if (Read)
	{

		bool hasError = false;
		if (streamCell->WaitDataForReading(100, &hasError))
		{
			//ShowMessage("Has data");
			char obuf[8];
			memset(obuf, 0, 8);
			// данные есть

			long long readBytes = streamCell->Read(obuf, 8);
			if (readBytes < 0)
			{
				std::string errStr = streamCell->ErrorString();
				ShowMessage("er data");
			}

			char obuf1[9];
			obuf1[0] = obuf[7];
			obuf1[1] = obuf[6];
			obuf1[2] = obuf[5];
			obuf1[3] = obuf[4];
			obuf1[4] = obuf[3];
			obuf1[5] = obuf[2];
			obuf1[6] = obuf[1];
			obuf1[7] = obuf[0];
			obuf1[8] = 0x0;


			char obuf2[8];
			BinToHex(obuf1,obuf2,8); // преобразовываем исходный текст в HEX
		   //	ShowMessage(obuf2);
			return  obuf2;
		}
		else if(hasError)
		{
			std::string errStr = streamCell->ErrorString();
					ShowMessage("Has error");
		}
		else
		{
			ShowMessage("No data");
			//данных нет
		}
	}
	//отключение от удаленной стороны
	//udpClient.Disconnect();


}
void BL3CR37::LoadMFC1()
{


				for (int i = 0; i < 5; ++i)
	{
		SENDLAN(MFC1->Kluch(i),0,0);
	}

				for (int i = 0; i < 10; i++)
	{
	  SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_L(2,i),0); // HMC830
	}
				for (int i = 18; i < 20; i++)
	{
	  SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_L(2,i),0); // HMC830
	}
				for (int i = 10; i < 18; i++)
	{
	  SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_L(2,i),0); // HMC830
	}
}
void BL3CR37::LoadMFC11(double F, int ADR)
{//TODO: МФЧ1 @Прогрузка (0)
	//MFC1->AdrMod = ADR<<28;
	MFC11->SetFreq(F,F,0,0);
 int i = 0;
				for (i = 0; i < 5; ++i)
	{
		SENDLAN(MFC11->KluchM(i),0,0);
	}

				for (i = 0; i < 10; i++)
	{
	  SENDLAN(MFC11->SintLOAD_H(2),MFC11->SintLOAD_L(2,i),0); // HMC830
	}
				for (i = 18; i < 20; i++)
	{
	  SENDLAN(MFC11->SintLOAD_H(2),MFC11->SintLOAD_L(2,i),0); // HMC830
	}
				for (i = 10; i < 18; i++)
	{
	  SENDLAN(MFC11->SintLOAD_H(2),MFC11->SintLOAD_L(2,i),0); // HMC830
	}
		for (i = 3; i<116; ++i)
	{
		SENDLAN(MFC11->SintLOAD_H(1),MFC11->SintLOAD_LMXLCR(i),0);

	}
	MFC11->SetAUTOCOR(0,1);
    MFC11->BFCHP->PLMX2594->VCO_CAPCTRL(0);
	SENDLAN(MFC11->SintLOAD_H(1),MFC11->SintLOAD_LMXLCR(96),0);
}
void BL3CR37::LoadMFC2(double F, int ADR)
{   //TODO: МФЧ2 @Прогрузка (0)
	//MFC2->AdrMod = ADR<<28;
	long SW;
    int i = 0;
	MFC2->SetFreq(F,F,0,0);
				for (int i = 0; i < 5; ++i)
	{
		SENDLAN(MFC2->KluchM(i),0,0);
		// SW = MFC2->KluchM(i);
	}

				for (int i = 0; i < 10; i++)
	{
	  SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_L(2,i),0); // HMC830
	  // SW = MFC2->SintLOAD_H(2);
	  // SW = MFC2->SintLOAD_L(2,i);
	}
				for (int i = 18; i < 20; i++)
	{
	  SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_L(2,i),0); // HMC830
	  // SW = MFC2->SintLOAD_H(2);
	  // SW = MFC2->SintLOAD_L(2,i);
	}
				for (int i = 10; i < 18; i++)
	{
	 SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_L(2,i),0); // HMC830
	  // SW =  MFC2->SintLOAD_H(2);
	  // SW =  MFC2->SintLOAD_L(2,i);
	}

		for (i = 3; i<116; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(1),MFC2->SintLOAD_LMXLCR(i),0);
		// SW = MFC2->SintLOAD_H(1);
		// SW = MFC2->SintLOAD_LMXLCR(i);

	}


	MFC2->SetAUTOCOR(0,1);
	MFC2->BFCHP->PLMX2594->VCO_CAPCTRL(0);
	SENDLAN(MFC2->SintLOAD_H(1),MFC2->SintLOAD_LMXLCR(96),0);
	// SW = MFC2->SintLOAD_H(1);
	// SW = MFC2->SintLOAD_LMXLCR(96);

}
void BL3CR37::Load830UNO(int r)
{

	  SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_L(2,r),0); // HMC830

}
void BL3CR37::LoadLMX1()
{
	MFC1->Sint1_LMX2594->REG[0] = 0x00241A;
	SENDLAN(MFC1->SintLOAD_H(1),MFC1->SintLOAD_L(1,0),0); // LMX2594
	MFC1->Sint1_LMX2594->REG[0] = 0x002418;
	SENDLAN(MFC1->SintLOAD_H(1),MFC1->SintLOAD_L(1,0),0); // LMX2594
		for (int i = 112; i > -1; i--)
	{
	  SENDLAN(MFC1->SintLOAD_H(1),MFC1->SintLOAD_L(1,i),0); // LMX2594
	}
}
void BL3CR37::FriqSET(int Mod,int Kanal,double Fin,bool Ampl,int DB1,int DB2,int DB3,int DB4)
	{
					switch (Kanal)
		{

		  case 0:
		 PRC->SetFriq(0,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;        //	void FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);
		  case 1:
		 PRC->SetFriq(1,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 2:
		 PRC->SetFriq(1,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 3:
		 PRC->SetFriq(2,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 4:
		 PRC->SetFriq(2,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 5:
		 PRC->SetFriq(3,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 6:
		 PRC->SetFriq(3,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 7:
		 PRC->SetFriq(4,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 8:
		 PRC->SetFriq(4,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 9:
		 PRC->SetFriq(5,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 10:
		 PRC->SetFriq(5,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 11:
		 PRC->SetFriq(6,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 12:
		 PRC->SetFriq(6,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 13:
		 PRC->SetFriq(7,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 14:
		 PRC->SetFriq(7,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 15:
		 PRC->SetFriq(8,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 16:
		 PRC->SetFriq(8,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 20:
		 PRC->SetFriq(7,0,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		  case 21:
		 PRC->SetFriq(7,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;

		 default : PRC->SetFriq(0,1,Fin,Ampl,DB1,DB2,DB3,DB4,1);break;
		 }
	 /**

	TODO: Установка @Установка (1)
	- First todo item
	- Second todo item

	*/

		 MFC1->SetFreq(Fin,Fin,0,0);
	/**

	TODO: Прогрузка частоты Блок @Прогрузка(1)
	- First todo item
	- Second todo item

	*/

	LoadBL3CR37();
}
/*
	             #
	 ####       ##  ####
	##     ##  #### ##   # #  ##   ###
	####  ## #  ##  #### ### ## # # ##
	  ### ####  ##  ##   ##  #### # ##
	## ## ##    ##  ##   ##  ##   # ##
	 ###   ##    ## ##   ##   ##   ###
	                                ##
*/

void BL3CR37::SetFreq(double F,double Fat,int ATT1,int ATT2,int ATT3,int Kanal,int ALL,int BPERENOS)
{//TODO: Установка частоты @SETFRIQ (BLKBL3CR37.cpp)
	switch (Kanal)
	{	case 0://SetFriq(int Mod, int Kanal, double Fin, bool Ampl, int DB1,int DB2,int DB3,int DB4,int PARAM);
		 PRC->SetFriq(0,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		 case 1:
		 PRC->SetFriq(1,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 2:
		 PRC->SetFriq(1,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 3:
		 PRC->SetFriq(2,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 4:
		 PRC->SetFriq(2,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 5:
		 PRC->SetFriq(3,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 6:
		 PRC->SetFriq(3,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 7:
		 PRC->SetFriq(4,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 8:
		 PRC->SetFriq(4,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 9:
		 PRC->SetFriq(5,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 10:
		 PRC->SetFriq(5,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 11:
		 PRC->SetFriq(6,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 12:
		 PRC->SetFriq(6,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 13:
		 PRC->SetFriq(7,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 14:
		 PRC->SetFriq(7,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 15:
		 PRC->SetFriq(8,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 16:
		 PRC->SetFriq(8,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 20:
		 PRC->SetFriq(7,0,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
		  case 21:
		 PRC->SetFriq(7,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;

		 default : PRC->SetFriq(0,1,F,1,ATT1,ATT2,ATT3,ALL,BPERENOS);break;
	 }
//PRC->SetFriq(0,Kanal,F,1, ATT1,ATT2,ATT3,ALL);

MFC11->SetFreq(PRC->MKanal->FrGet1,PRC->MKanal->FrGet1,0,0);
//MFC2->SetFreq(3755,F,0,0);
	switch (BPERENOS)
	{
	case 0:
		MFC2->SetFreq(2005,F,0,0);
	break;
	case 1:
		MFC2->SetFreq(3755,F,0,0);
	break;
	default:
		MFC2->SetFreq(3755,F,0,0);
	break;
	}
LoadBL3CR371();
}

void BL3CR37::SetMFC1(double FM1,int DIV15,int BLUPR1,int BLUPR2)
{

		SENDLAN(MFC1->Kluch(1),0,0);
		SENDLAN(MFC1->Kluch(3),0,0);
		SENDLAN(MFC1->Kluch(4),0,0);
}
void BL3CR37::LoadLMXUNO(int X)
{

	SENDLAN(MFC1->SintLOAD_H(1),MFC1->SintLOAD_L(1,X),0); // LMX2594
}
char *BL3CR37::ReadLMXUNO(int X)
{
	return SENDLAN(MFC1->SintLOAD_H(1),MFC1->SintLOAD_L(1,X)|0x80000000,1); // LMX2594
}
void BL3CR37::LoadBL3CR37()//LoadBL3CR37ALL
{ //	TODO: Прогрузка частоты Блок @Прогрузка(2)

int i =0;


	//TODO: Прогрузка Ключи короткая МФЧ @Прогрузка(2)

  /*	LONG SER;
	for ( i = 0; i < 5; ++i)
	{
		SENDLAN(MFC1->KluchM(i),0,0);
		// SER = MFC1->KluchM(i);
	}
	//TODO: Прогрузка 830 короткая МФЧ @Прогрузка(2)

		for (int i = 0; i < 10; ++i)
	{
		SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for (int i = 18; i < 20; ++i)
	{
		SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for (int i = 10; i < 18; ++i)
	{
		SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}

	//	TODO: Прогрузка LMX2594 короткая МФЧ @Прогрузка(2)


		for (i = 0; i<116; ++i)
	{
		SENDLAN(MFC1->SintLOAD_H(1),MFC1->SintLOAD_LMXLCR(i),0);
		// SER =  MFC1->SintLOAD_H(1);
		// SER =  MFC1->SintLOAD_LMXLCR(i);
	}
//-----------------------------------
		for ( i = 0; i < 5; ++i)
	{
		SENDLAN(MFC2->KluchM(i),0,0);
		// SER = MFC1->KluchM(i);

	}

		for (int i = 0; i < 10; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for (int i = 18; i < 20; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for (int i = 10; i < 18; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}

		for (i = 0; i<116; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(1),MFC2->SintLOAD_LMXLCR(i),0);
		// SER =  MFC1->SintLOAD_H(1);
		// SER =  MFC1->SintLOAD_LMXLCR(i);
	}
*/
//-----------------------------------

for(i = 0; i < 4; ++i){SENDLAN(PRC->LoadKL(i),0,0);}
for(i = 0; i < 4; ++i){SENDLAN(PRC->LoadATT(i),0,0);}
	/*if(PRC->Modul_All)
	{
		PRC->MKanal->KanalNum_B_Mod=0;
		PRC->MKanal->AmplifSET(0);  //1 Вкл
			for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
			for(int i = 0; i < 4; ++i){SENDLAN(PRC->LoadATT(i),0,0);}
		PRC->MKanal->KanalNum_B_Mod=1;
		PRC->MKanal->AmplifSET(0);  //1 Вкл
			for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
			for(int i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}
	}
	else
	{	PRC->MKanal->AmplifSET(0);  //1 Вкл
			for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
		  	for(int i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}
	}


	if(PRC->Modul_All)
	{
		PRC->MKanal->KanalNum_B_Mod=0;
		PRC->MKanal->AmplifSET(1);  //1 Вкл
			for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
			for(int i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}
		PRC->MKanal->KanalNum_B_Mod=1;
		PRC->MKanal->AmplifSET(1);  //1 Вкл
			for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
			for(int i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}

	}
	else
	{		PRC->MKanal->AmplifSET(1);  //1 Вкл
		  	for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
		  	for(int i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}
	}*/


}
void BL3CR37::LoadBL3CR371()//LoadBL3CR37ALL
{ //TODO: Прогрузка частоты Блок @Прогрузка(2)
	int i =0;
  // TODO: Прогрузка Ключи короткая МФЧ @Прогрузка(2)

	LONG SER;
	for ( i = 0; i < 5; ++i)
	{
		SENDLAN(MFC11->KluchM(i),0,0);
		// SER = MFC1->KluchM(i);
	}

		for ( i = 0; i < 10; ++i)
	{
		SENDLAN(MFC11->SintLOAD_H(2),MFC11->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for ( i = 18; i < 20; ++i)
	{
		SENDLAN(MFC11->SintLOAD_H(2),MFC11->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for ( i = 10; i < 18; ++i)
	{
		SENDLAN(MFC11->SintLOAD_H(2),MFC11->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}

	/**
	TODO: Прогрузка LMX2594 короткая МФЧ @Прогрузка(2)
	- First todo item
	- Second todo item
	*/
		for (i = 3; i<116; ++i)
	{
		SENDLAN(MFC11->SintLOAD_H(1),MFC11->SintLOAD_LMXLCR(i),0);
		// SER =  MFC1->SintLOAD_H(1);
		// SER =  MFC1->SintLOAD_LMXLCR(i);
	}
	MFC11->SetAUTOCOR(0,1);
	MFC11->BFCHP->PLMX2594->VCO_CAPCTRL(0);
	SENDLAN(MFC11->SintLOAD_H(1),MFC11->SintLOAD_LMXLCR(96),0);
	// SER = MFC1->SintLOAD_H(1);
	// SER = MFC1->SintLOAD_LMXLCR(96);
//-----------------------------------
		for ( i = 0; i < 5; ++i)
	{
		SENDLAN(MFC2->KluchM(i),0,0);
		// SER = MFC1->KluchM(i);

	}

		for ( i = 0; i < 10; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for ( i = 18; i < 20; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}
		for ( i = 10; i < 18; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(2),MFC2->SintLOAD_LFCCR(i),0);//HMC830
		// SER =  MFC1->SintLOAD_H(2);
		// SER =  MFC1->SintLOAD_LFCCR(i);
	}

		for (i = 3; i<116; ++i)
	{
		SENDLAN(MFC2->SintLOAD_H(1),MFC2->SintLOAD_LMXLCR(i),0);
		// SER =  MFC1->SintLOAD_H(1);
		// SER =  MFC1->SintLOAD_LMXLCR(i);
	}
    MFC2->SetAUTOCOR(0,1);
	MFC2->BFCHP->PLMX2594->VCO_CAPCTRL(0);
	SENDLAN(MFC2->SintLOAD_H(1),MFC2->SintLOAD_LMXLCR(96),0);
	// SER = MFC2->SintLOAD_H(1);
	//SER = MFC2->SintLOAD_LMXLCR(96);
//-----------------------------------

/*
	if(PRC->Modul_All)
	{
		PRC->MKanal->KanalNum_B_Mod=0;
		PRC->MKanal->AmplifSET(0);  //1 Вкл
			for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
			for(int i = 0; i < 4; ++i){SENDLAN(PRC->LoadATT(i),0,0);}
		PRC->MKanal->KanalNum_B_Mod=1;
		PRC->MKanal->AmplifSET(0);  //1 Вкл
			for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
			for(int i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}
	}
	else
	{	PRC->MKanal->AmplifSET(0);  //1 Вкл
		  	for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
		  	for(int i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}
	}
*/


	for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadKL(i),0,0);}
	for(i = 0; i < 4; ++i) {SENDLAN(PRC->LoadATT(i),0,0);}
}
#pragma package(smart_init)
