//---------------------------------------------------------------------------


#pragma hdrstop
#include "MFC1RR.h"

//---------------------------------------------------------------------------



MMFC1RR::MMFC1RR(int FIN)
{
	Fget1 = 2300;
	AdrMod = 0xD<<28;
	AdrMod = Adress::OBSH;

	L = 0;// //L-бит включения авто-калибровки VCO.«1» - avtocal enable. «0» - avtocal disable
	U = 0;// //U-бит направления авто-калибровки.«1»-up correction.«0» - down correction.
	NumDapazon = 10;//Номер диапазона

	Sint1_HMC830 = new HMC830(178,127,28,100);//ТОК 127  -10dB Noise
	//CHANGED: ТОК LMX @LMX (1)
	//Sint1_LMX2594 = new LMX2594(8000,60,28,100);
	Sint1_LMX2594 = new LMX2594(8000,1,28,100);

	MXHMC394 = new HMC394();
//---------------------------------------------------------------------------
	BFCHP = new FCHP();
	MXUXM15 = new UXM15();
	MXUXM20 = new UXM20();
	BFCHP->FINE = FIN;
//---------------------------------------------------------------------------



DEVFC1R[0].F394 = 		0x4100000;
DEVFC1R[0].S15p = 		0x4200000;
DEVFC1R[0].S20p = 		0x4300000;
DEVFC1R[0].RSV = 		0x4400000;
DEVFC1R[0].PDP = 		0x4500000;
DEVFC1R[0].FMC830 = 	0x7000000;
DEVFC1R[0].SMX2594 = 	0x8000000;
DEVFC1R[0].I2CRSF =		0xE000000;
DEVFC1R[0].I2CWIF =		0xE500000;
DEVFC1R[0].I2CRIF =		0xEE00000;
DEVFC1R[0].I2CRR =		0xEF00000;
//---------------------------------------------------------------------------

DEVFC1R[1].F394 = 		0x2;
DEVFC1R[1].S15p = 		0x2;
DEVFC1R[1].S20p = 		0x2;
DEVFC1R[1].RSV = 		0x2;
DEVFC1R[1].PDP = 		0x2;
DEVFC1R[1].FMC830 = 	0x2;
DEVFC1R[1].SMX2594 = 	0x2;
DEVFC1R[1].I2CRSF= 		0x2;
DEVFC1R[1].I2CWIF = 	0x2;
DEVFC1R[1].I2CRIF= 		0x2;
DEVFC1R[1].I2CRR = 		0x2;

//---------------------------------------------------------------------------
DEVFC1R[2].F394 =		15;
DEVFC1R[2].S15p =		17;
DEVFC1R[2].S20p =		18;
DEVFC1R[2].RSV =		19;
DEVFC1R[2].PDP =		19;
DEVFC1R[2].FMC830 = 	1;
DEVFC1R[2].SMX2594 = 	7;
DEVFC1R[2].I2CRSF=		20;
DEVFC1R[2].I2CWIF =		20;
DEVFC1R[2].I2CRIF=		20;
DEVFC1R[2].I2CRR =		20;



//---------------------------------------------------------------------------
/*F	Внутренняя частота синтезатора
M	Петлевой делитель UXM15P
K	Полярность фазового детектора (1-переключение на инверсную петлю)
OUT	Выходной делитель синтезатора LMX2594
N	N-делитель синтезатора LMX2594
CAP1	код CAP
VCO	Номер ядра VCO (1-7)
FOUT	Выходная частота синтезатора*/



PLAN[0].FVCO = 7500;        PLAN[0].F =  7500;     PLAN[0].M = 4;  PLAN[0].K = 1;   PLAN[0].OUTM = 1;  PLAN[0].N = 150;  PLAN[0].CAP = 1;   PLAN[0].VCO = 3;
PLAN[1].FVCO = 7684.6;      PLAN[1].F =  7684.6;   PLAN[1].M = 4;  PLAN[1].K = 1;   PLAN[1].OUTM = 1;  PLAN[1].N = 80;   PLAN[1].CAP = 2;   PLAN[1].VCO = 4;
PLAN[2].FVCO = 7889.4;      PLAN[2].F =  7889.4;   PLAN[2].M = 4;  PLAN[2].K = 1;   PLAN[2].OUTM = 1;  PLAN[2].N = 54;   PLAN[2].CAP = 3;   PLAN[2].VCO = 5;
PLAN[3].FVCO = 8084.2;      PLAN[3].F =  8084.2;   PLAN[3].M = 4;  PLAN[3].K = 1;   PLAN[3].OUTM = 1;  PLAN[3].N = 42;   PLAN[3].CAP = 4;   PLAN[3].VCO = 6;
PLAN[4].FVCO = 8281.4;      PLAN[4].F =  8281.4;   PLAN[4].M = 4;  PLAN[4].K = 1;   PLAN[4].OUTM = 1;  PLAN[4].N = 34;   PLAN[4].CAP = 5;   PLAN[4].VCO = 7;
PLAN[5].FVCO = 8461.5;      PLAN[5].F =  8461.5;   PLAN[5].M = 4;  PLAN[5].K = 1;   PLAN[5].OUTM = 1;  PLAN[5].N = 30;   PLAN[5].CAP = 6;   PLAN[5].VCO = 8;
PLAN[6].FVCO = 8649.3;      PLAN[6].F =  8649.3;   PLAN[6].M = 5;  PLAN[6].K = -1;  PLAN[6].OUTM = 1;  PLAN[6].N = 90;   PLAN[6].CAP = 7;   PLAN[6].VCO = 9;
PLAN[7].FVCO = 8834.3;      PLAN[7].F =  8834.3;   PLAN[7].M = 5;  PLAN[7].K = -1;  PLAN[7].OUTM = 1;  PLAN[7].N = 130;  PLAN[7].CAP = 8;   PLAN[7].VCO = 10;
PLAN[8].FVCO = 9022.7;      PLAN[8].F =  9022.7;   PLAN[8].M = 6;  PLAN[8].K = -1;  PLAN[8].OUTM = 1;  PLAN[8].N = 28;   PLAN[8].CAP = 9;   PLAN[8].VCO = 11;
PLAN[9].FVCO = 9242.9;      PLAN[9].F =  9242.9;   PLAN[9].M = 6;  PLAN[9].K = -1;  PLAN[9].OUTM = 1;  PLAN[9].N = 32;   PLAN[9].CAP = 10;  PLAN[9].VCO = 12;
PLAN[10].FVCO = 9465.3;     PLAN[10].F =  9465.3;  PLAN[10].M = 6; PLAN[10].K = -1; PLAN[10].OUTM = 1; PLAN[10].N = 38;  PLAN[10].CAP = 11; PLAN[10].VCO = 13;
PLAN[11].FVCO = 9701.2;     PLAN[11].F =  9701.2;  PLAN[11].M = 6; PLAN[11].K = -1; PLAN[11].OUTM = 1; PLAN[11].N = 46;  PLAN[11].CAP = 12; PLAN[11].VCO = 14;
PLAN[12].FVCO = 9921.1;     PLAN[12].F =  9921.1;  PLAN[12].M = 6; PLAN[12].K = -1; PLAN[12].OUTM = 1; PLAN[12].N = 56;  PLAN[12].CAP = 13; PLAN[12].VCO = 15;
PLAN[13].FVCO = 10155.0; 	PLAN[13].F =  10155.0; PLAN[13].M = 6; PLAN[13].K = -1; PLAN[13].OUTM = 1; PLAN[13].N = 76;  PLAN[13].CAP = 14; PLAN[13].VCO = 16;
PLAN[14].FVCO = 10405.2; 	PLAN[14].F =  10405.2; PLAN[14].M = 6; PLAN[14].K = -1; PLAN[14].OUTM = 1; PLAN[14].N = 110; PLAN[14].CAP = 15; PLAN[14].VCO = 17;
PLAN[15].FVCO = 10631.0; 	PLAN[15].F =  10631.0; PLAN[15].M = 7; PLAN[15].K = -1; PLAN[15].OUTM = 1; PLAN[15].N = 34;  PLAN[15].CAP = 16; PLAN[15].VCO = 18;
PLAN[16].FVCO = 10878.2; 	PLAN[16].F =  10878.2; PLAN[16].M = 7; PLAN[16].K = -1; PLAN[16].OUTM = 1; PLAN[16].N = 40;  PLAN[16].CAP = 17; PLAN[16].VCO = 19;
PLAN[17].FVCO = 11129.0; 	PLAN[17].F =  11129.0; PLAN[17].M = 7; PLAN[17].K = -1; PLAN[17].OUTM = 1; PLAN[17].N = 46;  PLAN[17].CAP = 18; PLAN[17].VCO = 20;
PLAN[18].FVCO = 11373.5; 	PLAN[18].F =  11373.5; PLAN[18].M = 7; PLAN[18].K = -1; PLAN[18].OUTM = 1; PLAN[18].N = 56;  PLAN[18].CAP = 19; PLAN[18].VCO = 21;
PLAN[19].FVCO = 11654.9; 	PLAN[19].F =  11654.9; PLAN[19].M = 7; PLAN[19].K = -1; PLAN[19].OUTM = 1; PLAN[19].N = 72;  PLAN[19].CAP = 20; PLAN[19].VCO = 22;
PLAN[20].FVCO = 11950.6; 	PLAN[20].F =  11950.6; PLAN[20].M = 7; PLAN[20].K = -1; PLAN[20].OUTM = 1; PLAN[20].N = 100; PLAN[20].CAP = 21; PLAN[20].VCO = 23;
PLAN[21].FVCO = 12239.9; 	PLAN[21].F =  12239.9; PLAN[21].M = 6; PLAN[21].K = 1;  PLAN[21].OUTM = 1; PLAN[21].N = 58;  PLAN[21].CAP = 22; PLAN[21].VCO = 24;
PLAN[22].FVCO = 12495.6; 	PLAN[22].F =  12495.6; PLAN[22].M = 6; PLAN[22].K = 1;  PLAN[22].OUTM = 1; PLAN[22].N = 50;  PLAN[22].CAP = 23; PLAN[22].VCO = 25;
PLAN[23].FVCO = 12779.5; 	PLAN[23].F =  12779.5; PLAN[23].M = 6; PLAN[23].K = 1;  PLAN[23].OUTM = 1; PLAN[23].N = 42;  PLAN[23].CAP = 24; PLAN[23].VCO = 26;
PLAN[24].FVCO = 13113.8; 	PLAN[24].F =  13113.8; PLAN[24].M = 8; PLAN[24].K = -1; PLAN[24].OUTM = 1; PLAN[24].N = 70;  PLAN[24].CAP = 25; PLAN[24].VCO = 27;
PLAN[25].FVCO = 13446.8; 	PLAN[25].F =  13446.8; PLAN[25].M = 8; PLAN[25].K = -1; PLAN[25].OUTM = 1; PLAN[25].N = 92;  PLAN[25].CAP = 26; PLAN[25].VCO = 28;
PLAN[26].FVCO = 13768.3; 	PLAN[26].F =  13768.3; PLAN[26].M = 7; PLAN[26].K = 1;  PLAN[26].OUTM = 1; PLAN[26].N = 100; PLAN[26].CAP = 27; PLAN[26].VCO = 29;
PLAN[27].FVCO = 14092.0; 	PLAN[27].F =  14092.0; PLAN[27].M = 7; PLAN[27].K = 1;  PLAN[27].OUTM = 1; PLAN[27].N = 76;  PLAN[27].CAP = 28; PLAN[27].VCO = 30;
PLAN[28].FVCO = 14428.7; 	PLAN[28].F =  14428.7; PLAN[28].M = 7; PLAN[28].K = 1;  PLAN[28].OUTM = 1; PLAN[28].N = 62;  PLAN[28].CAP = 29; PLAN[28].VCO = 31;
PLAN[29].FVCO = 14778.8; 	PLAN[29].F =  14778.8; PLAN[29].M = 7; PLAN[29].K = 1;  PLAN[29].OUTM = 1; PLAN[29].N = 52;  PLAN[29].CAP = 30; PLAN[29].VCO = 32;

//---------------------------------------------------------------------------
	Polosa830[0].DFv =  130;   Polosa830[0].DNSys = 20;
	Polosa830[1].DFv =  131.6; Polosa830[1].DNSys = 22;
	Polosa830[2].DFv =  132;   Polosa830[2].DNSys = 20;
	Polosa830[3].DFv =  134;   Polosa830[3].DNSys = 22;
	Polosa830[4].DFv =  134.2; Polosa830[4].DNSys = 20;
	Polosa830[5].DFv =  136.1; Polosa830[5].DNSys = 22;
	Polosa830[6].DFv =  140.7; Polosa830[6].DNSys = 20;
	Polosa830[7].DFv =  149.7; Polosa830[7].DNSys = 22;
	Polosa830[8].DFv =  156.3; Polosa830[8].DNSys = 20;

}

