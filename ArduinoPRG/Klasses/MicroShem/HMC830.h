//---------------------------------------------------------------------------

#ifndef HMC830H
#define HMC830H
#include "BitsU.h"
//---------------------------------------------------------------------------
 class HMC830
  {
   public:
   HMC830(double F,int I,int N,double Ref);
   ~HMC830();
   void SetFreq(double fsint);
   long   RegLoad830(int Reg);
   long   RGLoad830STR(int Reg);

   double FregSIN;
   void SetBIT09(int Offset,int UP,int DN,int MHiKCP);
   void CURSet(int IH, int IL);
   void DIVOUTEN(int ENBL);
   void GAIN_RF(int GRF);
   void Div_Gain(int DIvG);
   void SetREF(double INREF, double INR);
   int Reg00;
   int Reg01;
   int Reg02;
   int Reg03;
   int Reg04;
   int Reg050;
   int Reg05;

   int Reg052;
   int Reg053;
   int Reg054;
   int Reg055;
   int Reg06;
   int Reg07;
   int Reg08;
   int Reg09;
   int RegA;
   int RegB;
   int RegC;
   int RegD;

   int RegF;



   double Nfrak;
   double Nint;
   double Xtal; //ֳּונצ
 private:
   int GainRF;
   int GainDiv;
	double Nakt;
	double R;
	double Nref;
	int CurSetH;
	int CurSetL;
	int Lmagn9;//1011111
	int L_Dir_UP;
	int L_Dir_DN;
	int HiKcp;
   enum regnum5
		{
			F1raz = BIN24(00000000,11100000,10010000), //875   0x6090;
			F2raz = BIN24(00000000,11100001,00010000), //0x6110,
			F4raz = BIN24(00000000,11100010,00010000) // 0x002

		};
	enum regnum6
		{
			integer = 0x2003CA, //875
			frak = 0x200B4A     //
		};

  } ;
#endif
