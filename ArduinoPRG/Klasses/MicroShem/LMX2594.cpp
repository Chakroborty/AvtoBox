//---------------------------------------------------------------------------


#pragma hdrstop
#include <math.h>
#include "LMX2594.h"
//#include "BitsU.h"

//#define   BIN8(x)   BIN___(0##x)
//#define   BIN___(x)(((x/01ul)%010)*(2>>1)+ \
//((x/010ul)   %   010)*(2<<0)   +           \
//((x/ 0100ul)   %   010)*(2<<1)   +         \
//((x/ 01000ul)   %   010)*(2<<2)   +        \
//((x/ 010000ul)   %   010)*(2<<3)   +       \
//((x/ 0100000ul)   %   010)*(2<<4)   +      \
//((x/ 01000000ul)   %   010)*(2<<5)   +      \
//((x/ 010000000ul)   %   010)*(2<<6))
//
//#define BIN16(x1,x2)\
//((BIN8(x1)<<8)+BIN8(x2))
//
//#define BIN24(x1,x2,x3) ((BIN8(x1)<<16)+(BIN8(x2)<<8)+BIN8(x3))
//
//#define BIN32(x1,x2,x3,x4)((BIN8(x1)<<24)+(BIN8(x2)<<16)+(BIN8(x3)<<8)+BIN8(x4))
//---------------------------------------------------------------------------

 LMX2594::LMX2594(double F,int I,int N,double Ref)
 {
	//FregSIN = F;
	R = 1;
	Nref = N;
	Xtal = Ref; //МГерц
	PREr =  1 ;
	POSTR  = 1;
	MULT = 1;

/*
###  ###  ####  ### #### #####
#  # #  # #    #    #      #
#  # #  # #    #    #      #
###  ###  ###   ##  ###    #
#    # #  #       # #      #
#    #  # #       # #      #
#    #  # #### ###  ####   #
*/
/*
  +----+------------+
  |Code|   current  |
  +----+------------+
  |  0:| 0 mA       |
  +----+------------+
  |  1:| 6 mA       |
  +----+------------+
  |  2:| Reserved   |
  +----+------------+
  |  3:| 12 mA      |
  +----+------------+
  |  4:| 3 mA       |
  +----+------------+
  |  5:| 9 mA       |
  +----+------------+
  |  6:| Reserved   |
  +----+------------+
  |  7:| 15 mA      |
  +----+------------+ */

	/* ДляПРЧ051 */

REGIM[0].NINT = 54;		// TPRC51->FCHP2594->PLMX2594->NSET(56);//34 36
REGIM[0].CURSET = 4; 	// SENDLAN(TPRC51->FCHLOAD_LMX(TPRC51->FCHP2594->PLMX2594->CURSET(4)),0,0);//PDCUR
REGIM[0].SEG1EN = 0; 	// SENDLAN(TPRC51->FCHLOAD_LMX(TPRC51->FCHP2594->PLMX2594->SEG1EN(0)),0,0);//SEG
REGIM[0].FCAL_EN = 0;	// SENDLAN(TPRC51->FCHLOAD_LMX(TPRC51->FCHP2594->PLMX2594->FCAL_EN(0)),0,0);//FCAL_EN
REGIM[0].OUTAPWR = 63;	// TPRC51->FCHP2594->PLMX2594->OUTAPWR(63);//44
REGIM[0].OUTBPWR = 63;	// TPRC51->FCHP2594->PLMX2594->OUTBPWR(63);//45
REGIM[0].CHANDiV = 0;	// TPRC51->FCHP2594->PLMX2594->CHANDiV(0);//R75[10:6]


// TPRC51->FCHP2594->PLMX2594->FRSET(0);//42 43
// TPRC51->FCHP2594->PLMX2594->CHANDiV(0);//R75[10:6]






/************************VCO Core Ranges********************/
	VCO[0].FcorMIN=7500; VCO[0].FcorMAX=8600;  VCO[0].CcorMIN=164;  VCO[0].CcorMAX=12; VCO[0].AcorMIN=299;VCO[0].AcorMAX=240;
	VCO[0].DeltF=1100;VCO[0].DeltC=152;VCO[0].DeltA=-59;

	VCO[1].FcorMIN=7500; VCO[1].FcorMAX=8600;  VCO[1].CcorMIN=164;  VCO[1].CcorMAX=12; VCO[1].AcorMIN=299;VCO[1].AcorMAX=240;
	VCO[1].DeltF=1100;VCO[1].DeltC=152;VCO[1].DeltA=-59;

	VCO[2].FcorMIN=8600; VCO[2].FcorMAX=9800;  VCO[2].CcorMIN=165;  VCO[2].CcorMAX=16; VCO[2].AcorMIN=356;VCO[2].AcorMAX=247;
	VCO[2].DeltF=1200;VCO[2].DeltC=149;VCO[2].DeltA=-109;

	VCO[3].FcorMIN=9800; VCO[3].FcorMAX=10800;  VCO[3].CcorMIN=158;  VCO[3].CcorMAX=19; VCO[3].AcorMIN=324;VCO[3].AcorMAX=224;
	VCO[3].DeltF=1000;VCO[3].DeltC=139;VCO[3].DeltA=-100;

	VCO[4].FcorMIN=10800; VCO[4].FcorMAX=12000;  VCO[4].CcorMIN=140;  VCO[4].CcorMAX=0; VCO[4].AcorMIN=383;VCO[4].AcorMAX=244;
	VCO[4].DeltF=1200;VCO[4].DeltC=140;VCO[4].DeltA=-139;

	VCO[5].FcorMIN=12000; VCO[5].FcorMAX=12900;  VCO[5].CcorMIN=183;  VCO[5].CcorMAX=36; VCO[5].AcorMIN=205;VCO[5].AcorMAX=146;
	VCO[5].DeltF=900;VCO[5].DeltC=147;VCO[5].DeltA=-59;

	VCO[6].FcorMIN=12900; VCO[6].FcorMAX=13900;  VCO[6].CcorMIN=155;  VCO[6].CcorMAX=6; VCO[6].AcorMIN=242;VCO[6].AcorMAX=163;
	VCO[6].DeltF=1000;VCO[6].DeltC=149;VCO[6].DeltA=-79;

	VCO[7].FcorMIN=13900; VCO[7].FcorMAX=1500;  VCO[7].CcorMIN=175;  VCO[7].CcorMAX=19; VCO[7].AcorMIN=323;VCO[7].AcorMAX=244;
	VCO[7].DeltF=1100;VCO[7].DeltC=156;VCO[7].DeltA=-79;

/******Регистр Set***/
	Default();

/*
		0xD80000000500C800									  //			  | PLL_PRE
REG[12]	= 0x0C5001;// 0x0C5001; 	0x0C5001	 0x1100 0101 0000 0000 0001
											  //		 | PLL_R<<4
REG[11]	= 0x0B0018;// 0x0B0018; 	0x0B0018	 0x1011 0000 0000 0001 1000
											  //	  | MULT<<7
REG[10]	= 0x0A10D8;// 0x0A10D8; 	0x0A10D8	 0x1010 0001 0000 1101 1000
											 //| OSC2<<12
REG[9]	= 0x090604;// 0x091604; 	0x091604     0x1001 0001 0110 0000 0100

*/


//REG[12] = REG[12]&0xFF000;  //1111 1111 0000 0000 0000 0xFF000
//REG[12] = REG[12]| PLL_PRE;
//
//REG[11] = REG[11]&0xFF00F;  //1111 1111 0000 0000 1111 0xFF00F
//REG[11] = REG[11]|PLL_R<<4;
//
//REG[10] = REG[10]&0xFF07F;  //1111 1111 0000 0111 1111  0xFF07F
//REG[10] = REG[10]|MULT<<7;
//
//REG[9] = REG[9]&0xFEFFF;  //1111 1110 1111 1111 1111  0xFEFFF
//REG[9] = REG[9]|OSC2<<12;

	CURSET(I);

 }
 LMX2594::~LMX2594()
 {

 }
 void LMX2594::DIVOUTEN(int ENBL)
 {

			switch(ENBL)
	{
		case 0:
		//Reg050 &=~(1<<8);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:
	//	Reg050 &=~(1<<9);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:
//		Reg050 &=~(1<<10);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:
//		Reg050 &=~(1<<11);   // Чтобы  записат ь  ноль  в  бит  N,   выполни:


		break;
		case 1:
//		Reg050 |=(1<<8); // Чтобы  записат ь  единицу  в  бит  N,   выполни:
	//	Reg050 |=(1<<9); // Чтобы  записат ь  единицу  в  бит  N,   выполни:
//		Reg050 |=(1<<10); // Чтобы  записат ь  единицу  в  бит  N,   выполни:
//		Reg050 |=(1<<11); // Чтобы  записат ь  единицу  в  бит  N,   выполни:



		break;

	}
 }


 void LMX2594::SetREFPaTH(int OSC2,int PLL_PRE,int MLT,int PLL_R)
 {

		switch (OSC2)
	{
	case 0:  OSCDBL = 0;  break;
	case 1:  OSCDBL = 1;  break;
	default: OSCDBL = 0;  break;
	}

	 if(PLL_PRE>128) {PREr = 128;}
	 else if(PLL_PRE<1) {PREr = 1;}
	 else {	PREr = PLL_PRE; }

	     switch (MLT)
	 {
	case 1: MULT = 1;   break;
	case 3: MULT = 3;   break;
	case 4: MULT = 4;   break;
	case 5: MULT = 5;   break;
	case 6: MULT = 6;   break;
	case 7: MULT = 7;   break;
   default: MULT = 1;   break;
	 }
		if(PLL_R>255) {	POSTR =255; }
	 else if(PLL_PRE<1) {POSTR = 1; }
	 else {	POSTR = PLL_R; }



	REG[12]&=REG[12]&0xFFF000;  //1111 1111 0000 0000 0000 0xFF000
	REG[12]|=REG[12]|PREr;

	REG[11] = REG[11]&0xFFF00F;  //1111 1111 0000 0000 1111 0xFF00F
	REG[11] = REG[11]|POSTR<<4;

	REG[10] = REG[10]&0xFFF07F;  //1111 1111 0000 0111 1111  0xFF07F
	REG[10] = REG[10]|MULT<<7;

	REG[9] = REG[9]&0xFFEFFF;  //1111 1110 1111 1111 1111  0xFEFFF
	REG[9] = REG[9]|OSCDBL<<12;
 }
 void LMX2594::GAIN_RF(int GRF)
 {
	 		if(GRF>=0 & GRF<4)
	 {
	 	GainRF = GRF;
	 }
	 else
	 {
	 	GainRF = 0;
	 }

			switch(GainRF)
	{
			case 0:
		//Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
	//	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
		//Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
	//	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:

			break;
			case 1:
	//	Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
		//Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
		//Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
	//	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
			break;
			case 2:
		//Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
	//	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
	//	Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
		//Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
			break;
			case 3:
	//	Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
		//Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
	//	Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
		//Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
			break;

		default:
		//Reg050 &=~(1<<13);//Чтобы записать ноль в бит N, выполни:
	//	Reg050 |=(1<<13); //Чтобы записать единицу в бит N, выполни:
		//Reg050 &=~(1<<14);//Чтобы записать ноль в бит N, выполни:
	//	Reg050 |=(1<<14); //Чтобы записать единицу в бит N, выполни:
		break;
	}

 }
