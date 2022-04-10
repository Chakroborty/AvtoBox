// ---------------------------------------------------------------------------

#pragma hdrstop
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#pragma hdrstop
#include "Switch34980A.h"
#include "visa.h"
#pragma comment(lib,"visa32.lib")
#include <math.h>

// ---------------------------------------------------------------------------
Switch34980::Switch34980(int Adr, char* Ip) {
	Gadr = 9;
	ControlDiap(Adr,30,Gadr);
	GPIB = "9";
	itoa(Gadr, GPIB, 10);
	strcpy(ipAdres, Ip);
	strcpy(ipLok, "/n");
	strcpy(ipLok,"10.29.31.27");
	Com21 = 1;
	Com22 = 1;
	Com23 = 1;
	Com61 = 1;
	Com62 = 1;
	Com63 = 1;
	Com64 = 1;
//============================947======================================
	strcpy(ARRAY947[1][1],"1101,");
	strcpy(ARRAY947[1][2],"1102,");
	strcpy(ARRAY947[2][1],"1201,");
	strcpy(ARRAY947[2][2],"1202,");
	strcpy(ARRAY947[3][1],"1301,");
	strcpy(ARRAY947[3][2],"1302,");

	strcpy(ARRAY947[4][1],"2101,");
	strcpy(ARRAY947[4][2],"2102,");
	strcpy(ARRAY947[5][1],"2201,");
	strcpy(ARRAY947[5][2],"2202,");
	strcpy(ARRAY947[6][1],"2301,");
	strcpy(ARRAY947[6][2],"2302,");

	strcpy(ARRAY947[7][1],"3101,");
	strcpy(ARRAY947[7][2],"3102,");
	strcpy(ARRAY947[8][1],"3201,");
	strcpy(ARRAY947[8][2],"3202,");
	strcpy(ARRAY947[9][1],"3301,");
	strcpy(ARRAY947[9][2],"3302,");

	strcpy(ARRAY947[10][1],"4101,");
	strcpy(ARRAY947[10][2],"4102,");
	strcpy(ARRAY947[11][1],"4201,");
	strcpy(ARRAY947[11][2],"4202,");
	strcpy(ARRAY947[12][1],"4301,");
	strcpy(ARRAY947[12][2],"4302,");


//============================941======================================

	strcpy(ARRAY941[1][1],"6101,");
	strcpy(ARRAY941[1][2],"6102,");
	strcpy(ARRAY941[1][3],"6103,");
	strcpy(ARRAY941[1][4],"6104,");
	strcpy(ARRAY941[2][1],"6201,");
	strcpy(ARRAY941[2][2],"6202,");
	strcpy(ARRAY941[2][3],"6203,");
	strcpy(ARRAY941[2][4],"6204,");
	strcpy(ARRAY941[3][1],"6301,");
	strcpy(ARRAY941[3][2],"6302,");
	strcpy(ARRAY941[3][3],"6303,");
	strcpy(ARRAY941[3][4],"6304,");
	strcpy(ARRAY941[4][1],"6401,");
	strcpy(ARRAY941[4][2],"6402,");
	strcpy(ARRAY941[4][3],"6403,");
	strcpy(ARRAY941[4][4],"6404,");
//=============================941============================================

	strcpy(ARRAY941[5][1],"7101,");
	strcpy(ARRAY941[5][2],"7102,");
	strcpy(ARRAY941[5][3],"7103,");
	strcpy(ARRAY941[5][4],"7104,");
	strcpy(ARRAY941[6][1],"7201,");
	strcpy(ARRAY941[6][2],"7202,");
	strcpy(ARRAY941[6][3],"7203,");
	strcpy(ARRAY941[6][4],"7204,");
	strcpy(ARRAY941[7][1],"7301,");
	strcpy(ARRAY941[7][2],"7302,");
	strcpy(ARRAY941[7][3],"7303,");
	strcpy(ARRAY941[7][4],"7304,");
	strcpy(ARRAY941[8][1],"7401,");
	strcpy(ARRAY941[8][2],"7402,");
	strcpy(ARRAY941[8][3],"7403,");
	strcpy(ARRAY941[8][4],"7404,");
//===============================647==========================================
	strcpy(ARRAY947[13][1],"8101,");
	strcpy(ARRAY947[13][2],"8102,");
	strcpy(ARRAY947[14][1],"8201,");
	strcpy(ARRAY947[14][2],"8202,");
	strcpy(ARRAY947[15][1],"8301");
	strcpy(ARRAY947[15][2],"8302");

//0
//0
//1
//1
//2
//2
//3
//3
//4
//4
//5
//5
//6
//6
//7
//7
//8
//8
//9
//9
//10
//10
//11
//11
//12
//12
//13
//13
//14
//14












	// char *DSA;
	// strcpy(DSA,ARRAY947[0][0]);
	// strcat(DSA,ARRAY947[0][1]);
}

