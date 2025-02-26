//---------------------------------------------------------------------------


#pragma hdrstop
#include "E5071BNetwAnalizer.h"
#include "Agilent8560.h"
#include "HPE44XXB.h"
#include "Switch34980A.h"
#include "Stend3GD1.h"
#include "visa.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vcl.h>
#include "BL3PX1.h"
#pragma comment(lib,"visa32.lib")

//---------------------------------------------------------------------------
	 StendRPU16::StendRPU16(char* Ip)
	 {
	  Vstende5071 = new E5071B(25, Ip); // "10.29.31.160"
	  KOM34980 = new Switch34980(15, Ip);  /* TODO -cGPIB : ���������� GPIB 15 */

	  An8560 = new Analiz8560(20, Ip);
	  An9030 = new Analiz9030(18, Ip,0);
	  AE4426 = new HPE4426B(22, Ip);
	  RS_FSUP50 = new FSU50(21,  Ip);
	  RS_PanZVA50 = new PanZVA50(21,  Ip);
	  SMU200 = new SMU200GEN(28, Ip);
	  AgE44XX = new HPE4426B(19, Ip);
	  Ag4425 = new HPE4426B(17, Ip);
	  MP_N6702A = new N6702A(5,Ip,0);
	  analiz =0;
	  get = 0;
	  FrGen = 15;
	  PowGen = -50;
	  Span = 0.1;
	  RefL= 10;
	  RBW = 3000;
	  FrAn =140;
	  RefL10M = 10;
	  VstendeBL3DG1 = new BL3DG1(true);  //VstendeBlRPU16 = new TRpu16;  /* TODO : ����� ����� RPU16 */
	  buffer[400] = 0;
	  rezult[256] = 0;
	  status = 0;
	}




	 StendRPU16::~StendRPU16()
	  {

	  } 

void StendRPU16::Set5071_NoPerenos(double Fstr, double Fstop, double Pow, int Var)
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
double StendRPU16::Set5071_Perenos(double Fnastr, double Fpc,bool InvSp, double Pow)
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
							/* TODO -c������� : ��������������� Stend */
		 return Vstende5071->Neravnom(1,6,7,Fnastr-15,Fnastr+15,InvSp);



 }
