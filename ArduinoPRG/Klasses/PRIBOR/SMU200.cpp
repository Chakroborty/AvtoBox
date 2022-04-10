//---------------------------------------------------------------------------

#pragma hdrstop
#include "SMU200.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#pragma hdrstop

#include <math.h>

#include "visa.h"
#pragma comment(lib,"visa32.lib")
//---------------------------------------------------------------------------
SMU200GEN::SMU200GEN(int Adr, char* Ip) {
		Control(Adr, 30, Gadr);
		strcpy(GPIB,"28");
		itoa(Gadr, GPIB, 10);
		strcpy(ipLok, "10.29.31.28");
		//ipAdres = "0";
		strcpy(ipAdres, Ip);

		AFmin = 0.1;
		AFmax = 6000;

		BFmin = 0.1;
		BFmax = 3000;

}

SMU200GEN::~SMU200GEN() {

}

char* SMU200GEN::PriborLoad() {

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

void SMU200GEN::GPIB_Set(AnsiString Adr, AnsiString Ip) {   /* TODO -cIP ADR : добавить в метод IP */

	int Gadr = StrToInt(Adr);

	if (Gadr >= 0 && Gadr <= 30) {
		itoa(Gadr, GPIB, 10);
	}
	else {
		strcpy(GPIB,"19");
	}
	strcpy(ipAdres, Ip.c_str());
}

void SMU200GEN::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
char* SMU200GEN::GetGPIB()
{
	return GPIB;
}
char* SMU200GEN::GetIPlok()
{
	return ipLok;
}

AnsiString  SMU200GEN::Zapt(AnsiString str)
{
    AnsiString string;
	string = StringReplace(str,",",".",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);
	   return  string;
}


long SMU200GEN::GenSetA(double Fset, double Pow, bool OutOn) {

	AnsiString string;
	ControlFA(Fset, AFreq);
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	strcpy(buffer, "SOUR1:FREQ ");
	string  = FloatToStr(AFreq);
	string  = Zapt(string);
	strcat(buffer,string.c_str());
	strcat(buffer, " MHZ");
	strcat(buffer, "\n");
	viPrintf(vi, buffer);

	strcpy(buffer, "SOUR1:POW:LEV:IMM:AMPL ");                //:POWER 4 DBM	#Установка уровня
	string  = FloatToStr(Pow);
	strcat(buffer,string.c_str());
	strcat(buffer, " dbm");
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
		  if (OutOn) {
		 PowStat =true;
	 } else {
      PowStat = false;
	 }
	strcpy(buffer, "OUTP1:STAT ");				//:POWer:STATe ON
	if (PowStat) {
		string  = "ON";
	} else {
		string  = "OFF";
	}
	strcat(buffer,string.c_str());
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);

	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session

	 return status;
}
long SMU200GEN::GenSetB(double Fset, double Pow, bool OutOn) {

	AnsiString string;
	ControlFA(Fset, BFreq);
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
strcpy(buffer, "SOUR2:FREQ ");
	string  = FloatToStr(BFreq);
	string  = Zapt(string);
	strcat(buffer,string.c_str());
	strcat(buffer, " MHZ");
	strcat(buffer, "\n");
	viPrintf(vi, buffer);

	strcpy(buffer, "SOUR2:POW:LEV:IMM:AMPL ");                //:POWER 4 DBM	#Установка уровня
	string  = FloatToStr(Pow);
	strcat(buffer,string.c_str());
	strcat(buffer, " dbm");
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
		  if (OutOn) {
		 PowStat =true;
	 } else {
      PowStat = false;
	 }
	strcpy(buffer, "OUTP2:STAT ");				//:POWer:STATe ON
	if (PowStat) {
		string  = "ON";
	} else {
		string  = "OFF";
	}
	strcat(buffer,string.c_str());
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);

	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session

	 return status;
}


void SMU200GEN::ControlFA(double F, double& Com)
 {
  if (F >= AFmin && F <= AFmax) {
if (F != 0) {
	Com = F;
}
}
else {
 ShowMessage("Диапазон выхода А 0,1-6000 ГГц");
Com = 3000;
}
 }
void SMU200GEN::ControlFB(double F, double& Com)
 {
  if (F >= BFmin && F <= BFmax) {
if (F != 0) {
	Com = F;
}
}
else {ShowMessage("Диапазон выхода А 0,1-3000 ГГц");
Com = 3000;
}
 }

void SMU200GEN::Control(int K, int Pred, int& Com) {

if (K >= 0 && K <= Pred) {
if (K != 0) {
	Com = K;
}
}
else {
Com = 1;
}
}

#pragma package(smart_init)
