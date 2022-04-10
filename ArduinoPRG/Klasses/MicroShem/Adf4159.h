// ---------------------------------------------------------------------------

#ifndef Adf4159H
#define Adf4159H

// ---------------------------------------------------------------------------
class ADF4159
{
	public:
		ADF4159(double F, int I, int N, bool Pol_PUS, double Ref,int Dabl);
		~ADF4159();

		double FregSIN;

		void SetFreq(double fsint,double Fref, bool OptI);
		long RegLoad4159(int Reg);
		void PARAMSEt4159(int CPTri,int Cur);
		void NRSEt4159(int R,int N,int PNF,int PREs);
		void MAP00();
		void MAP01();
		void MAP02();
		void MAP03();
		void MAP04();
		void MAP05();
		void MAP06();
		void MAP07();
		void Operation1();

		double Xtal;// МГерц
		int POWDN;

	protected:
	private:
		/** **********Reg 0************* */

		int Ramp;
		int MUXOUT;
		//double
		float Nakt;
		double Fpfd;
		int Nref;
		int Nint;
		int FRAC;
		unsigned int Nfrak;
		double Nfrak_prog;
		// Reg00 = Ramp << 31 | MUXOUT << 27| Nint << 20 | FRAC << 18 | 0X0;
		//
		/** **********Reg 1************* */
		int PHADJ;
		int FRAKLSB; //13 bit LSB
		int PHASE;
		 // Reg01 = PHADJ << 28 |FRAKLSB << 20 |PHASE << 18 | 0X1;
		/** **********Reg 2************* */
		int CSR;
		int CP_CUR;
		int CurSet; // опорный ток
		int PRESCALER;
		int RDIV2DBB;
		int DOUBLER;
		int R;
		int CLKDIV;
		 // Reg02 = CSR << 28 |CP_CUR << 24 |PRESCALER << 22 |RDIV2DBB << 21|
		 //	DOUBLER << 20|R << 15|CLKDIV << 3|0X2;
		/** **********Reg 3************* */
		int NBLDCUR;
		int NBLEN;
		int LOL;
		int NSEL;
		int SDRESET;
		int RAMPMOD;
		int PSK;
		int FSK;
		int LDP;
		int PDPOLAR;
	   //	int POWDN;
		int CPTHREE;
		int COUNTRES;
		// Reg03 = NBLDCUR << 22 |NBLEN << 21 |LOL << 16 |NSEL << 15|SDRESET << 14|RAMPMOD << 10|
		// PSK << 9|FSK << 8|LDP << 7|PDPOLAR<< 6| POWDN<< 5| CPTHREE<< 4| COUNTRES<< 3| 0X3;
		/** **********Reg 4************* */
		int LESEL ;
		int MMODE;
		int RAMPST;
		int CLKDMODE;
		int CLKDIVVALUE;
		int CLKDIVSEL;
		// Reg04 = LESEL << 31|MMODE << 26 |RAMPST << 21 |CLKDMODE << 19|
		// CLKDIVVALUE << 7|CLKDIVSEL << 6|0X4;

		/************Reg 5**************/
		int TXINV;
		int TXCLK;
		int PRAMP;
		int INR;
		int FSKR;
		int DUALR;
		int DEVSEL;
		int DEVOFW;
		int DEVW;
		// Reg05 = TXINV << 31|TXCLK << 26 |PRAMP << 21 |INR << 19|FSKR << 7|
		// DUALR << 6|DEVSEL<< 6|DEVOFW << 6|DEVW<< 6|0X5;
		/************Reg 6**************/
		int STEPS;
		int STEPW;
		// Reg06 = STEPS << 23|STEPW << 3|0X6;
		/************Reg 7**************/
		int TXDTRIGDEL;
		int TRIDEL;
		int SFULTRI;
		int TXDATTR;
		int FASTR;
		int RDELFL;
		int RDELAY;
		int DCLKSEL;
		int DSTARTEN;
		int DSTARTW;
		// Reg07 = TXDTRIGDEL << 23|TRIDEL << 22 |SFULTRI << 21 |TXDATTR << 20|FASTR << 19|RDELFL << 18|
		// RDELAY << 17|DCLKSEL << 16|DSTARTEN << 15|DSTARTW << 3| 0X7;




	   /** **************************** */

		long Reg00;
		long Reg01;
		long Reg02;
		long Reg03;
		long Reg04;
		long Reg05;
		long Reg06;
		long Reg07;

		enum PrNom
		{
			Del4_5 = 0, Del8_9 = 1
		};

		enum Polar
		{
			Polog = 1, Otric = 0
		};

		enum ModeSp
		{
			LSM = 0, // LOWEST SPUR MODE 00000
			LNSM = 0xE0, // LOW NOISE AND SPUR MODE 11100
			LNM = 0xF1 // LOWEST NOISE MODE 11111
		};
};

#endif
