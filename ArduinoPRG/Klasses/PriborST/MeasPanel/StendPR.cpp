//---------------------------------------------------------------------------


#pragma hdrstop
#include "E5071BNetwAnalizer.h"
#include "Agilent8560.h"
#include "HPE44XXB.h"
#include "Switch34980A.h"
#include "StendPR.h"
#include "visa.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vcl.h>
//#include "EBOARD830.h"
//#include "BL3PX1.h"
#pragma comment(lib,"visa32.lib")

//---------------------------------------------------------------------------
	 StendPRibor::StendPRibor(char* Ip)
	// StendPRibor::StendPRibor(char* Ip,IBLock* Block)
	 {/*Анализатор цепей*/

	  Vstende5071 = new E5071B(25, Ip); // "10.29.31.160"
	  RS_PanZVA50 = new PanZVA50(21,  Ip);

	  /*Коммутатор*/
	  TCom = 3;
	  KOM34980 = new Switch34980(15, Ip);  /* TODO -cGPIB : Коммутатор GPIB 15 */
	  /* Генераторы */

	  NN5183 = new N5183A(27,Ip,0);
	  AgE44XX = new HPE4426B(19, Ip,0);
	  Ag4425 = new HPE4426B(17, Ip,0);
	  AE4426 = new HPE4426B(22, Ip,0);
	  SMU200 = new SMU200GEN(28, Ip);
	  RSSMF100A = new SMF100A(26,Ip,0);
	  get1 = 0;
	  get2 = 0;
	 /* Анализатор спектра */
	  analiz = 1;
	  An8560 = new Analiz8560(20, Ip);
	  An9030 = new Analiz9030(18, Ip,0);
	  RS_FSUP50 = new FSU50(21,  Ip);
	  RS_FSL = new FSL18(23,  Ip,0);
	  AnE4407 = new AnalizE4407(24,  Ip,0);
	  Key9020 = new Analiz9020(11, Ip,0);
	 /* Источник питания */
	  MP_N6702A = new N6702A(5,Ip,0);

	  /*Блоки*/
	 // VstendeBlRPU16 = new BlRPU16();
	 // StBlock = Block;
	 //VstendeBlRPU16 = new TRpu16;  /* TODO : Класс блока RPU16 */
	 // BR830 = new HMC830BR();
	  /*=====  End of   ======*/


	  FrGen = 15;
	  PowGen = -50;
	  Span = 0.1;
	  RefL= 10;
	  RBW = 3000;
      Fofs = 100;
	  FrAn =140;
	  RefL10M = 10;
	  buffer[400] = 0;
	  rezult[256] = 0;
	  status = 0;
	  CTbl[0] = 0;//0.1;
	  CTbl[1] = 0;//0.5;
	  CTbl[2] = 0;//2.2;
	  CTbl[3] = 0;//4;

	};




	 StendPRibor::~StendPRibor()
	  {

	  }

void StendPRibor::Set5071_NoPerenos(double Fstr, double Fstop, double Pow, int Var)
{

		Vstende5071->NumTRsSET(3);
		Vstende5071->DispleiSet(3,3,1,10,5,30); //    (int Trase, int Par, int Form, double Div, int Pos, int Lev);
		Vstende5071->DispleiSet(2,2,1,10,5,30);
		Vstende5071->DispleiSet(1,1,1,10,5,30);

	Vstende5071->In_No_perenos(Fstr,Fstop,Pow);     //Vstende5071->In_NEsim_perenos(1,51,Fnastr,70,true, -30);
	Pribor5071_IzmLoad();
						switch (Var)
	{

		case 0:
		Vstende5071->Marker_set(22,32,50,60,0,0,0);  //Vstende5071->GetF_Get()
		 break;
		case 1:
		Vstende5071->Marker_set(40,50,70,80,0,0,0);  //Vstende5071->GetF_Get()
		 break;
		case 2:
		Vstende5071->Marker_set(60,70,105,115,0,0,0);  //Vstende5071->GetF_Get()
		 break;
			case 3:
		Vstende5071->Marker_set(85,125,155,195,0,0,0);  //Vstende5071->GetF_Get()
		 break;

		 default :	Vstende5071->Marker_set(22,32,50,60,0,0,0);
		 break;
	}
		Pribor5071_MarkLoad();

}
double StendPRibor::Set5071_Perenos(double Fnastr, double Fpc,bool InvSp, double Pow)
{
		Vstende5071->NumTRsSET(3);
		Vstende5071->DispleiSet(3,3,1,10,5,30); //(int Trase, int Par, int Form, double Div, int Pos, int Lev);
		Vstende5071->DispleiSet(2,2,1,10,5,30);
		Vstende5071->DispleiSet(1,1,1,10,5,30);
		Vstende5071->StartStop_set(Fnastr, Fpc, 100, InvSp, Pow);
		Pribor5071_IzmLoad();
		Vstende5071->Marker_set(Fnastr, Fnastr-17, Fnastr-15, Fnastr+15, Fnastr+17, Fnastr,Fnastr);  //Vstende5071->GetF_Get()
		Pribor5071_MarkLoad();
		// Vstende5071->CalkMarkBW(1,6);
		/* TODO -cмаркеры : Неравномерность Stend */
		return Vstende5071->Neravnom(1,6,7,Fnastr-15,Fnastr+15,InvSp);



 }

