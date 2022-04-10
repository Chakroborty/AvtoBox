#pragma hdrstop
#include "AgilentFF.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#include "visa.h"

#include <math.h>



#pragma comment(lib,"visa32.lib")

AnalizFFox::AnalizFFox(int Adr, char* Ip)
{
	Control(Adr, 30, Gadr);
	strcpy(GPIB,"18");
	itoa(Gadr, GPIB, 10);
	strcpy(ipAdres, Ip);
	strcpy(ipLok, "10.29.31.15");
	CentrF = 140;
	RL = 20;
	Span = 100;
	RBW = 3000;
	Fmin = 0.000003;
	Fmax = 4000000;
	Lan_GPIB = 0;



    lBytesRetrieved  = 0L;
									/* setup commands for CSA/PSA */
	//strcpy(saSetup,"*RST;*CLS;");	/* Reset the device and clear status */
	strcpy(saSetup,":INIT:CONT 0;");	/* Set analyzer to single measurement mode */
	strcat(saSetup,":FREQ:CENT 1E9;");	/* tune the analyzer to 1 GHz */
	strcat(saSetup,":FREQ:SPAN 1E9;");	/* Set a span of 1 GHz */
	strcat(saSetup,":FORM:DATA REAL,32;");	/* Set the ouput format to a binary 32 bit format */
	strcat(saSetup,"FORM:BORD SWAP\n");	/* set the binary byte order to SWAP (for PC) */
	//strcat(saSetup,":INIT:IMM;\n;");		/* trigger a spectrum measurement */

}

AnalizFFox::~AnalizFFox()
{
}
void AnalizFFox::Wite(int Msec)
{
		lOpc=0;
		viPrintf(FieldFox, "*OPC\n");

		while ((lOpc & 1) == 0)
	{
	  viQueryf(FieldFox, "*ESR?\n", "%d", &lOpc);
	  Sleep(Msec);
	}
}

