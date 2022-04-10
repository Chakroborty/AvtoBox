//---------------------------------------------------------------------------


#pragma hdrstop
#include "E5071BNetwAnalizer.h"
#include "Agilent8560.h"
#include "HPE44XXB.h"
#include "Switch34980A.h"
#include "Stend3CR68.h"
#include "visa.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vcl.h>

#pragma comment(lib,"visa32.lib")

//---------------------------------------------------------------------------
	 StendKV68::StendKV68(bool Blok3CR6, char* Ip)
	 {
	  Vstende5071 = new E5071B(25, Ip); // "10.29.31.160"


	  An8560 = new Analiz8560(20, Ip);
	  An9030 = new Analiz9030(18, Ip,0);
	  RS_FSUP50 = new FSU50(21,  Ip);
	  Ag4425 = new HPE4426B(17, Ip,0);
	  AE4426 = new HPE4426B(22, Ip,0);
	   Ag4425->IP_Set("10.29.31.17");
	   AE4426->IP_Set("10.29.31.22");
	  AgE44XX = new HPE4426B(19, Ip,0);
	  KOM34980 = new Switch34980(15, Ip);  /* TODO -cGPIB : Коммутатор GPIB 15 */
	  RS_PanZVA50 = new PanZVA50(21,  Ip);
	  SMU200 = new SMU200GEN(28, Ip);


	  MP_N6702A = new N6702A(5,Ip,0);
	  /*===================  Конец Приборы  =============================*/
	  VstendeBl3CR6 = new Bl3CR6(Blok3CR6); /* TODO : Класс блока 3Чр68 */

	  TCom = 1;
	  analiz =0;
	  get = 0;
	  FrGen = 15;
	  PowGen = -50;
	  Span = 0.1;
	  RefL= 10;
	  RBW = 3000;
	  FrAn =140;
	  RefL10M = 10;
	  buffer[400] = 0;
	  rezult[256] = 0;
	  status = 0;
	 



	}




	 StendKV68::~StendKV68()
	  {

	  } 
void StendKV68::Sint_SetBLOK68(double Fin)
{
	DWORD  dwStatus;

  //VstendeBl3CR6->SetFriq(Fin);
  VstendeBl3CR6->SetFriq(0,0,50,0,0,Fin,0,256,false);
		   //(int Kanal,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC)
    if (!VstendeBl3CR6->GetBlTyp3CR6())
	{    VstendeBl3CR6->SetFriq(0,0,50,0,0,Fin,0,256,false);
	} else
	{

	   VstendeBl3CR6->SetFriq(0,0,50,0,0,Fin,0,256,false);
	}

}
void StendKV68::Set5071_NoPerenos(double Fstr, double Fstop, double Pow, int Var)
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
double StendKV68::Set5071_PerenosBW(double Fnastr, double Fpc,bool InvSp, double Pow,double Pos,double Span)
{
		Vstende5071->NumTRsSET(3);
		Vstende5071->DispleiSet(3,3,1,10,5,Pos);  // DispleiSet(int Trase, int Par, int Form, double Div, int Pos, int Lev);
		Vstende5071->DispleiSet(2,2,1,10,5,Pos);
		Vstende5071->DispleiSet(1,1,1,10,5,Pos);                                                              /* TODO -cДоработать : Ввести управление REF position */
		Vstende5071->StartStop_set(Fnastr, Fpc, Span, InvSp, Pow);
		Pribor5071_IzmLoad();
		Vstende5071->Marker_set(Fnastr, 0, 0, 0, 0, 0, 0);  //Vstende5071->GetF_Get()
		Pribor5071_MarkLoad();
		Vstende5071->SetMark(1,1,4);
		Pribor5071_MarkLoad();
		Sleep(500);

		return  Vstende5071->CalkMarkBW(1,1);//Vstende5071->Neravnom(1,4,5,Fnastr-15,Fnastr+15,InvSp);



 }