void LMX2594::SetVCO(int VCON)
{
	//VCO_CAPCTRL_STRT = round (CCoreMin – (CCoreMin – CCoreMax) × (fVCO – fCoreMin) / (fCoreMax – fCoreMin));


	VCO_CAPCTRL_ST = 	floor(0.5+VCO[VCON].CcorMIN - (VCO[VCON].DeltC)*(FregSIN-VCO[VCON].FcorMIN)/VCO[VCON].DeltF);
	REG[78] = REG[78]&0xFFFE01;  //11111111111000000001 FFE01
	REG[78] = REG[78]|VCO_CAPCTRL_ST<<1;
	//VCO_DACISET_STRT = round (ACoreMin + (ACoreMax – ACoreMin) × (fVCO – fCoreMin)/(fCoreMax – fCoreMin));
	VCO_DACISET_ST =  floor(0.5+VCO[VCON].AcorMIN + (VCO[VCON].DeltA)*(FregSIN-VCO[VCON].FcorMIN)/VCO[VCON].DeltF);
	REG[17] = REG[17]&0xFFFE00;  //1111 1111 1110 0000 0000 0xFFE00
	REG[17] = REG[17]|VCO_DACISET_ST;
}
/*
   ________   ________    __________   ____   __________ __________
   `MMMMMMMb. `MMMMMMMb.  `MMMMMMMMM  6MMMMb\ `MMMMMMMMM MMMMMMMMMM
    MM    `Mb  MM    `Mb   MM      \ 6M'    `  MM      \ /   MM   \
    MM     MM  MM     MM   MM        MM        MM            MM
    MM     MM  MM     MM   MM    ,   YM.       MM    ,       MM
    MM    .M9  MM    .M9   MMMMMMM    YMMMMb   MMMMMMM       MM
    MMMMMMM9'  MMMMMMM9'   MM    `        `Mb  MM    `       MM
    MM         MM  \M\     MM              MM  MM            MM
    MM         MM   \M\    MM              MM  MM            MM
    MM         MM    \M\   MM      / L    ,M9  MM      /     MM
   _MM_       _MM_    \M\__MMMMMMMMM MYMMMM9  _MMMMMMMMM    _MM_
*/
void LMX2594::Default()
{
	/******Регистр Set***/
		REG[112]= 0x700000; //0x700000; 	0x700000
		REG[111]= 0x6F0000; //0x6F0000; 	0x6F0000
		REG[110]= 0x6E0000; //0x6E0000; 	0x6E0000
		REG[109]= 0x6D0000; //0x6D0000; 	0x6D0000
		REG[108]= 0x6C0000; //0x6C0000; 	0x6C0000
		REG[107]= 0x6B0000; //0x6B0000; 	0x6B0000
		REG[106]= 0x6A0000; //0x6A0000; 	0x6A0000
		REG[105]= 0x690021; //0x690021; 	0x690021
		REG[104]= 0x680000; //0x680000; 	0x680000
		REG[103]= 0x670000; //0x670000; 	0x670000
		REG[102]= 0x660000; //0x660000; 	0x660000
		REG[101]= 0x650011; //0x650011; 	0x650011
		REG[100]= 0x640000; //0x640000; 	0x640000
		REG[99]	= 0x630000; // 0x630000; 	0x630000
		REG[98]	= 0x620000; // 0x620000; 	0x620000
		REG[97]	= 0x610888; // 0x610888; 	0x610888
		REG[96]	= 0x600000; // 0x600000; 	0x600000
		REG[95]	= 0x5F0000; // 0x5F0000; 	0x5F0000
		REG[94]	= 0x5E0000; // 0x5E0000; 	0x5E0000
		REG[93]	= 0x5D0000; // 0x5D0000; 	0x5D0000
		REG[92]	= 0x5C0000; // 0x5C0000; 	0x5C0000
		REG[91]	= 0x5B0000; // 0x5B0000; 	0x5B0000
		REG[90]	= 0x5A0000; // 0x5A0000; 	0x5A0000
		REG[89]	= 0x590000; // 0x590000; 	0x590000
		REG[88]	= 0x580000; // 0x580000; 	0x580000
		REG[87]	= 0x570000; // 0x570000; 	0x570000
		REG[86]	= 0x560000; // 0x560000; 	0x560000
		REG[85]	= 0x550000; // 0x550000; 	0x550000
		REG[84]	= 0x540000; // 0x540000; 	0x540000
		REG[83]	= 0x530000; // 0x530000; 	0x530000
		REG[82]	= 0x520000; // 0x520000; 	0x520000
		REG[81]	= 0x510000; // 0x510000; 	0x510000
		REG[80]	= 0x500000; // 0x500000; 	0x500000
		REG[79]	= 0x4F0000; // 0x4F0000; 	0x4F0000
		REG[78]	= 0x4E0203; // 0x4E0003; 	0x4E0003  <-0x4E00BF
		REG[77]	= 0x4D0000; // 0x4D0000; 	0x4D0000
		REG[76]	= 0x4C000C; // 0x4C000C; 	0x4C000C
		REG[75]	= 0x4B0800; // 0x4B0C40; 	0x4B0800
		REG[74]	= 0x4A0000; // 0x4A0000; 	0x4A0000
		REG[73]	= 0x49003F; // 0x49003F; 	0x49003F
		REG[72]	= 0x480001; // 0x480001; 	0x480001
		REG[71]	= 0x470081; // 0x470081; 	0x470081
		REG[70]	= 0x46C350; // 0x46C350; 	0x46C350
		REG[69]	= 0x450000; // 0x450000; 	0x450000
		REG[68]	= 0x4403E8; // 0x4403E8; 	0x4403E8
		REG[67]	= 0x430000; // 0x430000; 	0x430000
		REG[66]	= 0x4201F4; // 0x4201F4; 	0x4201F4
		REG[65]	= 0x410000; // 0x410000; 	0x410000
		REG[64]	= 0x401388; // 0x401388; 	0x401388
		REG[63]	= 0x3F0000; // 0x3F0000; 	0x3F0000
		REG[62]	= 0x3E0322; // 0x3E0322; 	0x3E0322
		REG[61]	= 0x3D00A8; // 0x3D00A8; 	0x3D00A8
		REG[60]	= 0x3C0000; // 0x3C0000; 	0x3C0000
		REG[59]	= 0x3B0001; // 0x3B0001; 	0x3B0001
		REG[58]	= 0x3A8001; // 0x3A8001; 	0x3A8001
		REG[57]	= 0x390020; // 0x390020; 	0x390020
		REG[56]	= 0x380000; // 0x380000; 	0x380000
		REG[55]	= 0x370000; // 0x370000; 	0x370000
		REG[54]	= 0x360000; // 0x360000; 	0x360000
		REG[53]	= 0x350000; // 0x350000; 	0x350000
		REG[52]	= 0x340820; // 0x340820; 	0x340820
		REG[51]	= 0x330080; // 0x330080; 	0x330080
		REG[50]	= 0x320000; // 0x320000; 	0x320000
		REG[49]	= 0x314180; // 0x314180; 	0x314180
		REG[48]	= 0x300300; // 0x300300; 	0x300300
		REG[47]	= 0x2F0300; // 0x2F0300; 	0x2F0300
		REG[46]	= 0x2E07FD; // 0x2E07FD; 	0x2E07FD  111111
		REG[45]	= 0x2DC8FF; // 0x2DC8DF; 	0x2DC8DF  2DC8FF   //FIXME: POW @LMX (0)
		REG[44]	= 0x2C3F23; // 0x2C1FA3; 	0x2C1FA3  2C3F23
		REG[43]	= 0x2B0000; // 0x2B0000; 	0x2B0000  nom15:0
		REG[42]	= 0x2A0000; // 0x2A0000; 	0x2A0000  nom31:16
		REG[41]	= 0x290000; // 0x290000; 	0x290000
		REG[40]	= 0x280000; // 0x280000; 	0x280000
		REG[39]	= 0x270000; // 0x2703E8; 	0x2703E8  denom15:0
		REG[38]	= 0x260100; // 0x260000; 	0x260000  denom31:16
		REG[37]	= 0x250404; // 0x250304; 	0x250304
		REG[36]	= 0x240050; // 0x240029; 	0x240029
		REG[35]	= 0x230004; // 0x230004; 	0x230004  1000110000000000000100
		REG[34]	= 0x220000; // 0x220000; 	0x220000  2228224
		REG[33]	= 0x211E21; // 0x211E21; 	0x211E21
		REG[32]	= 0x200393; // 0x200393; 	0x200393
		REG[31]	= 0x1F43EC; // 0x1F03EC; 	0x1F03EC
		REG[30]	= 0x1E318C; // 0x1E318C; 	0x1E318C
		REG[29]	= 0x1D318C; // 0x1D318C; 	0x1D318C
		REG[28]	= 0x1C0488; // 0x1C0488; 	0x1C0488
		REG[27]	= 0x1B0002; // 0x1B0002; 	0x1B0002
		REG[26]	= 0x1A0DB0; // 0x1A0DB0; 	0x1A0DB0
		REG[25]	= 0x190C2B; // 0x190C2B; 	0x190624
		REG[24]	= 0x18071A; // 0x18071A; 	0x18071A
		REG[23]	= 0x17007C; // 0x17007C; 	0x17007C
		REG[22]	= 0x160001; // 0x160001; 	0x160001
		REG[21]	= 0x150401; // 0x150401; 	0x150401
		REG[20]	= 0x14E048; // 0x14E048; 	0x14E048 <-
		REG[19]	= 0x1327B7; // 0x1327B7; 	0x1327B7
		REG[18]	= 0x120064; // 0x120064; 	0x120064
		REG[17]	= 0x11012C; // 0x11012C; 	0x11012C <-
		REG[16]	= 0x100080; // 0x100080; 	0x100080
		REG[15]	= 0x0F064F; // 0x0F064F; 	0x0F064F
		REG[14]	= 0x0E1E40; // 0x0E1E70; 	0x0E1E70 <-1110
		REG[13]	= 0x0D4000; // 0x0D4000; 	0x0D4000
		REG[12]	= 0x0C5001; // 0x0C5001; 	0x0C5001	 0x1100 0101 0000 0000 0001
		REG[11]	= 0x0B0018; // 0x0B0018; 	0x0B0018	 0x1011 0000 0000 0001 1000
		REG[10]	= 0x0A10D8; // 0x0A10D8; 	0x0A10D8	 0x1010 0001 0000 1101 1000
		REG[9]	= 0x090604; // 0x091604; 	0x091604     0x1001 0001 0110 0000 0100
		REG[8]	= 0x082000; // 0x082000; 	0x082000
		REG[7]	= 0x0740B2; // 0x0740B2; 	0x0740B2
		REG[6]	= 0x06C802; // 0x06C802; 	0x06C802	D8000000EDE5F200
		REG[5]	= 0x0500C8; // 0x0500C8; 	0x0500C8    A80000000D00C800
		REG[4]	= 0x040A43; // 0x040A43; 	0x040A43    a80000000D000000
		REG[3]	= 0x030642; // 0x030642; 	0x030642
		REG[2]	= 0x020500; // 0x020500; 	0x020500
		REG[1]	= 0x010808; // 0x010808; 	0x010808   1 0000 1000 0000 1000
		REG[0]	= 0x00241C; // 0x002514; 	0x002518      241C 10010000011100
		REG[113] = 0x00241C; // 0x002514; 	0x002518      241A 10010000011010
		REG[114] = 0x00241C; // 0x002514; 	0x002518      2418 10010000011000

}
//10010000011100
//00000000001010
/* ### ## ### ##  ### ###  ## ## ### ### #### ##
    ##  ## ##  ##  ##  ## ##   ## ##  ## # ## ##
    ##  ## ##  ##  ##     ####    ##       ##
    ##  ## ## ##   ## ##   #####  ## ##    ##
    ## ##  ## ##   ##         ### ##       ##
    ##     ##  ##  ##  ## ##   ## ##  ##   ##
   ####   #### ## ### ###  ## ## ### ###  ####
*/
void LMX2594::SETPRESET(int PR)
{

	NSET(REGIM[PR].NINT);
	CURSET(REGIM[PR].CURSET);
	SEG1EN(REGIM[PR].SEG1EN);
	FCAL_EN(REGIM[PR].FCAL_EN);
	OUTAPWR(REGIM[PR].OUTAPWR);
	OUTBPWR(REGIM[PR].OUTBPWR);
	CHANDiV(REGIM[PR].CHANDiV);

}
void LMX2594::SETRGIM(int N,int CUR,int SEG1,int FCAL,int APWR,int BPWR,int CDiV)
{
	NSET(N);
	CURSET(CUR);
	SEG1EN(SEG1);
	FCAL_EN(FCAL);
	OUTAPWR(APWR);
	OUTBPWR(BPWR);
	CHANDiV(CDiV);
}