char* AnalizFFox::PriborLoad()
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
void AnalizFFox::fieldfoxtest( int Meas,double *TData,long Number_Points_ff, long Measurement_avg_ff, long Background_avg_ff, double Start_Fq_ff, double Stop_Fq_ff)
 {
	// TODO: Before you run this code do the following:
	// * Set the maximum sizes for any array variables.
	// * If your code queries binary block data, make sure it sets the byte order of the instrument to big endian.
	// void DumpCSVFile(const char,double,int);

	Start_Fq_ff = Start_Fq_ff*1000000000;
	Stop_Fq_ff = Stop_Fq_ff*1000000000;
	ViSession rm;
	viOpenDefaultRM(&rm);
	//ViSession FieldFox;
	int data_size = Number_Points_ff;
	double *data = new double[data_size]; // allocate data_size doubles
	ViUInt16 io_prot;
	ViUInt16 intfType;
	ViString intfName= new char[50];

	status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &FieldFox);
		if (status < VI_SUCCESS)
		{
			ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		   //	return "-110";
		}


	//viOpen(rm, "TCPIP0::192.168.0.110::inst0::INSTR", VI_NULL, VI_NULL, &FieldFox);
	ViBoolean termDefaultFieldFox = VI_FALSE;
	// Determine whether the termination character should be enabled by default.
	if((VI_SUCCESS == viGetAttribute(FieldFox, VI_ATTR_RSRC_CLASS, intfName)) && (0 == strcmp("SOCKET", (ViString)intfName)))
	termDefaultFieldFox = VI_TRUE;
	else if((VI_SUCCESS == viGetAttribute(FieldFox, VI_ATTR_INTF_TYPE, &intfType)) && (intfType == VI_INTF_ASRL))
	termDefaultFieldFox = VI_TRUE;

	viSetAttribute(FieldFox,  VI_ATTR_TMO_VALUE, 5000);
	//viSetAttribute(FieldFox, VI_ATTR_TERMCHAR_EN, termDefaultFieldFox);
	//viPrintf(FieldFox,"*CLS\n"); // 'Reset status register
	//viPrintf(FieldFox,"*RST\n");
	//viPrintf(FieldFox,"*WAI\n");
	// lOpc=0;
	// Sleep(10);
	//		viPrintf(FieldFox, "*OPC\n");
	//  while (lOpc==0)
	//	{
	//
	//		Sleep(10);
	//		viQueryf(FieldFox, "*OPC?\n", "%d", &lOpc);
	//	}
	//Sleep(5000);

	Wite(100);
	viPrintf(FieldFox,":INSTrument:SELect \"%s\"\n","NA");
	viPrintf(FieldFox,"*WAI\n",0);
	Wite(100);
	//=========================================================
	//Setup screen on fieldfox for the traces and such
	// viPrintf(FieldFox,":INITiate:CONTinuous %@1d\n",0);
	Sleep(5000);

	viPrintf(FieldFox,":DISPlay:WINDow:SPLit D12H;*WAI\n");
	Wite(100);
	Sleep(200);

	//=========================================================
	viPrintf(FieldFox,":CALC:PAR1:DEF %s\n", "S11");
	Wite(100);
	viPrintf(FieldFox,":CALC:PAR2:DEF %s\n", "S21");
	Wite(100);
	Sleep(200);
	//=========================================================
	viPrintf(FieldFox,":SENSe:FREQuency:STARt %@3lf\n", Start_Fq_ff);
	Wite(100);
	viPrintf(FieldFox,":SENSe:FREQuency:STOP %@3lf\n", Stop_Fq_ff);
	Wite(100);
	viPrintf(FieldFox,":SENSe:SWEep:POINts %@1d\n", Number_Points_ff);
	Sleep(200);
	// viPrintf(FieldFox, ":SENSe:AVERage:COUNt %@1d\n", Measurement_avg_ff);
	//	 lOpc=0;
	//  while (lOpc==0)
	//	{
	//	 Sleep(10);
	//	 viPrintf(FieldFox, "*OPC\n");
	//	 Sleep(10);
	//	 viQueryf(FieldFox, "*OPC?\n", "%d", &lOpc);
	//	}
	// viPrintf(FieldFox, ":SENSe:AVERage:COUNt %@1d\n", Background_avg_ff);
	//=============================================================

	//Prepare to save CSV file
	viPrintf(FieldFox,":FORMat:DATA %s,%@1d\n", "REAL", 64);
	Wite(100);
	//viPrintf(FieldFox,":INIT:IMM;*WAI\n");  //

	//viSetAttribute(FieldFox, VI_ATTR_TERMCHAR_EN, VI_FALSE);

		switch(Meas)
	 {case 0:viPrintf(FieldFox,":CALC:PAR1:SEL\n"); break;
	  case 1:viPrintf(FieldFox,":CALC:PAR2:SEL\n"); break;
	 }
	Wite(100);

	// FieldFox sends data back as little-endian by default. "!ol" swaps from normally expected
	// big-endian to expecting little-endian.
	viQueryf(FieldFox,":CALC:DATA:FDAT?\n", "%#!olZb", &data_size, data);
	viSetAttribute(FieldFox, VI_ATTR_TERMCHAR_EN, termDefaultFieldFox);
	if (termDefaultFieldFox)
	viScanf(FieldFox, "%*c"); // Clear the termination character from the buffer.
	//Save CSV file with Data

	// FILE* pFile = fopen("e:\\myfile1.csv", "w"); // open in text mode.
	// //if( !pFile )
	// //return -1; Commented out due to return inside of void
	// fprintf(pFile,"Point,param\n");
	//
	for(int i = 0; i < data_size; ++i)
	{
	// fprintf(pFile, "%f,%f\n",i, data[i]);
	  TData[i] = data[i];
	}
	// fclose(pFile);

	delete [] data;
	delete [] intfName;
	viPrintf(FieldFox,":INITiate:CONTinuous %@1d\n",1);
	viPrintf(FieldFox,"*WAI\n");
	viClose(FieldFox);
	viClose(rm);
 }
void AnalizFFox::Reset(void)
{
		status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
		strcpy(buffer,PriborLoad());
		printf_s("\n", buffer);
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &FieldFox);
		if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
	//break;
 }


	viPrintf(FieldFox,"*CLS\n"); // 'Reset status register
	viPrintf(FieldFox,"*RST\n");
	viPrintf(FieldFox,"*WAI\n");
	Sleep(5000) ;







	viClose(FieldFox);                    // closes session
	viClose(defaultRM);             // closes default session


 }