MMFC1RR::~MMFC1RR()
{

}

/*
	 ###  ## ## #####  ###   #### #### #####
	## ## ## ##  ##   ## ## ##    ##    ##
	## ## ## ##  ##   ##  # ####  ####  ##
	##### ## ##  ##   ##  #   ### ##    ##
	## ## ## ##  ##   ## ## ## ## ##    ##
	## ##  ###   ##    ###   ###  ####  ##
*/
/**
 * [MMFC1RR::SetAUTOCOR description]
 * @param SL [Вкл Автоподстойка]
 * @param SU [Вкл Калибровка]
 */
void MMFC1RR::SetAUTOCOR(int SL,int SU)
{//	TODO: SETAUTO МФЧ

	L = SL<<1;
	U = SU;
	BFCHP->SETAUTO(SL,SU);
}
double MMFC1RR::Initfreq(double Freq,int K1,int K2,double  NDel,int SysN,int AR,int AN)
{

	// TODO: Делитель перед MIX2 @Старая Ф
	// Делитель основы 35.40.45
	// Делитель основы 35.40.45.50

	//Fop = Freq* Pr*Div/(Pr*Div + Pr*Pol2 + Div*Pol1*Pol2);
	//Fopdiv = Fop/Div;
	//FDIVocn = Fop/SysN; //Основа 5000+HMC830
	Fz = (Fop - 5000)*2;
	if (Pol1*Pol2>0) { ADPOL = 0; }
	else {ADPOL = 1;	}
	return Fz;//Рассчитанная частота модуляции (HMC830)

}

