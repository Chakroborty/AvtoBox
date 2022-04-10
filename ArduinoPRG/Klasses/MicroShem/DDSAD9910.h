//---------------------------------------------------------------------------

#ifndef DDSAD9910H
#define DDSAD9910H
//---------------------------------------------------------------------------

class AD9910
{
  public:
	AD9910(int I, int PN, bool Pol_PUS, double Ref);
	~AD9910();

	double FregSIN;
	void SetFreq(double fsint);
	int RegLoad4002(int Reg);
	void ParamSET(int Pol, int Cur,int Rdiv, int Ndiv);
	void CurSET(int Cur);
	double Xtal; 	// МГерц
	long Reg00;
	long Reg01;
	long Reg02;
	long Reg03;
	void MAP00();
	void MAP01();
	void MAP02();
	void MAP03();

protected:
private:
	/** **********Reg 0************* */
	int LDP;
	int TMB;
	int ABP;
	int R;

	/** **********Reg 1************* */
	int CP_GAIN;

	int A_COUNT;
	int Nref;
	int N;
	/** **********Reg 2************* */
	int PRESCALER;
	int PD1;

	int CurSet; // опорный ток
	int T_OUT;
	int FASTLOCK;
	int CP_Trist;
	int Polarity;
	int MUXOUT;
	int PD2;
	int CounRes;

};
#endif