void LMX2594::FReset(int RES)
{
	REG[0] = REG[0]&0xFFFFFD;
	REG[0] = REG[0]|RES<<1;
}
void LMX2594::PDovn(int PD)
{
	REG[0] = REG[0]&0xFFFFFE;
	REG[0] = REG[0]|PD;
}

void LMX2594::MoUTLD(int SEL)
{
	REG[0] = REG[0]&0xFFFFFB;
	REG[0] = REG[0]|SEL<<2;
}

void LMX2594::LDTupe(int Sel)
{
	REG[59] = REG[59]&0xFFFFFE;  //3B 59  1110
	REG[59] = REG[59]|Sel;
}
void LMX2594::LDDLY(int SEL)
{
	REG[60] = REG[60]&0xFF0000;  //3C 60
	REG[60] = REG[60]|SEL;
}
/****Новый блок VCO**/

int LMX2594::VCO_SEL_FORCE(int VALUE)
{
	REG[20] = REG[20]&0xFFFBFF;  // R20[10]  FFFBFF
	REG[20] = REG[20]|VALUE<<10;
	return 20;
}
int LMX2594::VCO_SEL(int VALUE)
{
	VCOSEL = VALUE;
	REG[20] = REG[20]&0xFFC7FF;  // R20[13:11] FFC7FF
	REG[20] = REG[20]|VALUE<<11;
	return 20;
}
int LMX2594::VCO_CAPCTRL_FORCE(int VALUE)
{
	REG[8] = REG[8]&0xFFF7FF;  //  R8[11] FFF7FF
	REG[8] = REG[8]|VALUE<<11;
	return 8;
}
int LMX2594::VCO_CAPCTRL(int VALUE)
{
	REG[19] = REG[19]&0xFFFF00;  // R19[7:0]
	REG[19] = REG[19]|VALUE;
	return 19;
}
void LMX2594::VCO_CAPCTRL_STRT(int VALUE)
{
	REG[78] = REG[78]&0xFFFE01;  // R78[8:1] FFFE01
	REG[78] = REG[78]|VALUE<<1;
}
/*****************************/
void LMX2594::VCO_DACISET_FORCE(int VALUE)
{
	REG[8] = REG[8]&0xFFF7FF;  //1111 1111 1110 0000 0000 0xFF7FF
	REG[8] = REG[8]|VALUE<<11;//R8[11]
}
void LMX2594::VCO_DACISET_STRT(int VALUE)
{
	VCO_DACISET_ST =  VALUE;
	REG[17] = REG[17]&0xFFFE00;  //1111 1111 1110 0000 0000 0xFFE00
	REG[17] = REG[17]|VCO_DACISET_ST;//R17[8:0]
}
void LMX2594::VCO_DACISET(int VALUE)
{
	REG[16] = REG[16]&0xFFFE00;  //1111 1111 1110 0000 0000 0xFFE00
	REG[16] = REG[16]|VALUE;	//R16[8:0]
}
/**********************************************/
void LMX2594::NSET(int VALUE)
{
	REG[34] = REG[34]&0xFF0000;
	REG[34] = REG[34]|(VALUE>>16&0x7);

	REG[36] = REG[36]&0xFF0000;
	REG[36] = REG[36]|(VALUE&0xFFFF);
}
void LMX2594::FRSET(int VALUE)
{
	REG[42] = REG[42]&0xFF0000;//&=~(1<<15);//Чтобы записать ноль в бит N, выполни:
	REG[42] = REG[42]|VALUE>>16&0xFFFF;//|=(1<<15); //Чтобы записать единицу в бит N, выполни:


	REG[43] = REG[43]&0xFF0000;
	REG[43] = REG[43]|VALUE&0xFFFF;
}
int LMX2594::FCAL_EN(int VALUE)
{
	REG[0] = REG[0]&0xFFFFF7;
	REG[0] = REG[0]|(VALUE<<3);
	return 0;
}
/****************CUR_SET********************/
int LMX2594::CURSET(int VALUE)
{
/*
  +----+------------+
  |Code|   current  |
  +----+------------+
  |  0:| 0 mA       |
  +----+------------+
  |  1:| 6 mA       |
  +----+------------+
  |  2:| Reserved   |
  +----+------------+
  |  3:| 12 mA      |
  +----+------------+
  |  4:| 3 mA       |
  +----+------------+
  |  5:| 9 mA       |
  +----+------------+
  |  6:| Reserved   |
  +----+------------+
  |  7:| 15 mA      |
  +----+------------+ */

	REG[14] = REG[14]&0xFFFF8F;
	REG[14] = REG[14]|(VALUE<<4);//R14[6:4]
	return 14;
}
void LMX2594::FCALHPFDADJ(int VALUE)
{
	REG[0] = REG[0]&0xFFFE7F;
	REG[0] = REG[0]|(VALUE<<7);	//R0[8:7]
}
void LMX2594::FCALLPFDADJ(int VALUE)
{
	REG[0] = REG[0]&0xFFFF9F;
	REG[0] = REG[0]|(VALUE<<5);	//R0[6:5]
}
void LMX2594::CALCLKDIV(int VALUE)
{
	REG[1] = REG[1]&0xFFFFF8;  //R1[2:0]
	REG[1] = REG[1]|(VALUE);
}
/*===== ========================  ======*/

