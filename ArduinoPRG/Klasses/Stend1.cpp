//---------------------------------------------------------------------------


#pragma hdrstop
#include "E5071BNetwAnalizer.h"
#include "Agilent8560.h"
#include "HPE44XXB.h"
#include "Switch34980A.h"
#include "Stend1.h"
#include "visa.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vcl.h>
#include "Unit3CR5.h"
#pragma comment(lib,"visa32.lib")

//---------------------------------------------------------------------------
	 Stend1::Stend1(bool Blok3CR6, char* Ip)
{
		Vstende5071 = new E5071B(25, Ip); // "10.29.31.160"
		KOM34980 = new Switch34980(9, Ip);

		
		An8560 = new Analiz8560(20, Ip);
		An9030 = new Analiz9030(18, Ip,0);
		AgE44XX = new HPE4426B(19, Ip);
		MP_N6702A = new N6702A(5,Ip,0);

		VstendeBl3CR6 = new Bl3CR6(Blok3CR6);
		buffer[400] = 0;
		rezult[256] = 0;
		status = 0;
		analiz =0;
		get = 0;
		FrGen = 15;
		PowGen = -50;
		Span = 0.1;
		RefL= 10;
		RBW = 3000;
		FrAn =140;
		RefL10M = 10;

}
//---------------------------------------------------------------------------



	 Stend1::~Stend1()
	  {

	  } /*
void Stend1::SendBlokALL(void)
{ DWORD  dwStatus;

	if (!VstendeBl3CR6->GetBlTyp3CR6())
	{dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->SetFriq(false,0,0),0,0,0);
	 dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->SetFriq(false,1,0),0,0,0);
	 dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->SetFriq(false,2,0),0,0,0);
	 dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->SetFriq(false,3,0),0,0,0);
	 dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->SetFriq(false,4,0),0,0,0);
	 dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->SetFriq(false,5,0),0,0,0);
	} else
	{dwStatus=DeviceUSB->WriteDword(4,VstendeBl3CR6->SetFriq(false,0,0),VstendeBl3CR6->SetFriq(false,1,0),
	VstendeBl3CR6->SetFriq(false,2,0),VstendeBl3CR6->SetFriq(false,3,0));
	dwStatus=DeviceUSB->WriteDword(2,VstendeBl3CR6->SetFriq(false,4,0),VstendeBl3CR6->SetFriq(false,5,0),0,0);
	}

***************************************************************************
if (!VstendeBl3CR6->GetBlTyp3CR6())
{dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->LoadAMPL_UPC(),0,0,0);}
else
{dwStatus=DeviceUSB->WriteDword(1,VstendeBl3CR6->LoadAMPL_UPC(),0,0,0);}

***************************************************************************
if (!VstendeBl3CR6->GetBlTyp3CR6())
{dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->LoadATT_UPC(),0,0,0);}
else
{dwStatus=DeviceUSB->WriteDword(1,VstendeBl3CR6->LoadATT_UPC(),0,0,0);}
**************************************************************************
if (!VstendeBl3CR6->GetBlTyp3CR6())
{dwStatus=DeviceUSB->WriteDword(0,VstendeBl3CR6->LoadKL(),0,0,0);}
else
{dwStatus=DeviceUSB->WriteDword(1,VstendeBl3CR6->LoadKL(),0,0,0);}
}   */

void Stend1::Sint_SetBLOK68(double Fin)
{
	DWORD  dwStatus;

  //VstendeBl3CR6->SetFriq(Fin);
  VstendeBl3CR6->SetFriq(0,50,0,0,Fin,0,256,false);
		   //(int Kanal,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC)
    if (!VstendeBl3CR6->GetBlTyp3CR6())
	{    VstendeBl3CR6->SetFriq(0,50,0,0,Fin,0,256,false);
	} else
	{

	   VstendeBl3CR6->SetFriq(0,50,0,0,Fin,0,256,false);
	}

}
void Stend1::AMPLUPC_SetBLOK68(int Ampl)
{ DWORD  dwStatus;
  VstendeBl3CR6->SetAMPL_UPC(Ampl);

}
void Stend1::ATTUPC_SetBLOK68(double Db)
{
	DWORD  dwStatus;

  VstendeBl3CR6->SetATT_UPC(Db);



}
void Stend1::VX_SetBLOK68(bool Priem)
{   	DWORD  dwStatus;
 VstendeBl3CR6->SetVX(Priem,0);
}
void Stend1::ATTPres_SetBLOK68(int Db)
{  	DWORD  dwStatus;
 VstendeBl3CR6->SetATT_Pres(Db);

}
void Stend1::FVC_SetBLOK68(int Fset)
{ 	DWORD  dwStatus;
VstendeBl3CR6->SetFVC(Fset);
}
void Stend1::PC_SetBLOK68(bool PC40)
{  	DWORD  dwStatus;
 VstendeBl3CR6->SetPC(PC40);

}




