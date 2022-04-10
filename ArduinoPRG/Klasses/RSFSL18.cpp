#pragma hdrstop
#include "RSFSL18.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#include "visa.h"

#include <math.h>



#pragma comment(lib,"visa32.lib")

FSL18::FSL18(int Adr, char* Ip, int LAN) {
	Control(Adr, 30, Gadr);
	GPIB = "21";
	itoa(Gadr, GPIB, 10);
	strcpy(ipAdres, Ip);
	strcpy(ipLok, "10.29.31.12");
	CentrF = 140;
	RL = 20;
	Span = 100;
	RBW = 3000;
	Fmin = 0.000003;
	Fmax = 18000;
	Lan_GPIB = LAN;


}

FSL18::~FSL18() {
}

char* FSL18::PriborLoad()
{
		 char sttr[100]; //
		   switch (Lan_GPIB)
		   {
			 case 0:
				strcpy(sttr,"TCPIP0::");
				strcat(sttr, ipLok);
				strcat(sttr, "::inst0::INSTR");

			 break;
			 case 1:
				strcpy(sttr,"TCPIP0::");
				strcat(sttr, ipAdres);
				strcat(sttr, "::GPIB0:");
				strcat(sttr, GPIB);
				strcat(sttr, "::INSTR");
			 break;


		   default:break;
		   }

	return sttr;
}
void FSL18::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}

void FSL18::GPIB_Set(AnsiString Adr, AnsiString Ip) {      /* TODO -cIP ADR : добавить в метод IP */
	int Gadr = StrToInt(Adr);
	 Lan_GPIB = 1;
	if (Gadr >= 0 && Gadr <= 30) {
		itoa(Gadr, GPIB, 10);
	}
	else {
		GPIB = "20";
	}
	strcpy(ipAdres, Ip.c_str());
}
AnsiString  FSL18::Zapt(AnsiString str)
{   AnsiString string;
	string = StringReplace(str,",",".",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);

	/*
	   int i = str.Pos(",");

		  if (i!=0) {
		   str =   str.SubString(1,i-1)+"."+ str.SubString(i+1,8);
		 }
  */
	   return  string;
}
long FSL18::AnSpanSet(double Fset, double SP, double BW, double RWFL) {
	AnsiString string;

 if (Fset>Fmax) {
		CentrF = 18000;
 }
 else {if (Fset<Fmin)
		{
			CentrF = 0.000003;
		} else {
		CentrF = Fset;
				}
 }
  if (SP>0&&SP<26499.75) { Span = SP;}

  if (CentrF-Span/2<Fmin) {
		 Span = 2*(CentrF-Fmin);
	 } else {
		if (CentrF+Span/2>Fmax) {
		 Span = 2*(Fmax-CentrF);
		}
	 }
	RL = RWFL;
	RBW = BW;



	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	strcpy(buffer, "FREQ:CENT "); // CF 70MHZ;SP 100KHZ;RB 100HZ;RL-10DBM
	string = Zapt(FloatToStr(CentrF));
	strcat(buffer, string.c_str());
	strcat(buffer, " MHZ\n");    // нужен ли пробел ?
	viPrintf(vi, buffer);
	strcpy(buffer, "FREQ:SPAN "); // SP 100KHZ; Установка спан
	string = Zapt(FloatToStr(Span));
	strcat(buffer, string.c_str());
	strcat(buffer, " MHZ\n");
	 viPrintf(vi, buffer);
	strcpy(buffer, "BAND "); // RB 100HZ; Установка BW
	string = FloatToStr(RBW);
	strcat(buffer, string.c_str());
	strcat(buffer, "HZ\n");
	viPrintf(vi, buffer);
	strcpy(buffer, "DISP:WIND:TRAC:Y:RLEV "); // RL-10DBM; Установка BW
	string = FloatToStr(RL);
	strcat(buffer, string.c_str());
	strcat(buffer, "DBM\n");
	status = viPrintf(vi, buffer);

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}



char* FSL18::GetGPIB() {
	return GPIB;
}
char* FSL18::GetIPlok()
{
	return ipLok;
}

int FSL18::Control(int K, int Pred, int& Com) {
	if (K >= 0 && K <= Pred) {
		//if (K != 0) {
			Com = K;
		//}
	}
	else {
		Com = 0;
	}
}

long FSL18::MkrPeak(int n) {
	AnsiString string;
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}

	strcpy(buffer, "CALC:MARK");
	string = IntToStr(n);
	strcat(buffer, string.c_str());
	strcat(buffer, " ON\n");

	status = viPrintf(vi, buffer);
	strcpy(buffer, "CALC:DELT");
	string = IntToStr(n);
	strcat(buffer, string.c_str());
	strcat(buffer, " OFF\n");

	status = viPrintf(vi, buffer); //CALC:DELT1 OFF

	strcpy(buffer, "CALC:MARK");
