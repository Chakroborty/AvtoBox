//---------------------------------------------------------------------------

#ifndef hmc839H
#define hmc839H
//---------------------------------------------------------------------------
  class HMC839
  {
   public:
   HMC839(double F,int I,int N,double Ref);
   ~HMC839();
   void SetFreq(double fsint);
	int   RegLoad839(int Reg);
   double FregSIN;
   int Reg00;
   int Reg01;
   int Reg02;
   int Reg03;
   int Reg04;

   int Reg05;
   int Reg052;
   int Reg053;
   int Reg054;

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
   double Nakt;
   double R;
   double Nref;
   int CurSet;
   int Lmagn9;//1011111
	int L_Dir_UP;
	int L_Dir_DN;
	int HiKcp;
   enum regnum5
		{
		F4200 = 0xE80D, //875
		F1175 = 0xF80D,
		F2300 = 0xE80D,
		};
   enum regnum52
		{
		F2_4200 = 0xA395, //875
		F2_2300 = 0xAB95,
		F2_1175 = 0xAB95,

		};

  } ;

#endif
