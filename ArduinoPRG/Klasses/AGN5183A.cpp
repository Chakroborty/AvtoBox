
#include "AGN5183A.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#pragma hdrstop

#include <math.h>

#include "visa.h"
#pragma comment(lib,"visa32.lib")

N5183A::N5183A(int Adr, char* Ip, int LAN) {
	Control(Adr, 30, Gadr);

	itoa(Gadr, GPIB, 10);
	//ipAdres = "0";
	strcpy(ipAdres, Ip);
	strcpy(ipLok, "10.1.2.118");
	Fmin = 0.25;
	Fmax = 43500;
	Lan_GPIB = LAN;


}

N5183A::~N5183A() {

}

char* N5183A::PriborLoad() {

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

void N5183A::GPIB_Set(AnsiString Adr, AnsiString Ip) {   /* TODO -cIP ADR : добавить в метод IP */

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
void N5183A::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
AnsiString  N5183A::Zapt(AnsiString str)
{
    AnsiString string;
	string = StringReplace(str,",",".",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);


	   return  string;
}


long N5183A::GenSet(double Fset, double Pow, bool OutOn) {

	AnsiString string;
	ControlF(Fset, Freq);
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("јдрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
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

	strcpy(buffer, ":POWER ");                //:POWER 4 DBM	#”становка уровн€
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


char* N5183A::GetGPIB() {

return GPIB;

}
char* N5183A::GetIPlok()
{
	return ipLok;
}
void N5183A::ControlF(double F, double& Com)
 {
	  if (F >= Fmin && F <= Fmax)
	{
		if (F != 0) {
			Com = F;
	}
	}
	else {  ShowMessage("ƒиапазон генератора N5183A 0,1-43500 ћ√ц");
			Com = 3000;
	}
 }


void N5183A::Control(int K, int Pred, int& Com) {

if (K >= 0 && K <= Pred) {
if (K != 0) {
	Com = K;
}
}
else {
Com = 1;
}
}



