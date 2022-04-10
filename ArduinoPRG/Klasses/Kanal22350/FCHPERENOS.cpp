//---------------------------------------------------------------------------

#pragma hdrstop

#include "FCHPERENOS.h"
//---------------------------------------------------------------------------
FCHP::FCHP()
{//CHANGED: ТОК LMX @LMX (0)
//PLMX2594 = new LMX2594(8000,60,28,100);
PLMX2594 = new LMX2594(8000,1,28,100);
MXUXM15 = new UXM15();
MXUXM20 = new UXM20();
UPR1 = 0;
UPR2 = 1;
FINE = 0;
TL = 0;
TU = 1;

//0 9	1000	46	-1	5	8214,285714	2	4107,142857	15,6641604	178,5714286	+ 1 65
//1 50	1000	46	-1	6	9517,241379	2	4758,62069	21,04032729	206,8965517	+ 2 61
//2 96	1000	120	-1	6	10909,09091	2	5454,545455	16,04278075	90,90909091	+ 4 152
//3 145	1000	102	-1	7	12310,34483	2	6155,172414	14,31911163	120,6896552	+ 5 118
//4 187	1000	87	-1	8	13514,56311	2	6757,281553	11,94921583	155,3398058	+ 6 93
//5 217	1000	146	-1	8	14419,75309	2	7209,876543	19,03911944	98,7654321	+ 7 113
//6 247	1000	56	-1	9	7753,846154	1	7753,846154	18,88111888	138,4615385	+ 1 102

//FIXME: SETPR @PRESET (0)
FNUM[0].NPLL = 40 ; FNUM[0].SUM = -1; FNUM[0].uxm15p = 5; FNUM[0].FVCO = 8000.0;      FNUM[0].OUTDIV = 2; FNUM[0].VCO = 1; FNUM[0].CAP = 101; FNUM[0].FOUT = 4000.0;
FNUM[1].NPLL = 108; FNUM[1].SUM = -1; FNUM[1].uxm15p = 6; FNUM[1].FVCO = 10800.0;     FNUM[1].OUTDIV = 2; FNUM[1].VCO = 3; FNUM[1].CAP = 32;  FNUM[1].FOUT = 5400.0;
FNUM[2].NPLL = 90;  FNUM[2].SUM = -1; FNUM[2].uxm15p = 9; FNUM[2].FVCO = 15000.0;     FNUM[2].OUTDIV = 2; FNUM[2].VCO = 7; FNUM[2].CAP = 27;  FNUM[2].FOUT = 7500.0;


FNUM[3].NPLL = 46;  FNUM[3].SUM = -1;FNUM[3].uxm15p = 5;FNUM[3].FVCO = 8214.285714;	FNUM[3].OUTDIV = 2;	FNUM[3].VCO = 1;FNUM[3].CAP = 65; FNUM[3].FOUT = 4107.142857;
FNUM[4].NPLL = 46;  FNUM[4].SUM = -1;FNUM[4].uxm15p = 6;FNUM[4].FVCO = 9517.241379;	FNUM[4].OUTDIV = 2; FNUM[4].VCO = 2;FNUM[4].CAP = 61; FNUM[4].FOUT = 4758.62069;
FNUM[5].NPLL = 120;	FNUM[5].SUM = -1;FNUM[5].uxm15p = 6;FNUM[5].FVCO = 10909.09091;	FNUM[5].OUTDIV = 2;	FNUM[5].VCO = 4;FNUM[5].CAP = 152;FNUM[5].FOUT = 5454.545455;
FNUM[6].NPLL = 102;	FNUM[6].SUM = -1;FNUM[6].uxm15p = 7;FNUM[6].FVCO = 12310.34483;	FNUM[6].OUTDIV = 2;	FNUM[6].VCO = 5;FNUM[6].CAP = 118;FNUM[6].FOUT = 6155.172414;
FNUM[7].NPLL = 87;  FNUM[7].SUM = -1;FNUM[7].uxm15p = 8;FNUM[7].FVCO = 13514.56311;	FNUM[7].OUTDIV = 2;	FNUM[7].VCO = 6;FNUM[7].CAP = 93; FNUM[7].FOUT = 6757.281553;
FNUM[8].NPLL = 146;	FNUM[8].SUM = -1;FNUM[8].uxm15p = 8;FNUM[8].FVCO = 14419.75309;	FNUM[8].OUTDIV = 2;	FNUM[8].VCO = 7;FNUM[8].CAP = 113;FNUM[8].FOUT = 7209.876543;
FNUM[9].NPLL = 56;  FNUM[9].SUM = -1;FNUM[9].uxm15p = 9;FNUM[9].FVCO = 7753.846154;	FNUM[9].OUTDIV = 1;	FNUM[9].VCO = 1;FNUM[9].CAP = 128;FNUM[9].FOUT = 7753.846154;




}
FCHP::~FCHP()
{

}
int FCHP::SETUMX15(int NUM)
{
	PUXM15 = MXUXM15->SETUXM15(NUM);
return PUXM15;
}
int FCHP::SETUMX20(int NUM)
{
 	PUXM20 = MXUXM20->SETUXM20(NUM);
return PUXM20;
}
void FCHP::SETFINE(int ZN)
{
	FINE = ZN;
}
void FCHP::SETAUTO(int ZL,int ZU)
{
	switch (ZL)
	{
	case 0:  TL = 0;  break;
	//case 1:  TL = 2;  break;
	default: TL = 2;   break;
	}


	switch (ZU)
	{
	case 0:  TU = 0;  break;
	//case 1:  TU = 1;  break;
	default: TU = 1;   break;
	}

}