void StendKV68::Set5071_Perenos(double StartIN, double StopIN, double Fnastr, double Fpc, double Pow)
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
double StendKV68::Set5071_Perenos28(double Fnastr, double Fpc,bool InvSp, double Pow)
{
		Vstende5071->NumTRsSET(3);
		Vstende5071->DispleiSet(3,3,1,10,5,30); //    (int Trase, int Par, int Form, double Div, int Pos, int Lev);
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
bool StendKV68::ChekCon(double FrGen,int Kanal)
{                        /* TODO : Проверка проверка подключения */
	 bool ChKon = false;
	   //	//VstendeBL3DG1->SendDATA_SPI_USB(//VstendeBL3DG1->ModulPX2->LoadATT_K1(i),0);
	 double Gein = GeinAnGen(FrGen,0,0,Kanal)-GeinAnGen(FrGen,20,0,Kanal); //= GeinAnGen(15,15,1)- GeinAnGen(15,15,0,20,0,1);
		   if (Gein<8||Gein>12)
		   {
				ChKon = true;

		   }
				Gein = GeinAnGen(FrGen,0,0,Kanal);

		   if (Gein<40)
		   {
				ShowMessage("Проверить кабели");
				ChKon = true;
		   }
	//   	//VstendeBL3DG1->SendDATA_SPI_USB(//VstendeBL3DG1->ModulPX2->LoadATT_K1(i),0);
	   return ChKon ;
}
void StendKV68::SelektKanal(int Kanal)
{
					switch(TCom)
   {
	 case 0:   break;
	 case 1: KOM34980->KanalSet(Kanal);  break;
	 case 2: KOM34980->KanalSet16(Kanal); break;

   }
}

void StendKV68::Pribor5071_MarkLoad()
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
void StendKV68::Pribor5071_LimitLoad()
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
void StendKV68::Pribor5071_IzmLoad()
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
		strcpy(buffer,":SENS1:BWID  3E3");//Установка Average BW 
		strcat(buffer,"\n");
		viPrintf(vi, buffer);


	   status = viClose(vi);
	   status = viClose(defaultRM);
}
float StendKV68::RazborStr (int poz, char* str)
{     char* St = strstr(rezult,",");
	  int i=1;

for (i = 1; i < poz; i++) {
				*St = '0';
				strcpy(rezult,St);
				St = strstr(rezult,",");
				if (i<(poz-1)) {
                    *St = 0;
				}
}  return 0.01*floor(100*strtod(rezult,NULL));

}
float StendKV68::MarkerZapros(int NumTRASE,int NumMARK)
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
float StendKV68::CHenalPOW(double BW,double Centr,int Kanal){
KOM34980->KanalSet16(Kanal);
//VstendeBlRPU16->SetAttNOISE(0);
An8560->AnSpanSet(Centr,BW,3000,10);
Sleep(5000);
Sleep(5000);
return	0.1*floor(0.5+10*strtod(An8560->CHPWRBW(BW),NULL));;
}
void StendKV68::DataRet(double *Data, double *Freq, int point)
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
double StendKV68::IP1(double Lstart, double Lmax,double Fin, double Fout, int Kanal, int Com)
{  			if (jgut)
	{ 	TKanal = 0;
	}else
	{   SelektKanalCr68(Kanal);
		TKanal = Kanal-1;

    }


VstendeBl3CR6->SetFriq(TKanal,1,0,0,0,Fin,0,255,0);//SetFriq(int Kanal,int Clbr,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC);
				if (jgut)
	{
				 switch (get)
	   {
			 case 0:

			// AE4426->GenSet(//VstendeBL3DG1->Geterodin1(),5,true);
		   //	 Ag4425->GenSet(//VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
		  //	 SMU200->GenSetA(//VstendeBL3DG1->Geterodin1(),5,true);
		  //	 SMU200->GenSetB(//VstendeBL3DG1->Geterodin2(),0,true);
			 break;
	   } //	KOM34980->KanalSet(Kanal);

	}
		AgE44XX->GenSet(Fin,Lstart,true);
		switch (analiz)
   {
	 case 0:
	 An8560->AnSpanSet(70,0.1,3000,Lmax);
	 Sleep(300);
	 An8560->MkrPeak();
	 An8560->MkDelta(true,0);
	 break;
	 case 1:
	 An9030->AnSpanSet(70,0.1,3000,Lmax);
	 //An9030->SetMarker(0,0,0,0);
	 Sleep(800);
	 An9030->MkrPeak(1);
	 An9030->MkDelta(1,true,0);

	 break;
	  case 2:
	 RS_FSUP50->AnSpanSet(70,0.1,3000,Lmax);
	 break;
   }
				i = 0;Meas =0;
			  while ((i-Meas)<1)
		 {
			  i=i+1;
			  AgE44XX->GenSet(Fin,Lstart+i,true);
			  Sleep(1000);
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
			 }
		 }
			 AgE44XX->GenSet(Fin,Lstart+i-1,true);

						switch (analiz)
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
		 }


   return  0.1*floor(10*Meas);
}
double StendKV68::Sens(double Lin,double Lan, double Fin, int Kanal,int Com)
{

	   	if (jgut)
	{ 	TKanal = 0;
	}else
	{   SelektKanalCr68(Kanal);
		TKanal = Kanal-1;

    }

 VstendeBl3CR6->SetFriq(TKanal,1,0,0,0,Fin,0,256,0);//SetFriq(int Kanal,int Clbr,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC);
 AgE44XX->GenSet(Fin,Lin,true);
// //VstendeBL3DG1->FriqSET(Fin,False ,0,0,Kanal);      /* TODO -cЧувствительность : Убрать LNA */
				if (jgut)
  {

			 switch (get)
	   {
		 case 0:

		// AE4426->GenSet(//VstendeBL3DG1->Geterodin1(),5,true);
		// Ag4425->GenSet(//VstendeBL3DG1->Geterodin2(),0,true);
		 break;

		 case 1:
		// SMU200->GenSetA(//VstendeBL3DG1->Geterodin1(),5,true);
		// SMU200->GenSetB(//VstendeBL3DG1->Geterodin2(),0,true);
		 break;
	   } //	KOM34980->KanalSet(Kanal);
  }
		 switch (analiz)
	   {
		 case 0:
		 An8560->AnSpanSet(70,0.1,3000,Lan);
		 Sleep(300);
		 An8560->MkrPeak();
		 An8560->MkDelta(true,0);
		 break;
		 case 1:
		 Meas = An9030->Sens(Lan,70,Span,RBW,30);
		 break;
		 case 2:
		 RS_FSUP50->AnSpanSet(70,0.1,3000,Lan);
		 break;
	   }






   return  Meas+Lin+10;


}
double StendKV68::SensATT(double Lin,double Lan, double Fin, int Kanal){

 AgE44XX->GenSet(Fin,Lin,true);
 ////VstendeBL3DG1->FriqSET(Fin,false ,0,0,Kanal);
	if (jgut) {

			 switch (get)
	   {
			 case 0:

		  //	 AE4426->GenSet(//VstendeBL3DG1->Geterodin1(),5,true);
		  //	 Ag4425->GenSet(//VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
		 //	 SMU200->GenSetA(//VstendeBL3DG1->Geterodin1(),5,true);
		 //	 SMU200->GenSetB(//VstendeBL3DG1->Geterodin2(),0,true);
			 break;
	   } //	KOM34980->KanalSet(Kanal);
  }
		 switch (analiz)
		  {
			 case 0:
			 An8560->AnSpanSet(140,0.1,3000,Lan);
			 Sleep(300);
			 An8560->MkrPeak();
			 An8560->MkDelta(false,0);
			 Meas = 0.1*floor(10*strtod(An8560->Result(),NULL));
			 break;
			 case 1:
			 An9030->AnSpanSet(140,0.1,3000,Lan);
			 An9030->SetMarker(0,0,0,0);
			 An9030->MkDelta(1,false,0);                             /* TODO 1 -cАнализатор  : Добавить сброс накопления в маркер пик */
			 Sleep(300);
			 An9030->MkrPeak(1);
			 Meas = 0.1*floor(10*strtod(An9030->Result(1),NULL));


			 break;
			  case 2:
			 RS_FSUP50->AnSpanSet(140,0.1,3000,Lan);
			 break;
		  }
		Sleep(500);
		//VstendeBL3DG1->FriqSET(Fin,false ,50,50,Kanal);

        	 switch (analiz)
			 {
					 case 0:
					 An8560->AnSpanSet(140,0.1,3000,Lan);
					 An8560->MkDelta(false,0);
					 Sleep(300);
					 An8560->MkrPeak();

					 return	 Meas - 0.1*floor(10*strtod(An8560->Result(),NULL));
					 break;
					 case 1:
					 An9030->AnSpanSet(140,0.1,3000,Lan);
					 An9030->MkDelta(1,false,0);
					 Sleep(500);
					 An9030->MkrPeak(1);
					 return Meas - 0.1*floor(10*strtod(An9030->Result(1),NULL));


					 break;
					 case 2:
					 return Meas - RS_FSUP50->AnSpanSet(140,0.1,3000,Lan);
					 break;
			 }


}
void StendKV68::GetSet()
{   switch (get)
		{
			 case 0:

			 //AE4426->GenSet(VstendeBL3DG1->Geterodin1(),0,true);
			 //Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
			 //SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),0,true);
			 //SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
			 break;
		}

}
double StendKV68::GeinAnGen(double FrGen,int ATT,int ATT1, int Kanal)
{/* GeinAnGen  param4 */

		//VstendeBL3DG1->FriqSET(FrGen,false,ATT,ATT1,Kanal);
		AgE44XX->GenSet(FrGen,PowGen,1);
			if (jgut)
	{

			 switch (get)
		{
			 case 0:

			 //AE4426->GenSet(VstendeBL3DG1->Geterodin1(),5,true);
			 //Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
			 //SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),5,true);
			 //SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
			 break;
		}

	}

		switch (analiz)
		{
			 case 0:
			 An8560->AnSpanSet(140,Span,RBW,RefL10M);  // 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			 break;

			 case 1:
			 An9030->AnSpanSet(140,Span,RBW,RefL10M);
			 break;

			 case 2:
			 RS_FSUP50->AnSpanSet(140,Span,RBW,RefL10M);
			 break;

		}
   //	//VstendeBL3DG1->FriqSET(FrGen,false,ATT,ATT1,Kanal);

	
			 Sleep(100);

		 switch (analiz)
		{
			 case 0:

			 An8560->MkrPeak();                                   // An8560->MkrPeak();
			 return  0.1*floor(10*strtod(An8560->Result(),NULL))-PowGen; //return  0.1*floor(10*(strtod(An8560->Result(),NULL) - PowGen));
			 break;

			 case 1:
			 An9030->MkDelta(1,false,0);

			 An9030->MkrPeak(1);
			 Sleep(100);
			 Meas = 0.1*floor(10*strtod(An9030->Result(1),NULL))-PowGen;
			 //Sleep(200);
			 return  Meas;
			 break;
		}




}
double StendKV68::GeinAnGen(double FrGen,bool Com,int ATT,int ATT1, int Kanal,bool Shirokaia,int Comm)//   VstendeBl3PX1->FriqSET(FrGen,false,ATT,ATT1,Kanal);
{/* GeinAnGen  param8 */


	if (jgut)
	{ 	TKanal = 0;
	}else
	{   SelektKanalCr68(Kanal);
		TKanal = Kanal-1;

    }

	//VstendeBl3CR6->SetFriq(0,50,0,0,,0,256);
	//BLOKUKV->FriqSET(FrGen,ATT,ATT1,Modul,Shirokaia,Peleng);   //FriqSET(double Fin1,int DB1,int DB2,int Kanal,bool Shrokaia,bool Peleng);
//								 switch (Shirokaia)
//	  {  case 0:
//
//		 VstendeBl3CR6->SetFriq(16,1,0,0,0,FrGen,0,256,0);//SetFriq(int Kanal,int Clbr,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC);
//		// Rez = Set5071_PerenosBW(FrGen,70,1,-55,20,6);Set5071_PerenosBW(double Fnastr, double Fpc,bool InvSp, double Pow,double Pos,double Span)
//		 break;
//		 case 1:
//		 VstendeBl3CR6->SetFriq(16,1,0,0,0,FrGen,0,256,1);// WaidPC = 1 полоса узкая Clbr = 1 вход ант.
//		 //Rez = Set5071_PerenosBW(FrGen,70,1,-55,20,0.1);
//		 break;
//		 default: VstendeBl3CR6->SetFriq(16,1,0,0,0,FrGen,0,256,0); break;     //Set5071_PerenosBW(1000,70,1,-45,20,6);
//	  }    VstendeBl3CR6->SetFriq(Kanal-1,1,0,0,0,Fin,0,256,0);
		   VstendeBl3CR6->SetFriq(TKanal,1,0,ATT,0,FrGen,ATT1,256,!Shirokaia);

			if (jgut)
	 {

				 switch (get)
			{
				 case 0:

			 //	 AE4426->GenSet(BLOKUKV->Geterodin1(),5,true);
			 //	 Ag4425->GenSet(BLOKUKV->Geterodin2(),0,true);
				 break;

				 case 1:
			 //	 SMU200->GenSetA(BLOKUKV->Geterodin1(),5,true);
			 //	 SMU200->GenSetB(BLOKUKV->Geterodin2(),0,true);
				 break;
			}
	 }
			switch (analiz)
	 {
		 case 0:
		 An8560->AnSpanSet(70,Span,RBW,RefL10M);  // 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
		 break;

		 case 1:
		 An9030->AnSpanSet(70,Span,RBW,RefL10M);
		 break;
	 }
	 AgE44XX->GenSet(FrGen,PowGen,1);





	Sleep(500);
		 switch (analiz)
		{
			 case 0:

			 An8560->MkrPeak();                                   // An8560->MkrPeak();
			 return  0.1*floor(10*strtod(An8560->Result(),NULL))-PowGen; //return  0.1*floor(10*(strtod(An8560->Result(),NULL) - PowGen));
			 break;

			 case 1:
			// An9030->MkDelta(1,false,0);
			 An9030->MkrPeak(1);

			 return  0.1*floor(10*strtod(An9030->Result(1),NULL))-PowGen;
			 break;
		}
 }