int LMX2594::CHANDiV(int VALUE)//R75[10:6]
{
	REG[75] = REG[75]&0xFFF83F;
	REG[75] = REG[75]|VALUE<<6;
	return 75;
}
int LMX2594::SEG1EN(int VALUE)//R31[14]
{
	REG[31] = REG[31]&0xFFBFFF;
	REG[31] = REG[31]|VALUE<<14;
		return 31;
}
int LMX2594::OUTAPWR(int VALUE)//R44[13:8]
{
	REG[44] = REG[44]&0xFFC0FF;
	REG[44] = REG[44]|VALUE<<8;
		return 44;
}
int LMX2594::OUTAMUX(int VALUE)//R45[12:11] E 7 FF
{
	REG[45] = REG[45]&0xFFE7FF;      // 0x2D 1100 1000 1101 1111	 C 8 D F  VCO
	REG[45] = REG[45]|VALUE<<11;      //		1100 0000 1101 1111    C 0 D F Channel divider
		return 45;                    //		1101 1000 1101 1111    D 8 D F Z
}
int LMX2594::OUTBPWR(int VALUE)//R45[5:0]
{

	REG[45] = REG[45]&0xFFFFC0; //R45[5:0]
	REG[45] = REG[45]|VALUE;	//		0 7 F C 	0 111 1111 1100 грузит наоборот
		return 45;				//    	0 7 F D 	0 111 1111 1101
}
int LMX2594::OUTBMUX(int VALUE)//R46[1:0]
{
	REG[46] = REG[46]&0xFFFFFC;
	REG[46] = REG[46]|VALUE;
		return 46;
}

