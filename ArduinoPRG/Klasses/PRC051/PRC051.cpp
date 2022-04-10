//---------------------------------------------------------------------------


#pragma hdrstop

#include "PRC051.h"
#include <math.h>


//---------------------------------------------------------------------------
 PRC51::PRC51(int Mod_kanalNum)
{
		AdrMod = Adress::OBSH;
  DLMX2594 = new LMX2594(8000,60,28,100);
  FCHP2594 = new FCHP();

ASW[0].Att1 =         0x31000000;
ASW[0].Att2 =         0x32000000; //Адрес устр.
ASW[0].In_SW =        0x41000000;
ASW[0].LNA_sw =       0x42000000;
ASW[0].Conv_sw =      0x43000000;
ASW[0].UsilPCH_sw =   0x44000000;
ASW[0].Filtr_sw =     0x45000000;
ASW[0].refsw =        0x46000000;
ASW[0].lptrf =        0x47000000;
ASW[0].Pres_Fil_sw =  0x48000000;
ASW[0].uxm15p =       0x49000000;
ASW[0].sinth=         0x80000000;

ASW[1].Att1 =         0x0;
ASW[1].Att2 =         0x0;
ASW[1].In_SW =        0x0;
ASW[1].LNA_sw =       0x0;  //Значение
ASW[1].Conv_sw =      0x1;
ASW[1].UsilPCH_sw =   0x0;
ASW[1].Filtr_sw =     0x0;
ASW[1].refsw =        0xF;
ASW[1].lptrf =        0x0;
ASW[1].Pres_Fil_sw =    0;
ASW[1].uxm15p =         0;
ASW[1].sinth=         0;

ASW[2].Att1 =         20;
ASW[2].Att2 =         20;
ASW[2].In_SW =        21; //Сдвиг
ASW[2].LNA_sw =       22;
ASW[2].Conv_sw =      23;
ASW[2].UsilPCH_sw =   22;
ASW[2].Filtr_sw =     23;
ASW[2].refsw =        23;
ASW[2].lptrf =        23;
ASW[2].Pres_Fil_sw =  21;
ASW[2].uxm15p =       21;
ASW[2].sinth=         4;
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
 PRC51::~PRC51()
{
	//Freal = 10;
}


 void PRC51::WriteFregIN(double freqCR, int Kanal)
{
	  KanalNum_B_Mod =  Kanal;





}
 int PRC51::LoadKL(int div)
{    int i;
	 int  SW_SW;
 if (div >= 0 && div < 11)
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
    SW_SW = ASW[0].Att1|ASW[1].Att1<<ASW[2].Att1;
    break;
    case 1:
    SW_SW = ASW[0].Att2|ASW[1].Att2<<ASW[2].Att2;
    break;
    case 2:
    SW_SW = ASW[0].In_SW|ASW[1].In_SW<<ASW[2].In_SW ;
    break;
    case 3:
    SW_SW = ASW[0].LNA_sw|ASW[1].LNA_sw<<ASW[2].LNA_sw;
    break;
    case 4:
    SW_SW = ASW[0].Conv_sw|ASW[1].Conv_sw<<ASW[2].Conv_sw;
    break;
    case 5:
    SW_SW = ASW[0].UsilPCH_sw|ASW[1].UsilPCH_sw<<ASW[2].UsilPCH_sw;
    break;
    case 6:
    SW_SW = ASW[0].Filtr_sw|ASW[1].Filtr_sw<<ASW[2].Filtr_sw;
    break;
    case 7:
    SW_SW = ASW[0].refsw|ASW[1].refsw<<ASW[2].refsw;
    break;
    case 8:
    SW_SW = ASW[0].lptrf|ASW[1].lptrf<<ASW[2].lptrf;
    break;
    case 9:
    SW_SW = ASW[0].Pres_Fil_sw|ASW[1].Pres_Fil_sw<<ASW[2].Pres_Fil_sw;
    break;
    case 10:
    SW_SW = ASW[0].uxm15p|ASW[1].uxm15p<<ASW[2].uxm15p;
    break;

	default : SW_SW = ASW[0].Filtr_sw|ASW[1].Filtr_sw<<ASW[2].Filtr_sw;break;
   }

	return  SW_SW;
}
void PRC51::AmplifSET(int Amplif)
 {

	  ASW[1].LNA_sw = Amplif;

 }
void PRC51::ATT1_SET(double DB)
{
	if (DB >= 0 && DB <= 16)
	   {
		ASW[1].Att1 = 0xF -(int)(DB);
	   }
	else
	   {
		ASW[1].Att1 = 0;
	   }

}
void PRC51::ATT2_SET(double DB)
{
   if (DB >= 0 && DB <= 16)
   {
	ASW[1].Att2 = 0xF -(int)(DB);
   }
   else
   {
	ASW[1].Att2 = 0;
   }

}

