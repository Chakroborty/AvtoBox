#pragma hdrstop
#include "Agilent9030.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#include "visa.h"

#include <math.h>



#pragma comment(lib,"visa32.lib")

Analiz9030::Analiz9030(int Adr, char* Ip,int LAN)
{
	Control(Adr, 30, Gadr);
	strcpy(GPIB,"18");
	itoa(Gadr, GPIB, 10);
	strcpy(ipAdres, Ip);
	strcpy(ipLok, "10.29.31.14");
	CentrF = 140;
	RL = 20;
	Span = 100;
	RBW = 3000;
	Fmin = 0.000003;
	Fmax = 26500;
	Lan_GPIB = LAN;

}

Analiz9030::~Analiz9030()
{
}
int Analiz9030::Pinitial()
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
char* Analiz9030::GETIDN()
{
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS)
	{
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return 0;
	}

	strcpy(buffer,"*IDN?\n");
	int bufLength = sizeof(rezult); //
	status = viQueryf(vi, buffer, "%#t", &bufLength, rezult);
	viClose(vi);                    // closes session
	viClose(defaultRM);
	return  rezult;
}
char* Analiz9030::PriborLoad()
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

void Analiz9030::GPIB_Set(AnsiString Adr, AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	int Gadr = StrToInt(Adr);

	if (Gadr >= 0 && Gadr <= 30) {
		itoa(Gadr, GPIB, 10);
	}
	else {
		strcpy(GPIB,"20");
	}
	Lan_GPIB = 1;
	strcpy(ipAdres, Ip.c_str());
}
void Analiz9030::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
char* Analiz9030::GetGPIB()
{
	return GPIB;
}
char* Analiz9030::GetIPlok()
{
	return ipLok;
}

AnsiString  Analiz9030::Zapt(AnsiString str)
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
long Analiz9030::AnSpanSet(double Fset, double SP, double BW, double RWFL) {
 AnsiString string;
 SetMarker(0,0,0,0);

 if (Fset>Fmax) {
		CentrF = 26500;
 }
 else {if (Fset<Fmin)
		{
			CentrF = 0.000003;
		}
		else
		{
			CentrF = Fset;
		}
 }
  if (SP>0&&SP<26499.75) { Span = SP;}

		if (CentrF-Span/2<Fmin)
	{
		 Span = 2*(CentrF-Fmin);
	}
		 else
	{
	  if (CentrF+Span/2>Fmax) { Span = 2*(Fmax-CentrF);}
	}
	RL = RWFL;
	RBW = BW;



	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS)
	{
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	strcpy(buffer, "FREQ:CENT "); // CF 70MHZ;SP 100KHZ;RB 100HZ;RL-10DBM
	string = Zapt(FloatToStr(CentrF));
	strcat(buffer, string.c_str());
	strcat(buffer, " MHZ\n");
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

double Analiz9030::Sens(double Lin,double Fin, double SP, double BW,double Ofs){
 AnSpanSet(Fin,SP,BW, Lin);
 Sleep(300);
 MkDelta(1,false,0);
 MkrPeak(1);
 MkDelta(1,true,Ofs);
 SetMarker(true, 0, false, 100);
 Sleep(5000);
 return  0.1*floor(10*strtod(Result(1),NULL));
}

int Analiz9030::Control(int K, int Pred, int& Com) {
	if (K >= 0 && K <= Pred) {

			Com = K;

	}
	else {
		Com = 0;
	}
}

long Analiz9030::MkrPeak(int n) {
	AnsiString string;
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	strcpy(buffer, "CALC:MARK"); // MKD 30KHZ;
	string = IntToStr(n);
	strcat(buffer,string.c_str());
	strcat(buffer,":MODE POS\n");
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);
	strcpy(buffer, "CALC:MARK");
	string = IntToStr(n);
	strcat(buffer, string.c_str());
	strcat(buffer, ":MAX\n");

	status = viPrintf(vi, buffer);
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}

