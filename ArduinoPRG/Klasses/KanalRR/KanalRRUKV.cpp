//---------------------------------------------------------------------------


#pragma hdrstop

#include "KanalRRUKV.h"
#include <math.h>


//---------------------------------------------------------------------------
 KanalRR::KanalRR(int Mod_kanalNum, int Blok_kanalNum, double Polosa)
{
		KanalNum_B_Blok = Blok_kanalNum;
		KanalNum_B_Mod = Mod_kanalNum;

// 0x3000000	0x3300000
// 0x3100000	0x3400000
// 0x3200000	0x3500000
// 0x3600000	0x3700000
// 0x4400000	0x4500000
// 0x4800000	0x4900000
// 0x4A00000	0x4B00000
// 0x4C00000	0x4D00000
// 0x5000000	0x5300000
// 0x5100000	0x5400000
// 0x5200000	0x5500000
// 0x5600000	0x5900000
// 0x5700000	0x5A00000
// 0x5800000	0x5800000
// 0x5B00000	0x5E00000
// 0x5C00000	0x5F00000
// 0x5D00000	0x5D00000





 NKanal[0].Pres_Att1 =      0x3000000;			 NKanal[1].Pres_Att1 =     0x3300000;
 NKanal[0].Pres_Att2 =      0x3100000;			 NKanal[1].Pres_Att2 =     0x3400000;
 NKanal[0].Pres_Att3 =      0x3200000;			 NKanal[1].Pres_Att3 =     0x3500000;
 NKanal[0].Pch2_Att4 =      0x3600000;			 NKanal[1].Pch2_Att4 =     0x3700000;
 NKanal[0].Pres_Band_LNA =  0x4400000;			 NKanal[1].Pres_Band_LNA = 0x4500000;
 NKanal[0].Pres_Fil =       0x4800000;			 NKanal[1].Pres_Fil =      0x4900000;
 NKanal[0].Pch1_Sw =        0x4A00000;			 NKanal[1].Pch1_Sw =       0x4B00000;
 NKanal[0].Pch2_Sw =        0x4C00000;			 NKanal[1].Pch2_Sw =       0x4D00000;
 NKanal[0].Pres_RF =        0x5000000;			 NKanal[1].Pres_RF =       0x5300000;
 NKanal[0].Pres_Out1 =      0x5100000;			 NKanal[1].Pres_Out1 =     0x5400000;
 NKanal[0].Pres_Out2 =      0x5200000;			 NKanal[1].Pres_Out2 =     0x5500000;
 NKanal[0].Pch1_RF =        0x5600000;			 NKanal[1].Pch1_RF =       0x5900000;
 NKanal[0].Pch1_Out =       0x5700000;			 NKanal[1].Pch1_Out =      0x5A00000;
 NKanal[0].Pch1_LO =        0x5800000;			 NKanal[1].Pch1_LO =       0x5800000;
 NKanal[0].Pch2_RF =        0x5B00000;			 NKanal[1].Pch2_RF =       0x5E00000;
 NKanal[0].Pch2_Out =       0x5C00000;			 NKanal[1].Pch2_Out =      0x5F00000;
 NKanal[0].Pch2_LO =        0x5D00000;			 NKanal[1].Pch2_LO =       0x5D00000;
/******************Канал 1***********/
// 30-50				1	0	1	0	0	0	1  |	1010001 | //PRES = 0x51;  101000  28
// 50-70				1	0	1	0	0	1	1  |	1010011 | //PRES = 0x53;  ‭‭010111‬ 17
// 70-105				1	0	1	0	1	0	1  |	1010101 | //PRES = 0x55;
// 105-175				1	0	1	0	1	1	1  |	1010111 | //PRES = 0x57;
// 175-315				1	0	1	1	0	0	1  |	1011001 | //PRES = 0x59;
// 315-525				1	0	1	1	0	1	1  |	1011011 | //PRES = 0x5B;
// 525-805				1	0	1	1	1	0	1  |	1011101 | //PRES = 0x5D;
// 805-1250				1	1	0	Х	Х	Х	1  |	1100001 | //PRES = 0x61;
// 1200-1650			1	0	0	Х	Х	Х	1  |	1000001 | //PRES = 0x41;
// 1650-2550			0	0	1	Х	Х	Х	1  |	0010001 | //PRES = 0x11;
// 2550-3200			0	1	1	Х	Х	Х	1  |	0110001 | //PRES = 0x31;
// 1705-1795 вых ПЧ1	0	1	0	Х	Х	Х	1  |	0100001 | //PRES = 0x21;
// 1705-1795 вых ПЧ2	0	1	0	Х	Х	Х	0  |	0100000 | //PRES = 0x20;


/******************Канал 1***********/
//KK1 30-50				1	0	1	0	0	0	1  |	1010001 | //PRES = 0x51;
//K2  30-50				0	1	0	1	1	1	1									101000   0x3F - 0x28	 23  0101111 0x2F
//KK1 50-70				1	0	1	0	0	1	1  |	1010011 | //PRES = 0x53;
//K2  50-70				0	1	0	1	1	0	1									101001   0x3F - 0x29	 22  0101101 0x2D
//KK1 70-105			1	0	1	0	1	0	1  |	1010101 | //PRES = 0x55;
//K2  70-105			0	1	0	1	0	1	1									101010   0x3F - 0x2A	 21  0101011 0x2B
//KK1 105-175			1	0	1	0	1	1	1  |	1010111 | //PRES = 0x57;
//K2  105-175			0	1	0	1	0	0	1									101011   0x3F - 0x2B	 20  0101001 0x29
//KK1 175-315			1	0	1	1	0	0	1  |	1011001 | //PRES = 0x59;
//K2  175-315			0	1	0	0	1	1	1									101100   0x3F - 0x2C	 19  0100111 0x27
//KK1 315-525			1	0	1	1	0	1	1  |	1011011 | //PRES = 0x5B;
//K2  315-525			0	1	0	0	1	0	1									101101   0x3F - 0x2D	 18  0100101 0x25
//KK1 525-805			1	0	1	1	1	0	1  |	1011101 | //PRES = 0x5D;
//K2  525-805			0	1	0	0	0	1	1									101110   0x3F - 0x2E	 17  0100011 0x23
//KK1 805-1250			1	1	0	Х	Х	Х	1  |	1100001 | //PRES = 0x61;
//K2  805-1250			0	0	1	1	1	1	1									110000   0x3F - 0x30	 15  0011111 0x1F
//KK1 1200-1650			1	0	0	Х	Х	Х	1  |	1000001 | //PRES = 0x41;
//K2  1200-1650			0	1	1	1	1	1	1									100000   0x3F - 0x20	 31  0111111 0x3F
//KK1 1650-2550			0	0	1	Х	Х	Х	1  |	0010001 | //PRES = 0x11;
//K2  1650-2550			1	1	0	1	1	1	1									001000   0x3F - 0x8	 	 55  1101111 0x6F
//KK1 2550-3200			0	1	1	Х	Х	Х	1  |	0110001 | //PRES = 0x31;
//K2  2550-3200			1	0	0	1	1	1	1									011000   0x3F - 0x18	 39  1001111 0x4F
//KK1 1705-1795 вых ПЧ1	0	1	0	Х	Х	Х	1  |	0100001 | //PRES = 0x21;
//K2  1705-1795 вых ПЧ1	1	0	1	1	1	1	1									010000   0x3F - 0x10	 47  1011111 0x5F
//KK1 1705-1795 вых ПЧ2	0	1	0	Х	Х	Х	0  |	0100000 | //PRES = 0x20;
//K2  1705-1795 вых ПЧ2	1	0	1	1	1	1	0									010000   0x3F - 0x10	 47  1011110 0x5E

NKanal[2].Pres_Att1 =     0x0;
NKanal[2].Pres_Att2 =     0x0;
NKanal[2].Pres_Att3 =     0x0;
NKanal[2].Pch2_Att4 =     0x0;
NKanal[2].Pres_Band_LNA = 0x0;
NKanal[2].Pres_Fil =      0x0;
NKanal[2].Pch1_Sw =       0x0;
NKanal[2].Pch2_Sw =       0x0;
NKanal[2].Pres_RF =       0x0;
NKanal[2].Pres_Out1 =     0x0;
NKanal[2].Pres_Out2 =     0x0;
NKanal[2].Pch1_RF =       0x0;
NKanal[2].Pch1_Out =      0x0;
NKanal[2].Pch1_LO =       0x0;
NKanal[2].Pch2_RF =       0x0;
NKanal[2].Pch2_Out =      0x0;
NKanal[2].Pch2_LO =       0x0;

 // DIAPAZON[13] ={0x51,0x53,0x55,0x57,0x59,0x5B,0x5D,0x61,0x41,0x11,0x31,0x21,0x20};
 DIAPAZON[0][0] =  0x51<<13;	DIAPAZON[1][0] =  0x2F<<13;
 DIAPAZON[0][1] =  0x53<<13;	DIAPAZON[1][1] =  0x2D<<13;
 DIAPAZON[0][2] =  0x55<<13;	DIAPAZON[1][2] =  0x2B<<13;
 DIAPAZON[0][3] =  0x57<<13;	DIAPAZON[1][3] =  0x29<<13;
 DIAPAZON[0][4] =  0x59<<13;	DIAPAZON[1][4] =  0x27<<13;
 DIAPAZON[0][5] =  0x5B<<13;	DIAPAZON[1][5] =  0x25<<13;
 DIAPAZON[0][6] =  0x5D<<13;	DIAPAZON[1][6] =  0x23<<13;
 DIAPAZON[0][7] =  0x61<<13;	DIAPAZON[1][7] =  0x1F<<13;
 DIAPAZON[0][8] =  0x41<<13;	DIAPAZON[1][8] =  0x3F<<13;
 DIAPAZON[0][9] =  0x11<<13;	DIAPAZON[1][9] =  0x6F<<13;
 DIAPAZON[0][10] =  0x31<<13;	DIAPAZON[1][10] =  0x4F<<13;
 DIAPAZON[0][11] =  0x21<<13;	DIAPAZON[1][11] =  0x5F<<13;         //CHANGED: 1750 PRESEL PRESET @PERENOS (0)
 DIAPAZON[0][12] =  0x20<<13;	DIAPAZON[1][12] =  0x5E<<13;


LNAD = 0;
LNAMATRIX[0][0].UPR = 1<<19;    LNAMATRIX[0][0].RNG = 1<<18;
LNAMATRIX[0][1].UPR = 0<<19; 	LNAMATRIX[0][1].RNG = 0<<18;


LNAMATRIX[1][0].UPR = 0<<19;	LNAMATRIX[1][0].RNG = 0<<18;
LNAMATRIX[1][1].UPR = 1<<19;	LNAMATRIX[1][1].RNG = 1<<18;

PC2INMATRIX[0][0] = 1;   PC2INMATRIX[1][0] = 0;
PC2INMATRIX[0][1] = 0;   PC2INMATRIX[1][1] = 1;

KanalNum_B_Mod = Mod_kanalNum;



}
 KanalRR::~KanalRR()
{
	//Freal = 10;
}
void KanalRR::WriteFregIN(double freqCR, int Kanal,int PRNS)
{//NOTE: FREQSET @KANAL (0)
		KanalNum_B_Mod =  Kanal;
			if (freqCR>=30)
		{

		} else {
			 goto NN1;
		}

		// item 35
		if (freqCR>=50)
		{

		} else {
				// item 290
		PRES = 0;
		NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

		LNAD = 0;
		PCH3035 = 1;
		CTRLIN = 1;
		goto NN1;
		}

		// item 27
		if (freqCR>=70)
		{

		} else {
				// item 291
				PRES = 1;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

		LNAD = 0;
				PCH3035 = 1;
				CTRLIN = 1;
		 goto NN1;
		}

		// item 50
		if (freqCR>=105)
		{
		} else {
				// item 292
				PRES = 2;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

				LNAD = 0;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 43
		if (freqCR>=175)
		{
		} else {
				// item 293
				PRES = 3;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

				LNAD = 0;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 63
		if (freqCR>=315)
		{
		} else {
				// item 294
				PRES = 4;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

				LNAD = 0;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 57
		if (freqCR>=525)
		{
		} else {
				// item 295
				PRES = 5;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

				LNAD = 0;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 77
		if (freqCR>=805)
		{
		} else {
				// item 296
				PRES = 6;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];
				NKanal[2].Pres_Band_LNA = 0;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 71
		if (freqCR>=1250)
		 {
		} else {
				// item 297
				PRES = 7;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

		LNAD = 1;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 92
		if (freqCR>=1650)
		 {
		} else {
				// item 298
				PRES = 8;
				NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];

		LNAD = 1;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 86
		if (freqCR>=2550)
		 {
		} else {
				// item 299
				PRES = 9;
				Pres_UPR_Kluch = DIAPAZON[KanalNum_B_Mod][PRES];
				LNAD = 1;
				PCH3035 = 1;
				CTRLIN = 1;
			 goto NN1;
		}

		// item 104
		if (freqCR>=1650)
		 {
		} else {
				// item 300
				PRES = 10;

				Pres_UPR_Kluch = DIAPAZON[KanalNum_B_Mod][PRES];
				LNAD = 1;
				PCH3035 = 1;
				CTRLIN = 1;
				goto NN1;
				}

		// item 98
		if (freqCR>=2550)
		 {
				// item 302
				PRES = 12;
				Pres_UPR_Kluch = DIAPAZON[KanalNum_B_Mod][PRES];
		LNAD = 1;
				PCH3035 = 1;
				CTRLIN = 1;
		} else {
				// item 301
				PRES = 11;
				Pres_UPR_Kluch = DIAPAZON[KanalNum_B_Mod][PRES];
		LNAD = 1;
				PCH3035 = 1;
		CTRLIN = 1;
		}
		NN1:
PRESELSET(PRES);
AmplifSET(1);
NKanal[2].Pch1_Sw = 1;
PERENOS(PRNS);
//PC2INSET(1);
//NKanal[2].Pch2_Sw = NKanal[2].Pch2_Sw&0x1;
FregIN = freqCR;
Fpc1 = 3500;
FrGet1 = FregIN+Fpc1;
FrGet2 = Fpc1+255;


}
void KanalRR::PERENOS(int PRES)
{		switch (PRES)
		{//CHANGED: Перенос @FRSET (0)
		case 0:
			NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][12];
			NKanal[3].Pres_Fil = DIAPAZON[1][12];
			PC2INSET(0);
		break;
		case 1:
			// NKanal[2].Pres_Fil = DIAPAZON[0][9];
			// NKanal[3].Pres_Fil = DIAPAZON[1][9];
			PC2INSET(1);
		break;
		default:
			// NKanal[2].Pres_Fil = DIAPAZON[0][9];
			// NKanal[3].Pres_Fil = DIAPAZON[1][9];
			PC2INSET(1);
		break;
		}

}

int KanalRR::LoadKL(int div)
{//TODO: LOADKL Kanal @Прогрузка (0)
		int i;
		int  SW_SW;
		if (div >= 0 && div < 8)
	{
		i = div;
	}
	else
	{
		i = 0;
	}
														 switch (i)
 {
				case 0:
				SW_SW = NKanal[KanalNum_B_Mod].Pres_Band_LNA + NKanal[2].Pres_Band_LNA;
				break;
				case 1:
				SW_SW = NKanal[KanalNum_B_Mod].Pres_Fil + NKanal[2].Pres_Fil;
				break;
				case 2:
				SW_SW = NKanal[KanalNum_B_Mod].Pch1_Sw|NKanal[2].Pch1_Sw<<19;
				break;
				case 3:
				SW_SW = NKanal[KanalNum_B_Mod].Pch2_Sw|NKanal[2].Pch2_Sw<<18;
				break;
				/*
				case 4:
				SW_SW = NKanal[KanalNum_B_Mod].Pres_Band_LNA + NKanal[2].Pres_Band_LNA;
				break;
				case 5:
				SW_SW = NKanal[KanalNum_B_Mod].Pres_Fil + NKanal[2].Pres_Fil;
				break;
				case 6:
				SW_SW = NKanal[KanalNum_B_Mod].Pch1_Sw +  NKanal[2].Pch1_Sw;
				break;
				case 7:
				SW_SW = NKanal[KanalNum_B_Mod].Pch2_Sw + NKanal[2].Pch2_Sw;
				break;
				*/
				default : SW_SW = NKanal[KanalNum_B_Mod].Pres_Fil + NKanal[2].Pres_Fil;break;
 }

				return  SW_SW;
}
void KanalRR::AmplifSET(int Amplif)
 {   AmpSET = Amplif;

	 NKanal[2].Pres_Band_LNA = LNAMATRIX[KanalNum_B_Mod][AmpSET].UPR|LNAMATRIX[KanalNum_B_Mod][LNAD].RNG;

 }
void KanalRR::PC2INSET(int PC)
{
	NKanal[2].Pch2_Sw = NKanal[2].Pch2_Sw&0x2;
	NKanal[2].Pch2_Sw = NKanal[2].Pch2_Sw|PC2INMATRIX[KanalNum_B_Mod][PC];
}
void KanalRR::ATT1_SET(double DB)
{
	if (DB >= 0 && DB <= 63)
		 {
		ATT_pervi = 0x3F -(int)(DB) ;
		 }
	else
		 {
		ATT_pervi = 0;
		 }
		 Amp_Att1 = ATT_pervi<<14;
}
void KanalRR::ATT2_SET(double DB)
{
	 if (DB >= 0 && DB <= 63)
	 {
	ATT_pervi = 0x3F -(int)(DB);
	 }
	 else
	 {
	ATT_pervi = 0;
	 }
	 Amp_Att2 = ATT_pervi <<14;
}
void KanalRR::ATT3_SET(double DB)
{
	 if (DB >= 0 && DB <= 63)
	 {
	 ATT_pervi = 0x3F - (int)(DB);
	 }
	 else
	 {
	 ATT_pervi = 0;
	 }
	 Amp_Att3 = ATT_pervi <<14;
}
void KanalRR::ATT4_SET(double DB)
{
	 if (DB >= 0 && DB <= 63)
	 {
	 ATT_vtoroi = 0x3F -(int)(DB);
	 }
	 else
	 {
	 ATT_vtoroi = 0;
	 }
	 Pch2_Att4 =ATT_vtoroi <<14;
}

void KanalRR::PRESELSET(int PRES)
{   //NOTE: PRESEL @KANAL (1)

	NKanal[2].Pres_Fil = DIAPAZON[KanalNum_B_Mod][PRES];
	NKanal[3].Pres_Fil = DIAPAZON[1][PRES];
					if(PRES<7)
		{
			LNAD = 0;
		}
			else
		{
			LNAD = 1;
		}

}


 int KanalRR::LoadATT(int div)
{    int i;
	 int  ATT_db;
 if (div >= 0 && div < 8)
	 {
	 i = div;

	 }
	 else
	 {
	i = 0;
	 }
//****************************************************************
		switch (i)
	 {
	case 0:
	ATT_db = NKanal[KanalNum_B_Mod].Pres_Att1+Amp_Att1;

	break;
	case 1:
	ATT_db = NKanal[KanalNum_B_Mod].Pres_Att2+Amp_Att2;

	break;
	case 2:
	ATT_db = NKanal[KanalNum_B_Mod].Pres_Att3+Amp_Att3;

	break;
	case 3:
	ATT_db = NKanal[KanalNum_B_Mod].Pch2_Att4+Pch2_Att4;break;

	default : ATT_db = NKanal[KanalNum_B_Mod].Pres_Att2 + Amp_Att2;break;
	 }
//****************************************************************
 return  ATT_db;
}


double KanalRR::FreqFout()
{return FsigPC2;}
//--------------------------------------------------------------
unsigned long KanalRR::LoadGET1H(){
	unsigned long SW = 0;
	if (true) {
		 SW = 1;
	} else {
		 SW = 0;
	}

}
unsigned long KanalRR::LoadGET2H(){
if (KanalNum_B_Mod) {
	2;

}   else {
2;
	}

}
//--------------------------------------------------------------



#pragma package(smart_init)