void StendPRibor::SETGet1(double Friq1)
{
       if (jgut)
	{

			 switch (get1)
		{
			 case 0:
			 AE4426->GenSet(Friq1,5,true);
			 break;
			 case 1:
			 SMU200->GenSetA(Friq1,5,true);
			 break;
			 case 2:
			 SMU200->GenSetA(Friq1,5,true);
			 break;
		}

	}
}
void StendPRibor::SETGet2(double Friq)
{

}
void StendPRibor::Pribor5071_MarkLoad()
{
		status = viOpenDefaultRM(&defaultRM);
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
void StendPRibor::Pribor5071_LimitLoad()
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
void StendPRibor::Pribor5071_IzmLoad()
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
		   for (i = 0; i < 12; i++)
			 { strcpy(buffer,"/n");
 strcpy(buffer,Vstende5071->PriborSET(i));

			  strcat(buffer,"\n");
			  viPrintf(vi, buffer);
			 }
/**********************************************************************************/

			 for (j = 3; j > 0; j--) {      //for (j = 3; j > 0; j--)
				 for (i = 0; i < 7; i++)    // for (i = 0; i < 7; i++)                  /* TODO -cTrase : Доработать в классе кол-во  трасс */
					 {
				  strcpy(buffer,Vstende5071->IzmerenSet(j,i));
				  strcat(buffer,"\n");
				  viPrintf(vi, buffer);
				 }
			 }
	   status = viClose(vi);
	   status = viClose(defaultRM);
}
float StendPRibor::RazborStr (int poz, char* str)
{     char* St = strstr(rezult,",");
	  int i=1;

for (i = 1; i < poz; i++) {
				*St = '0';
				strcpy(rezult,St);
				St = strstr(rezult,","); //    -4.94485800E+001,-1.23997000E+002  St = ,-1.23997000E+002
				if (i<(poz-1)) {
                    *St = 0;
				}
}  return 0.01*floor(100*strtod(rezult,NULL));

}
float StendPRibor::MarkerZapros(int NumTRASE,int NumMARK)
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
float StendPRibor::CHenalPOW(double BW,double Centr,int Kanal){
//KOM34980->KanalSet16(Kanal);
SelektKanal(Kanal);
//VstendeBlRPU16->SetAttNOISE(0);
//VstendeBlRPU16->KanalComNG(1,1);
//VstendeBlRPU16->DeviceUSB->NG_ON();
//An8560->AnSpanSet(Centr,BW,3000,10);

switch (analiz)
		{
			case 0:
			An8560->AnSpanSet(Centr,BW,3000,10);// 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 1:
		 //	An9030->AnSpanSet(Centr,BW,3000,10);
			break;
			case 2:
			RS_FSUP50->AnSpanSet(Centr,BW,3000,10);
			break;
			case 3:
			RS_FSL->AnSpanSet(Centr,BW,3000,10);
			break;
			case 4:
		  //	AnE4407->AnSpanSet(Centr,BW,3000,10);
			break;
			case 5:
			Key9020->AnSpanSet(Centr,BW,3000,10);
			break;
		}




Sleep(5000);
Sleep(5000);
//return	0.1*floor(0.5+10*strtod(An8560->CHPWRBW(BW),NULL));
switch (analiz)
		{
			case 0:
			return	0.1*floor(0.5+10*strtod(An8560->CHPWRBW(BW),NULL)); //An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 1:
			return	0.1*floor(0.5+10*strtod(An9030->CHPWRBW(Centr,BW),NULL));//An9030->AnSpanSet(Centr,BW,3000,10);
			break;
			case 2:
			//RS_FSUP50->AnSpanSet(Centr,BW,3000,10);
			break;
			case 3:
			//RS_FSL->AnSpanSet(Centr,BW,3000,10);
			break;
			case 4:
			return	0.1*floor(0.5+10*strtod(AnE4407->CHPWRBW(Centr,BW),NULL));
			break;
			case 5:
			//Key9020->AnSpanSet(Centr,BW,3000,10);
			break;
		}

}
void StendPRibor::DataRet(double *Data, double *Freq, int point)
{   status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
		 strcpy(buffer,RS_FSUP50->PriborLoad());
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
double StendPRibor::GeinAnGen16(double FrGen,double FrAn, int Kanal)
{  	//An8560->AnSpanSet(FrAn,Span,RBW,RefL);
	ALLAnSpanSet(FrAn,Span,RBW,RefL);
/**************************************************************/
	AgE44XX->GenSet(FrGen,PowGen,1);
/**************************************************************/
	//KOM34980->KanalSet16(Kanal);
	SelektKanal(Kanal);
/**************************************************************/
	//VstendeBlRPU16->BlokINITIAL();
	//VstendeBlRPU16->SetAttNOISE(63);
	//StBlock->SetFreq(0,0,0,0);
	Sleep(700);
	//An8560->MkrPeak();
	//return  0.1*floor(10*(strtod(An8560->Result(),NULL) - PowGen));

	return  (ALLAnPeak(1)- PowGen);;
}
void StendPRibor::GetSet()
{   switch (get1)
		{
			 case 0:

			// AE4426->GenSet(VstendeBL3DG1->Geterodin1(),0,true);
			// Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
//			 SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),0,true);
//			 SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
			 break;
		}

}
void StendPRibor::SelektKanal(int Kanal)
{
					switch(TCom)
   {
	 case 0:   break;
	 case 1: KOM34980->KanalSet(Kanal);  break;
	 case 2: KOM34980->KanalSet16(Kanal); break;
	 case 3: KOM34980->CommSetK16HF(Kanal); break;
   }
}
void  StendPRibor::ALLAnSpanSet(double FrAn,double Span,double RBW,double RefL)
{      switch (analiz)
		{
			case 0:
			An8560->AnSpanSet(FrAn,Span,RBW,RefL);// 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 1:
			An9030->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 2:
			RS_FSUP50->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 3:
			RS_FSL->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 4:
			AnE4407->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 5:
			Key9020->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
		}
}
void StendPRibor::ALLAnInit()
{
	switch (analiz)
		{
			case 0:
			An8560->Pinitial();// 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 1:
			An9030->Pinitial();
			break;
			case 2:
			//RS_FSUP50->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 3:
			//RS_FSL->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 4:
			AnE4407->Pinitial();
			break;
			case 5:
			//Key9020->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
		}
}
double StendPRibor::ALLAnPeak(int Num)
{
			switch (analiz)
	{
		case 0:
		An8560->MkrPeak();// 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
		Sleep(1500);
		return  0.1*floor(10*(strtod(An8560->Result(),NULL)));
		break;
		case 1:
		An9030->MkrPeak(Num);
		Sleep(1500);
		return  0.1*floor(10*(strtod(An9030->Result(Num),NULL)));
		break;
		case 2:
		//RS_FSUP50->AnSpanSet(FrAn,Span,RBW,RefL);
		break;
		case 3:
		//RS_FSL->AnSpanSet(FrAn,Span,RBW,RefL);
		break;
		case 4:
		AnE4407->MkrPeak(Num);
		Sleep(1500);
		return  0.1*floor(10*(strtod(AnE4407->Result(Num),NULL)));
		break;
		case 5:
		//Key9020->AnSpanSet(FrAn,Span,RBW,RefL);
		break;
	}
}
double  StendPRibor::ALLAnRESULT(void)
{
	switch (analiz)
	{
		 case 0:
		 	Meas=strtod(An8560->Result(),NULL);
		 	break;
		 case 1:
		 	Meas=strtod(An9030->Result(1),NULL);
		 	break;
		 case 2:
		 	Meas=strtod(RS_FSUP50->Result(1),NULL);
		 	break;
		 case 3:
		 	Meas=strtod(RS_FSL->Result(1),NULL);
		 	break;
	}
	return Meas;
}
void  StendPRibor::ALLAnDELTA(double Fan,double Lan)
{//FUNC: STALLFUNC @STMEAS (0)
	switch (analiz)
	{
		case 0:
			An8560->AnSpanSet(Fan,0.1,3000,Lan);
			Sleep(300);
			An8560->MkrPeak();
			An8560->MkDelta(true,0);
			break;
		case 1:
			An9030->AnSpanSet(Fan,0.1,3000,Lan); //+
			Sleep(800);//+
			An9030->MkrPeak(1);//+
			An9030->MkDelta(1,true,0);//+
			break;
		case 2:
			RS_FSUP50->AnSpanSet(Fan,0.1,3000,Lan);
			break;
		case 3:
			RS_FSL->AnSpanSet(Fan,0.1,3000,Lan);
			RS_FSL->MkrPeak(1);
			RS_FSL->MkDelta(0);
			break;
	}
}
double  StendPRibor::ALLAnSENS(double Fan,double Lan)
{
	 switch (analiz)
	   {
			case 0:
			An8560->AnSpanSet(Fan,Span,RBW,Lan);
			Sleep(300);
			An8560->MkrPeak();
			An8560->MkDelta(true,0);
			break;
			case 1:
			Meas = An9030->Sens(Lan,Fan,Span,RBW,Fofs);
			break;
			case 2:
			RS_FSUP50->AnSpanSet(Fan,Span,RBW,Lan);
			break;
			case 3:
			RS_FSL->AnSpanSet(Fan,Span,RBW,Lan);//SFSL
			RS_FSL->MkrPeak(1);
			Sleep(300);
			RS_FSL->MkDelta(40);
			Meas = RS_FSL->Sens(Lan,Fan,Span,RBW,Fofs);
			break;
	   }
	return Meas;
}
void  StendPRibor::SetAnaliz(double F)
{
	switch (analiz)
		{
			case 0:
			An8560->AnSpanSet(F,Span,RBW,RefL10M);// 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 1:
			An9030->AnSpanSet(F,Span,RBW,RefL10M);
			break;
			case 2:
			RS_FSUP50->AnSpanSet(F,Span,RBW,RefL10M);
			break;
			case 3:
			RS_FSL->AnSpanSet(F,Span,RBW,RefL10M);
			break;
			case 4:
			AnE4407->AnSpanSet(F,Span,RBW,RefL10M);
			break;
			case 5:
			Key9020->AnSpanSet(F,Span,RBW,RefL10M);
			break;
		}
}

void StendPRibor::Stend_LimitLoad(double Pow, double Ref, double Ref10M,double Sp ,double RB,double VFOFS ){
	  PowGen = Pow;
	  Span = Sp;
	  RefL= Ref;
	  RBW = RB;
	  RefL10M = Ref10M;
	  Fofs = VFOFS;

}
double StendPRibor::Friq(void){
	  switch (analiz)
		{
			case 0:
			return  0.001*floor(1E-3*An8560->FMark());
			break;
			case 1:
			return  1E-3*floor(1E-3*An9030->FMark());
			break;
			case 2:
			return  1E-3*floor(1E-3*RS_FSUP50->FMark());
			break;
			case 3:
			return  1E-3*floor(1E-3*RS_FSL->FMark());
			break;
			case 4:
			return  1E-3*floor(1E-3*AnE4407->FMark());
			break;
			case 5:
			return  1E-3*floor(1E-3*Key9020->FMark());
			break;
		}
}
void StendPRibor::Stend_LimitRet(double &Pow, double &Ref, double &Ref10M,double &Sp ,double &RB ){

	  Pow = PowGen;
	  Sp  = Span;
	  Ref = RefL;
	  RB  = RBW;
	  Ref10M = RefL10M;

}
void StendPRibor::Stend_PrAdress(int An, int Get1, int Get2,
		int ANLAN, AnsiString AdrAN,
		int GENLAN, AnsiString AdrGEN,
		int GEN1LAN,AnsiString AdrGEN1,
		int GEN2LAN, AnsiString AdrGEN2,
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
				ShowMessage("Установлен анализатор R&S FSU50");


				switch(ANLAN)
				{
				case 0: RS_FSUP50->IP_Set(AdrAN.c_str());   break;
				case 1: RS_FSUP50->GPIB_Set(AdrAN, Ip); break;
				}
				break;
				case 4:
				ShowMessage("Установлен анализатор Keysight E4407");


				switch(ANLAN)
				{
				case 0: AnE4407->IP_Set(AdrAN.c_str());   break;
				case 1: AnE4407->GPIB_Set(AdrAN, Ip); break;
				}
				break;
				case 5:
				ShowMessage("Установлен анализатор Keysight N9020B");


				switch(ANLAN)
				{
				case 0: Key9020->IP_Set(AdrAN.c_str());   break;
				case 1: Key9020->GPIB_Set(AdrAN, Ip); break;
				}
				break;





			}
			 get1 = Get1;
			 get2 = Get2;

							switch (get1)
	{
		 case 0:
			ShowMessage("Гетеродин1 Agilent E4426B 4 ГГц");
						switch(GEN1LAN)
		   {   case 0: Ag4425->IP_Set(AdrGEN1.c_str());	break;
			   case 1: Ag4425->GPIB_Set(AdrGEN1, Ip); break;
		   }
			ShowMessage("Гетеродин2 Agilent E4425B 3 ГГц");
						switch(GEN2LAN)
		   {
			 case 0: AE4426->IP_Set(AdrGEN2.c_str());   break;
			 case 1: AE4426->GPIB_Set(AdrGEN2, Ip); break;
		   }
		 break;

		 case 1:
			 ShowMessage("Гетеродин1 SMU200 A 6 ГГц");
			 ShowMessage("Гетеродин2 SMU200 B 3 ГГц");
					switch(GEN1LAN)
		   {
			 case 0:SMU200->IP_Set(AdrGEN1.c_str());    break;
			 case 1:SMU200->GPIB_Set(AdrGEN1, Ip);  break;

		   }

		 break;

	}


				switch(GENLAN)
		{
			case 0: AgE44XX->IP_Set(AdrGEN.c_str()); 	break;
			case 1: AgE44XX->GPIB_Set(AdrGEN, Ip); 		break;
		}

				switch(PANLAN)
		{
			case 0: Vstende5071->IP_Set(AdrPan.c_str());  	break; /* TODO -cIp ADR: 114752 Установка режимов приборов Stend  */
			case 1: Vstende5071->GPIB_Set(AdrPan,Ip); 		break;
		}
				switch(SWLAN)
		{
			case 0: KOM34980->IP_Set(AdrSW.c_str()); 	break;
			case 1: KOM34980->GPIB_Set(AdrSW,Ip); 		break;
		}
				switch (BPLAN)
		{
			case 0:	MP_N6702A->IP_Set(AdrBP.c_str()); break;
			case 1:	MP_N6702A->GPIB_Set(AdrBP, Ip);   break;
		}

  }

  /*******************************************************************************/