/**
 * [SetFreq рассчет]
 * @param  Fg4159 [Частота настройки]
 * @param  fget   [Предустановка частота модуляции (HMC830)]
 * @param  Fas1   [Ключ1]
 * @param  Fas2   [Ключ2]
 * @param  SysN   [Предустановка системного делителя 35.40.45]
 * @return        [Рассчитанная частота модуляции (HMC830)]
 */
double MMFC1RR::SetFreq(double Fg4159,double fget,int Fas1,int Log)
{
if (Fg4159<15000.0) {
	DEVFC1R[1].S20p = BFCHP->SETUMX20(1);
	Fop = Fg4159;
}
if (Fg4159<7500.0) {
	DEVFC1R[1].S20p = BFCHP->SETUMX20(2);
	Fop = Fg4159*2;
}
if (Fg4159<3725.0) {
	DEVFC1R[1].S20p = BFCHP->SETUMX20(4);
	Fop = Fg4159*4;
}
if (Fg4159<1875.0) {
	DEVFC1R[1].S20p = BFCHP->SETUMX20(8);
	Fop = Fg4159*8;
}

		NumDapazon = 29;
				for (int i = 29; i > 0; --i)
		{
				if (Fop<PLAN[i].F) NumDapazon = i-1;
		}
/**
	TODO: Установка частоты @Установка (0)
	- First todo item
	- Second todo item
*/
//Edit2->Text.ToDouble()/(Form4->Polosa[i].DM*Form4->Polosa[i].MOUT)  - Form4->Polosa[i].K*Edit2->Text.ToDouble()/Form4->Polosa[i].DN -1000;

//Fz	= Fop/PLAN[NumDapazon].M  - PLAN[NumDapazon].K*PLAN[NumDapazon].OUTM*Fop/PLAN[NumDapazon].N -1000;
Fz	= 2000 - Fop*(PLAN[NumDapazon].K * PLAN[NumDapazon].N - PLAN[NumDapazon].M)/(PLAN[NumDapazon].M * PLAN[NumDapazon].K * PLAN[NumDapazon].N);



/**	TODO: Set n LMX2594 @Установка(0)
	- Set n LMX2594 (0)
	- Second todo item
 */
SetAUTOCOR(0,0);
BFCHP->PLMX2594->Default();
//BFCHP->PLMX2594->SetFreq(Fop*PLAN[NumDapazon].OUTM); //CHANGED: R[11] удваивает MULT @LMX2594 (0)
BFCHP->SETDF(PLAN[NumDapazon].M,PLAN[NumDapazon].K,1,PLAN[NumDapazon].OUTM,PLAN[NumDapazon].N,PLAN[NumDapazon].CAP,PLAN[NumDapazon].VCO);  //int DXM15, int LOOP, int NOUT, int NPLL, int CAP, int VCO

DEVFC1R[1].S15p = BFCHP->MXUXM15->SETUXM15(PLAN[NumDapazon].M);
DEVFC1R[1].RSV =  BFCHP->UPR2;
DEVFC1R[1].PDP =  BFCHP->UPR1;
/*
PLAN[NumDapazon].M	//Петлевой делитель UXM15P
PLAN[NumDapazon].K; //Полярность фазового детектора (1-переключение на инверсную петлю)
PLAN[NumDapazon].OUT//Выходной делитель синтезатора LMX2594
PLAN[NumDapazon].N	//N-делитель синтезатора LMX2594
PLAN[NumDapazon].CAP1//	код CAP
PLAN[NumDapazon].VCO//Номер ядра VCO (1-7)
*/

POINT.F 	= PLAN[NumDapazon].F;
POINT.FVCO 	= PLAN[NumDapazon].FVCO;
POINT.M 	= PLAN[NumDapazon].M;
POINT.K 	= PLAN[NumDapazon].K;
POINT.OUTM 	= PLAN[NumDapazon].OUTM;
POINT.N 	= PLAN[NumDapazon].N;
POINT.CAP 	= PLAN[NumDapazon].CAP;
POINT.VCO 	= PLAN[NumDapazon].VCO;





				for (int j = 0; j < 9; ++j)
		{
			if (Fz>Polosa830[j].DFv) Diapazon830 = j;
		}
		Sint1_HMC830->SetREF(2000.0/Polosa830[Diapazon830].DNSys,1);
		N394 = MXHMC394->SET394(Polosa830[Diapazon830].DNSys);
		DEVFC1R[1].F394 = N394;
		Sint1_HMC830->SetFreq(Fz);

		return  Fz;
}
void MMFC1RR::Set394(int div)
{        N394 = MXHMC394->SET394(div);}