void Stend1::Set5071_NoPerenos(double Fnastr, double Span, double Pow)
{
		/*
		Vstende5071->NumTRsSET(3);
			Vstende5071->DispleiSet(3,3,1,10,10,10);
			Vstende5071->DispleiSet(2,2,1,10,10,10);
			Vstende5071->DispleiSet(1,1,1,10,10,10);
	*/
	Vstende5071->In_No_perenos(Fnastr-Span/2,Fnastr+Span/2,Pow);     //Vstende5071->In_NEsim_perenos(1,51,Fnastr,70,true, -30);
	Pribor5071_IzmLoad();
	//Vstende5071->Marker_set(58,66,68,69,71,72,74);  //Vstende5071->GetF_Get()
	Pribor5071_MarkLoad();
		/*
		Vstende5071->SetLimitOc(58,66,68,69,71,72,74,82,-50,-32,-8,-3,-3,-8,-32,-50);
			Vstende5071->SetLimitProf(-1,-1,-1,-1,1,1,1,1);
			Vstende5071->SetLimitzAZOR(0.5,3,-8);  //dF, dL, Lopor
	*/
	Pribor5071_LimitLoad();

}
void Stend1::Set5071_Perenos(double StartIN, double StopIN, double Fnastr, double Fpc, double Pow)
{
/**********************************************************************************/
		/*
			 Vstende5071->NumTRsSET(3);
				 Vstende5071->DispleiSet(3,3,1,10,10,10);
				 Vstende5071->DispleiSet(2,2,1,10,10,10);
				 Vstende5071->DispleiSet(1,1,1,10,10,10);
	*/
		 Vstende5071->In_NEsim_perenos(StartIN, StopIN, Fnastr,Fpc,true,Pow);//   1,51,Fnastr,70,true,Pow
		 Pribor5071_IzmLoad();
		 //Vstende5071->Marker_set(Fnastr, 1.5, 8, 13, 32, 35, 40);  //Vstende5071->GetF_Get()
		 Pribor5071_MarkLoad();
		          /*
             Vstende5071->SetLimitOc(1.5,8,13,15,32,36,40,48,-10,-10.3,-8.3,-8.3,-13,-17,-42,-48);
					 Vstende5071->SetLimitProf(0,0,0,0,0,-1,-1,-1);
					 Vstende5071->SetLimitzAZOR(0.9,3,-8.3);  //dF, dL, Lopor
         */
		 Pribor5071_LimitLoad();
		 Sleep(200);

 }
void Stend1::Pribor5071_MarkLoad()
{  status = viOpenDefaultRM(&defaultRM);
		 strcpy(buffer,Vstende5071->PriborLoad());
		 printf_s("%s\n", buffer);
		 status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		 if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
	return ;
 }      // viPrintf(vi,"*RST\n");
		  int i=0;
		  int j=0;
		  for (i = 0; i < 7; i++)
			 {
 strcpy(buffer,Vstende5071->MarkerONload(i));
			  strcat(buffer,"\n");
			  viPrintf(vi, buffer);
			 }
		  for (i = 0; i < 7; i++)
			 {
 strcpy(buffer,Vstende5071->MarkerFload(i));
			  strcat(buffer,"\n");
			  viPrintf(vi, buffer);
			 }

		status = viClose(vi);
		status = viClose(defaultRM);
}
void Stend1::Stend_LimitLoad(double Pow, double Ref, double Ref10M,double Sp ,double RB ){
	  PowGen = Pow;
	  Span = Sp;
	  RefL= Ref;
	  RBW = RB;
	  RefL10M = Ref10M;

}
void Stend1::Stend_LimitRet(double &Pow, double &Ref, double &Ref10M,double &Sp ,double &RB ){

	  Pow = PowGen;
	  Sp  = Span;
	  Ref = RefL;
	  RB  = RBW;
	  Ref10M = RefL10M;

}

void Stend1::Stend_PrAdress(int An, int Gen,int ANLAN, AnsiString AdrAN,
		int GENLAN, AnsiString AdrGEN,
		int GEN1LAN,AnsiString AdrGEN1,int GEN2LAN, AnsiString AdrGEN2,

		int SWLAN, AnsiString AdrSW,

	   int PANLAN,	AnsiString AdrPan, 
	   int BPLAN,	AnsiString AdrBP, AnsiString Ip)
 {

	   analiz = An;
	   switch (analiz)
			{
				 case 0:
				 ShowMessage("Установлен анализатор Agilent 8560SA");
				switch (ANLAN)
				{
					case 0:An8560->GPIB_Set(AdrAN, Ip);  break;
					case 1:An8560->GPIB_Set(AdrAN, Ip);  break;
				}
				 break;

				 case 1:
				 ShowMessage("Установлен анализатор Agilent N9030A");
				switch (ANLAN)
				{
					case 0:	An9030->IP_Set(AdrAN.c_str()); break;
					case 1:	An9030->GPIB_Set(AdrAN, Ip);   break;
				}
				 break;

				 case 2:
				 ShowMessage("Установлен анализатор R&S FSU ");
				 RS_FSUP50->GPIB_Set(AdrAN, Ip);
				 break;
			}
			 get = Gen;
//	   switch (get)
//			{
//				 case 0:
//				 ShowMessage("Гетеродин1 Agilent E4426B 4 ГГц");
//				 ShowMessage("Гетеродин2 Agilent E4425B 3 ГГц");
//				 Ag4425->GPIB_Set(AdrGEN1, Ip);
//				 AE4426->GPIB_Set(AdrGEN2, Ip);
//				 break;
//
//				 case 1:
//				 ShowMessage("Гетеродин1 SMU200 A 6 ГГц");
//				 ShowMessage("Гетеродин2 SMU200 B 3 ГГц");
//				 SMU200->GPIB_Set(AdrGEN1, Ip);
//
//				 break;
//
//			}


	 AgE44XX->GPIB_Set(AdrGEN, Ip);
	 KOM34980->GPIB_Set(AdrSW,Ip);
	 Vstende5071->GPIB_Set(AdrPan,Ip); /* TODO -cIp ADR: 114752 Установка режимов приборов Stend  */
					switch (BPLAN)
		{
			case 0:	MP_N6702A->IP_Set(AdrBP.c_str()); break;
			case 1:	MP_N6702A->GPIB_Set(AdrBP, Ip);   break;
		}

	 //SMU200->
  }

