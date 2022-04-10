//---------------------------------------------------------------------------

#ifndef ADF4350H
#define ADF4350H
//---------------------------------------------------------------------------
 class ADF4350
  {
   public:
   ADF4350(double F,int I,int N,double Ref);
   ~ADF4350();
   void SetFreq(double fsint);
   int   RegLoad830(int Reg);
   void SetFreq(double F,int I,double PFD,double Ref);
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
		F1raz = 0x6090, //875
		F2raz = 0x6110,
		F4raz = 0x002,
		};
	enum regnum6
		{
		integer = 0x2003CA, //875
		frak = 0x200B4A     //
    	};

  } ;
#endif