void MMFC1RR::SetUXM15(int div)
{   UXD15 = MXUXM15->SETUXM15(div);
	// 	switch (div)
	// {
	// case 4: UXD15 = 0x3;   break;
	// case 5: UXD15 = 0x7;   break;
	// case 6: UXD15 = 0x1;   break;
	// case 7: UXD15 = 0x5;   break;
	// case 8: UXD15 = 0x0;   break;
	// case 9: UXD15 = 0x4;   break;

	// default:  UXD15 = 0x4;  break; // N = 9
	// }
}
void MMFC1RR::SetUXD20(int div)
{
	UXD20 = MXUXM20->SETUXM20(div);
	// 	switch (div)
	// {
	// case 1: UXD20 = 0;   break;
	// case 2: UXD20 = 0x3;   break;
	// case 4: UXD20 = 0x1;   break;
	// case 5: UXD20 = 0x2;   break;
	// default: UXD20 = 0;   break; // N = 1
	// }
}
/*********************Load Ключи***********/
int MMFC1RR::Kluch(int Num)
   {
	 switch(Num)
	 {	case 0:
		//return  AdrMod|0x4<<24|0x1<<20|N394<<15;//Foch_hmc394
		return  AdrMod|DEVFC1R[0].F394|DEVFC1R[1].F394<<DEVFC1R[2].F394;
		break;
		case 1:
		return  AdrMod|0x4<<24|0x2<<20|UXD15<<17; //Sint1_UXD15p
		break;
		case 2:
		return  AdrMod|0x4<<24|0x3<<20|UXD20<<18; //Sint1_uxd20p
		break;
		case 3:
		return  AdrMod|0x4<<24|0x4<<20|UPR2<<19; //Sint1_refsw UPR2
		break;
		case 4:
		return  AdrMod|0x4<<24|0x5<<20|UPR1<<19; //Sint1_pdp UPR1
		break;

	 }
   }

