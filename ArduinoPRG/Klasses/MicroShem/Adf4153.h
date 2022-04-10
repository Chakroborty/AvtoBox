// ---------------------------------------------------------------------------

#ifndef ADF4153H
#define ADF4153H

// ---------------------------------------------------------------------------
class ADF4153 {
public:
	ADF4153(double F, int I, int N, bool Pol_PUS, double Ref, double ssHag,int Dabl);
	~ADF4153();

	double FregSIN;

	/**
	 * <url>element://model:project::Exsampl/design:view:::3i1lcz4zc2g_v</url>
	 * <url>element://model:project::Exsampl/design:view:::wbudsexay9f3dharo_v</url>
	 */
	void SetFreq(double fsint);
	void SetPFD(int Cur);
	void SetDUB(int Dubl);
	int RegLoad4153(int Reg);

	void Operation1();

	double Xtal;

	// МГерц
protected:
private:
	/** **********Reg 0************* */

	int FASTLOCK;
	int Nref;
	double Nakt;
	int Nint;
	int    INfrak;
	double Nfrak;
	double Nfrak_prog;

	/** **********Reg 1************* */
	int Load_CONTR;
	int MUXOUT;
	int PRESCALER;
	int R;
	int  IMODUL;
	double MODUL;
	double MOD_prog;
	/** **********Reg 2************* */
	int Resinc;
	int DOUBLER;
	int CP_CUR;
	int CurSet; // опорный ток
	int Polarity;
	int LDP;
	int P_Dovn;
	int CP_Trist;
	int CounRes;
	/** **********Reg 3************* */
	int NoiseSpur;

	/** **************************** */

	double SHag;
	int Reg00;
	int Reg01;
	int Reg02;
	int Reg03;

	enum PrNom {
		Del4_5 = 0, Del8_9 = 1
	};

	enum Polar {
		Polog = 1, Otric = 0
	};

	enum ModeSp {
		LSM = 0, // LOWEST SPUR MODE 00000
		LNSM = 0xE0, // LOW NOISE AND SPUR MODE 11100
		LNM = 0xF1 // LOWEST NOISE MODE 11111
	};
};

#endif
