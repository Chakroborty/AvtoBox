//---------------------------------------------------------------------------

#ifndef HMC700H
#define HMC700H
//---------------------------------------------------------------------------

 class HMC700
  {

public:
	HMC700(double F,int I,int N,double Ref);
	~HMC700();
	double FregSIN;

	void SetFreq(double fsint);
	void SetDFreq(double Fsint,double Fop);
	void ParamSet(int Pol,int Cur,int CP);
	double GetR();
	double GetN();
	double GetFrak();
	double GetPFD();
	int RegLoad700(int Reg);
    int Nref;
   unsigned	int Reg00;
   unsigned	int Reg01;
   unsigned	int Reg02;
   unsigned	int Reg03;
   unsigned	int Reg04;
   unsigned	int Reg05;
   unsigned	int Reg06;
   unsigned	int Reg07;
   unsigned	int Reg08;

   unsigned	int Reg09ost;
   unsigned	int RegA;
   unsigned	int RegB;
   unsigned	int RegC;
   unsigned	int RegD;
   unsigned	int RegE;
   unsigned	int RegF;

private:

	double Nakt;
	double Nint;
	double Nfrak;
	double Xtal; //ֳּונצ
	int CpEn;   //Reg 08h Analog EN Register

	int Polarity;// Reg 0Bh PFD Register

	double Fdiv;
	int R;
	int CurRef;
	int CurSet;
  } ;
 #endif