int MMFC1RR::KluchM(int Num)
   {
	 switch(Num)
	 {	case 0:
	 	return  AdrMod|DEVFC1R[0].F394|DEVFC1R[1].F394<<DEVFC1R[2].F394;
		//AdrMod|0x4<<24|0x1<<20|N394<<16;//Foch_hmc394
		break;
		case 1:
		return  AdrMod|DEVFC1R[0].S15p|DEVFC1R[1].S15p<<DEVFC1R[2].S15p;
		//AdrMod|0x4<<24|0x2<<20|UXD15<<17; //Sint1_UXD15p
		break;
		case 2:
		return  AdrMod|DEVFC1R[0].S20p|DEVFC1R[1].S20p<<DEVFC1R[2].S20p;
		//AdrMod|0x4<<24|0x3<<20|UXD20<<18; //Sint1_uxd20p
		break;
		case 3:
		return  AdrMod|DEVFC1R[0].RSV|DEVFC1R[1].RSV<<DEVFC1R[2].RSV;
		//AdrMod|0x4<<24|0x4<<20|UPR2<<19; //Sint1_refsw UPR2
		break;
		case 4:
		return  AdrMod|DEVFC1R[0].PDP|DEVFC1R[1].PDP<<DEVFC1R[2].PDP;
		//AdrMod|0x4<<24|0x5<<20|UPR1<<19; //Sint1_pdp UPR1
		break;

	 }
   }