/*

	  #####   #######  ######            #######
	 ##   ##  ##         ##              ##
	 ##       ##         ##              ##
	  #####   #####      ##              #####
	      ##  ##         ##              ##
	 ##   ##  ##         ##              ##
	  #####   #######    ##              ##

	                            #######
*/

void FCHP::SETF(int NUM)
{
 /**
	TODO: Установка ПРЕСЕТ ФЧ @Установка (0)
	- полярность
	- Second todo item
 */
	SETUMX15(FNUM[NUM].uxm15p);
	PLMX2594->VCO_SEL_FORCE(1);//20
	PLMX2594->VCO_CAPCTRL_FORCE(1);//8
	PLMX2594->VCO_SEL(FNUM[NUM].VCO);//20
	PLMX2594->VCO_CAPCTRL(FNUM[NUM].CAP+FINE);//19
	PLMX2594->NSET(FNUM[NUM].NPLL);//34 36

	switch (FNUM[NUM].OUTDIV)
	{
	case 1:
			PLMX2594->OUTAMUX(1);//45
			PLMX2594->OUTBMUX(1);//46
	break;//R75[10:6]

	case 2:	PLMX2594->CHANDiV(0);//R75[10:6]
			PLMX2594->OUTAMUX(0);//45
			PLMX2594->OUTBMUX(0);//46
	break;
	default:
			PLMX2594->OUTAMUX(1);//45
			PLMX2594->OUTBMUX(1);//46
	break;
	}
}

void FCHP::SETDF(int DXM15,int POL, int LOOP, int NOUT, int NPLL, int CAP, int VCO)
{
	SETUMX15(DXM15);
	//PLMX2594->Default();
	//PLMX2594->SetFreq();
//TODO: Установка Перем. ФЧ @Установка (0)

		if(POL>0/* condition */)
	{
		UPR1 = 1;
	}
		else
	{
		UPR1 = 0;
	}

	UPR2 = LOOP;
	PLMX2594->VCO_SEL_FORCE(1);//20
	PLMX2594->VCO_CAPCTRL_FORCE(1);//8

	switch (NOUT)
	{
	case 1:
			PLMX2594->OUTAMUX(1);//45
			PLMX2594->OUTBMUX(1);//46
	  break;//R75[10:6]

	case 2:	PLMX2594->CHANDiV(0);//R75[10:6]
			PLMX2594->OUTAMUX(0);//45
			PLMX2594->OUTBMUX(0);//46
	break;
	default:
			PLMX2594->OUTAMUX(1);//45
			PLMX2594->OUTBMUX(1);//46
   	break;
	}
	PLMX2594->MoUTLD(1);
	PLMX2594->NSET(NPLL);//34 36
	PLMX2594->FRSET(0);//42 43
	PLMX2594->VCO_CAPCTRL(CAP+FINE);//19
	PLMX2594->VCO_SEL(VCO);//20
	PLMX2594->VCO_SEL_FORCE(1);
	PLMX2594->VCO_CAPCTRL_FORCE(1);
}
/*
	##        #######     ###    ########          ########
	##       ##     ##   ## ##   ##     ##         ##
	##       ##     ##  ##   ##  ##     ##         ##
	##       ##     ## ##     ## ##     ##         ######
	##       ##     ## ######### ##     ##         ##
	##       ##     ## ##     ## ##     ##         ##
	########  #######  ##     ## ########  ####### ##
*/

long FCHP::LOAD_F(int NUM)
{   long  SW_SW;
	// 	switch (NUM)
	// {
	// case 0: PLMX2594->RegLoadLMX2594(8 );   break;
	// case 1: PLMX2594->RegLoadLMX2594(19);   break;
	// case 2: PLMX2594->RegLoadLMX2594(20);   break;
	// case 3: PLMX2594->RegLoadLMX2594(34);   break;
	// case 4: PLMX2594->RegLoadLMX2594(36);   break;
	// case 5: PLMX2594->RegLoadLMX2594(75);   break;

	// default:   PLMX2594->RegLoadLMX2594(75);  break;
	// }
  //---------------------------------------------------
			switch (NUM)
	{
		// case 19:/* TODO : LMX2594 autoset  LOADAUTO*/
		// 		SW_SW = PLMX2594->RegLoadLMX2594(19)<<2;
		// 		SW_SW = SW_SW +TL+TU;
		// 	break;
			case 96:
				SW_SW = PLMX2594->RegLoadINIT(96)<<2;
				SW_SW = SW_SW +TL+TU;
			break;

		default: SW_SW = PLMX2594->RegLoadINIT(NUM)<<2;
		//SW_SW = PLMX2594->RegLoadLMX2594(NUM);
			break;
	}

  //---------------------------------------------------
	 return SW_SW;
}
long FCHP::LoadINITLMX2594(Poz)
{
	return PLMX2594->RegLoadINIT(Poz);
}
#pragma package(smart_init)
