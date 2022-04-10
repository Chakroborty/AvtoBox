//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "BLKPRC51.h"
#include "UdpClient.h"
#include "UdpServer.h"
#include "TcpClient.h"
using namespace LightNetwork;



//---------------------------------------------------------------------------
RPURR::RPURR()
{

	TPRC51 = new PRC51(0xD);

}
RPURR::~RPURR()
{

}
char *RPURR::SENDLAN(int ADR,int data,bool Read)
{   TcpClient tcpClient;
	//UdpClient udpClient;
	bool result = tcpClient.Connect("10.29.31.5", UDP_051_PORT);
	//bool result = udpClient.Connect(HostADR, UDP_038_PORT,UDP_038_PORTR);
	//bool result = udpClient.Connect(HostADR, PORT);
	if (!result)
	{
		ShowMessage("Connection failed");
	   	return "";
	}
	//	NetworkStreamUdp *stream = udpClient.Stream();
		NetworkStream *stream = tcpClient.Stream();
	//	UdpServer udpServer;
	//result = udpServer.Bind("192.168.1.100", UDP_038_PORT,UDP_038_PORTRR);
	//result = udpServer.Bind("192.168.1.100", PORT);
	//	result = udpServer.Bind("10.29.31.5", UDP_051_PORT);
	//	if (!result)
	//	{
	//		ShowMessage("Connection failed");
	//		return "";
	//	}
	//	NetworkStreamUdp *streamCell = udpServer.Stream();

	char buf[8];
	// запись
//	buf[0] = data&0xFF;
//	buf[1] = data>>8&0xFF;
//	buf[2] = data>>16&0xFF;
//	buf[3] = data>>24&0xFF;
//	buf[4] = ADR&0xFF;
//	buf[5] = ADR>>8&0xFF;
//	buf[6] = ADR>>16&0xFF;
//	buf[7] = ADR>>24&0xFF;

 	buf[0] = ADR>>24&0xFF;
	buf[1] = ADR>>16&0xFF;
	buf[2] = ADR>>8&0xFF;
	buf[3] = ADR&0xFF;
	buf[4] = data>>24&0xFF;
	buf[5] = data>>16&0xFF;
	buf[6] = data>>8&0xFF;
	buf[7] = data&0xFF;

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
//	if (streamCell->WaitDataForReading(100, &hasError))
	 if (stream->WaitDataForReading(100, &hasError))
	{
//		//ShowMessage("Has data");
		char obuf[8];
		memset(obuf, 0, 8);
//		// данные есть
//
//		long long readBytes = streamCell->Read(obuf, 8);
		long long readBytes = stream->Read(obuf, 8);
		if (readBytes < 0)
		{
			//std::string errStr = streamCell->ErrorString();
			std::string errStr = stream->ErrorString();
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
		//std::string errStr = streamCell->ErrorString();
		std::string errStr = stream->ErrorString();
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

	   tcpClient.Disconnect();
}

void RPURR::LoadMFC1()
{

				for (int i = 0; i < 5; ++i)
	{
		SENDLAN(MFC1->Kluch(i),0,0);
	}

		// SENDLAN(MFC1->Kluch(3),0);
		// SENDLAN(MFC1->Kluch(4),0);

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
void RPURR::Load830UNO(int r)
{

	  SENDLAN(MFC1->SintLOAD_H(2),MFC1->SintLOAD_L(2,r),0); // HMC830

}

void RPURR::LoadLMX1()
{
		MFC1->Sint1_LMX2594->REG[0] = 0x00241A;
		SENDLAN(TPRC51->SintLOAD_L(0),0,0); // LMX2594
		MFC1->Sint1_LMX2594->REG[0] = 0x002418;
		SENDLAN(TPRC51->SintLOAD_L(0),0,0); // LMX2594

		for (int i = 112; i > -1; i--)
		{
		  SENDLAN(TPRC51->SintLOAD_L(i),0,0); // LMX2594
		}


}
void RPURR::FriqSET(int Mod,int Kanal,double Fin,bool Ampl,int DB1,int DB2,int DB3,int DB4)
	{
//					switch (Kanal)
//		{
//
//		  case 0:
//		 PRC->SetFriq(0,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;        //	void FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal);
//		  case 1:
//		 PRC->SetFriq(1,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 2:
//		 PRC->SetFriq(1,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 3:
//		 PRC->SetFriq(2,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 4:
//		 PRC->SetFriq(2,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 5:
//		 PRC->SetFriq(3,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 6:
//		 PRC->SetFriq(3,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 7:
//		 PRC->SetFriq(4,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 8:
//		 PRC->SetFriq(4,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 9:
//		 PRC->SetFriq(5,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 10:
//		 PRC->SetFriq(5,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 11:
//		 PRC->SetFriq(6,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 12:
//		 PRC->SetFriq(6,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 20:
//		 PRC->SetFriq(7,0,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		  case 21:
//		 PRC->SetFriq(7,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//
//		 default : PRC->SetFriq(0,1,Fin,Ampl,DB1,DB2,DB3,DB4);break;
//		 }
	//	LoadRPURR();
}

//'IBLock::SetFreq(double,double,int,int,int,int,int,int) = 0'
void RPURR::SetFreq(double F,double Fr,int ATT1,int ATT2,int ATT3,int Kanal,int ATT4,int PERENOS)
{

}
void RPURR::SetMFC1(double FM1,int DIV15,int BLUPR1,int BLUPR2)
{
	   //	MFC1->SetKLUCH(DIV15,BLUPR1,BLUPR2,0,0,0,0);
		SENDLAN(MFC1->Kluch(1),0,0);
		SENDLAN(MFC1->Kluch(3),0,0);
		SENDLAN(MFC1->Kluch(4),0,0);
}

void RPURR::LoadLMXUNO(int X)
{

	SENDLAN(TPRC51->SintLOAD_L(X),0,0); // LMX2594  Замена51
}
char *RPURR::ReadLMXUNO(int X)
{
	return SENDLAN(TPRC51->SintLOAD_L(X)|0x80000000,0,1); // LMX2594
}
void RPURR::LoadRPURR()//LoadRPURRALL
{
	for(int i = 0; i < 4; ++i) {
		SENDLAN(PRC->LoadKL(i),0,0);
	}
		for(int i = 0; i < 4; ++i) {
		SENDLAN(PRC->LoadATT(i),0,0);
	}
}

char *RPURR::LoadPRC51()//Load51
{

		for(int i = 0; i < 11; ++i) {
		SENDLAN(TPRC51->LoadKL(i),0,0);
	}
		//SENDLAN(TPRC51->LoadKL(9),0,1);
		for(int i = 0; i < 2; ++i) {
		SENDLAN(TPRC51->LoadATT(i),0,0);
	}
}
void RPURR::LoadR018(int COM)
{
	SENDLAN(COM,0,0);
}
void RPURR::PRC51PRES(int P)
{
	TPRC51->PRESELSET(P);
	SENDLAN(TPRC51->LoadKL(9),0,0);
}
void RPURR::PRC51PERENOS(int P)
{
	TPRC51->PERENOS(P);
	SENDLAN(TPRC51->LoadKL(4),0,0);
}

void RPURR::PRC51ATT1(int DB)
{
	TPRC51->ATT1_SET(DB);
	SENDLAN(TPRC51->LoadATT(0),0,0);
	// LoadPRC51();
}
void RPURR::PRC51PMA32(int UPR)
{
	if (UPR)
	{
	TPRC51->ASW[1].LNA_sw = TPRC51->ASW[1].LNA_sw|0x1;
	} 	else
	{
	TPRC51->ASW[1].LNA_sw = TPRC51->ASW[1].LNA_sw&0x2;
	}
	SENDLAN(TPRC51->LoadKL(3),0,0);

}
void RPURR::PRC51PHA3(int UPR)
{//CHANGED: UPR_PHA @PRES51 (2)
	switch (UPR)
	{
	case 0: TPRC51->ASW[1].UsilPCH_sw = 1;break;
	case 1: TPRC51->ASW[1].UsilPCH_sw = 2;break;
	case 2: TPRC51->ASW[1].UsilPCH_sw = 0;break;
	default: TPRC51->ASW[1].UsilPCH_sw = 0;break;
	}
	SENDLAN(TPRC51->LoadKL(5),0,0);
}
void RPURR::PRC51ATT2(int DB)
{
	TPRC51->ATT2_SET(DB);
	SENDLAN(TPRC51->LoadATT(1),0,0);
	// LoadPRC51();
}
void RPURR::PRC51UPR1(int ST)
{
	TPRC51->SUPR1(ST);
	SENDLAN(TPRC51->LoadKL(7),0,0);
}
void RPURR::PRC51UPR2(int ST)
{
	TPRC51->SUPR2(ST);
	SENDLAN(TPRC51->LoadKL(8),0,0);
}
void RPURR::PRC51INSW(int S)
{
	TPRC51->INSET(S);
	SENDLAN(TPRC51->LoadKL(2),0,0);
}
void RPURR::PRC51UXM15(int ST)
{
	 TPRC51->SetUXM15(ST);
	SENDLAN(TPRC51->LoadKL(10),0,0);
}
void RPURR::LoadLMX051()
{
		TPRC51->DLMX2594->REG[0] = 0x00241A;
		SENDLAN(TPRC51->SintLOAD_L(1),0,0); // LMX2594
		TPRC51->DLMX2594->REG[0] = 0x002418;
		SENDLAN(TPRC51->SintLOAD_L(1),0,0); // LMX2594

		for (int i = 112; i > -1; i--)
		{
		  SENDLAN(TPRC51->SintLOAD_L(i),0,0); // LMX2594
		}
}
void RPURR::LoadLMX051F()
{
		TPRC51->DLMX2594->REG[0] = 0x00241A;
		SENDLAN(TPRC51->SintLOAD_L(1),0,0); // LMX2594
		TPRC51->DLMX2594->REG[0] = 0x002418;
		SENDLAN(TPRC51->SintLOAD_L(1),0,0); // LMX2594

		TPRC51->DLMX2594->SetFreq(8500);

		TPRC51->DLMX2594->NSET(79);
		SENDLAN(TPRC51->SintLOAD_L(34),0,0); // LMX2594
		SENDLAN(TPRC51->SintLOAD_L(36),0,0); // LMX2594
		TPRC51->DLMX2594->FRSET(0);
		SENDLAN(TPRC51->SintLOAD_L(42),0,0); // LMX2594
		SENDLAN(TPRC51->SintLOAD_L(43),0,0); // LMX2594
		for (int i = 112; i > -1; i--)
		{
		  SENDLAN(TPRC51->SintLOAD_L(i),0,0); // LMX2594
		}
}
void RPURR::LoadFCHPR()
{

		TPRC51->FCHP2594->PLMX2594->REG[0] =  0x00241A;
		SENDLAN(TPRC51->SintLOAD_L(1),0,0); // LMX2594
		TPRC51->FCHP2594->PLMX2594->REG[0] = 0x002418;
		SENDLAN(TPRC51->SintLOAD_L(1),0,0); // LMX2594

		TPRC51->FCHP2594->PLMX2594->SetFreq(8500);
		TPRC51->FCHP2594->PLMX2594->NSET(79);
		SENDLAN(TPRC51->SintLOAD_L(34),0,0); // LMX2594
		SENDLAN(TPRC51->SintLOAD_L(36),0,0); // LMX2594
		TPRC51->FCHP2594->PLMX2594->FRSET(0);
		SENDLAN(TPRC51->SintLOAD_L(42),0,0); // LMX2594
		SENDLAN(TPRC51->SintLOAD_L(43),0,0); // LMX2594
		for (int i = 112; i > -1; i--)
		{
		  SENDLAN(TPRC51->SintLOAD_L(i),0,0); // LMX2594
		}
}
/*



	## ##   ## ## ######
	## ###  ## ##   ##
	## ###  ## ##   ##
	## ## # ## ##   ##
	## ## # ## ##   ##
	## ##  ### ##   ##
	## ##  ### ##   ##
	## ##   ## ##   ##


*/
void RPURR::PRC51FCHINIT()
{
	/**

		TODO:
		- FCHLOAD_LMX(1)
		- FCHLOAD_LMX(0)

	 */
TPRC51->FCHP2594->PLMX2594->Default();
TPRC51->FCHP2594->PLMX2594->SETPRESET(0);

for (int i = 0; i < 13; ++i)
{
	SENDLAN(TPRC51->FCHLOAD_LMXINIT(i),0,0);
}


	/*TPRC51->FCHP2594->PLMX2594->REG[0] =  0x00241A;
	SENDLAN(TPRC51->FCHLOAD_LMX(1),0,0); // LMX2594 FCHLOAD_LMX(0)
	TPRC51->FCHP2594->PLMX2594->REG[0] = 0x002418;
	SENDLAN(TPRC51->FCHLOAD_LMX(1),0,0); // LMX2594 FCHLOAD_LMX(0)
	TPRC51->FCHP2594->PLMX2594->Default();
	TPRC51->FCHP2594->PLMX2594->NSET(56);//34 36
	TPRC51->FCHP2594->PLMX2594->FRSET(0);//42 43
	TPRC51->FCHP2594->PLMX2594->CHANDiV(0);//R75[10:6]
	TPRC51->FCHP2594->PLMX2594->OUTAPWR(63);//44
	TPRC51->FCHP2594->PLMX2594->OUTBPWR(63);//45

	SENDLAN(TPRC51->FCHLOAD_LMX(34),0,0);//34 36
	SENDLAN(TPRC51->FCHLOAD_LMX(36),0,0);//34 36
	SENDLAN(TPRC51->FCHLOAD_LMX(42),0,0);//FRSET
	SENDLAN(TPRC51->FCHLOAD_LMX(43),0,0);//FRSET
	SENDLAN(TPRC51->FCHLOAD_LMX(44),0,0);//OUTAPWR
	SENDLAN(TPRC51->FCHLOAD_LMX(45),0,0);//OUTBPWR
	SENDLAN(TPRC51->FCHLOAD_LMX(75),0,0);//CHANDiV
	SENDLAN(TPRC51->FCHLOAD_LMX(TPRC51->FCHP2594->PLMX2594->CURSET(4)),0,0);//PDCUR
	SENDLAN(TPRC51->FCHLOAD_LMX(TPRC51->FCHP2594->PLMX2594->SEG1EN(0)),0,0);//SEG
	SENDLAN(TPRC51->FCHLOAD_LMX(TPRC51->FCHP2594->PLMX2594->FCAL_EN(0)),0,0);//FCAL_EN*/

}
/*
	 ####  ##### ######        #####
	##  ## ##      ##          ##
	###    ##      ##          ##
	 ####  #####   ##          ####
	   ### ##      ##          ##
	#   ## ##      ##          ##
	##  ## ##      ##          ##
	 ####  #####   ##          ##
	                    ######
*/
void RPURR::PRC51FCHFRIQ(int NUM)
{//CHANGED: LOADPRESET @LOAD (0)
	TPRC51->FCHP2594->SETF(NUM);
	// SENDLAN(TPRC51->FCHLOAD_LMX(20),0,0);//20 VCO_SEL_FORCE(1) и VCO_SEL ;
	// SENDLAN(TPRC51->FCHLOAD_LMX(8),0,0);//8 VCO_CAPCTRL_FORCE
	// SENDLAN(TPRC51->FCHLOAD_LMX(75),0,0);//R75[10:6] OUTDIV
	// SENDLAN(TPRC51->FCHLOAD_LMX(19),0,0);//19 VCO_CAPCTRL
	// SENDLAN(TPRC51->FCHLOAD_LMX(34),0,0);//34 36
	// SENDLAN(TPRC51->FCHLOAD_LMX(36),0,0);//34 36
	// SENDLAN(TPRC51->FCHLOAD_LMX(45),0,0);//45 46 AMUX
	// SENDLAN(TPRC51->FCHLOAD_LMX(46),0,0);//45 46 BMUX
		for (int i = 0; i < 3; i++)
	{
	  SENDLAN(TPRC51->FCHLOAD_KL(i),0,0); // LMX2594
	}
	TPRC51->FCHP2594->SETAUTO(0,0);
		for (int i = 3; i<116; i++)
	{
	  SENDLAN(TPRC51->FCHLOADF(i),0,0); // LMX2594
	}
	TPRC51->FCHP2594->SETAUTO(0,1);
	SENDLAN(TPRC51->FCHLOADF(96),0,0); // LMX2594
}
#pragma package(smart_init)
