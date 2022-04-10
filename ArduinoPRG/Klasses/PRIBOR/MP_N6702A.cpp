
#include "MP_N6702A.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#pragma hdrstop

#include <math.h>

#include "visa.h"
#pragma comment(lib,"visa32.lib")

N6702A::N6702A(int Adr, char* Ip,int Mode)
{   /* , ADAPTgpib * Adapter */

		Lan_GPIB = Mode;
		USB = false;
		Control(Adr, 30, Gadr);
		itoa(Gadr, GPIB, 10);
		strcpy(ipAdres, Ip);
		strcpy(ipLok, "10.29.31.162");
		retCnt = 0;
		Vmin = 0.25;
		Vmax = 12.7;
		//SET_METER(4);
		V1=V2=V3=V4=Stat1 = Stat2 = Stat3 = Stat4 = 0;

}

N6702A::~N6702A() {

}


char* N6702A::PriborLoad() {



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
long N6702A::Comand(AnsiString Com,char *Rez)
{
        status = viOpenDefaultRM(&defaultRM);
        strcpy(buffer, PriborLoad());
        status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
        if (status < VI_SUCCESS)
        {
            ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
            (AnsiString)GPIB + " невозможно открыть."); //
            return status;
        }

				strcpy(buffer,Com.c_str());
        strcat(buffer,"\n");
        viPrintf(vi, buffer);
        viRead(vi, buffer, sizeof(buffer), &retCnt);

        strcpy(Rez,buffer);


        return  status ;


}
void N6702A::GPIBLAN_Set(bool LG){

	Lan_GPIB = LG;

}
void N6702A::GPIB_Set(AnsiString Adr, AnsiString Ip) {   /* TODO -cIP ADR : добавить в метод IP */

	int Gadr = StrToInt(Adr);

	if (Gadr >= 0 && Gadr <= 30) 	{ itoa(Gadr, GPIB, 10); }
	else 							{ strcpy(GPIB,"19" ); }

		
	strcpy(ipAdres, Ip.c_str());



}
void N6702A::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
char* N6702A::GetIPlok()
{
	return ipLok;
}
AnsiString  N6702A::Zapt(AnsiString str)
{
    AnsiString string;
	string = StringReplace(str,",",".",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);


	   return  string;
}
long N6702A::OPENOUT(bool Swich,bool Normal,int Kanal){
			AnsiString string;
		if (!USB){ 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS) {
						ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
							(AnsiString)GPIB + " невозможно открыть."); //
						return status;
					}


			}
			strcpy(buffer, "OUTP ");				//:POWer:STATe ON



			if (Normal)

	{
				if (Swich)
		{
		   strcat(buffer,"ON, (@");
		} else
		{
		   strcat(buffer,"OFF, (@");
		}

	} else
	{
			 if (Swich)
		{
		   strcat(buffer,"ON,NOR, (@");
		} else
		{
		   strcat(buffer,"OFF,NOR, (@");
		}
	}




		string  = IntToStr(Kanal);
		strcat(buffer,string.c_str());
		strcat(buffer,")");
		strcat(buffer, "\n");
		if (USB) {
	 //		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
		  viPrintf(vi, buffer);
		}

		if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}

}
long N6702A::SET_METER(int Kanal) {

 		AnsiString string;
		if (!USB)
		{ 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS)
					{
						switch(Lan_GPIB)
					  {case 0:
						ShowMessage("Источник питания с Ip " + (AnsiString)ipAdres +
							(AnsiString)ipLok + " не подключен."); //
						break;
					   case 1:
						ShowMessage("Источник питания TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
							(AnsiString)GPIB + " не подключен."); //
						break;


					  }
						return status;
					}


		}

		strcpy(buffer, "DISP:CHAN ");				//:POWer:STATe ON
		string  = IntToStr(Kanal);
		strcat(buffer,string.c_str());

		strcat(buffer, "\n");
		if (USB) {
	 //		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
		  viPrintf(vi, buffer);
		}

			strcpy(buffer, "DISP:VIEW METER");				//:POWer:STATe ON


				if (Kanal==4) {
			string  = IntToStr(Kanal);  // To set multiple-channel view:
		} else {
			string  = "1";
		}
		strcat(buffer,string.c_str());

		strcat(buffer, "\n");
		if (USB) {
	 //		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
		  viPrintf(vi, buffer);
		}

		if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}

}

