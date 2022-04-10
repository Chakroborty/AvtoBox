#pragma hdrstop
#include "Agilent8560.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#include "visa.h"

#include <math.h>



#pragma comment(lib,"visa32.lib")

Analiz8560::Analiz8560(int Adr, char* Ip) {
	Control(Adr, 30, Gadr);
	GPIB = "20";
	itoa(Gadr, GPIB, 10);
	strcpy(ipAdres, Ip);
	CentrF = 140;
	RL = 20;
	Span = 100;
	RBW = 3000;
	Fmin = 0.25;
	Fmax = 2900;
	Lan_GPIB = 1;
}

Analiz8560::~Analiz8560() {
}

char* Analiz8560::PriborLoad() {
	char str[100];
	strcpy(str, "TCPIP0::");

	strcat(str, ipAdres);
	strcat(str, "::gpib0,");
	strcat(str, GPIB);
	strcat(str, "::INSTR");
	return str;



}

void Analiz8560::GPIB_Set(AnsiString Adr, AnsiString Ip) {      /* TODO -cIP ADR : добавить в метод IP */
	int Gadr = StrToInt(Adr);

	if (Gadr >= 0 && Gadr <= 30) {
		itoa(Gadr, GPIB, 10);
	}
	else {
		GPIB = "20";
	}
	strcpy(ipAdres, Ip.c_str());
}
int Analiz8560::Pinitial()
{
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return 0;
		}

	 //*RST;*CLS;:INIT:CONT 1;:RADIO:STANDARD IS95
	viPrintf(vi,"*RST;*CLS;:INIT:CONT 1;:RADIO:STANDARD IS95\n");
	viClose(vi);                    // closes session
	viClose(defaultRM);
}
AnsiString  Analiz8560::Zapt(AnsiString str)
	{ AnsiString string;
	string = StringReplace(str,",",".",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);

	/*
	   int i = str.Pos(",");

		  if (i!=0) {
		   str =   str.SubString(1,i-1)+"."+ str.SubString(i+1,8);
		 }
  */
	   return  string;
	}

long Analiz8560::AnSpanSet(double Fset, double SP, double BW, double RWFL) {
	AnsiString string;

 if (Fset>Fmax) {
		CentrF = 2900;
 }
 else {if (Fset<Fmin)
		{
			CentrF = 0.3;
		} else {
		CentrF = Fset;
				}
 }
  if (SP>0&&SP<2899.75) { Span = SP;}

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
	strcpy(buffer, "CF "); // CF 70MHZ;SP 100KHZ;RB 100HZ;RL-10DBM
	string = Zapt(FloatToStr(CentrF));
	strcat(buffer, string.c_str());
	strcat(buffer, " MHZ;");
	//strcat(buffer, ")\n");
	// viPrintf(vi, buffer);
	strcat(buffer, "SP "); // SP 100KHZ; Установка спан
	string = Zapt(FloatToStr(Span));
	strcat(buffer, string.c_str());
	strcat(buffer, "MHZ;");
	//strcat(buffer, ")\n");
	// viPrintf(vi, buffer);
	strcat(buffer, "RB "); // RB 100HZ; Установка BW
	string = FloatToStr(RBW);
	strcat(buffer, string.c_str());
	strcat(buffer, "HZ;");
	//strcat(buffer, ")\n");
	strcat(buffer, "RL "); // RL-10DBM; Установка BW
	string = FloatToStr(RL);
	strcat(buffer, string.c_str());
	strcat(buffer, "DBM;");
	strcat(buffer, "\n");

	status = viPrintf(vi, buffer);

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}



char* Analiz8560::GetGPIB() {
	return GPIB;
}


void Analiz8560::Control(int K, int Pred, int& Com) {
	if (K >= 0 && K <= Pred) {
		if (K != 0) {
			Com = K;
		}
	}
	else {
		Com = 0;
	}
}

long Analiz8560::MkrPeak() {
	AnsiString string;
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	strcpy(buffer, "MKPK HI;");
	
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}

long Analiz8560::MkDelta(bool Enabl,double Del) {
	AnsiString string;
	//Control(Del, 10000, DELTA);
    status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	if (Enabl) {
		strcpy(buffer, "MKD "); // MKD 30KHZ;
		string = FloatToStr(Del);
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

long Analiz8560::SetMarker(bool Del, int Delta, bool Pik, int Count) {
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
double Analiz8560::FMark(){

 return Fmark;
}
long Analiz8560::AVG(int D)
{       AnsiString string;
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS)
	{
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}

		strcpy(buffer, "VAVG ");
		if (D!=0)
	{
		string = IntToStr(D);
		strcat(buffer, string.c_str());
		strcat(buffer, ";");

	}
	else
	{
		strcat(buffer, "OFF;"); // MKD 30KHZ;

	}
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);

		viClose(vi);                    // closes session
	 	viClose(defaultRM);             // closes default session


		return status;

}

char* Analiz8560::Result() {
		 AnsiString string;
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return "-110";
		}

		strcpy(buffer, "MKF?;");
		strcat(buffer, "\n");
		int bufLength = sizeof(rezult); //
	   status =	viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		Fmark = strtod(rezult,NULL);

			//buffer = {0};
		strcpy(buffer, "MKA?;");
		strcat(buffer, "\n");
		 bufLength = sizeof(rezult); //
	   status =	viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		Rmark = strtod(rezult,NULL);

	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session


		return rezult;
}
char* Analiz8560::CHPWRBW(double Chnl){
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