//	string = IntToStr(n);
//	strcat(buffer, string.c_str());
	strcat(buffer, ":MAX\n");

	status = viPrintf(vi, buffer);
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}

long FSL18::MkDelta(double Del) {
	AnsiString string;
	Control(Del, 10000, DELTA);
    	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	if (DELTA) { 
		strcpy(buffer, "CALC:DELT1 ON"); // MKD 30KHZ;
		strcat(buffer, "\n");  
		status = viPrintf(vi, buffer);                                                    /* TODO : Mark delta */
		strcpy(buffer, "CALC:DELT:X "); // MKD 30KHZ;
		string = FloatToStr(DELTA);
		strcat(buffer, string.c_str());
		strcat(buffer, "KHZ");
		strcat(buffer, "\n");
		status = viPrintf(vi, buffer);
	}
	else {
		strcpy(buffer, "CALC:DELT1 OFF"); // MKD 30KHZ;
		strcat(buffer, "\n");
		status = viPrintf(vi, buffer);
	}
	
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}
double FSL18::Sens(double Lin,double Fin, double SP, double BW,double Ofs){
	AnSpanSet(Fin,SP,BW, Lin);
	Sleep(300);
	//MkDelta(0);
	MkrPeak(1);
	MkDelta(Ofs);
	SetMarker(true, 0, false, 100);
	Sleep(3000);
	Rez =  0.1*floor(10*strtod(DResult(),NULL));
	SetMarker(true, 0, false, 0);
	return  Rez;
}
long FSL18::SetMarker(bool Del, int Delta, bool Pik, int Count) {
	AnsiString string;
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	Control(Count, 200, Coun);

	if (Coun) {
		strcpy(buffer, "AVER:COUN "); //   	#Накопление
		string = FloatToStr(Coun);
		strcat(buffer, string.c_str());     /* TODO -cAG8560 : Маркер анализатора */
		strcat(buffer, "\n");
		status = viPrintf(vi, buffer);
		strcpy(buffer, "AVER ON");
		strcat(buffer, "\n");
		status = viPrintf(vi, buffer);
	}
	else {	
		strcpy(buffer, "AVER OFF"); //   	#Накопление
		strcat(buffer, "\n");
		status = viPrintf(vi, buffer);
	}
	
	
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}
double FSL18::FMark(){

 return Fmark;
}
char* FSL18::Result(int n) {
		 AnsiString string;
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return "-110";
		}
		strcpy(buffer, "CALC:MARK");
		string = IntToStr(n);
		strcat(buffer, string.c_str());
		strcat(buffer, ":X?\n");

		int bufLength = sizeof(rezult); //
		status =	viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		Fmark = strtod(rezult,NULL);

			//buffer = {0};
		strcpy(buffer, "CALC:MARK");
		string = IntToStr(n);
		strcat(buffer, string.c_str());
		strcat(buffer, ":Y?\n");
		bufLength = sizeof(rezult); //
		status =	viQueryf(vi, buffer, "%#t", &bufLength, rezult);


	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session


		return rezult;
}
char* FSL18::DResult() {
		AnsiString string;
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return "-110";
		}
		strcpy(buffer, "CALC:DELT:Y?\n");
//		string = IntToStr(n);
//		strcat(buffer, string.c_str());
//		strcat(buffer, ":X?\n");

		int bufLength = sizeof(rezult); //
		status = viQueryf(vi, buffer, "%#t", &bufLength, rezult);
//		Fmark = strtod(rezult,NULL);
//
//			//buffer = {0};
//		strcpy(buffer, "CALC:MARK");
//		string = IntToStr(n);
//		strcat(buffer, string.c_str());
//		strcat(buffer, ":Y?\n");
//		bufLength = sizeof(rezult); //
//		status =	viQueryf(vi, buffer, "%#t", &bufLength, rezult);


	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session


		return rezult;
}
char* FSL18::CHPWRBW(double Chnl){
		AnsiString string;
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return 0;
		}
		strcpy(buffer, "CHANPWR TRA,");   //CHANPWR TRA,29MHZ,?;
		Control(Chnl, 10000, DELTA);
		string = FloatToStr(DELTA);
		strcat(buffer,string.c_str());
		strcat(buffer, "MHZ,?;");
		strcat(buffer, "\n\n");
		int bufLength = sizeof(rezult); // viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		viClose(vi);                    // closes session
		viClose(defaultRM);             // closes default session
		return rezult;
}
void FSL18::DataRet(double *Data, double *Freq, int point)
{   status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
		 strcpy(buffer,PriborLoad());
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