void PRC51::PERENOS(int SW)
{

switch (SW)
  {
  case 0:  ASW[1].Conv_sw = 0;  break;
  case 1:  ASW[1].Conv_sw = 1;  break;
  default: ASW[1].Conv_sw = 1;   break;
  }
}
void PRC51::PRESELSET(int PRES)
{
		  switch (PRES)
  {
    case 0:ASW[1].Pres_Fil_sw = 0;break;  //000    0
    case 1:ASW[1].Pres_Fil_sw = 0x3;break;//011    3
    case 2:ASW[1].Pres_Fil_sw = 0x4;break;//100    4
    case 3:ASW[1].Pres_Fil_sw = 0x2;break;//010    2
    case 4:ASW[1].Pres_Fil_sw = 0x1;break;//001    1
    case 5:ASW[1].Pres_Fil_sw = 0x5;break;//101    5
    case 6:ASW[1].Pres_Fil_sw = 0x6;break;//110    6
	default:ASW[1].Pres_Fil_sw = 0;break;
  }

//0000   0
//0110   6
//1000   8
//0100   4
//0010   2
//1010   A
//1100   C
}
void PRC51::INSET(int IN)
{
      switch (IN)
  {
    case 0:ASW[1].In_SW = 7;break;//000   111 7
    case 1:ASW[1].In_SW = 6;break;//001   110 6
    case 2:ASW[1].In_SW = 5;break;//010   101 5
    case 3:ASW[1].In_SW = 4;break;//011   100 4
    case 4:ASW[1].In_SW = 3;break;//100   011 3

  default:ASW[1].In_SW = 7;break;
  }

//0000   0
//0110   6
//1000   8
//0100   4
//0010   2
//1010   A
//1100   C
}

void PRC51::SUPR1(int S)
{
  ASW[1].refsw = S;
}
void PRC51::SUPR2(int S)
{
  ASW[1].lptrf = S;
}

int PRC51::LoadATT(int div)
{
    int i;
    int  ATT_db;
      if (div >= 0 && div < 2)
    {i = div;}
    else
    {i = 0;}
//****************************************************************
           switch (i)
    {
      case 0:
      ATT_db = ASW[0].Att1|ASW[1].Att1<<ASW[2].Att1;
      break;
      case 1:
      ATT_db = ASW[0].Att2|ASW[1].Att2<<ASW[2].Att2;;
      break;
      default : ATT_db = ASW[0].Att1|ASW[1].Att1<<ASW[2].Att1;;break;
    }
//****************************************************************
    return  ATT_db;
}
void PRC51::SetUXM15(int div)
{
    switch (div)
  {
  case 4: ASW[1].uxm15p = 0x3;   break;
  case 5: ASW[1].uxm15p = 0x7;   break;
  case 6: ASW[1].uxm15p = 0x1;   break;
  case 7: ASW[1].uxm15p = 0x5;   break;
  case 8: ASW[1].uxm15p = 0x0;   break;
  case 9: ASW[1].uxm15p = 0x4;   break;

  default:  ASW[1].uxm15p = 0x4;  break; // N = 9
  }
}

long PRC51::SintLOAD_L(int Poz)
/*---------- Subsection SintLOAD_L  ----------*/

   {  int i;
      if (Poz>=0)
    {  i = Poz;
    }
     long  SW_SW;
		  SW_SW = ASW[0].sinth|DLMX2594->RegLoadLMX2594(i)<<ASW[2].sinth;

  return  SW_SW;

}
/*
  ##    ###   ###  ####
  ##   ## ## ## ## ## ##
  ##   ##  # ## ## ## ##
  ##   ##  # ##### ## ##
  ##   ## ## ## ## ## ##
  ####  ###  ## ## ####
*/

long PRC51::FCHLOAD_LMX(int Poz)
/*---------- Subsection FCHLOADLOAD_LMX  ----------*/

{  int i;
      if (Poz>=0)
    {  i = Poz;
    }
     long  SW_SW = ASW[0].sinth|FCHP2594->PLMX2594->RegLoadLMX2594(i)<<ASW[2].sinth;

  return  SW_SW;

}
long PRC51::FCHLOAD_KL(int Poz)
/*---------- Subsection FCHLOADLOAD_LMX  ----------*/

{     long  SW_SW;
      switch (Poz)
     {
      case 0:SW_SW = ASW[0].refsw|FCHP2594->UPR1<<ASW[2].refsw; break;
      case 1:SW_SW = ASW[0].lptrf|FCHP2594->UPR2<<ASW[2].lptrf; break;
      case 2:SW_SW = ASW[0].uxm15p|FCHP2594->PUXM15<<ASW[2].uxm15p; break;
     default:    break;
     }

  return  SW_SW;

}

long PRC51::FCHLOADF(int Poz)
/*---------- Subsection FCHLOADLOADF  ----------*/

{
  //long  SW_SW = ASW[0].sinth|FCHP2594->PLMX2594->RegLoadF(Poz)<<ASW[2].sinth;
  long  SW_SW = ASW[0].sinth|FCHP2594->LOAD_F(Poz)<<2;
  return  SW_SW;
}
/*
  ooooo oooo   oooo ooooo ooooooooooo oooo   oooo
   888   8888o  88   888  88  888  88  8888o  88
   888   88 888o88   888      888      88 888o88
   888   88   8888   888      888      88   8888
  o888o o88o    88  o888o    o888o    o88o    88
*/
long PRC51::FCHLOAD_LMXINIT(int Poz)
{
long  SW_SW = ASW[0].sinth|FCHP2594->LoadINITLMX2594(Poz)<<ASW[2].sinth;
return  SW_SW;
}

#pragma package(smart_init)