long Analiz9030::MkDelta(int num,bool Enabl,double Del) {
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
	if (Enabl) {           /* TODO : Mark delta */
		strcpy(buffer, "CALC:MARK"); // MKD 30KHZ;
		string = IntToStr(num);
		strcat(buffer, string.c_str());
		strcat(buffer, ":MODE DELT\n");

		status = viPrintf(vi, buffer);
		strcpy(buffer, "CALC:MARK");
        string = IntToStr(num);
		strcat(buffer, string.c_str());
		strcat(buffer, ":X ");
		string = FloatToStr(DELTA);
		strcat(buffer, string.c_str());
		strcat(buffer, "kHz\n");
        status = viPrintf(vi, buffer);
	}
	else {
		strcpy(buffer, "CALC:MARK"); // MKD 30KHZ;
        string = IntToStr(num);
		strcat(buffer,string.c_str());
		strcat(buffer,":MODE POS\n");
        strcat(buffer, "\n");
	}
	status = viPrintf(vi, buffer);
	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}
long Analiz9030::MarkerCent(int N){
 	AnsiString string;
    status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}

	strcpy(buffer, "CALC:MARK"); // MKD 30KHZ;
	string = IntToStr(N);
	strcat(buffer,string.c_str());
	strcat(buffer,":CENT");
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);



    viClose(vi);
	viClose(defaultRM);


	return status;

}

long Analiz9030::SetMarker(bool Del, int Delta, bool Pik, int Count) {
	AnsiString string;
    status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}


	Control(Count, 200, Coun);

	if (Coun) {
		strcpy(buffer, "OBW:AVER:COUN ");
		string = FloatToStr(Coun);
		strcat(buffer, string.c_str());
		strcat(buffer, "\n");			/* TODO -cAG8560 : Маркер анализатора */
		status = viPrintf(vi, buffer);
		strcpy(buffer, "TRAC:TYPE AVER\n");
		status = viPrintf(vi, buffer);

	}
	else {
		strcpy(buffer, "TRAC:TYPE WRIT\n");
		status = viPrintf(vi, buffer);
	}


	viClose(vi);
	viClose(defaultRM);


	return status;
}
double Analiz9030::FMark(){

 return Fmark;
}
char* Analiz9030::Result(int n) {
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
		PeakF = Fmark/1000000;
			//buffer = {0};
		strcpy(buffer, "CALC:MARK");
		string = IntToStr(n);
		strcat(buffer, string.c_str());
		strcat(buffer, ":Y?\n");
		bufLength = sizeof(rezult); //
		status = viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		PeakP = strtod(rezult,NULL);
	 viClose(vi);                    // closes session
	 viClose(defaultRM);             // closes default session


		return rezult;
}
char* Analiz9030::CHPWRBW(double Chnl,double ChBW){
		Pinitial();

		AnsiString string;
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return 0;
		}
		viSetAttribute(vi,VI_ATTR_TMO_VALUE,20000);
		strcpy(buffer, ":SENS:FREQ:CENT ");   //15.75 MHZ;
		//Control(Chnl, 10000, DELTA);
		string = FloatToStr(Chnl);
		string = Zapt(string);
		strcat(buffer,string.c_str());
		strcat(buffer, " MHZ\n");
		status = viPrintf(vi, buffer);

		strcpy(buffer, ":CONF:CHP;:INIT:CONT 1\n");   //15.75 MHZ;
		status = viPrintf(vi, buffer);

		strcpy(buffer, ":SENSe:CHPower:BWIDth:INTegration ");   //28.5 MHZ;
		string = FloatToStr(ChBW);
		string = Zapt(string);
		strcat(buffer,string.c_str());
		strcat(buffer, " MHZ\n");
		status = viPrintf(vi, buffer);

		strcpy(buffer, ":SENSe:CHPower:FREQuency:SPAN ");   //28.5 MHZ;
		string = FloatToStr(Chnl+ChBW/2);
		string = Zapt(string);
		strcat(buffer,string.c_str());
		strcat(buffer, " MHZ\n");
		status = viPrintf(vi, buffer);

		strcpy(buffer,":READ:CHP?;*wai");   //:READ:CHPower?;*wai
		int bufLength = 0;//sizeof(rezult);  viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		status = viQueryf(vi,"%s\n","%#t",buffer,&bufLength,rezult);  //  viQueryf(vi, buffer, "%#t", &bufLength, rezult);
		viClose(vi);                    // closes session
		viClose(defaultRM);// closes default session
		char* St = strtok(rezult,",");//    -4.94485800E+001,-1.23997000E+002  St = -4.94485800E+001

		return St;

}
void Analiz9030::DataRet(double *Data, double *Freq, int point)
{     // float *fdata = new float[point];  allocate data_size doubles
status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
		 strcpy(buffer,PriborLoad());
		 printf_s("%s\n", buffer);
		 status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		 if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
	return;
 }
 int retCount = point;
 //viPrintf(vi,":FORMat:DATA ASC\n");
 viPrintf(vi,":UNIT:POW DBM\n");
 viPrintf(vi,":FORMat:DATA %s,%@1d\n", "REAL", 64);