long MMFC1RR::SintLOAD_LMXLCR(int Poz)
   {//	TODO: Load MFC CR(3)

		return BFCHP->LOAD_F(Poz)<<6;//LMX2594
   }
   /*=============================================
   =            Section  DivSet                 =
   =============================================*/



void MMFC1RR::AdrSet(int JGUT)
{
	switch(JGUT)
	{
		case 0:
		AdrMod = Adress::MFC1;
		break;
		case 1:
		AdrMod = Adress::OBSH;
		break;


	}
}

long MMFC1RR::SintLOAD_L(int dev,int Poz)
/*---------- Subsection SintLOAD_L  ----------*/

   {  int i;
			if (Poz>=0)
	  {  i = Poz;
	  }
		 long  SW_SW;

		switch(dev)
		{   case 1:  /*	TODO: прогрузка LMX2594 @Прогрузка(3)*/

			  					switch (i)
			    {

				 case 19:
// LOADAUTO
					SW_SW = Sint1_LMX2594->RegLoadLMX2594(i)<<2;
					//SW_SW = SW_SW +L;
					SW_SW = SW_SW +L+U;
					break;

				 // case 2:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 3:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 4:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 5:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 6:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 7:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 8:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 9:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;

				 // case 10:

				 // SW_SW = Sint1_LMX2594->RegLoad2594(i);break;





				 default : SW_SW = 	Sint1_LMX2594->RegLoadLMX2594(i)<<2;break;

			   }
			   SW_SW = SW_SW <<6; break;

			 case 2:   /*	TODO:прогрузка HMC830 @Прогрузка(3)*/

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 1:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 2:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 3:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 4:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 5:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 6:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 7:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 8:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 9:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 10:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 11:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				  case 12:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 13:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 14:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 15:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
				 case 16:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
				 case 17:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
				 case 18:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
                 case 19:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;



				 default : SW_SW = Sint1_HMC830->RegLoad830(0);break;

			   }  		  SW_SW = SW_SW <<1;		 	break;

		}

	return  SW_SW;

   }
/***********************************************************************************/
long MMFC1RR::SintLOAD_LFCCR(int Poz)
/*---------- Subsection SintLOAD_L  ----------*/

   {
		 long  SW_SW;

		/*	TODO: прогрузка HMC830 добавить из МСХ */
			//SW_SW = Sint1_HMC830->RGLoad830STR(Poz);
			SW_SW = Sint1_HMC830->RGLoad830STR(Poz);
			SW_SW = SW_SW <<1;
	return  SW_SW;

   }

/***********************************************************************************/
long MMFC1RR::SintLOAD_H(int dev)
   {

	switch(dev)
		{   case 1:
			return  AdrMod|DEVFC1R[0].SMX2594;//LMX2594
			break;
			case 2:
			return  AdrMod|DEVFC1R[0].FMC830;
			break;
			default: return  AdrMod|DEVFC1R[0].FMC830;
		}
   }
#pragma package(smart_init)