long N6702A::BP_SET(double Vset, double Cur,int Kanal) {

	AnsiString string;
	ControlV(Vset, Volt);

			if (USB) {
			  strcpy(buffer, "VOLT ");
			}
			else { 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS)
					{
						ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
							(AnsiString)GPIB + " невозможно открыть."); //
						return status;
					}
					strcpy(buffer, "VOLT  ");

			}


	string  = FloatToStr(Volt);
	string  = Zapt(string);
	strcat(buffer,string.c_str());
	strcat(buffer, ", (@");
	string  = IntToStr(Kanal);
	strcat(buffer,string.c_str());
	strcat(buffer,")");
	strcat(buffer, "\n");
		if (USB) {
		  //AdapterGPIB->USBviPrintf(Gadr,buffer);

		  }else {
	  viPrintf(vi, buffer);
	}


	strcpy(buffer, "CURR ");                //:POWER 4 DBM	#Установка уровня
	string  = FloatToStr(Cur);
	string  = Zapt(string);
	strcat(buffer,string.c_str());
	strcat(buffer, ", (@");
	string  = IntToStr(Kanal);
	strcat(buffer,string.c_str());
	strcat(buffer,")");
	strcat(buffer, "\n");

		if (USB) {
		//	 AdapterGPIB->USBviPrintf(Gadr,buffer);
    	} else {
    	  viPrintf(vi, buffer);
		}





		if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}


	 return status;
} long N6702A::SetGroup(int GR, int Kan1, int Kan2)
{     	AnsiString string;
		if (!USB){ 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS)
					{
						ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
							(AnsiString)GPIB + " невозможно открыть."); //
						return status;
					}


			}

		strcpy(buffer, "SYST:GRO:DEF (");
		string = IntToStr(Kan1);
			switch(GR)
	{		case 1:

			strcat(buffer, "@1,");
			strcat(buffer, string.c_str());
			strcat(buffer, ",");
			string = IntToStr(Kan2);
			strcat(buffer, string.c_str()); break;
			case 2:

			strcat(buffer, "@2,");
			strcat(buffer, string.c_str());
			strcat(buffer, ",");
			string = IntToStr(Kan2);
			strcat(buffer, string.c_str()); break;
			case 3:

			strcat(buffer, "@3,");
			strcat(buffer, string.c_str());
			strcat(buffer, ",");
			string = IntToStr(Kan2);
			strcat(buffer, string.c_str());	break;
			case 4:

			strcat(buffer, "@4,");
			strcat(buffer, string.c_str());
			strcat(buffer, ",");
			string = IntToStr(Kan2);
			strcat(buffer, string.c_str()); break;
	}

		strcat(buffer, ")\n");
		if (USB) {
	 //		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
		  viPrintf(vi, buffer);
		}

		if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}


}
long N6702A::ResetGroup()
{     	AnsiString string;
		if (!USB){ 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS)
					{
						ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
							(AnsiString)GPIB + " невозможно открыть."); //
						return status;
					}


			}

        strcpy(buffer, "SYST:GRO:DEL:ALL");				//:POWer:STATe ON
		strcat(buffer, "\n");
		if (USB) {
	 //		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
		  viPrintf(vi, buffer);
		}

		if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}


}

char* N6702A::GetGPIB() {

return GPIB;

}

void N6702A::ControlV(double V, double& Com)
 {
	if (V >= Vmin && V <= Vmax)
	{
		if (V != 0)
		{
			Com = V;
		}
	}
		else
	{
		Com = 0.05;
	}
 }


void N6702A::Control(int K, int Pred, int& Com) {

if (K >= 0 && K <= Pred) {
if (K != 0) {
	Com = K;
}
}
else {
Com = 1;
}
}

double N6702A::MeasureVolt(int Kanal){
		 AnsiString string;
			if (USB) {
			  strcpy(buffer, "MEAS:VOLT? (@");
			}
			else { 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS) {
						ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
							(AnsiString)GPIB + " невозможно открыть."); //
						return status;
					}
					strcpy(buffer, "MEAS:VOLT? (@");

			}
		string  = IntToStr(Kanal);
		strcat(buffer,string.c_str());
		strcat(buffer,")");
		strcat(buffer, "\n");
		if (USB) {
	//		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
			 int bufLength = sizeof(rezult);
			 viQueryf(vi, buffer, "%#t", &bufLength, rezult);

		}
			if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}
           switch (Kanal) {
			 case 1:
			 V1 = atof(rezult);
			 break;
			 case 2:
			 V2 = atof(rezult);
			 break;
			 case 3:
			 V3 = atof(rezult);
			 break;
			 case 4:
			 V4 = atof(rezult);
			 break;
			 default:
			 break;
			 }
		  return 0.01*floor(100*atof(rezult)+0.5);
}
double N6702A::MeasureAmper(int Kanal){
		AnsiString string;
			if (USB) {
			  strcpy(buffer, "MEAS:CURR? (@");
			}
			else { 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS) {
						ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
							(AnsiString)GPIB + " невозможно открыть."); //
						return status;
					}
					strcpy(buffer, "MEAS:CURR? (@");

			}
		string  = IntToStr(Kanal);
		strcat(buffer,string.c_str());
		strcat(buffer,")");
		strcat(buffer, "\n");
		if (USB) {
	//		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
			 int bufLength = sizeof(rezult);
			 viQueryf(vi, buffer, "%#t", &bufLength, rezult);

		}
			if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}
			return 0.001*floor(1000*atof(rezult)+0.5);

}

int N6702A::STATUS(int Kanal){
		AnsiString string;
			if (USB) {
			  strcpy(buffer, "OUTP:STAT? (@");
			}
			else { 	status = viOpenDefaultRM(&defaultRM);
					strcpy(buffer, PriborLoad());
					status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
					if (status < VI_SUCCESS) {
						ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +  (AnsiString)GPIB + " невозможно открыть."); //

						return 0;
					}
					strcpy(buffer, "OUTP:STAT? (@");

			}
		string  = IntToStr(Kanal);
		strcat(buffer,string.c_str());
		strcat(buffer,")");
		strcat(buffer, "\n");
		if (USB) {
	//		AdapterGPIB->USBviPrintf(Gadr,buffer);
		} else {
			 int bufLength = sizeof(rezult);
			 viQueryf(vi, buffer, "%#t", &bufLength, rezult);

		}
			if (!USB) {
			 viClose(vi);                    // closes session
		 viClose(defaultRM);
		}
			 switch (Kanal) {
			 case 1:
			 Stat1 = atoi(rezult);
			 break;
			 case 2:
			 Stat2 = atoi(rezult);
			 break;
			 case 3:
			 Stat3 = atoi(rezult);
			 break;
			 case 4:
			 Stat4 = atoi(rezult);
			 break;
			 default:
			 break;
			 }

			return atoi(rezult);

}