//Set Analyzer to single sweep mode
 viPrintf(vi, ":INIT:CONT 0\n");
//Trigger a sweep and wait for sweep to complete
 viPrintf(vi, ":INIT:IMM;*WAI\n");
 Wite(100);

	//Query the trace data from the instrument
	//Note: Change the "%#zb" to "%#Zb" for Real,64 data
	//      For Int,32 leave the modifier as "%#zb"
	//viVQueryf(vi, ":TRAC:DATA? TRACE1" + Chr$(10),"%#zb", ArrayPtr(0))






 //viQueryf(vi, ":SENS1:OFFS:PORT1:DATA?\n", "%,#lf", &retCount, Freq);	//SENS1:FREQ:DATA?
 //retCount = 2*retCount;
 retCnt = point*4;
   //	Wite(100);
 //viQueryf(vi, ":CALC:DATA1?\n", "%#!olZb",&retCnt,  fdata);   //%#!olZb  %#zb%#!olZb
 viPrintf(vi, ":TRACE? TRACE1\n");  //  FETCH:SPEC7? :CALC:DATA1?
 viScanf(vi, "%#Zb", &retCnt, Data);

//		for (Coun = 0; Coun < point-1; Coun++) {
//		 Data[Coun] = fdata[Coun];
//	}
//status=viPrintf(vi, "%s\n", ":FORM:BORD NORM;:FORM:DATA REAL,32;:CALC:DATA1?;*WAI");
//status=viScanf(vi, "%#!olZb", &retCnt, Data);


//viRead (vi,Data,250,&byteret);

 viPrintf(vi, ":INIT:CONT 1\n");

 	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
}
long  Analiz9030::Spurs(int Line)
{   float *fdata = new float[100];  //allocate data_size doubles
	status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
	strcpy(buffer,PriborLoad());
	printf_s("%s\n", buffer);
	status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
			if (status < VI_SUCCESS)
	{
		ShowMessage("Can't open VISA address");
		return status;
	}
			viPrintf(vi,":FORM:TRAC:DATA %s,%@1d\n", "REAL", 64);
			//viPrintf(vi,":FORM:TRAC:DATA ASCI\n");
			viPrintf(vi,":CALC:MARK:PEAK:SORT FREQ\n");



			//viPrintf(vi,":INIT:CONT 0\n");
			//Trigger a sweep and wait for sweep to complete
			viPrintf(vi, ":INIT:IMM;*WAI\n");
			Wite(100);
			//	viPrintf(vi,":TRAC:MATH:PEAK?\n");  //  FETCH:SPEC7? :CALC:DATA1?
			//viScanf(vi,"%#!olZb", &retCnt, fdata);

			int bufLength = sizeof(rezult);
			viQueryf(vi,":TRAC:MATH:PEAK?\n","%#t", &bufLength, rezult);

			//viQueryf(vi, ":TRAC:MATH:PEAK?\n", "%#!olZb",&retCnt,fdata );  //    %#!olZb

				for (Coun = 0;Coun < 20; Coun++)
			{
				Spur[Coun] = RazborStr (Coun, rezult);
			}



	viPrintf(vi, ":INIT:CONT 1\n");
	viClose(vi);                    // closes session
	viClose(defaultRM);
}
double Analiz9030::RazborStr (int poz, char* str)
{     char* St;

		if (poz > 0)
	{
		St = "0";
		St = strstr(str,",");
		if (St==NULL) { return -100;}
			*St = '0';
			St = St+1;
			strcpy(str,St);
			St = strstr(str,",");

			/*
			if (i<(poz-1)) {
			*St = 0;
			}
			*/
	}

return 0.01*floor(100*strtod(str,NULL));

}

