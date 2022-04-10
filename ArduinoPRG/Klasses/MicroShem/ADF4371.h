//---------------------------------------------------------------------------

#ifndef ADF4371H
#define ADF4371H


//---------------------------------------------------------------------------
struct PRESET
   {
      int NINT;
      int CURSET;// 4
      int SEG1EN;// 0
      int FCAL_EN;// 0
      int OUTAPWR;
      int OUTBPWR;
      int CHANDiV;
   };
//---------------------------------------------------------------------------
struct Diapazon
   {
      int FcorMIN;
      int FcorMAX;
      int DeltF;
      int CcorMIN;
      int CcorMAX;
      int DeltC;
      int AcorMIN;
      int AcorMAX;
      int DeltA;
   };



//-----------------------------------------------------------
 class ADF4371
  {
   public:
   ADF4371(double F,int I,int N,double Ref);
   ~ADF4371();

/*
########  ########  ######   ##        #######     ###    ########
##     ## ##       ##    ##  ##       ##     ##   ## ##   ##     ##
##     ## ##       ##        ##       ##     ##  ##   ##  ##     ##
########  ######   ##   #### ##       ##     ## ##     ## ##     ##
##   ##   ##       ##    ##  ##       ##     ## ######### ##     ##
##    ##  ##       ##    ##  ##       ##     ## ##     ## ##     ##
##     ## ########  ######   ########  #######  ##     ## ########    */

  long RegLoadADF4371(int NReg);
  long RegLoadINIT(int RG);
  long RegLoadF(int RG);
//********************************************************************
   int OSCDBL;
   int PREr;
   int MULT;
   int POSTR;
 //*******************************************************************
	int VCO_CAPCTRL_ST;
	int VCO_DACISET_ST;
 //****************************************************************
	int VCOSEL;
	double FregSIN, Fpd;

   Diapazon VCO[8];

   void SetVCO(int VCON);
   void Default();
   void FReset(int RES);
   void PDovn(int PD);
   void MoUTLD(int SEL);
   void LDTupe(int Sel);
   void LDDLY(int SEL);
/****************************************************/
   int VCO_CAPCTRL_FORCE(int VALUE);
   int VCO_CAPCTRL(int VALUE);
   void VCO_CAPCTRL_STRT(int VALUE);

   int VCO_SEL_FORCE(int VALUE);
   int VCO_SEL(int VALUE);

   void VCO_DACISET_FORCE(int VALUE);
   void VCO_DACISET_STRT(int VALUE);
   void VCO_DACISET(int VALUE);
/*************************************************/
void NSET(int VALUE);
void FRSET(int VALUE);
int FCAL_EN(int VALUE);
/*************************************************/

void DIVOUTEN(int ENBL);
/*************************************************/
int CURSET(int VALUE);
void FCALHPFDADJ(int VALUE);
void FCALLPFDADJ(int VALUE);
void CALCLKDIV(int VALUE);
/*===== ========================  ======*/
int CHANDiV(int VALUE);//R75[10:6]
int SEG1EN(int VALUE);//R31[14]

int OUTAPWR(int VALUE);//R44[13:8]
int OUTAMUX(int VALUE);//R45[12:11]
int OUTAPD(int VALUE);//R44[6]

int OUTBPWR(int VALUE);//R45[5:0]
int OUTBMUX(int VALUE);//R46[1:0]
int OUTBPD(int VALUE);//R44[7]
/*=====  End of CHAN Div  ======*/
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
PRESET REGIM[10];
void SetREFPaTH(int OSC2,int PLL_PRE,int MLT,int PLL_R);
void SETPRESET(int PR);
void SETRGIM(int N,int CUR,
   int SEG1,int FCAL,
   int APWR,int BPWR,
   int CDiV);
/*----------  PRESET  ----------*/

void SetFreq(double fsint);



void GAIN_RF(int GRF);
// void Div_Gain(int DIvG);
int REG[125];



   int REZ;
   int Nfrak;
   double Nint;
   int NIint;
   int CAP;
   double Xtal; //ֳּונצ
 private:
   int GainRF;
   int GainDiv;
	double Nakt;

//********************************************************************
	double R;
	double Nref;
	int CurSet;
	int Lmagn9;//1011111
	int L_Dir_UP;
	int L_Dir_DN;
	int HiKcp;
  };
#endif
