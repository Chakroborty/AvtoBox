#pragma hdrstop
#include "RSFSU50.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#include "visa.h"

#include <math.h>



#pragma comment(lib,"visa32.lib")

FSU50::FSU50(int Adr, char* Ip) {
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
	Fmax = 26500;
	Lan_GPIB = 0;


}

FSU50::~FSU50() {
}

char* FSU50::PriborLoad()
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
				strcat(sttr, "::gpib0,");
				strcat(sttr, GPIB);
				strcat(sttr, "::INSTR");
			 break;


		   default:break;
		   }

	return sttr;
}
void FSU50::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}

void FSU50::GPIB_Set(AnsiString Adr, AnsiString Ip) {      /* TODO -cIP ADR : добавить в метод IP */
	int Gadr = StrToInt(Adr);

	if (Gadr >= 0 && Gadr <= 30) {
		itoa(Gadr, GPIB, 10);
	}
	else {
		GPIB = "20";
	}
	strcpy(ipAdres, Ip.c_str());
}
AnsiString  FSU50::Zapt(AnsiString str)
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
long FSU50::AnSpanSet(double Fset, double SP, double BW, double RWFL) {
	AnsiString string;

 if (Fset>Fmax) {
		CentrF = 26500;
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
	strcat(buffer, " MHZ\n");
	viPrintf(vi, buffer);
	strcat(buffer, "FREQ:SPAN "); // SP 100KHZ; Установка спан
	string = Zapt(FloatToStr(Span));
	strcat(buffer, string.c_str());
	strcat(buffer, " MHZ\n");
	 viPrintf(vi, buffer);
	strcat(buffer, "BAND "); // RB 100HZ; Установка BW
	string = FloatToStr(RBW);
	strcat(buffer, string.c_str());
	strcat(buffer, "HZ\n");
	viPrintf(vi, buffer);
	strcat(buffer, "DISP:WIND:TRAC:Y:RLEV "); // RL-10DBM; Установка BW
	string = FloatToStr(RL);
	strcat(buffer, string.c_str());
	strcat(buffer, "DBM\n");
	status = viPrintf(vi, buffer);

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}



char* FSU50::GetGPIB() {
	return GPIB;
}
char* FSU50::GetIPlok()
{
	return ipLok;
}

int FSU50::Control(int K, int Pred, int& Com) {
	if (K >= 0 && K <= Pred) {
		if (K != 0) {
			Com = K;
		}
	}
	else {
		Com = 0;
	}
}

long FSU50::MkrPeak(int n) {
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
	strcat(buffer, ":MAX\n");

	status = viPrintf(vi, buffer);
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}

long FSU50::MkDelta(double Del) {
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
	if (DELTA) {                                                       /* TODO : Mark delta */
		strcpy(buffer, "MKD "); // MKD 30KHZ;
		string = FloatToStr(DELTA);
		strcat(buffer, string.c_str());
		strcat(buffer, "KHZ;");
		strcat(buffer, "\n");
	}
	else {
		strcpy(buffer, "MKN;"); // MKD 30KHZ;
		strcat(buffer, "\n");
	}
	status = viPrintf(vi, buffer);
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}

long FSU50::SetMarker(bool Del, int Delta, bool Pik, int Count) {
	AnsiString string;



	Control(Count, 200, Coun);
	strcpy(buffer, "VAVG "); // VAVG 100; VAVG OFF;  	#Накопление
	if (Coun) {
		string = FloatToStr(Coun);
		strcat(buffer, string.c_str());            /* TODO -cAG8560 : Маркер анализатора */
		strcat(buffer, ";");
	}
	else {
		strcat(buffer, "OFF;");
	}
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);
	return status;
}
double FSU50::FMark(){

 return Fmark;
}
char* FSU50::Result(int n) {
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
char* FSU50::CHPWRBW(double Chnl){
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
void FSU50::DataRet(double *Data, double *Freq, int point)
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