int LMX2594::OUTAPD(int VALUE)//R44[6]
{
	REG[44] = REG[44]&0xFFFFBF;//111111111111111110111111 FFFFBF
	REG[44] = REG[44]|VALUE<<6;
	return 44;
}
int LMX2594::OUTBPD(int VALUE)//R44[7]
{
	REG[44] = REG[44]&0xFFFF7F;//111111111111111101111111  FFFF7F
	REG[44] = REG[44]|VALUE<<7;
	return 44;
}
/*=====  End of CH DIV  ======*/


void LMX2594::SetFreq(double fsint)
 {   int a = 0;

  if (fsint >= 7500 && fsint <= 8600)
	  {
		FregSIN = fsint;//FreqAktual = freq;
		a = 1;
		VCOSEL = 1;

	  }
 if (fsint >= 8600 && fsint < 9800) //1035 fsint >= 25
	  {
		FregSIN = fsint;// FreqAktual = freq*2;
		a = 1;
		VCOSEL = 2;

	  }


 if (fsint >= 9800 && fsint < 10800) //
	  {
		FregSIN = fsint;//
		a = 1;
		VCOSEL = 3;

	  }
 if (fsint >= 10800 && fsint < 12000 ) //
	  {
		FregSIN = fsint;//
		a = 1;
		VCOSEL = 4;
	  }
  if (fsint >= 12000 && fsint < 12900) //
	  {
		FregSIN = fsint;// FreqAktual = freq*2;
		a = 1;
		VCOSEL = 5;
	  }

		if (fsint >= 12900 && fsint <13900 )
	  {
		FregSIN = fsint;//
		a = 1;
		VCOSEL = 6;
	  }
										//  1111 1110 1100 1000 0100 1000
   if (fsint >= 13900 && fsint <=15000 ) //  11 101 110 1000 0100  10100
	  {
		FregSIN = fsint;// FreqAktual = freq*2;
		 a = 1;
		VCOSEL = 7;
	  }
	if (a==0)
	  {
		FregSIN = 8000;
		VCOSEL = 1;
	  }
	REG[20] = REG[20]&0xFFC7FF;  //1111 1100 0111 1111 1111 0xFC7FF
	REG[20] = REG[20]|VCOSEL<<11;
	SetVCO(VCOSEL);
	Fpd = Xtal*(OSCDBL+1)*MULT/(PREr*POSTR);
      POSTR = 1;
	  Nakt = FregSIN/Fpd;
//			if (Nakt<24)
//	  {
//			POSTR = POSTR*2;
//			REG[11] = REG[11]&0xFFF00F;  //1111 1111 0000 0000 1111 0xFF00F
//			REG[11] = REG[11]|POSTR<<4;
//			Fpd = (OSCDBL+1)*MULT/(PREr*POSTR);
//			Nakt = FregSIN/Fpd;
//	  }

	  		if(Fpd>200)
	  	{
	  		/* code */
	  	}
	  		else if(Fpd>150)
	  			{
	  				/* code */
	  			}
	  				else if (Fpd>100)
	  				{
	  					/* code */
	  				}
	  				else
	  			{
	  				/* code */
	  			}

		Nint = floor(Nakt);
		NIint =	Nint;
		Nfrak = floor(0.5 + pow(2.0,24)*(Nakt - Nint));

		REG[34] = REG[34]&0xFF0000;
		REG[34] = REG[34]|(NIint>>16&0x7);


		REG[36] = REG[36]&0xFF0000;
		REG[36] = REG[36]|(NIint&0xFFFF);

		REG[42] = REG[42]&0xFF0000;//&=~(1<<15);//Чтобы записать ноль в бит N, выполни:
		REG[42] = REG[42]|Nfrak>>16&0xFFFF;//|=(1<<15); //Чтобы записать единицу в бит N, выполни:


		REG[43] = REG[43]&0xFF0000;
		REG[43] = REG[43]|Nfrak&0xFFFF;
}
/*

	 ####                 #                        #
	 #   #                #                        #
	 #   #   ###    ## #  #       ###    ###    ## #
	 ####   #   #  #  #   #      #   #      #  #  ##
	 # #    #####   ##    #      #   #   ####  #   #
	 #  #   #      #      #      #   #  #   #  #  ##
	 #   #   ###    ###   #####   ###    ####   ## #
	               #   #
	                ###
*/

