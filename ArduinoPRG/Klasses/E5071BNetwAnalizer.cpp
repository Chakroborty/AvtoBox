//---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <vcl.h>
//#pragma hdrstop

#include "E5071BNetwAnalizer.h"
#include <math.h>

#include "visa.h"
#pragma comment(lib,"visa32.lib")
//---------------------------------------------------------------------------
	E5071B::E5071B(int Adr, char* Ip)
	{

			ControlDiap(Adr, 30, Gadr);
			//GPIB = "25";
			itoa(Gadr, GPIB, 10);
			//ipAdres = "0";
			strcpy(ipAdres, Ip);
			strcpy(ipLok, "10.29.31.25");
			Threshold = -6;//Threshold BW
			Inv = false;
			F_IN_Start = 50;
			F_IN_Stop = 210;
			F_OUT_Start = 50;
			F_OUT_Stop = 210;

			Preob = false;
			Pow = -50;
			LIM_Offset = 0;
			LIM_deltaF = 2;
			LIM_deltaL = -4;
			NumLin = 5;
			Flev[0][0] = 1;
			Flev[1][0] = 8;
			Flev[2][0] = 13;
			Flev[3][0] = 15;
			Flev[4][0] = 32;
			Flev[5][0] = 37;
			Flev[6][0] = 41;
			Flev[7][0] = 48;

			Flev[0][1] = -25;
			Flev[1][1] = -18;
			Flev[2][1] = -15;
			Flev[3][1] = -8;
			Flev[4][1] = -13;
			Flev[5][1] = -18;
			Flev[6][1] = -41;
			Flev[7][1] = -48;

			Flev[0][2] = -1;
			Flev[1][2] = -1;
			Flev[2][2] = -1;
			Flev[3][2] = -1;
			Flev[4][2] = 0;
			Flev[5][2] = 1;
			Flev[6][2] = 1;
			Flev[7][2] = 1;
	}
	E5071B::~E5071B()
	{

	}
//---------------------------------------------------------------------------

char* E5071B::GetGPIB() {

return GPIB;

}
char* E5071B::GetIPlok()
{
	return ipLok;
}