void Analiz9030::DispLINE(int LEV,int ENbl)
{   status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
	strcpy(buffer,PriborLoad());
	printf_s("%s\n", buffer);
	status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
			if (status < VI_SUCCESS)
	{
		ShowMessage("Can't open VISA address");
		return ;
	}
	viPrintf(vi,":CALC:MARK:PEAK:SORT FREQ\n");
	viPrintf(vi,":CALC:MARK:PEAK:THR %@1d\n", LEV);
	viPrintf(vi,":CALC:MARK:PEAK:EXC %@1d\n", 3);
	viPrintf(vi,":CALC:MARK:PEAK:EXC:STATE %@1d\n",ENbl);
	viPrintf(vi,":CALC:MARK:PEAK:THR:STATE %@1d\n",ENbl);


	viClose(vi);                    // closes session
	viClose(defaultRM);
}
void Analiz9030::Wite(int Msec)
{
		lOpc=0;
		viPrintf(vi, "*OPC\n");
		Coun = 0;
		while ((lOpc & 1) == 0)
	{ Coun = Coun +1;
	  viQueryf(vi, "*ESR?\n", "%d", &lOpc);
	  Sleep(Msec);

			if (Coun>10)
	  {
           break;
	  }
	}
}
void Analiz9030::Reset()
{   status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
	strcpy(buffer,PriborLoad());
	printf_s("%s\n", buffer);
	status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
			if (status < VI_SUCCESS)
	{
		ShowMessage("Can't open VISA address");
		return ;
	}
	viPrintf(vi,"*CLS\n");
	viPrintf(vi,"*RST\n");

	viClose(vi);                    // closes session
	viClose(defaultRM);
}
long Analiz9030::SavPath(AnsiString MPath)
{   DataPath = MPath+"\\";
//	status = viOpenDefaultRM(&defaultRM);
//	strcpy(buffer, PriborLoad());
//	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
//	if (status < VI_SUCCESS)
//	{
//		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
//			(AnsiString)GPIB + " невозможно открыть."); //
//		return status;
//	}
//	strcpy(buffer, ":MMEM:CDIR """); // CF 70MHZ;SP 100KHZ;RB 100HZ;RL-10DBM
//	//string = Zapt(FloatToStr(CentrF));
//	strcat(buffer, DataPath.c_str());
//	//strcat(buffer, MPath.c_str());
//	strcat(buffer, """\n");
//	viPrintf(vi, buffer);
}
long Analiz9030::Screen(AnsiString FName)
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
	strcpy(buffer, ":MMEM:STOR:SCR '"); // CF 70MHZ;SP 100KHZ;RB 100HZ;RL-10DBM
	//string = Zapt(FloatToStr(CentrF));
	strcat(buffer, DataPath.c_str());
	strcat(buffer, FName.c_str());

	strcat(buffer, "'\n");
	viPrintf(vi, buffer);
    viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
}