Switch34980::~Switch34980() {

}
int Switch34980::ControlDiap(int K, int Pred, int& Com)
{

	if (K >= 0 && K <= Pred)
	{
		if (K != 0)
		{
			Com = K;
		}
	}
	else
	{
		Com = 1;
	}
}
char* Switch34980::PriborLoad()
{
	char sttr[100];
			switch (Lan_GPIB)
	{	case 0:
		strcpy(sttr,"TCPIP0::");
		strcat(sttr, ipLok);
		strcat(sttr, "::inst0::INSTR");
		break;
		case 1:
		strcpy(sttr,"");
		strcpy(sttr,"TCPIP0::");
		strcat(sttr,ipAdres);
		strcat(sttr,"::gpib0,");
		strcat(sttr,GPIB);
		strcat(sttr,"::INSTR");
		break;
	}
	return sttr;
}
char* Switch34980::GetGPIB(void) {
	return GPIB;
}
char* Switch34980::GetIPlok()
{
	return ipLok;
}
void Switch34980::GPIB_Set(AnsiString Adr, AnsiString Ip) {  /* TODO -cIP ADR : добавить в метод IP */
	int Gadr = StrToInt(Adr);
	Lan_GPIB = 1;//Gadr = atoi(Adr);
	if (Gadr >= 0 && Gadr <= 30) {
		itoa(Gadr, GPIB, 10);
	}
	else {
		GPIB = "9";
	}
	strcpy(ipAdres, Ip.c_str());
}
void Switch34980::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
int Switch34980::ControlCom(int K, int Pred, int &Com)
{
	if (K >= 0 && K <= Pred)
	{
		if (K != 0)
		{
        	Com = K;
		}
	}

}
long Switch34980::KanalGset(int Knum)
{      	 switch (Knum)
		{
	 case 1:
	 status = CommSet(1,0,2,0,0,4,4);  //Kanal(1) = "ROUT:CLOS (@2102,2301,6104,6204)"
	 break;
	 case 2:
	 status = CommSet(1,0,2,0,0,3,3);  //Kanal(2) = "ROUT:CLOS (@2102,2301,6103,6203)"
	 break;
	 case 3:
	 status = CommSet(1,0,2,0,0,2,2);  //Kanal(3) = "ROUT:CLOS (@2102,2301,6102,6202)"
	 break;
	 case 4:
	 status = CommSet(1,0,2,0,0,1,1);  //Kanal(4) = "ROUT:CLOS (@2102,2301,6101,6201)"
	 break;
	 case 21:
	 status = CommSet(1,1,0,4,0,0,0);  //Kanal(1) = "ROUT:CLOS (@2102,2301,6104,6204)"
	 break;
	 case 22:
	 status = CommSet(1,1,0,3,0,0,0);  //Kanal(2) = "ROUT:CLOS (@2102,2301,6103,6203)"
	 break;
	 case 23:
	 status = CommSet(1,1,0,2,0,0,0);  //Kanal(3) = "ROUT:CLOS (@2102,2301,6102,6202)"
	 break;
	 case 24:
	 status = CommSet(1,1,0,1,0,0,0);  //Kanal(4) = "ROUT:CLOS (@2102,2301,6101,6201)"
	 break;



	  default : break;
		}
}
long Switch34980::KanalSet(int Knum)
{
	  ViStatus status;
			 switch (Knum)
  {
	 case 1:                            //CommSet(int K21, int K22, int K23, int K61, int K62, int K63, int K64);
	 status = CommSet(1,0,1,4,4,0,0);  //Kanal(1) = "ROUT:CLOS (@2102,2301,6104,6204)"
	 break;
	 case 2:
	 status = CommSet(1,0,1,3,3,0,0);  //Kanal(2) = "ROUT:CLOS (@2102,2301,6103,6203)"
	 break;
	 case 3:
	 status = CommSet(1,0,1,2,2,0,0);  //Kanal(3) = "ROUT:CLOS (@2102,2301,6102,6202)"
	 break;
	 case 4:
	 status = CommSet(1,0,1,1,1,0,0);  //Kanal(4) = "ROUT:CLOS (@2102,2301,6101,6201)"
	 break;
	 case 5:
	 status = CommSet(2,0,2,0,0,4,4);  //Kanal(5) = "ROUT:CLOS (@2101,2302,6304,6404)"
	 break;
	 case 6:
	 status = CommSet(2,0,2,0,0,3,3);  //Kanal(6) = "ROUT:CLOS (@2101,2302,6303,6403)"
	 break;
	 case 7:
	 status = CommSet(2,0,2,0,0,2,2);  //Kanal(7) = "ROUT:CLOS (@2101,2302,6302,6402)"
	 break;
	 case 8:
	 status = CommSet(2,0,2,0,0,1,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
	 break;
	 case 9:
	 status = CommSet(1,0,1,4,2,1,1);  //CROSS
	 break;
	 case 19:
	 status = CommSet(1,2,2,0,0,0,0);  //CROSS
	 break;
	 case 20:
	 status = CommSet(2,2,2,0,0,0,0);  //CROSS
	 break;

	 case 21:
	 status = CommSet(0,2,2,4,0,0,0);  //CROSS
	 break;
	 case 22:
	 status = CommSet(0,2,1,3,0,0,0);  //CROSS
	 break;
	 case 23:
	 status = CommSet(2,1,0,2,0,0,0);  //CROSS
	 break;
	 case 24:
	 status = CommSet(1,1,0,1,0,0,0);  //CROSS
	 break;
	 default : break;
  }


	return status;
}
long Switch34980::KanalSet16(int Knum)
{
	  ViStatus status;
			 switch (Knum)
		{
			 case 1:
			 status = CommSetK16(1,2,1,1, 4,4,4,4, 4,4,4,4);  //Kanal(1) = "ROUT:CLOS (@2102,2301,6104,6204)"
			 break;
			 case 2:
			 status = CommSetK16(1,2,1,1, 4,3,4,4, 4,3,4,4);  //Kanal(2) = "ROUT:CLOS (@2102,2301,6103,6203)"
			 break;
			 case 3:
			 status = CommSetK16(1,2,1,1, 4,2,4,4, 4,2,4,4);  //Kanal(3) = "ROUT:CLOS (@2102,2301,6102,6202)"
			 break;
			 case 4:
			 status = CommSetK16(1,2,1,1, 4,1,4,4, 4,1,4,4);  //Kanal(4) = "ROUT:CLOS (@2102,2301,6101,6201)"
			 break;

			 case 5:
			 status = CommSetK16(1,1,1,2, 4,1,4,4, 4,1,4,4);  //Kanal(5) = "ROUT:CLOS (@2101,2302,6304,6404)"
			 break;
			 case 6:
			 status = CommSetK16(1,1,1,2, 4,1,4,3, 4,1,4,3);  //Kanal(6) = "ROUT:CLOS (@2101,2302,6303,6403)"
			 break;
			 case 7:
			 status = CommSetK16(1,1,1,2, 4,1,4,2, 4,1,4,2);  //Kanal(7) = "ROUT:CLOS (@2101,2302,6302,6402)"
			 break;
			 case 8:
			 status = CommSetK16(1,1,1,2, 4,1,4,1, 4,1,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;

			 case 9:
			 status = CommSetK16(1,4,1,3, 4,4,4,1, 4,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 10:
			 status = CommSetK16(1,4,1,3, 3,4,4,1, 3,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 11:
			 status = CommSetK16(1,4,1,3, 2,4,4,1, 2,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 12:
			 status = CommSetK16(1,4,1,3, 1,4,4,1, 1,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;

			 case 13:
			 status = CommSetK16(1,3,1,4, 1,4,4,1, 4,4,4,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 14:
			 status = CommSetK16(1,3,1,4, 1,4,3,1, 4,4,3,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 15:
			 status = CommSetK16(1,3,1,4, 1,4,2,1, 4,4,2,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 16:
			 status = CommSetK16(1,3,1,4, 1,4,1,1, 4,4,1,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
	 default : break;
		}


	return status;
}
long Switch34980::KanalSet12(int Knum)
{
	  ViStatus status;
			 switch (Knum)
		{
			 case 1:
			 status = CommSetK16(1,2,1,1, 4,4,4,4, 4,4,4,4);  //Kanal(1) = "ROUT:CLOS (@2102,2301,6104,6204)"
			 break;
			 case 2:
			 status = CommSetK16(1,2,1,1, 4,3,4,4, 4,3,4,4);  //Kanal(2) = "ROUT:CLOS (@2102,2301,6103,6203)"
			 break;
			 case 3:
			 status = CommSetK16(1,2,1,1, 4,2,4,4, 4,2,4,4);  //Kanal(3) = "ROUT:CLOS (@2102,2301,6102,6202)"
			 break;
			 case 4:
			 status = CommSetK16(1,2,1,1, 4,1,4,4, 4,1,4,4);  //Kanal(4) = "ROUT:CLOS (@2102,2301,6101,6201)"
			 break;

			 case 5:
			 status = CommSetK16(1,1,1,2, 4,1,4,4, 4,1,4,4);  //Kanal(5) = "ROUT:CLOS (@2101,2302,6304,6404)"
			 break;
			 case 6:
			 status = CommSetK16(1,1,1,2, 4,1,4,3, 4,1,4,3);  //Kanal(6) = "ROUT:CLOS (@2101,2302,6303,6403)"
			 break;
			 case 7:
			 status = CommSetK16(1,1,1,2, 4,1,4,2, 4,1,4,2);  //Kanal(7) = "ROUT:CLOS (@2101,2302,6302,6402)"
			 break;
			 case 8:
			 status = CommSetK16(1,1,1,2, 4,1,4,1, 4,1,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;

			 case 9:
			 status = CommSetK16(1,4,1,3, 4,4,4,1, 4,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 10:
			 status = CommSetK16(1,4,1,3, 3,4,4,1, 3,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 11:
			 status = CommSetK16(1,4,1,3, 2,4,4,1, 2,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 12:
			 status = CommSetK16(1,4,1,3, 1,4,4,1, 1,4,4,1);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;

			 case 13:
			 status = CommSetK16(1,3,1,4, 1,4,4,1, 4,4,4,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 14:
			 status = CommSetK16(1,3,1,4, 1,4,3,1, 4,4,3,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 15:
			 status = CommSetK16(1,3,1,4, 1,4,2,1, 4,4,2,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
			 case 16:
			 status = CommSetK16(1,3,1,4, 1,4,1,1, 4,4,1,4);  //Kanal(8) = "ROUT:CLOS (@2101,2302,6301,6401)"
			 break;
	 default : break;
		}


	return status;
}

long Switch34980::CommSet(int K21, int K22, int K23, int K61, int K62, int K63,	int K64)
{   ControlCom( K21,  2, Com21);
	ControlCom( K22,  2, Com22);
	ControlCom( K23,  2, Com23);
	ControlCom( K61,  4, Com61);
	ControlCom( K62,  4, Com62);
	ControlCom( K63,  4, Com63);
	ControlCom( K64,  4, Com64);


	ViStatus status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());

	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS)
	{  	ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres +"::gpib0,"+ (AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}

	 strcpy(buffer,"ROUT:CLOS (@21");
	 strcat(buffer,COMdef(Com21));
	 strcat(buffer,",");
	 strcat(buffer,"22");
	 strcat(buffer,COMdef(Com22));
	 strcat(buffer,",");
	 strcat(buffer,"23");
	 strcat(buffer,COMdef(Com23));
	 strcat(buffer,",");
	 strcat(buffer,"61");
	 strcat(buffer,COMdef(Com61));
	 strcat(buffer,",");
	 strcat(buffer,"62");
	 strcat(buffer,COMdef(Com62));
	 strcat(buffer,",");
	 strcat(buffer,"63");
	 strcat(buffer,COMdef(Com63));
	 strcat(buffer,",");
	 strcat(buffer,"64");
	 strcat(buffer,COMdef(Com64));
	 strcat(buffer,")\n");
	 status = viPrintf(vi, buffer);

	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session

	 return status;

}
long Switch34980::CommSetK16(int K221,int K222,int K223,int K224,int K61,int K62,int K63,int K64,int K71,int K72,int K73,int K74)
{   ControlCom( K221,  4, Com221);
	ControlCom( K222,  4, Com222);
	ControlCom( K223,  4, Com223);
	ControlCom( K224,  4, Com224);
	ControlCom( K61,  4, Com61);
	ControlCom( K62,  4, Com62);
	ControlCom( K63,  4, Com63);
	ControlCom( K64,  4, Com64);
	ControlCom( K71,  4, Com71);
	ControlCom( K72,  4, Com72);
	ControlCom( K73,  4, Com73);
	ControlCom( K74,  4, Com74);

	ViStatus status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());

	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS)
	{  	ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres +"::gpib0,"+ (AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}

	 strcpy(buffer,"ROUT:CLOS (@21");
	 strcat(buffer,COMdef(Com221));
	 strcat(buffer,",");
	 strcat(buffer,"22");
	 strcat(buffer,COMdef(Com222));
	 strcat(buffer,",");
	 strcat(buffer,"23");
	 strcat(buffer,COMdef(Com223));
	 strcat(buffer,",");
	 strcat(buffer,"24");
	 strcat(buffer,COMdef(Com224));

	 strcat(buffer,",");
	 strcat(buffer,"61");
	 strcat(buffer,COMdef(Com61));
	 strcat(buffer,",");
	 strcat(buffer,"62");
	 strcat(buffer,COMdef(Com62));
	 strcat(buffer,",");
	 strcat(buffer,"63");
	 strcat(buffer,COMdef(Com63));
	 strcat(buffer,",");
	 strcat(buffer,"64");
	 strcat(buffer,COMdef(Com64));

	 strcat(buffer,",");
	 strcat(buffer,"71");
	 strcat(buffer,COMdef(Com71));
	 strcat(buffer,",");
	 strcat(buffer,"72");
	 strcat(buffer,COMdef(Com72));
	 strcat(buffer,",");
	 strcat(buffer,"73");
	 strcat(buffer,COMdef(Com73));
	 strcat(buffer,",");
	 strcat(buffer,"74");
	 strcat(buffer,COMdef(Com74));



	 strcat(buffer,")\n");
	 status = viPrintf(vi, buffer);

	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session

	 return status;
}
//-------------------------------------------------------------------------------------
bool Switch34980::Connect(ViStatus ST)
{
if (ST < VI_SUCCESS)
	{  		switch (Lan_GPIB)
		{
		case 0: ShowMessage("Коммутатор SW34980A IP::" + (AnsiString)ipLok + " не обаружен."); //
				   break;
		case 1: ShowMessage("Коммутатор SW34980A TCPIP0::" + (AnsiString)ipAdres +"::gpib0,"+ (AnsiString)GPIB + " не обаружен."); //
				   break;
		default:  ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres+ (AnsiString)GPIB + "  не обаружен."); break;
		}
		return true;
	}else
	{
		return false;
	}

}
//-------------------------------------------------------------------------------------
long Switch34980::CommSetK16HF(int KANAL)
 {   if(KANAL>0&&KANAL<<17) {
 	SWKANAL = KANAL;
 }
 else {
 	SWKANAL = 1;
 }
// ControlCom( K221,  4, Com221);
// 	ControlCom( K222,  4, Com222);
// 	ControlCom( K223,  4, Com223);
// 	ControlCom( K224,  4, Com224);
// 	ControlCom( K61,  4, Com61);
// 	ControlCom( K62,  4, Com62);
// 	ControlCom( K63,  4, Com63);
// 	ControlCom( K64,  4, Com64);
// 	ControlCom( K71,  4, Com71);
// 	ControlCom( K72,  4, Com72);
// 	ControlCom( K73,  4, Com73);
// 	ControlCom( K74,  4, Com74);

	ViStatus status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());

	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);

	if(Connect(status)) {
	 	return status;
	 }



	strcpy(buffer,"ROUT:CLOS (@");

	strcat(buffer,ARRAY947[1][SW947ST[SWKANAL][1]]);
	strcat(buffer,ARRAY947[2][SW947ST[SWKANAL][2]]);
	strcat(buffer,ARRAY947[3][SW947ST[SWKANAL][3]]);
	strcat(buffer,ARRAY947[4][SW947ST[SWKANAL][4]]);
	strcat(buffer,ARRAY947[5][SW947ST[SWKANAL][5]]);
	strcat(buffer,ARRAY947[6][SW947ST[SWKANAL][6]]);
	strcat(buffer,ARRAY947[7][SW947ST[SWKANAL][7]]);
	strcat(buffer,ARRAY947[8][SW947ST[SWKANAL][8]]);
	strcat(buffer,ARRAY947[9][SW947ST[SWKANAL][9]]);
	strcat(buffer,ARRAY947[10][SW947ST[SWKANAL][10]]);
	strcat(buffer,ARRAY947[11][SW947ST[SWKANAL][11]]);
	strcat(buffer,ARRAY947[12][SW947ST[SWKANAL][12]]);

	strcat(buffer,ARRAY941[3][SW941ST[SWKANAL][3]]);
	strcat(buffer,ARRAY941[5][SW941ST[SWKANAL][5]]);
	strcat(buffer,ARRAY941[6][SW941ST[SWKANAL][6]]);
	strcat(buffer,ARRAY941[7][SW941ST[SWKANAL][7]]);
	strcat(buffer,ARRAY941[8][SW941ST[SWKANAL][8]]);

	strcat(buffer,ARRAY947[13][SW947ST[SWKANAL][13]]);
	strcat(buffer,ARRAY947[14][SW947ST[SWKANAL][14]]);
	strcat(buffer,ARRAY947[15][SW947ST[SWKANAL][15]]);

	strcat(buffer,")\n");
	status = viPrintf(vi, buffer);

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session

	return status;
}


char* Switch34980::COMdef(int Pos) {
char str[100]="\n";

		 switch (Pos)
		{
	 case 1:
	 strcpy(str,"01");              /* TODO -cTrase : Установка параметров трассы и дисплея */
	 break;
	 case 2:
	 strcpy(str,"02");
	 break;
	 case 3:
	 strcpy(str,"03");
	 break;
	 case 4:
	 strcpy(str,"04");
	 break;

	 default : break;
		}
							  /* TODO -cDisp : Format DEF*/
		return  str;
}
#pragma package(smart_init)
