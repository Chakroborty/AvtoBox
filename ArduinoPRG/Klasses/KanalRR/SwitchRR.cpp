//---------------------------------------------------------------------------


#pragma hdrstop

#include "SwitchRR.h"
#include <math.h>


//---------------------------------------------------------------------------
 CSwitchRR::CSwitchRR(int Mod_kanalNum)
{
	AdrMod = Adress::OBSH;
	MADT7310 = new ADT7310();

ASW[0].Att1 =                 0x3100000;
ASW[0].Att2 =                 0x3200000;
ASW[0].In_SW =                0x4100000;
ASW[0].LNA_sw =               0x4200000;
ASW[0].Conv_sw =              0x4300000;
ASW[0].UsilPCH_sw =           0x4400000;
ASW[0].Filtr_sw =             0x4500000;
ASW[0].PwrOnUsil_sw =         0x4600000;
ASW[0].Pres_Fil_sw =          0x4800000;
ASW[0].Control_T =            0x5100000;
ASW[0].Control_R=             0x5E00000;

                              //0xC000000;
ASW[0].SR =                   0xC100000;// регистр
ASW[0].FSR =                  0xC200000;// регистр
ASW[0].NVCR  =                0xC300000;// регистр
ASW[0].VCR  =                 0xC400000;// регистр
ASW[0].EVCR  =                0xC500000;// регистр
ASW[0].WriteFregIN =          0xC600000;//Write Enable operation
                              //0xC700000;
ASW[0].ClearFSt =             0xC800000;
                              //0xC900000;
ASW[0].Write1b =              0xCA00000;//Write 1 byte to flash memory 
ASW[0].Read5b =               0xCB00000;//Read 5 byte from flash memory
                              //0xCC00000;
                              //0xCD00000;
ASW[0].BulkEr =               0xCE00000;
                              //0xCF00000;
ASW[0].Rflash =               0xE000000;
ASW[0].ReadST =               0xEF00000;  



ASW[1].Att1 =         0x0;
ASW[1].Att2 =         0x0;
ASW[1].In_SW =        0x0;
ASW[1].LNA_sw =       0x0;
ASW[1].Conv_sw =      0x1;
ASW[1].UsilPCH_sw =   0x0;
ASW[1].Filtr_sw =     0x0;
ASW[1].PwrOnUsil_sw = 0xF;
ASW[1].Pres_Fil_sw =  0x0;
ASW[1].Control_T =    0x0;
ASW[1].Control_R=      0;
ASW[1].ReadST =         0;







ASW[2].Att1 =          16;
ASW[2].Att2 =          16;
ASW[2].In_SW =         18;
ASW[2].LNA_sw =        18;
ASW[2].Conv_sw =       19;
ASW[2].UsilPCH_sw =    18;
ASW[2].Filtr_sw =      19;
ASW[2].PwrOnUsil_sw =  16;
ASW[2].Pres_Fil_sw =   16;
ASW[2].Control_T =     0;
ASW[2].Control_R=      20; 
ASW[2].ReadST =        24;





 
 
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
 DIAPAZON[0][11] =  0x21<<13;	DIAPAZON[1][11] =  0x5F<<13;
 DIAPAZON[0][12] =  0x20<<13;	DIAPAZON[1][12] =  0x5E<<13;
 


LNAMATRIX[0][0].UPR = 1<<19;
	                            LNAMATRIX[0][0].RNG = 1<<18;
LNAMATRIX[0][1].UPR = 0<<19; 	LNAMATRIX[0][1].RNG = 0<<18;


LNAMATRIX[1][0].UPR = 0<<19;	LNAMATRIX[1][0].RNG = 0<<18;
LNAMATRIX[1][1].UPR = 1<<19;	LNAMATRIX[1][1].RNG = 1<<18;
 
 



}
 CSwitchRR::~CSwitchRR()
{
	//Freal = 10;
}
 

 void CSwitchRR::WriteFregIN(double freqCR, int Kanal)
{      
	  KanalNum_B_Mod =  Kanal;

	     



}
 int CSwitchRR::LoadKL(int div)
{    int i;
	 int  SW_SW;
 if (div >= 0 && div < 24)
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
    SW_SW = AdrMod|ASW[0].Att1|ASW[1].Att1<<16;
    break;
    case 1:
    SW_SW = AdrMod|ASW[0].Att2|ASW[1].Att2<<16;
    break;
    case 2:
    SW_SW = AdrMod|ASW[0].In_SW|ASW[1].In_SW<<18 ;
    break;
    case 3:
    SW_SW = AdrMod|ASW[0].LNA_sw|ASW[1].LNA_sw<<18;
    break;
    case 4:
    SW_SW = AdrMod|ASW[0].Conv_sw|ASW[1].Conv_sw<<19;
    break;
    case 5:
    SW_SW = AdrMod|ASW[0].UsilPCH_sw|ASW[1].UsilPCH_sw<<18;
    break;
    case 6:
    SW_SW = AdrMod|ASW[0].Filtr_sw|ASW[1].Filtr_sw<<19;
    break;
    case 7:
    SW_SW = AdrMod|ASW[0].PwrOnUsil_sw|ASW[1].PwrOnUsil_sw<<16;
    break;
    case 8:
    SW_SW = AdrMod|ASW[0].Pres_Fil_sw|ASW[1].Pres_Fil_sw<<16;
    break;  
    case 9:
    SW_SW = AdrMod|ASW[0].Control_T|ASW[1].Control_T<<ASW[2].Control_T;
    break; 
    case 10:
    SW_SW = AdrMod|ASW[0].Control_R|ASW[1].Control_R<<ASW[2].Control_R;
    break;  
    case 22:
    SW_SW = AdrMod|ASW[0].ReadST|ASW[1].ReadST<<ASW[2].ReadST;
    break; 
    case 23:
    SW_SW = AdrMod|ASW[0].Rflash|ASW[1].Rflash<<ASW[2].Rflash;
    break;     
	default : SW_SW = AdrMod|ASW[0].Filtr_sw|ASW[1].Filtr_sw<<16;break;
   }
   
	return  SW_SW;
}
void CSwitchRR::AmplifSET(int Amplif)
 {

	  ASW[1].LNA_sw = Amplif;

 }