char* AnalizFFox::Comand(AnsiString Com,int RET )
{
		status = viOpenDefaultRM(&defaultRM);
		strcpy(buffer, PriborLoad());
		status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		if (status < VI_SUCCESS)
		{
			ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
			return "-110";
		}

		strcpy(buffer,Com.c_str());
		strcat(buffer,"\n");
		viPrintf(vi, buffer);

			 switch (RET)
		{
			case 0:
			return "-";
			break;

			case 1:
					for (int i = 0; i < 100; i++)
			{
				rezult[i]=0;
			}
			viRead(vi, rezult, sizeof(rezult), &retCnt);
			return  rezult;
			break;


			default : break;
		}

	

}
long AnalizFFox::DataRet(double *Data, double *Freq, int point)
{   status = viOpenDefaultRM(&defaultRM);//Vstende5071->PriborLoad()
		 strcpy(buffer,PriborLoad());
		 printf_s("\n", buffer);
		 status = viOpen(defaultRM,(ViBuf)buffer, VI_NULL, VI_NULL, &vi);
		 if (status < VI_SUCCESS)
 {
	ShowMessage("Can't open VISA address");
	//break;
 }

	viQueryf(vi,":INST:SEL \"SA\";:INST:SEL?\n", "%d", &lOpc);


	viPrintf(vi,saSetup);


	viQueryf(vi,"*OPC?\n", "%d", &lOpc);

	//viQueryf(vi, ":TRAC1:DATA?\n","%#Zb",&lBytesRetrieved,Data);
	viPrintf(vi,":TRAC2:DATA?\n");
	viRead (vi,(ViBuf)Data,401,&lBytesRetrieved);

	viPrintf(vi, "INIT:CONT 0 \n");

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}
void AnalizFFox::GPIB_Set(AnsiString Adr, AnsiString Ip)
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
void AnalizFFox::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
char* AnalizFFox::GetGPIB()
{
	return GPIB;
}
char* AnalizFFox::GetIPlok()
{
	return ipLok;
}

AnsiString  AnalizFFox::Zapt(AnsiString str)
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
long AnalizFFox::AnSpanSet(float Fset, double SP, double BW, double RWFL) {
 AnsiString string;
 //SetMarker(0,0,0,0);

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
	string = Zapt(FloatToStr(CentrF*10E5));
	strcat(buffer, string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
	strcpy(buffer, "FREQ:SPAN "); // SP 100KHZ; Установка спан
	string = Zapt(FloatToStr(Span*10E5));
	strcat(buffer, string.c_str());
	strcat(buffer, "\n");
	 viPrintf(vi, buffer);
	strcpy(buffer, "BAND "); // RB 100HZ; Установка BW
	string = FloatToStr(RBW*10E2);
	strcat(buffer, string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
	strcpy(buffer, "DISP:WIND:TRAC:Y:RLEV "); // RL-10DBM; Установка BW
	string = FloatToStr(RL);
	strcat(buffer, string.c_str());
	strcat(buffer, "\n");
	status = viPrintf(vi, buffer);

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session
	return status;
}

double AnalizFFox::Sens(double Lin,double Fin, double SP, double BW,double Ofs){
 AnSpanSet(Fin,SP,BW, Lin);
 Sleep(300);
 MkDelta(1,false,0);
 MkrPeak(1);
 MkDelta(1,true,Ofs);
 SetMarker(true, 0, false, 100);
 Sleep(5000);
 return  0.1*floor(10*strtod(Result(1),NULL));
}

int AnalizFFox::Control(int K, int Pred, int& Com) {
	if (K >= 0 && K <= Pred) {

			Com = K;

	}
	else {
		Com = 0;
	}
}

long AnalizFFox::MkrPeak(int n) {
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

long AnalizFFox::MkDelta(int num,bool Enabl,double Del) {
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
	if (Enabl) {                                                       /* TODO : Mark delta */
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

long AnalizFFox::SetMarker(bool Del, int Delta, bool Pik, int Count) {
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
double AnalizFFox::FMark(){

 return Fmark;
}
char* AnalizFFox::Result(int n) {
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
char* AnalizFFox::CHPWRBW(double Chnl){
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