void Stend1::Pribor5071_LimitLoad()
{        status = viOpenDefaultRM(&defaultRM);
		 strcpy(buffer,Vstende5071->PriborLoad());
		 printf_s("%s\n", buffer);
		 status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		 if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
	return ;
 }      // viPrintf(vi,"*RST\n");

	   strcpy(buffer,Vstende5071->LoadLimit(0,6,Vstende5071->GetF_Get()));
	   strcat(buffer,"\n");
	   viPrintf(vi, buffer);

	   status = viClose(vi);
	   status = viClose(defaultRM);
}
void Stend1::Pribor5071_IzmLoad()
{      	 status = viOpenDefaultRM(&defaultRM);
		 strcpy(buffer,Vstende5071->PriborLoad());
		 printf_s("%s\n", buffer);
		 status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		 if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
	return ;
 }      // viPrintf(vi,"*RST\n");

			int i=0;
			int j=0;
		   for (i = 0; i < 11; i++)
	{
		strcpy(buffer,Vstende5071->PriborSET(i));
		strcat(buffer,"\n");
		viPrintf(vi, buffer);
	}
/**********************************************************************************/

			 for (j = 3; j > 0; j--)
  {
				 for (i = 0; i < 7; i++)                       /* TODO -cTrase : Доработать в классе кол-во  трасс */
	{
		strcpy(buffer,Vstende5071->IzmerenSet(j,i));
		strcat(buffer,"\n");
		viPrintf(vi, buffer);
	}
  }
	   status = viClose(vi);
	   status = viClose(defaultRM);
}
float Stend1::RazborStr (int poz, char* str)
{     char* St = strstr(rezult,",");
	  int i=1;

	for (i = 1; i < poz; i++)
	{
					*St = '0';
					strcpy(rezult,St);
					St = strstr(rezult,",");
					if (i<(poz-1))
			{
				*St = 0;
			}
	}  return 0.01*floor(100*strtod(rezult,NULL));

}
float Stend1::MarkerZapros(int NumTRASE,int NumMARK)
{   status = viOpenDefaultRM(&defaultRM);
		 strcpy(buffer,Vstende5071->PriborLoad());
		 printf_s("%s\n", buffer);
		 status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		 if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
   //	break;
 }
		 strcpy(buffer,Vstende5071->ParSEL(NumTRASE));
		 strcat(buffer,"\n");
		 viPrintf(vi, buffer);

		 strcpy(buffer,Vstende5071->CalkMark(NumMARK));
		 strcat(buffer,"\n");

		 int bufLength = sizeof(rezult);//
   viQueryf(vi,buffer,"%#t",&bufLength, rezult);



    /*
	   char* St = strstr(rezult,",");
      		*St = '0';
      		strcpy(rezult,St);
      		St = strstr(rezult,",");
			*St = 0;
		return 0.01*floor(100*strtod(rezult,NULL));
  */
   return	RazborStr (1, rezult);
}

void Stend1::DataRet(double *Data, double *Freq, int point)
{   status = viOpenDefaultRM(&defaultRM);
		 strcpy(buffer,Vstende5071->PriborLoad());
		 printf_s("%s\n", buffer);
		 status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		 if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
	//break;
 }
 int retCount = point;
 viQueryf(vi, ":SENS1:OFFS:PORT1:DATA?\n", "%,#lf", &retCount, Freq);	//SENS1:FREQ:DATA?
 retCount = 2*retCount;
 viQueryf(vi, "CALC:DATA:FDAT?\n", "%,#lf", &retCount, Data);
}

double Stend1::IP1(double Lstart, double Lmax, double F, int Kanal)
{
	KOM34980->KanalSet(Kanal);
	An8560->AnSpanSet(70,100,3000,Lmax);
	AgE44XX->GenSet(F,Lstart,true);

   return  0.1*floor(10*strtod(An8560->Result(),NULL));
}
#pragma package(smart_init)