void CSwitchRR::ATT1_SET(double DB)
{
	if (DB >= 0 && DB <= 63)
	   {
		ASW[1].Att1 = 0x3F -(int)(DB) ;
	   }
	else
	   {
		ASW[1].Att1 = 0;
	   }

}
void CSwitchRR::ATT2_SET(double DB)
{
   if (DB >= 0 && DB <= 63)
   {
	ASW[1].Att2 = 0x3F -(int)(DB);
   }
   else
   {
	ASW[1].Att2 = 0;
   }

}
void CSwitchRR::ATT3_SET(double DB)
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
void CSwitchRR::ATT4_SET(double DB)
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
void CSwitchRR::PRESELSET(int PRES)
{

		ASW[1].Pres_Fil_sw = PRES;

		
}

int CSwitchRR::LoadATT(int div)
{    
    int i;
    int  ATT_db;
      if (div >= 0 && div < 8)
    {i = div;}
    else
    {i = 0;}
//****************************************************************
           switch (i)
    {
      case 0:
      ATT_db = AdrMod + ASW[0].Att1+ASW[1].Att1;
      break;
      case 1:
      ATT_db = AdrMod + ASW[0].Att2+ASW[1].Att2;
      break;
      default : ATT_db = AdrMod| + ASW[0].Att2+ASW[1].Att2;break;
    }
//****************************************************************
    return  ATT_db;
}

int CSwitchRR::SRCOM()
{
  return MADT7310->RCOM(0)<<24;
}



#pragma package(smart_init)