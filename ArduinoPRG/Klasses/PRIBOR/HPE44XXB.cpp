
#include "HPE44XXB.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#pragma hdrstop

#include <math.h>

#include "visa.h"
#pragma comment(lib,"visa32.lib")

HPE4426B::HPE4426B(int Adr, char* Ip, int LAN) {
	Control(Adr, 30, Gadr);

	itoa(Gadr, GPIB, 10);
	//ipAdres = "0";
	strcpy(ipAdres, Ip);
	strcpy(ipLok, "10.29.31.24");
	Fmin = 0.25;
	Fmax = 6000;
	Lan_GPIB = LAN;


}

HPE4426B::~HPE4426B() {

}

char* HPE4426B::PriborLoad() {

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

void HPE4426B::GPIB_Set(AnsiString Adr, AnsiString Ip) {   /* TODO -cIP ADR : добавить в метод IP */

	int Gadr = StrToInt(Adr);
    Lan_GPIB = 1;
	if (Gadr >= 0 && Gadr <= 30) {
		itoa(Gadr, GPIB, 10);
	}
	else {
		strcpy(GPIB,"19" );
	}
	strcpy(ipAdres, Ip.c_str());



}
void HPE4426B::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
AnsiString  HPE4426B::Zapt(AnsiString str)
{
    AnsiString string;
	string = StringReplace(str,",",".",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);


	   return  string;
}


long HPE4426B::GenSet(double Fset, double Pow, bool OutOn) {

	AnsiString string;
	ControlF(Fset, Freq);
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	strcpy(buffer, ":FREQ ");
	string  = FloatToStr(Freq);
	string  = Zapt(string);
	strcat(buffer,string.c_str());
	strcat(buffer, " MHZ");
	strcat(buffer, "\n");
	viPrintf(vi, buffer);

	strcpy(buffer, ":POWER ");                //:POWER 4 DBM	#Установка уровня
	string  = FloatToStr(Pow);
	strcat(buffer,string.c_str());
	strcat(buffer, " DBM");
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
		  if (OutOn) {
		 PowStat =true;
	 } else {
	  PowStat = false;
	 }
	strcpy(buffer, ":POW:STAT ");				//:POWer:STATe ON
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
long HPE4426B::GenOUTONOFF( bool OutOn){
    AnsiString string;
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}



	  if (OutOn) {
	 PowStat =true;
	} else {
	PowStat = false;
	}
	strcpy(buffer, ":POW:STAT ");				//:POWer:STATe ON
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

char* HPE4426B::GetGPIB() {

return GPIB;

}
char* HPE4426B::GetIPlok()
{
	return ipLok;
}
void HPE4426B::ControlF(double F, double& Com)
 {
	  if (F >= Fmin && F <= Fmax)
	{
	if (F != 0) {
		Com = F;
	}
	}
	else {
	Com = 3000;
	}
 }


void HPE4426B::Control(int K, int Pred, int& Com) {

if (K >= 0 && K <= Pred) {
if (K != 0) {
	Com = K;
}
}
else {
Com = 1;
}
}



