// ---------------------------------------------------------------------------

#ifndef Adf4108H
#define Adf4108H

// ---------------------------------------------------------------------------
class ADF4108 {
public:
	ADF4108(double F, int I, int N, bool Pol_PUS, double Ref, double ssHag,int Dabl);
	~ADF4108();

	double FregSIN;

	/**
	 * <url>element://model:project::Exsampl/design:view:::3i1lcz4zc2g_v</url>
	 * <url>element://model:project::Exsampl/design:view:::wbudsexay9f3dharo_v</url>
	 */
	void SetFreq(double fsint);
	int RegLoad4108(int Reg);
	void ParamSET(int Pol, int Cur,int Pres,int A,int B, int R);


	double Xtal; 	// ћ√ерц
protected:
private:
	/** **********Reg 0************* */
	int LDP;
	int TMB;
	int ABP;
	int Nref;
	/** **********Reg 1************* */
	int CP_GAIN;
	int B_COUNT;
	int A_COUNT;
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
	/** **********Reg 3************* */
//    int PRESCALER;
//	int PD1;
//	int PD2;
//	int CurSet; // опорный ток
//	int T_OUT;
//	int FASTLOCK;
//	int CP_Trist;
//	int Polarity;
//	int MUXOUT;
//	int P_Dovn;
//	int CounRes;














	/** **************************** */


	int Reg00;
	int Reg01;
	int Reg02;
	int Reg03;

	enum PrNom
	{
		Del4_5 = 0, Del8_9 = 1
	};

	enum Polar
	{
		Polog = 1, Otric = 0
	};


};

#endif