bool StendRPU16::ChekCon(double FrGen,int Kanal)
{                        /* TODO : �������� �������� ����������� */
	 bool ChKon = false;
		VstendeBL3DG1->SendDATA_SPI_USB(VstendeBL3DG1->ModulPX2->LoadATT_K1(i),0);
	 double Gein = GeinAnGen(FrGen,0,0,Kanal)-GeinAnGen(FrGen,20,0,Kanal); //= GeinAnGen(15,15,1)- GeinAnGen(15,15,0,20,0,1);
		   if (Gein<8||Gein>12)
		   {
				ChKon = true;

		   }
				Gein = GeinAnGen(FrGen,0,0,Kanal);

		   if (Gein<40)
		   {
				ShowMessage("��������� ������");
				ChKon = true;
		   }
       	VstendeBL3DG1->SendDATA_SPI_USB(VstendeBL3DG1->ModulPX2->LoadATT_K1(i),0);
	   return ChKon ;
}
void StendRPU16::Pribor5071_MarkLoad()
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
void StendRPU16::Pribor5071_LimitLoad()
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
void StendRPU16::Pribor5071_IzmLoad()
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
				 for (i = 0; i < 7; i++)    // for (i = 0; i < 7; i++)                  /* TODO -cTrase : ���������� � ������ ���-��  ����� */
					 {
				  strcpy(buffer,Vstende5071->IzmerenSet(j,i));
				  strcat(buffer,"\n");
				  viPrintf(vi, buffer);
				 }
			 }
	   status = viClose(vi);
	   status = viClose(defaultRM);
}
float StendRPU16::RazborStr (int poz, char* str)
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
float StendRPU16::MarkerZapros(int NumTRASE,int NumMARK)
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
float StendRPU16::CHenalPOW(double BW,double Centr,int Kanal){
KOM34980->KanalSet16(Kanal);
//VstendeBlRPU16->SetAttNOISE(0);
An8560->AnSpanSet(Centr,BW,3000,10);
Sleep(5000);
Sleep(5000);
return	0.1*floor(0.5+10*strtod(An8560->CHPWRBW(BW),NULL));;
}
void StendRPU16::DataRet(double *Data, double *Freq, int point)
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
double StendRPU16::IP1(double Lstart, double Lmax,double Fin, double Fout, int Kanal)
{VstendeBL3DG1->FriqSET(Fin,false,0,0,Kanal);
	if (jgut) {

			 switch (get)
	   {
			 case 0:

			 AE4426->GenSet(VstendeBL3DG1->Geterodin1(),5,true);
			 Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
			 SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),5,true);
			 SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
			 break;
	   } //	KOM34980->KanalSet(Kanal);
  } 	AgE44XX->GenSet(Fin,Lstart,true);
		 switch (analiz)
		   {
			 case 0:
			 An8560->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lmax);
			 Sleep(300);
			 An8560->MkrPeak();
			 An8560->MkDelta(true,0);
			 break;
			 case 1:
			 An9030->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lmax);
			 //An9030->SetMarker(0,0,0,0);
			 Sleep(800);
			 An9030->MkrPeak(1);
			 An9030->MkDelta(1,true,0);

			 break;
			  case 2:
			 RS_FSUP50->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lmax);
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
double StendRPU16::Sens(double Lin,double Lan, double Fin, int Kanal)
{
 VstendeBL3DG1->FriqSET(Fin,false ,10,10,Kanal);
 AgE44XX->GenSet(Fin,Lin,true);
 VstendeBL3DG1->FriqSET(Fin,False ,0,0,Kanal);      /* TODO -c���������������� : ������ LNA */
				if (jgut)
  {

			 switch (get)
	   {
		 case 0:

		 AE4426->GenSet(VstendeBL3DG1->Geterodin1(),5,true);
		 Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
		 break;

		 case 1:
		 SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),5,true);
		 SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
		 break;
	   } //	KOM34980->KanalSet(Kanal);
  }
		 switch (analiz)
	   {
		 case 0:
		 An8560->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
		 Sleep(300);
		 An8560->MkrPeak();
		 An8560->MkDelta(true,0);
		 break;
		 case 1:
		 Meas = An9030->Sens(Lan,VstendeBL3DG1->FriqOUT(),Span,RBW,30);
		 break;
		 case 2:
		 RS_FSUP50->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
		 break;
	   }






   return  Meas+Lin+10;


}
double StendRPU16::SensATT(double Lin,double Lan, double Fin, int Kanal){

 AgE44XX->GenSet(Fin,Lin,true);
 VstendeBL3DG1->FriqSET(Fin,false ,0,0,Kanal);
	if (jgut) {

			 switch (get)
	   {
			 case 0:

			 AE4426->GenSet(VstendeBL3DG1->Geterodin1(),5,true);
			 Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
			 SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),5,true);
			 SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
			 break;
	   } //	KOM34980->KanalSet(Kanal);
  }
		 switch (analiz)
		  {
			 case 0:
			 An8560->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
			 Sleep(300);
			 An8560->MkrPeak();
			 An8560->MkDelta(false,0);
			 Meas = 0.1*floor(10*strtod(An8560->Result(),NULL));
			 break;
			 case 1:
			 An9030->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
			 An9030->SetMarker(0,0,0,0);
			 An9030->MkDelta(1,false,0);                             /* TODO 1 -c����������  : �������� ����� ���������� � ������ ��� */
			 Sleep(300);
			 An9030->MkrPeak(1);
			 Meas = 0.1*floor(10*strtod(An9030->Result(1),NULL));


			 break;
			  case 2:
			 RS_FSUP50->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
			 break;
		  }
		Sleep(500);
		VstendeBL3DG1->FriqSET(Fin,false ,50,50,Kanal);

        	 switch (analiz)
			 {
					 case 0:
					 An8560->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
					 An8560->MkDelta(false,0);
					 Sleep(300);
					 An8560->MkrPeak();

					 return	 Meas - 0.1*floor(10*strtod(An8560->Result(),NULL));
					 break;
					 case 1:
					 An9030->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
					 An9030->MkDelta(1,false,0);
					 Sleep(500);
					 An9030->MkrPeak(1);
					 return Meas - 0.1*floor(10*strtod(An9030->Result(1),NULL));


					 break;
					 case 2:
					 return Meas - RS_FSUP50->AnSpanSet(VstendeBL3DG1->FriqOUT(),0.1,3000,Lan);
					 break;
			 }


}
void StendRPU16::GetSet()
{   switch (get)
		{
			 case 0:

			 AE4426->GenSet(VstendeBL3DG1->Geterodin1(),0,true);
			 Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
			 SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),0,true);
			 SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
			 break;
		}

}
double StendRPU16::GeinAnGen(double FrGen,int ATT,int ATT1, int Kanal)
{
		VstendeBL3DG1->FriqSET(FrGen,false,ATT,ATT1,Kanal);
		AgE44XX->GenSet(FrGen,PowGen,1);
			if (jgut)
	{

			 switch (get)
		{
			 case 0:

			 AE4426->GenSet(VstendeBL3DG1->Geterodin1(),5,true);
			 Ag4425->GenSet(VstendeBL3DG1->Geterodin2(),0,true);
			 break;

			 case 1:
			 SMU200->GenSetA(VstendeBL3DG1->Geterodin1(),5,true);
			 SMU200->GenSetB(VstendeBL3DG1->Geterodin2(),0,true);
			 break;
		}

	}

		switch (analiz)
		{
			 case 0:
			 An8560->AnSpanSet(VstendeBL3DG1->FriqOUT(),Span,RBW,RefL10M);  // 	An8560->AnSpanSet(FrAn,Span,RBW,RefL);
			 break;

			 case 1:
			 An9030->AnSpanSet(VstendeBL3DG1->FriqOUT(),Span,RBW,RefL10M);
			 break;

			 case 2:
			 RS_FSUP50->AnSpanSet(VstendeBL3DG1->FriqOUT(),Span,RBW,RefL10M);
			 break;

		}
   //	VstendeBL3DG1->FriqSET(FrGen,false,ATT,ATT1,Kanal);

	
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
void  StendRPU16::SetAnaliz(double F)
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
double StendRPU16::PowAn(double FrAn, int Kanal)
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
double StendRPU16::PowAn10(double FrAn, int Kanal)
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
void StendRPU16::Stend_LimitLoad(double Pow, double Ref, double Ref10M,double Sp ,double RB ){
	  PowGen = Pow;
	  Span = Sp;
	  RefL= Ref;
	  RBW = RB;
	  RefL10M = Ref10M;

}
double StendRPU16::Friq(void){
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
void StendRPU16::Stend_LimitRet(double &Pow, double &Ref, double &Ref10M,double &Sp ,double &RB ){

	  Pow = PowGen;
	  Sp  = Span;
	  Ref = RefL;
	  RB  = RBW;
	  Ref10M = RefL10M;

}
void StendRPU16::Stend_PrAdress(int An, int Gen,int ANLAN, AnsiString AdrAN,
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
				 ShowMessage("���������� ���������� Agilent 8560SA");
				switch (ANLAN)
				{
					case 0:An8560->GPIB_Set(AdrAN, Ip);  break;
					case 1:An8560->GPIB_Set(AdrAN, Ip);  break;
				}
				 break;

				 case 1:
				 ShowMessage("���������� ���������� Agilent N9030A");
				switch (ANLAN)
				{
					case 0:	An9030->IP_Set(AdrAN.c_str()); break;
					case 1:	An9030->GPIB_Set(AdrAN, Ip);   break;
				}
				 break;

				 case 2:
				 ShowMessage("���������� ���������� R&S FSU ");
				 RS_FSUP50->GPIB_Set(AdrAN, Ip);
				 break;
			}
			 get = Gen;
	   switch (get)
			{
				 case 0:
				 ShowMessage("���������1 Agilent E4426B 4 ���");
				 ShowMessage("���������2 Agilent E4425B 3 ���");
				 Ag4425->GPIB_Set(AdrGEN1, Ip);
				 AE4426->GPIB_Set(AdrGEN2, Ip);
				 break;

				 case 1:
				 ShowMessage("���������1 SMU200 A 6 ���");
				 ShowMessage("���������2 SMU200 B 3 ���");
				 SMU200->GPIB_Set(AdrGEN1, Ip);

				 break;

			}


	 AgE44XX->GPIB_Set(AdrGEN, Ip);
	 KOM34980->GPIB_Set(AdrSW,Ip);
	 Vstende5071->GPIB_Set(AdrPan,Ip); /* TODO -cIp ADR: 114752 ��������� ������� �������� Stend  */
					switch (BPLAN)
		{
			case 0:	MP_N6702A->IP_Set(AdrBP.c_str()); break;
			case 1:	MP_N6702A->GPIB_Set(AdrBP, Ip);   break;
		}

	 //SMU200->
  }
#pragma package(smart_init)