bool StendPRibor::ChekCon(){
	bool ChKon = false;
	double Gein = GeinAnGen(15,15,1) - GeinAnGen(15,15,0,20,0,1,1);//GeinAnGen(15,15,1)- GeinAnGen(15,15,0,20,0,1);
	   if (Gein<8||Gein>12) {
		   ChKon = true;
	   }
	Gein = GeinAnGen(15,15,1);

	   if (Gein<14.5||Gein>18.5) {
			  ChKon = true;
	   }
	return ChKon ;
}
double StendPRibor::GeinAnGen(double FrGen,double FrAn, int Kanal)
{  	//An8560->AnSpanSet(FrAn,Span,RBW,RefL);//GeinAnGen648
	ALLAnSpanSet(FrAn,Span,RBW,RefL);

	AgE44XX->GenSet(FrGen,PowGen,1);
	//KOM34980->KanalSet16(Kanal);
	SelektKanal(Kanal);
	//VstendeBlRPU16->BlokINITIAL();
	//VstendeBlRPU16->SetAttNOISE(63);

	Sleep(700);
	//An8560->MkrPeak();
	//return  0.1*floor(10*(strtod(An8560->Result(),NULL) - PowGen));
	return  (ALLAnPeak(1)- PowGen);
}
double StendPRibor::PowAn(double FrAn,double RefL, int Kanal)
{     //VstendeBlRPU16->->BlokINITIAL();
	  //KOM34980->KanalSet16(Kanal);
	  SelektKanal(Kanal);

	  //An8560->AnSpanSet(FrAn,Span,RBW,RefL10M);
	  ALLAnSpanSet(FrAn,Span,RBW,RefL10M);
	  Sleep(500);
	  //An8560->MkrPeak();
	  //return  0.1*floor(10*strtod(An8560->Result(),NULL));
	  return  ALLAnPeak(1);
}
double StendPRibor::SIP1(double Lstart, double Lmax, double Fin, double Fout, int Kanal)
{//FUNC: STENDIP1 @STMEAS (1)
	ALLAnSpanSet(Fin,Span,RBW,RefL);
//-----------------------------------
	AgE44XX->GenSet(Fin,Lstart,1);
//-----------------------------------
	SelektKanal(Kanal);
//-----------------------------------
	StBlock->SetFreq(Fin,0,0,0,0,Kanal,63,1);// ATT -63->0dB
//-----------------------------------
	Sleep(300);
	ALLAnDELTA(Fout,25);
			double A;
			i = 0; Meas = 0;
			  while ((i - Meas) < 1.0)
		 {
			  i=i+1;
			  AgE44XX->GenSet(Fin,Lstart+i,true);
			  Sleep(1000);

			/*			switch (analiz)
			 {
				 case 0:
				 Meas=strtod(An8560->Result(),NULL);
				 break;
				 case 1:
				 Meas=strtod(An9030->Result(1),NULL);
				 break;
				 case 2:
				 Meas=strtod(RS_FSUP50->Result(1),NULL);
				 break;
				 case 3:
				 Meas=strtod(RS_FSL->Result(1),NULL);
				 break;
			 }*/
			   ALLAnRESULT();
		 }
			AgE44XX->GenSet(Fin,Lstart+i-1,true);

						/*switch (analiz)
		 {
				case 0:
				An8560->MkDelta(false,0);
				Sleep(300);
				An8560->MkrPeak();
				Meas=strtod(An8560->Result(),NULL);
				break;
				case 1:
				An9030->MkDelta(1,false,0);
				Sleep(300);
				An9030->MkrPeak(1);
				Meas=strtod(An9030->Result(1),NULL);
				break;
				case 2:
				RS_FSUP50->MkDelta(1);
				Sleep(300);
				RS_FSUP50->MkrPeak(1);
				Meas=strtod(RS_FSUP50->Result(1),NULL);
				break;
				case 3:
				RS_FSL->MkDelta(1);
				Sleep(300);
				RS_FSL->MkrPeak(1);
				Meas=strtod(RS_FSL->Result(1),NULL);
				break;
		 }*/
			Meas = ALLAnPeak(1);
	return  0.1*floor(10*Meas);
}
double StendPRibor::Sens(double Lin, double Lan, double Fin,double Fan, int Kanal)
{//FUNC: STENDSENS @STMEAS (1)

//-----------------------------------
		AgE44XX->GenSet(Fin,Lin,true);
//-----------------------------------
		SelektKanal(Kanal);
//-----------------------------------

		//(double F,double Fat,int ATT1,int ATT2,int ATT3,int Kanal,int ALL)
		StBlock->SetFreq(Fin,0,0,0,0,Kanal,63,1);// ATT -63->0dB
 //VstendeBL3VK1->FriqSET(Fin,False ,0,0,Kanal);      /* TODO -cЧувствительность : Убрать LNA */

		/* switch (analiz)
	   {
			case 0:
			An8560->AnSpanSet(VstendeBL3VK1->FriqOUT(),0.1,3000,Lan);
			Sleep(300);
			An8560->MkrPeak();
			An8560->MkDelta(true,0);
			break;
			case 1:
			Meas = An9030->Sens(Lan,VstendeBL3VK1->FriqOUT(),Span,RBW,30);
			break;
			case 2:
			RS_FSUP50->AnSpanSet(VstendeBL3VK1->FriqOUT(),0.1,3000,Lan);
			break;
			case 3:
			RS_FSL->AnSpanSet(VstendeBL3VK1->FriqOUT(),0.1,3000,Lan);//SFSL
			RS_FSL->MkrPeak(1);
			Sleep(300);
			RS_FSL->MkDelta(40);
			Meas = RS_FSL->Sens(Lan,VstendeBL3VK1->FriqOUT(),Span,RBW,30);
			break;
	   }*/

		ALLAnSENS(Fan,Lan);
   		return  Meas+Lin+10;
}
//-----------------------------------
double StendPRibor::GeinAnGen(double FrGen,double FrAn,int ATT1,int ATT2,int PRES,int Kanal,int PARAM)
{
	 //TODO:  GEIN16RR  @STEND
//-----------------------------------

	ALLAnSpanSet(FrAn,Span,RBW,RefL);

   	AgE44XX->GenSet(FrGen,PowGen,1);

//-----------------------------------
   	SelektKanal(Kanal);
  //SetFreq(double F,double Fat,int ATT1,int ATT2,int ATT3,int Kanal,int ALL,int BPERENOS)
	StBlock->SetFreq(FrGen,0,ATT1,ATT2,ATT2,Kanal,63,PARAM);// ATT -63->0dB

	Sleep(700);

	return  (ALLAnPeak(1) - PowGen);
}
#pragma package(smart_init)