void StendKV68::SelektKanalCr68(int Kanal){
						if (jgut)
			{
					switch (Kanal)
				{
						case 1:
					   //	Peleng = KluchPC1::peleng;
						break;

						case 2:
					  //	Peleng = KluchPC1::peleng;
						break;
						case 3:
					  //	Peleng = KluchPC1::perexv;
						break;
						case 4:
					  //	Peleng = KluchPC1::perexv;
						break;
						case 5:
					  //	Peleng = KluchPC1::perexv;
						break;
						case 6:
					  //	Peleng = KluchPC1::perexv;
						break;

				}

			} else
			{
					
				if(Kanal>8) {
						KOM34980->KanalSet(Kanal-8);/* code */
					}
					else {
						KOM34980->KanalSet(Kanal);/* code */
					}
			}

}
double StendKV68::GeinPanoram(double FrGen,int ATT,int Kanal,int PC,int Com)
{
	if (jgut)
	{ 	TKanal = 0;
	}else
	{   SelektKanalCr68(Kanal);
		TKanal = Kanal-1;

    }


								 switch (PC)
	  {  case 0:


		 VstendeBl3CR6->SetFriq(TKanal,1,0,0,0,FrGen,0,255,0);//SetFriq(int Kanal,int Clbr,double Nois,double ATTpr,double Pres,double Fset,double ATT,double AmpUPC,bool WaidPC);
		 Rez = Set5071_PerenosBW(FrGen,70,1,-55,20,6);//Set5071_PerenosBW(double Fnastr, double Fpc,bool InvSp, double Pow,double Pos,double Span)
		 break;
		 case 1:
		 VstendeBl3CR6->SetFriq(TKanal,1,0,0,0,FrGen,0,255,1);// WaidPC = 1 полоса узкая Clbr = 1 вход ант.
		 Rez = Set5071_PerenosBW(FrGen,70,1,-55,20,0.1);
		 break;
		 default: Set5071_PerenosBW(1000,70,1,-45,20,6); break;
	  }
		 return  Rez;

}
void  StendKV68::SetAnaliz(double F)
{
  	switch (analiz)
		{
			 case 0:
			 An8560->AnSpanSet(F,Span,RBW,RefL10M);  // 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			 break;

			 case 1:
			 An9030->AnSpanSet(F,Span,RBW,RefL10M);
			 break;

			 case 2:
			 RS_FSUP50->AnSpanSet(F,Span,RBW,RefL10M);
			 break;

		}



}
double StendKV68::PowAn(double FrAn, int Kanal)
{     	 switch (analiz)
		{
			case 0:
			An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			break;

			case 1:
			An9030->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
			case 2:
			RS_FSUP50->AnSpanSet(FrAn,Span,RBW,RefL);
			break;
		}
	  Sleep(500);
		 switch (analiz)
		{
			case 0:
			An8560->MkrPeak();
			return  0.1*floor(10*strtod(An8560->Result(),NULL));
			break;

			case 1:
			An9030->MkrPeak(1);
			return  0.1*floor(10*strtod(An9030->Result(1),NULL));
			break;
			case 2:
			RS_FSUP50->MkrPeak(1);
			return  0.1*floor(10*strtod(RS_FSUP50->Result(1),NULL));
			break;

		}

}
double StendKV68::PowAn10(double FrAn, int Kanal)
{     	 switch (analiz)
		{
			 case 0:
			 An8560->AnSpanSet(FrAn,Span,RBW,RefL10M);
			 break;

			 case 1:
			 An9030->AnSpanSet(FrAn,Span,RBW,RefL10M);
			 break;
			 case 2:
			 RS_FSUP50->AnSpanSet(FrAn,Span,RBW,RefL10M);
			 break;

		}
	  Sleep(500);
		 switch (analiz)
		{
			 case 0:
			 An8560->MkrPeak();
			  return  0.1*floor(10*strtod(An8560->Result(),NULL));
			 break;

			 case 1:
			 An9030->MkrPeak(1);
			 return  0.1*floor(10*strtod(An9030->Result(1),NULL));
			 break;

			 case 2:
			 RS_FSUP50->MkrPeak(1);
			 return  0.1*floor(10*strtod(RS_FSUP50->Result(1),NULL));
			 break;
		}

}
void StendKV68::Stend_LimitLoad(double Pow, double Ref, double Ref10M,double Sp ,double RB ){
	  PowGen = Pow;
	  Span = Sp;
	  RefL= Ref;
	  RBW = RB;
	  RefL10M = Ref10M;

}
double StendKV68::Friq(void){
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
		}
}
void StendKV68::Stend_LimitRet(double &Pow, double &Ref, double &Ref10M,double &Sp ,double &RB ){

	  Pow = PowGen;
	  Sp  = Span;
	  Ref = RefL;
	  RB  = RBW;
	  Ref10M = RefL10M;

}
void StendKV68::Stend_PrAdress(int An, int Gen,int ANLAN, AnsiString AdrAN, //
	int GENLAN, AnsiString AdrGEN,                                          //
	int GEN1LAN,AnsiString AdrGEN1,int GEN2LAN, AnsiString AdrGEN2,         //
	int SWLAN, AnsiString AdrSW,                                            //
	int PANLAN,	AnsiString AdrPan,                                          //
	int BPLAN,	AnsiString AdrBP, AnsiString Ip)                            //
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


					switch(ANLAN)
				{
					case 0: RS_FSUP50->IP_Set(AdrAN.c_str());   break;
					case 1: RS_FSUP50->GPIB_Set(AdrAN, Ip); break;
				}
				 break;
			}
			 get = Gen;
							switch (get)
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

	 //SMU200->
  }
#pragma package(smart_init)