void E5071B::GPIB_Set(AnsiString Adr, AnsiString Ip) {      /* TODO -cIP ADR : добавить в метод IP */
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
void E5071B::IP_Set(AnsiString Ip)
{      /* TODO -cIP ADR : добавить в метод IP */
	Lan_GPIB = 0;
	strcpy(ipLok, Ip.c_str());
}
int E5071B::ControlDiap(int K, int Pred, int& Com) {

if (K >= 0 && K <= Pred) {
if (K != 0) {
	Com = K;
}
}
else {
Com = 1;
}
}

void  E5071B::SetLimitOc(double F0, double F1, double F2, double F3, double F4,
		double F5, double F6, double F7, double L0, double L1, double L2, double L3,
		double L4, double L5, double L6, double L7)
   {	   Flev[0][0]= F0;
		   Flev[1][0]= F1;
		   Flev[2][0]= F2;
		   Flev[3][0]= F3;
		   Flev[4][0]= F4;
		   Flev[5][0]= F5;
		   Flev[6][0]= F6;
		   Flev[7][0]= F7;

		   Flev[0][1]= L0;
		   Flev[1][1]= L1;
		   Flev[2][1]= L2;
		   Flev[3][1]= L3;
		   Flev[4][1]= L4;
		   Flev[5][1]= L5;
		   Flev[6][1]= L6;
		   Flev[7][1]= L7;
   }
void  E5071B::SetLimitProf(double P0, double P1, double P2, double P3, double P4, double P5, double P6, double P7)
   {       if (P0==1)
			{
			   Flev[0][2]= P0;
			} else {
				if (P0==-1)
			   {
				   Flev[0][2]= P0;
			   } else
			   {
					 if (P0==0)                                        /* TODO -cLIM : LIM line SET*/
				   {
					   Flev[0][2]= P0;
				   } else {
                         Flev[0][2]= 0;
				   }
			   }
		   }
		   Flev[1][2]= P1;
		   Flev[2][2]= P2;
		   Flev[3][2]= P3;
		   Flev[4][2]= P4;
		   Flev[5][2]= P5;
		   Flev[6][2]= P6;
		   Flev[7][2]= P7;

   }
void  E5071B::SetLimitzAZOR(double dF, double dL, double Lopor)    // опорный уровень в 4 поз
{
	LIM_Offset = Lopor - Flev[3][1];
	LIM_deltaF = dF;
	LIM_deltaL = dL;
}





//---------------------------------------------------------------------------
void E5071B::Marker_set(double Fm1, double Fm2, double Fm3, double Fm4, double Fm5, double Fm6, double Fm7)
{
		 if (Fm1>0.3&&Fm1<8500)
	 {
		Mark1_F = Fm1;
		Mark1 = true;
	 }
	 else
	 {
	   Mark1 = false;
	 }
//********************************************************************************
		 if (Fm2>0.3&&Fm2<8500)
	 {
		Mark2_F = Fm2;
		Mark2 = true;
	 }
	 else
	 {
	   Mark2 = false;
	 }
//********************************************************************************
		 if (Fm3>0.3&&Fm3<8500)
	 {
		Mark3_F = Fm3;
		Mark3 = true;
	 }
	 else
	 {
	   Mark3 = false;
	 }
//********************************************************************************

		 if (Fm4>0.3&&Fm4<8500)
	 {
		Mark4_F = Fm4;
		Mark4 = true;
	 }
	 else
	 {
	   Mark4 = false;
	 }
//********************************************************************************
		 if (Fm5>0.3&&Fm5<8500)
	 {
		Mark5_F = Fm5;
		Mark5 = true;
	 }
	 else
	 {
	   Mark5 = false;
	 }
//********************************************************************************
				 if (Fm6>0.3&&Fm6<8500)
	 {
		Mark6_F = Fm6;
		Mark6 = true;
	 }
	 else
	 {
	   Mark6 = false;
	 }
//********************************************************************************
				 if (Fm7>0.3&&Fm7<8500)
	 {
		Mark7_F = Fm7;
		Mark7 = true;
	 }
	 else
	 {
	   Mark7 = false;
	 }
//********************************************************************************

}
void E5071B::NumTRsSET(int NumTR)
{
	if (NumTR > 0&&NumTR < 5)
			{
				Disp_Numtr = NumTR;
			}
			else
			{
				Disp_Numtr = 1;
			}
}
void E5071B::DispleiSet(int Trase, int Par, int Form, double Div, int Pos, int Lev)
{       int TrNUM;
if (Trase > 0&&Trase < 5)
		{
			TrNUM = Trase;    //Номер трассы
		}
		else                                /* TODO -cTrase :  Установка параметров трассы и дисплея Метод */

		{
			TrNUM = 1;
		}
if (Par > 0&&Par < 4)
		{
		  Disp_par[TrNUM - 1] = Par;
		}
		else
		{
		  Disp_par[TrNUM - 1] = 1;
		}
if (Form >= 0 && Form < 10)
		{
		  Disp_form[TrNUM - 1] = Form;
		}
		else
		{
           Disp_form[TrNUM - 1] = 0;
		}
if (Pos > 0 && Pos < 16)
		{
		  Disp_pos[TrNUM - 1] = Pos;
		}
		else
		{
		  Disp_pos[TrNUM - 1] = 5;
		}

if (Div > 0 && Div < 51)
		{
		  Disp_div[TrNUM - 1] = Div;
		}
		else
		{
		  Disp_div[TrNUM - 1] = 10;
		}
if (Lev >= -150 && Lev < 100)
		{
		  Disp_Lev[TrNUM - 1] = Lev;
		}
		else
		{
		  Disp_Lev[TrNUM - 1] = 0;
		}
}
char* E5071B::IzmerenSet(int Trase,int Shag)      /* TODO -cTrase :  Можно использовать для выбора трассы с Shag = 1*/
{           char str[100]="\n";  //
		   AnsiString ansi_string = "" ;
		   ansi_string  = FloatToStr(Trase);
			   int realTR;
			 if (Trase <= Disp_Numtr) {
				realTR = Trase;
		   } else {
				return str;
		   }


					switch (Shag)
   {  case 0:
	 ansi_string  =  ":CALC1:PAR:COUN ";
	 ansi_string  =  ":CALC1:PAR:COUN ";						   //:CALC1:PAR:COUN 3
	 strcpy(str,ansi_string.c_str());
	 ansi_string  = FloatToStr(Disp_Numtr);
	 strcat(str,ansi_string.c_str());
	 break;


	  case 1:                            //:CALC1:PAR1:SEL
	 NumTrSEL = Trase-1;
	 strcpy(str,":CALC1:PAR");
	 strcat(str,ansi_string.c_str());    /* c_str()TODO -cTrase : Установка параметров трассы и дисплея и текущей тр*/

	 strcat(str,":SEL");
	 break;
	  case 2:                            //:CALC1:PAR1:DEF S21
	 strcpy(str,":CALC1:PAR");
	 strcat(str,ansi_string.c_str());
	 strcat(str,":DEF ");
	 strcat(str,ParDEF(Disp_par[Trase-1]));
	 break;
	  case 3:                            //:CALC1:FORM MLOG
	 strcpy(str,":CALC1:FORM ");
	 strcat(str,SetFormat(Disp_form[Trase - 1]));
	 break;
	  case 4:                                // :DISP:WIND1:TRAC1:Y:RLEV -5E1  on page 445
	 strcpy(str,":DISP:WIND1:TRAC");
	 strcat(str,ansi_string.c_str());
	 strcat(str,":Y:RLEV ");
	 ansi_string  = FloatToStr(Disp_Lev[Trase-1]);
	 strcat(str,ansi_string.c_str());
	 break;
	  case 5:                                //:DISP:WIND1:TRAC1:Y:RPOS 5
	 strcpy(str,":DISP:WIND1:TRAC");
	 strcat(str,ansi_string.c_str());
	 strcat(str,":Y:RPOS ");
	 ansi_string  = FloatToStr(Disp_pos[Trase-1]);
	 strcat(str,ansi_string.c_str());
	 break;
	   case 6:                                //:DISP:WIND1:Y:DIV 12
	 strcpy(str,":DISP:WIND1:TRAC");
	 strcat(str,ansi_string.c_str());
	 ansi_string  = FloatToStr(Disp_div[Trase-1]);
	 strcat(str,":Y:PDIV ");
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;


	   default : strcpy(str,":CALC1:PAR:COUN 3");break;    /* TODO -cDisp :  Format загр Izmeren*/
	}


	   return  str ;

}

char* E5071B::SetFormat(int FormNum)
   {    char str[100]="\n";

		 switch (FormNum)
		{
	 case 1:
	 strcpy(str,"MLOG\0");
	 break;
	 case 2:
	 strcpy(str,"PHAS\0");
	 break;
	 case 3:
	 strcpy(str,"SWR\0");
	 break;
	 default : strcpy(str,"MLOG");break;
		}
							  /* TODO -cDisp : Format*/
		return  str;
	}

char* E5071B::MarkerONload(int i)
   {

		   char str[100]="\n";  //


				switch (i)
   {
	  case 0:
		if (Mark1)
		{
		 strcpy(str,":CALC1:MARK1 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK1 OFF");
		 }
	 strcat(str,"\n");
	 break;               //:SENS1:OFFS:PORT2:STAR 8.4E7



   case 1:
		if (Mark2)
		{
		 strcpy(str,":CALC1:MARK2 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK2 OFF");
		 }
	 strcat(str,"\n");
	 break;               //:SENS1:OFFS:PORT2:STAR 8.4E7
	  case 2:
		if (Mark3)
		{
		 strcpy(str,":CALC1:MARK3 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK3 OFF");
		 }
	 strcat(str,"\n");
	 break;


	 case 3:
		if (Mark4)
		{
		 strcpy(str,":CALC1:MARK4 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK4 OFF");
		 }
	 strcat(str,"\n");
	 break;
	 case 4:
		if (Mark5)
		{
		 strcpy(str,":CALC1:MARK5 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK5 OFF");
		 }
	 strcat(str,"\n");
	 break;
	  case 5:
		if (Mark6)
		{
		 strcpy(str,":CALC1:MARK6 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK6 OFF");
		 }
	 strcat(str,"\n");
	 break;
	  case 6:
		if (Mark7)
		{
		 strcpy(str,":CALC1:MARK7 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK7 OFF");
		 }
	 strcat(str,"\n");
	 break;
	 default : 	if (Mark1)
		{
		 strcpy(str,":CALC1:MARK1 ON");
		 /*
		   ansi_string  = FloatToStr(Pow);
		   strcat(str,ansi_string.c_str());at(s  */
		 }
		 else
		 {
		 strcpy(str,":CALC1:MARK1 OFF");
		 }
	 strcat(str,"\n");break;

   }

		 return  str ;
   }
char* E5071B::MarkerFload(int i)
   {

			   char str[100]="\n";  //
			   AnsiString ansi_string ;

					switch (i)
	   {
		  case 0:
			if (Mark1)
			{
			 strcpy(str,":CALC1:MARK1:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark1_F)*1E6);
			 strcat(str,ansi_string.c_str());
					 }
			 else
			 {
			 strcpy(str,":CALC1:MARK1 OFF");
			 }
		 strcat(str,"\n");
		 break;               //:SENS1:OFFS:PORT2:STAR 8.4E7



	   case 1:
			if (Mark2)
			{
			 strcpy(str,":CALC1:MARK2:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark2_F)*1E6);
			 strcat(str,ansi_string.c_str());
			 }
			 else
			 {
			 strcpy(str,":CALC1:MARK2 OFF");
			 }
		 strcat(str,"\n");
		 break;               //:SENS1:OFFS:PORT2:STAR 8.4E7
		  case 2:
			if (Mark3)
			{
			 strcpy(str,":CALC1:MARK3:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark3_F)*1E6);
			 strcat(str,ansi_string.c_str());
			 }
			 else
			 {
			 strcpy(str,":CALC1:MARK3 OFF");
			 }
		 strcat(str,"\n");
		 break;


		 case 3:
			if (Mark4)
			{
			 strcpy(str,":CALC1:MARK4:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark4_F)*1E6);
			 strcat(str,ansi_string.c_str());
			 }
			 else
			 {
			 strcpy(str,":CALC1:MARK4 OFF");
			 }
		 strcat(str,"\n");
		 break;
		 case 4:
			if (Mark5)
			{
			 strcpy(str,":CALC1:MARK5:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark5_F)*1E6);
			 strcat(str,ansi_string.c_str());
			 }
			 else
			 {
			 strcpy(str,":CALC1:MARK5 OFF");
			 }
		 strcat(str,"\n");
		 break;
		  case 5:
			if (Mark6)
			{
			 strcpy(str,":CALC1:MARK6:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark6_F)*1E6);
			 strcat(str,ansi_string.c_str());
			 }
			 else
			 {
			 strcpy(str,":CALC1:MARK6 OFF");
			 }
		 strcat(str,"\n");
		 break;
		 case 6:
			if (Mark7)
			{
			 strcpy(str,":CALC1:MARK7:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark7_F)*1E6);
			 strcat(str,ansi_string.c_str());
			 }
			 else
			 {
			 strcpy(str,":CALC1:MARK7 OFF");
			 }
		 strcat(str,"\n");
		 break;
		 default : 	if (Mark1)
			{
			  strcpy(str,":CALC1:MARK1:X ");   //:CALC1:MARK1:X 1E9
			 ansi_string  = FloatToStr(RascetFout(Mark1_F)*1E6);
			 strcat(str,ansi_string.c_str());
			 }
			 else
			 {
			 strcpy(str,":CALC1:MARK1 OFF");
			 }
		 strcat(str,"\n");break;

	   }

		 return  str ;
   }
//*****************Limit Line***************************

AnsiString  E5071B::Zapt(AnsiString str)
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

char* E5071B::LoadLimit(int i,int numL,double G)
{      char str[800]="\n";  //
	   AnsiString ansi_string ;

				switch (i)
   {
	  case 0:
		if (numL>0) {
		 strcpy(str,":CALC1:LIM:DATA ");   //:CALC1:LIM:DATA 2,1,8E7,4E7,-20,-25,1,4E7,35E6,-20,-45
			 ansi_string  = FloatToStr(numL*2);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",2,");
			 ansi_string  = FloatToStr((RascetFout(Flev[0][0])+Flev[0][2]*LIM_deltaF/2)*1E6);
			 FloatToStr((G-Flev[0][0]+Flev[0][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
        	 strcat(str,ansi_string.c_str());
        	 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[1][0])+Flev[1][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[0][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[1][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());

	}      if (numL>1) {

			 strcat(str,",2,");
			 ansi_string  = FloatToStr((RascetFout(Flev[1][0])+Flev[1][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[2][0])+Flev[2][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[1][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[2][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			// strcat(str,"\n");
	}            if (numL>2) {

			 strcat(str,",2,");
			 ansi_string  = FloatToStr((RascetFout(Flev[2][0])+Flev[2][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[3][0])+Flev[3][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[2][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[3][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			// strcat(str,"\n");
	}              if (numL>3) {

			 strcat(str,",2,");
			 ansi_string  = FloatToStr((RascetFout(Flev[3][0])+Flev[3][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[4][0])+Flev[4][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[3][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[4][1]+LIM_deltaL/2+LIM_Offset);
			ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			// strcat(str,"\n");
	}                if (numL>4) {

			 strcat(str,",2,");
			 ansi_string  = FloatToStr((RascetFout(Flev[4][0])+Flev[4][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[5][0])+Flev[5][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[4][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[5][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());

	}                   if (numL>5) {

			 strcat(str,",2,");
			 ansi_string  = FloatToStr((RascetFout(Flev[5][0])+Flev[5][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[6][0])+Flev[6][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[5][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[6][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());

	  }					 if (numL>6) {

			 strcat(str,",2,");
			 ansi_string  = FloatToStr((RascetFout(Flev[6][0])+Flev[6][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[7][0])+Flev[7][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[6][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[7][1]+LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());




	}
	// break;



		 if (numL>0) {
/*
		 strcpy(str,":CALC1:LIM:DATA ");   //:CALC1:LIM:DATA 2,1,8E7,4E7,-20,-25,1,4E7,35E6,-20,-45
				 ansi_string  = FloatToStr(numL);
				 strcat(str,ansi_string.c_str());
*/
			 strcat(str,",1,");
			 ansi_string  = FloatToStr((RascetFout(Flev[0][0])-Flev[0][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[1][0])-Flev[1][2]*LIM_deltaF/2)*1E6);   /* TODO -cLIM : LIM line */
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[0][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[1][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());

	}      if (numL>1) {

			 strcat(str,",1,");
			 ansi_string  = FloatToStr((RascetFout(Flev[1][0])-Flev[1][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[2][0])-Flev[2][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[1][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[2][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			// strcat(str,"\n");
	}            if (numL>2) {
		 //strcpy(str,":CALC1:LIM:DATA ");   //:CALC1:LIM:DATA 2,1,8E7,4E7,-20,-25,1,4E7,35E6,-20,-45
		 //	 ansi_string  = FloatToStr(numL);
		 //	 strcat(str,ansi_string.c_str());
			 strcat(str,",1,");
			 ansi_string  = FloatToStr((RascetFout(Flev[2][0])-Flev[2][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[3][0])-Flev[3][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[2][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[3][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			// strcat(str,"\n");
	}              if (numL>3) {
		 //strcpy(str,":CALC1:LIM:DATA ");   //:CALC1:LIM:DATA 2,1,8E7,4E7,-20,-25,1,4E7,35E6,-20,-45
		 //	 ansi_string  = FloatToStr(numL);
		 //	 strcat(str,ansi_string.c_str());
			 strcat(str,",1,");
			 ansi_string  = FloatToStr((RascetFout(Flev[3][0])-Flev[3][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[4][0])-Flev[4][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[3][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[4][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			// strcat(str,"\n");
	}                if (numL>4) {

			 strcat(str,",1,");
			 ansi_string  = FloatToStr((RascetFout(Flev[4][0])-Flev[4][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[5][0])-Flev[5][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[4][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[5][1]-LIM_deltaL/2+LIM_Offset);
			ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			// strcat(str,"\n");
	}                   if (numL>5) {

			 strcat(str,",1,");
			 ansi_string  = FloatToStr((RascetFout(Flev[5][0])-Flev[5][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[6][0])-Flev[6][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[5][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[6][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());

	}                    if (numL>6) {

			 strcat(str,",1,");
			 ansi_string  = FloatToStr((RascetFout(Flev[6][0])-Flev[6][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr((RascetFout(Flev[7][0])-Flev[7][2]*LIM_deltaF/2)*1E6);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[6][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());
			 strcat(str,",");
			 ansi_string  = FloatToStr(Flev[7][1]-LIM_deltaL/2+LIM_Offset);
			 ansi_string =  Zapt(ansi_string);
			 strcat(str,ansi_string.c_str());

	}
	   break;
	case 1:
	 break;

	   default :
		 strcpy(str,":CALC1:MARK1:X ");   //:CALC1:MARK1:X 1E9
		 ansi_string  = FloatToStr(Mark1_F*1E6);
		 strcat(str,ansi_string.c_str());

	 strcat(str,"\n");break;

   }

		 return  str ;


}
//*****************Limit Line***************************
//---------------------------------------------------------------------------
 void E5071B::F_max (double &F_in, double &F_out, bool uvelic)
 {
  if (F_out > 8500)
	{
	 if (uvelic)
		{
			F_in = F_in + F_out - 8500;

		}
	   else
		{
			F_in = F_in - F_out + 8500;
		}
		F_out = 8500;
	}
	   F_diapazon(F_in);
 }
//---------------------------------------------------------------------------
 void E5071B::F_min (double &F_in, double &F_out, bool uvelic)
 {
	 if (F_out < 0.3)
	{
	 if (uvelic)
		{
			F_in = F_in + F_out - 0.3;

		}
	   else
		{
			F_in = F_in - F_out + 0.3;
		}
		F_out = 0.3;
	}
	   F_diapazon(F_in);
 }
//---------------------------------------------------------------------------
double E5071B::F_diapazon(double val)
{       double  F;
		if (val > 0.3 && val < 8500)
		{
			 F = val;
		}
		if (val > 8500)
		{
			 F = 8500;
		}
	  if (val < 0.3)
		{
			 F = 0.3;
		}
		return F;
}
void E5071B::StartStop_set(double Fin_centr, double Fout_centr, double SSpan, bool Reverse,double PowOUT)
 {   In_NEsim_perenos( Fin_centr-SSpan/2, Fin_centr+SSpan/2,Fin_centr, Fout_centr, Reverse, PowOUT);
 }

long E5071B::SetDiapazonBW(int Meas,double Fstart,double Fstop,bool Revers){
	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	 AnsiString ansi_string = ":CALC" + IntToStr(Meas)+":MARK:FUNC:DOM ON";//":CALC1:MARK:FUNC:DOM ON"
     strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
		viPrintf(vi, buffer);

if (!Revers) {
		ansi_string = ":CALC" + IntToStr(Meas)+":MARK:FUNC:DOM:STAR " + FloatToStr(RascetFout(Fstart)*1E6) +"\n";    // ":CALC1:MARK:FUNC:DOM:STAR 1.7E9"
		strcpy(buffer, ansi_string.c_str());
		strcat(buffer, "\n");
		viPrintf(vi, buffer);
		ansi_string = ":CALC" + IntToStr(Meas)+":MARK:FUNC:DOM:STOP " + FloatToStr(RascetFout(Fstop)*1E6) +"\n";    // ":CALC1:MARK:FUNC:DOM:STAR 1.7E9"
		strcpy(buffer, ansi_string.c_str());
		strcat(buffer, "\n");
		viPrintf(vi, buffer);
} else { ansi_string = ":CALC" + IntToStr(Meas)+":MARK:FUNC:DOM:STAR " + FloatToStr(RascetFout(Fstop)*1E6) +"\n";    // ":CALC1:MARK:FUNC:DOM:STAR 1.7E9"
		strcpy(buffer, ansi_string.c_str());
		strcat(buffer, "\n");
		viPrintf(vi, buffer);
		ansi_string = ":CALC" + IntToStr(Meas)+":MARK:FUNC:DOM:STOP " + FloatToStr(RascetFout(Fstart)*1E6) +"\n";    // ":CALC1:MARK:FUNC:DOM:STAR 1.7E9"
		strcpy(buffer, ansi_string.c_str());
		strcat(buffer, "\n");
		viPrintf(vi, buffer);

}




   viClose(vi);                    // closes session
   viClose(defaultRM);             // closes default session

	 return status;
}

double E5071B::Neravnom(int Meas,int NumMark1,int NumMark2,double Fstart,double Fstop,bool Revers)
{
	 /* TODO -cмаркеры : Неравномерность */
   SetDiapazonBW(Meas,Fstart,Fstop,Revers);
   Sleep(100);
   SetMark(Meas,NumMark1,1);//MIN
   SetMark(Meas,NumMark2,0);//MAX
   Sleep(100);
   return CalkMarkD( Meas, NumMark2) - CalkMarkD( Meas, NumMark1);

}


 double E5071B::RascetFout(double F)
{   double Fout;

   if (Disp_par[NumTrSEL]==1||Disp_par[NumTrSEL]==2)
  {
          if (Preob)
         	   {
                     if (Inv)
         					{Fout = F_Get - F;
         					}
							else
         					{	if (PereVverx)
         							{Fout = F_Get + F;
         							}
         						else
         							{Fout =  F - F_Get;
         							}
         					}

         		} else
         		{
				 Fout = F;
				}
  }
 else
  {

  }
		return Fout;
}
void E5071B::In_NEsim_perenos(double Fin_start, double Fin_stop, double Fnastr, double Fpc, bool inv_Sp,double PowOUT)
 {  if (PowOUT<-20)
		{
			Pow = PowOUT;
		}
		else
		{
			Pow = -60;
		}
		F_IN_Start = F_diapazon(Fin_start);
		F_IN_Stop = F_diapazon(Fin_stop);
		F_IN_Centr = F_diapazon(Fnastr);
		F_OUT_Centr = F_diapazon(Fpc);
		Inv = inv_Sp;
		Preob = true;

				if (Inv)
		{F_Get = F_OUT_Centr + F_IN_Centr;//   F_IN_Centr   F_OUT_Centr  F_Get
		 F_OUT_Start = F_Get - F_IN_Start;
		 F_OUT_Stop = F_Get - F_IN_Stop;
		}
		else
		{	if (F_OUT_Centr > F_IN_Centr)
				{PereVverx = true;
				 F_Get = F_OUT_Centr - F_IN_Centr;//   F_IN_Centr   F_Get   F_OUT_Centr
				 F_OUT_Start = F_Get + F_IN_Start;
				 F_OUT_Stop = F_Get + F_IN_Stop;
				 F_max(F_IN_Start, F_OUT_Start, false);
				 F_max(F_IN_Stop, F_OUT_Stop, false);
				}
			else
				{PereVverx = false;
				 F_Get =  F_IN_Centr - F_OUT_Centr;//   F_OUT_Centr   F_Get   F_IN_Centr
				 F_OUT_Start =  F_IN_Start - F_Get;
				 F_OUT_Stop = F_IN_Stop - F_Get;
				}


		}
	/* if (F_OUT_Centr > F_IN_Centr)
	 {
			if (Inv)
					{  F_Get = F_OUT_Centr + F_IN_Centr;//   F_IN_Centr   F_OUT_Centr  F_Get

					   F_OUT_Start = F_Get - F_IN_Start;
					   F_OUT_Stop = F_Get - F_IN_Stop;

					}
					else
					{
					   F_Get = F_OUT_Centr - F_IN_Centr;//   F_IN_Centr   F_Get   F_OUT_Centr
					   F_OUT_Start = F_Get + F_IN_Start;
					   F_OUT_Stop = F_Get + F_IN_Stop;
					   F_max(F_IN_Start, F_OUT_Start, false);
					   F_max(F_IN_Stop, F_OUT_Stop, false);
					}

	}
	else
	{      if (Inv)
					{  F_Get =  F_IN_Centr + F_OUT_Centr;//   F_OUT_Centr   F_IN_Centr  F_Get

					   F_OUT_Start = F_Get - F_IN_Start;
					   F_OUT_Stop = F_Get - F_IN_Stop;

					}
					else
					{
					   F_Get =  F_IN_Centr - F_OUT_Centr;//   F_OUT_Centr   F_Get   F_IN_Centr


					   F_OUT_Start =  F_IN_Start - F_Get;
					   F_OUT_Stop = F_IN_Stop - F_Get;
					}

    } */
 }
void E5071B::In_No_perenos (double Fin_start, double Fin_stop,  double PowOUT)
 {   if (PowOUT<-20)
		{
			Pow = PowOUT;
		}
		else
		{
			Pow = -60;
        }
		F_IN_Start = F_diapazon(Fin_start);
		F_IN_Stop = F_diapazon(Fin_stop);


		Preob = false;

 }
double E5071B::GetF_IN_Start(void)
 {
	 return F_IN_Start;
 }
double E5071B::GetF_IN_Stop(void)
   {
	 return F_IN_Stop;
 }
double E5071B::GetF_OUT_Start(void)
   {
	 return F_OUT_Start;
 }
double E5071B::GetF_OUT_Stop(void)
 {
	 return F_OUT_Stop;
 }
double E5071B::GetF_Get(void)
{
	 return F_Get;
}
//---------------------------------------------------------------------------
char*  E5071B::ParSEL(int NumPAR)
{    char str[100]="\n";
	 AnsiString ansi_string ;
	 strcpy(str,":CALC1:PAR");  //:CALC1:PAR2:SEL
	 ansi_string  = FloatToStr(NumPAR);
	 strcat(str,ansi_string.c_str());
	 strcat(str,":SEL");
	// strcat(str,"\n");
	 return  str ;
}
char*  E5071B::CalkMark(int NumMARK)
{    char str[100]="\n";
	 AnsiString ansi_string ;
	 strcpy(str,":CALC1:MARK");  //:CALC1:MARK1:Y?
	 ansi_string  = FloatToStr(NumMARK);
	 strcat(str,ansi_string.c_str());
	 strcat(str,":Y?");
	// strcat(str,"\n");
	 return  str ;
}

double  E5071B::CalkMarkD(int Meas,int NumMARK){
 	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}

AnsiString ansi_string  = ":CALC"+ IntToStr(Meas) +":MARK"+IntToStr(NumMARK)+":Y?";
	strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	int bufLength = sizeof(rezult); //
	 status =	viQueryf(vi, buffer, "%#t", &bufLength, rezult);

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session

	 return 0.01*floor(100*strtod(rezult,NULL));
 }

long E5071B::SetMark(int Meas,int NumMark,int Tape){




	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
ansi_string = ":CALC"+IntToStr(Meas)+":MARK"+IntToStr(NumMark)+":ACT";  //      :CALC1:MARK1:ACT
	strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);


ansi_string = ":CALC"+IntToStr(Meas)+":MARK"+IntToStr(NumMark)+":FUNC:TYPE ";    //":CALC1:MARK1:FUNC:TYPE PEAK"
		 switch (Tape)
		{
	 case 0:
	 ansi_string = ansi_string + "MAX\n";

	 break;
	 case 1:
	 ansi_string = ansi_string + "MIN\n";

	 break;
	 case 2:
	 ansi_string = ansi_string + "PEAK\n";
	 break;
	 case 3:
	 ansi_string = ":CALC"+IntToStr(Meas)+":MARK"+IntToStr(NumMark)+":X 7E7\n";
	 break;
	 case 4:
	 ansi_string = ansi_string + "TARG\n";
	 break;

	 default : ansi_string = ansi_string + "PEAK\n";break;
		}

	strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
	ansi_string = ":CALC"+IntToStr(Meas)+":MARK"+IntToStr(NumMark)+":FUNC:EXEC";							//:CALC1:MARK1:FUNC:EXEC
    strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);


	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session

	 return status;

}


double E5071B::CalkMarkBW(int Meas,int NumMARK){
	Sleep(1500);
   //	SetMark(Meas,NumMARK,0);

	status = viOpenDefaultRM(&defaultRM);
	strcpy(buffer, PriborLoad());
	status = viOpen(defaultRM, (ViBuf)buffer, VI_NULL, VI_NULL, &vi);
	if (status < VI_SUCCESS) {
		ShowMessage("Адрес TCPIP0::" + (AnsiString)ipAdres + "::gpib0," +
			(AnsiString)GPIB + " невозможно открыть."); //
		return status;
	}
	    /*
         strcpy(buffer,MarkerFload(NumMARK-1));
					  strcat(buffer,"\n");
					  viPrintf(vi, buffer);
	*/

	Sleep(500);
	ansi_string  = ":CALC"+ IntToStr(Meas) +":MARK:BWID ON";// ":CALC1:MARK:BWID ON"
	strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
	ansi_string  = ":CALC"+ IntToStr(Meas) +":MARK"+IntToStr(NumMARK)+":FUNC:TYPE ATAR";//:CALC1:MARK1:FUNC:TRAC ON
	strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);
	ansi_string  = ":CALC"+ IntToStr(Meas) +":MARK"+IntToStr(NumMARK)+":BWID:THR " +FloatToStr(Threshold); //":BWID:THR "  :CALC1:MARK1:BWID:THR
	strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	viPrintf(vi, buffer);

	ansi_string  = ":CALC"+ IntToStr(Meas) +":MARK"+IntToStr(NumMARK)+":BWID:DATA?"; //":CALC1:MARK1:BWID:DATA?

	strcpy(buffer, ansi_string.c_str());
	strcat(buffer, "\n");
	int bufLength = sizeof(rezult); //
	status = viQueryf(vi, buffer, "%#t", &bufLength, rezult);

	viClose(vi);                    // closes session
	viClose(defaultRM);             // closes default session

	Bwid = RazborStr (1, rezult);

		if (Bwid>1E5) {
		Bwid = 0.01*floor(100*Bwid/1E6);
    } else {
	   Bwid = 0.01*floor(100*Bwid/1E3);
	}
	Cent = RazborStr (2, rezult);
	Cent = 0.1*floor(10*Cent/1E6);
	Q    = RazborStr (2, rezult);
	Loss = RazborStr (2, rezult);
	Loss = 0.1*floor(10*Loss);
	//SetMark(Meas,NumMARK,4);

	 return Bwid;
 }

double E5071B::RazborStr (int poz, char* str)
{     char* St;
      int i;
for (i = 1; i < poz; i++) {
St = "0";
St = strstr(str,",");
if (St==NULL) {
	return -100;
}
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

char* E5071B::PriborSET(int i)
   {

		   char str[100]="\n";  //
		   AnsiString ansi_string ;

				switch (i)
   { case 0:
	 strcpy(str,":INIT1:CONT ON");
	  strcat(str,"\n");
	 break;



	 case 1:
	 strcpy(str,":SOUR1:POW:PORT1 ");
	 ansi_string  = FloatToStr(Pow);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;               //:SENS1:OFFS:PORT2:STAR 8.4E7



	 case 2:
	 strcpy(str,":CALC1:PAR1:DEF S21");
	 strcat(str,"\n");
	 break;               //:SENS1:OFFS:PORT2:STAR 8.4E7
	 case 3:
	 if (Preob)
	 {
	  strcpy(str,":SENS1:OFFS ON");
	 }
	 else
	 {
	   strcpy(str,":SENS1:OFFS OFF");
	 }
	 strcat(str,"\n");
	 break;
	 case 4:
	 strcpy(str,":SENS1:FREQ:STAR ");               //:SENS1:OFFS:PORT2:STAR 8.4E7
	 ansi_string  = FloatToStr(F_IN_Start*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 5:
	 strcpy(str,":SENS1:FREQ:STOP ");               //:SENS1:OFFS:PORT2:STAR 8.4E7
	 ansi_string  = FloatToStr(F_IN_Stop*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 6:
	 strcpy(str,":SENS1:OFFS:PORT1:STAR ");         //:SENS1:OFFS:PORT2:STAR 8.4E7
	 ansi_string  = FloatToStr(F_IN_Start*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 7:
	strcpy(str,":SENS1:OFFS:PORT1:STOP ");// strcpy(str,":SENS1:FREQ:STAR ");               :SENS1:OFFS:PORT2:STAR 8.4E7 :SENS1:FREQ:STAR 100E6"  старт
	ansi_string  = FloatToStr(F_IN_Stop*1E6);// ansi_string  = FloatToStr(F_IN_Start*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 8:
	 strcpy(str,":SENS1:OFFS:PORT1:STOP ");          //:SENS1:OFFS:PORT2:STAR 8.4E7
	 ansi_string  = FloatToStr(F_IN_Stop*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 9:
	 strcpy(str,":SENS1:OFFS:PORT1:STAR ");//strcpy(str,":SENS1:FREQ:STOP ");                // ":SENS1:FREQ:STOP 100E6"
	 ansi_string  = FloatToStr(F_IN_Start*1E6);//ansi_string  = FloatToStr(F_IN_Stop*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 10:
	 strcpy(str,":SENS1:OFFS:PORT2:STAR ");               //:SENS1:OFFS:PORT2:STAR 8.4E7
	 ansi_string  = FloatToStr(F_OUT_Start*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 11:
	 strcpy(str,":SENS1:OFFS:PORT2:STOP ");               //:SENS1:OFFS:PORT2:STAR 8.4E7
	 ansi_string  = FloatToStr(F_OUT_Stop*1E6);
	 strcat(str,ansi_string.c_str());
	 strcat(str,"\n");
	 break;

	 case 12:
	 strcpy(str,":CALC1:LIM:DISP ON");               //:CALC1:LIM:DISP ON

	 break;

	 default : strcpy(str,":INIT1:CONT ON");               //:SENS1:OFFS:PORT2:STAR 8.4E7

	 strcat(str,"\n");break;

   }

		 return  str ;
   }

char* E5071B::PriborLoad()
	{      char SERtr[100]="/n";  //
			switch (Lan_GPIB)
	   {
		case 0:
			strcpy(SERtr,"TCPIP0::");
			strcat(SERtr, ipLok);
			strcat(SERtr, "::inst0::INSTR");
		break;
		case 1:
			strcpy(SERtr,"TCPIP0::");  //"TCPIP0::" + textBox5->Text + "::gpib0," + textBox2->Text + "::INSTR";
			strcat(SERtr,ipAdres);
			strcat(SERtr,"::gpib0,");
			strcat(SERtr,GPIB);
			strcat(SERtr,"::INSTR");
		break;
	}
		return  SERtr ;
}

char* E5071B::ParDEF(int DefNum)
{      char str[100]="\n";


		 switch (DefNum)
		{
	 case 1:
	 strcpy(str,"S21"); /* TODO -cTrase : Установка параметров трассы и дисплея */

	 break;
	 case 2:
	 strcpy(str,"S22");
	 break;
	 case 3:
	 strcpy(str,"S11");
	 break;
	 case 4:
	 strcpy(str,"S12");
	 break;


	 default : strcpy(str,"S21");break;
		}
							  /* TODO -cDisp : Format DEF*/
		return  str;

}
//---------------------------------------------------------------------------
#pragma package(smart_init)