long LMX2594::RegLoadLMX2594(int NReg)
  {

/************Регистр Load***********/
  	return REG[NReg];

  }
 /*



  	  ##    ###   ###  ####  # ##  # # #####
  	  ##   ## ## ## ## ## ## # ##  # #  ##
  	  ##   ##  # ## ## ## ## # ### # #  ##
  	  ##   ##  # ##### ## ## # ##### #  ##
  	  ##   ## ## ## ## ## ## # ## ## #  ##
  	  ####  ###  ## ## ####  # ##  # #  ##


  */

long LMX2594::RegLoadINIT(int RG)
{
		switch (RG)
	{
		case 0:  return REG[113]; break;// return REG[113];  break;
		case 1:  return REG[114]; break;// return REG[114];  break;
		case 2:  return REG[0]; break;// return REG[0];  break;
		case 3:  return REG[112]; break;// return REG[75];  break;//Nint
		case 4:  return REG[111]; break;// return REG[45];  break;//Nint
		case 5:  return REG[110]; break;// return REG[44];  break;//FRSET
		case 6:  return REG[109]; break;// return REG[43];  break;//FRSET
		case 7:  return REG[108]; break;// return REG[42];  break;//OUTAPWR
		case 8:  return REG[107]; break;// return REG[36];  break;//OUTBPWR
		case 9:  return REG[106]; break;// return REG[32];  break;//CHANDiV
		case 10: return REG[105]; break;// return REG[31];  break;//CURSET
		case 11: return REG[104]; break;// return REG[14];  break;//SEG1EN
		case 12: return REG[103]; break;// return REG[0];  break; // FCAL_EN
		case 13: return REG[102]; break;//
		case 14: return REG[101]; break;//
		case 15: return REG[100]; break;//
		case 16: return REG[99]; break;//
		case 17: return REG[98]; break;//
		case 18: return REG[97]; break;//
		case 19: return REG[96]; break;//
		case 20: return REG[95]; break;//
		case 21: return REG[94]; break;//
		case 22: return REG[93]; break;//
		case 23: return REG[92]; break;//
		case 24: return REG[91]; break;//
		case 25: return REG[90]; break;//
		case 26: return REG[89]; break;//
		case 27: return REG[88]; break;//
		case 28: return REG[87]; break;//
		case 29: return REG[86]; break;//
		case 30: return REG[85]; break;//
		case 31: return REG[84]; break;//
		case 32: return REG[83]; break;//
		case 33: return REG[82]; break;//
		case 34: return REG[81]; break;//
		case 35: return REG[80]; break;//
		case 36: return REG[79]; break;//
		case 37: return REG[78]; break;//
		case 38: return REG[77]; break;//
		case 39: return REG[76]; break;//
		case 40: return REG[75]; break;//
		case 41: return REG[74]; break;//
		case 42: return REG[73]; break;//
		case 43: return REG[72]; break;//
		case 44: return REG[71]; break;//
		case 45: return REG[70]; break;//
		case 46: return REG[69]; break;//
		case 47: return REG[68]; break;//
		case 48: return REG[67]; break;//
		case 49: return REG[66]; break;//
		case 50: return REG[65]; break;//
		case 51: return REG[64]; break;//
		case 52: return REG[63]; break;//
		case 53: return REG[62]; break;//
		case 54: return REG[61]; break;//
		case 55: return REG[60]; break;//
		case 56: return REG[59]; break;//
		case 57: return REG[58]; break;//
		case 58: return REG[57]; break;//
		case 59: return REG[56]; break;//
		case 60: return REG[55]; break;//
		case 61: return REG[54]; break;//
		case 62: return REG[53]; break;//
		case 63: return REG[52]; break;//
		case 64: return REG[51]; break;//
		case 65: return REG[50]; break;//
		case 66: return REG[49]; break;//
		case 67: return REG[48]; break;//
		case 68: return REG[47]; break;//
		case 69: return REG[46]; break;//
		case 70: return REG[45]; break;//
		case 71: return REG[44]; break;//
		case 72: return REG[43]; break;//
		case 73: return REG[42]; break;//
		case 74: return REG[41]; break;//
		case 75: return REG[40]; break;//
		case 76: return REG[39]; break;//
		case 77: return REG[38]; break;//
		case 78: return REG[37]; break;//
		case 79: return REG[36]; break;//
		case 80: return REG[35]; break;//
		case 81: return REG[34]; break;//
		case 82: return REG[33]; break;//
		case 83: return REG[32]; break;//
		case 84: return REG[31]; break;//
		case 85: return REG[30]; break;//
		case 86: return REG[29]; break;//
		case 87: return REG[28]; break;//
		case 88: return REG[27]; break;//
		case 89: return REG[26]; break;//
		case 90: return REG[25]; break;//
		case 91: return REG[24]; break;//
		case 92: return REG[23]; break;//
		case 93: return REG[22]; break;//
		case 94: return REG[21]; break;//
		case 95: return REG[20]; break;//
		case 96: return REG[19]; break;//
		case 97: return REG[18]; break;//
		case 98: return REG[17]; break;//
		case 99: return REG[16]; break;//
		case 100: return REG[15]; break;//
		case 101: return REG[14]; break;//
		case 102: return REG[13]; break;//
		case 103: return REG[12]; break;//
		case 104: return REG[11]; break;//
		case 105: return REG[10]; break;//
		case 106: return REG[9]; break;//
		case 107: return REG[8]; break;//
		case 108: return REG[7]; break;//
		case 109: return REG[6]; break;//
		case 110: return REG[5]; break;//
		case 111: return REG[4]; break;//
		case 112: return REG[3]; break;//
		case 113: return REG[2]; break;//
		case 114: return REG[1]; break;//
		case 115: return REG[0]; break;//

		default: return REG[0];   break;
	}

}

long LMX2594::RegLoadF(int RG)
{
	//	TODO: Load LMX2594 CR(3)

		switch (RG)
	{
		case 0:  return REG[8 ];  break;
		case 1:  return REG[19];  break;
		case 2:  return REG[20];  break;
		case 3:  return REG[34];  break;//Nint
		case 4:  return REG[36];  break;//Nint
		case 5:  return REG[75];  break;//FRSET
		default: return REG[75];   break;
	}

}






#pragma package(smart_init)
