// ---------------------------------------------------------------------------

#ifndef Adf4355H
#define Adf4355H

// ---------------------------------------------------------------------------
class Adf4355
{
	public:
		Adf4355(double F, int I, int N, bool Pol_PUS, double Ref,int Dabl);
		~Adf4355();

		double FregSIN;
		void SetFreq(double fsint,double Fref);
		long RegLoad4159(int Reg);
		void PARAMSEt4159(int CPTri);
		void MAP00();
		void MAP01();
		void MAP02();
		void MAP03();
		void MAP04();
		void MAP05();
		void MAP06();
		void MAP07();
		void MAP08();
		void MAP09();
		void MAP11();
		void MAP12();
		void MAPALL();
		void MAPFRIQ();
		double Xtal;// МГерц
		
		

	protected:
	private:
		float Nakt;
		double Fpfd;

		/** **********Reg 0************* */
		                                                                                      	
		int AUTOCAL;
		int PRESCALER;
		int Nint;
		//double
		// Reg00 =  AUTOCAL << 21 | PRESCALER << 20| Nint << 4 | 0X0;


		/** **********Reg 1************* */
		
    
		int Nref;
		int FRAC1;
		unsigned int Nfrak;
		double Nfrak_prog;


		 // Reg01 = FRAC1<<4 | 0X1;


		/** **********Reg 2************* */
		int FRAC2;
		int MOD2;

		// Reg02 = FRAC2<<18|MOD2<<24|0X2;


		/** **********Reg 3************* */
		int SDLRES;
		int PHRES;
		int PHADJ;
		int PHVAL;
    
		
		
		
		// Reg03 =  SDLRES<<30|PHRES<<29|PHADJ<<28|PHVAL<<4|0X3;
		
		/** **********Reg 4************* */
		int MUXOUT;
		int DOUBLER;
		int RDIV2DBB;
		int R;
		int DBUF;

		int CurSet; // опорный ток
		int CP_CUR;
		int REF_MOD;
		int MLOG;
		int PDPOLAR;
		int POWDN;
		int CPTHREE;
		int COUNTRES;



		// Reg04 = MUXOUT<<27|DOUBLER<<26|RDIV2DBB<<25|R<<15|DBUF<<14|
		//  CP_CUR<<10|REF_MOD<<9|MLOG<<8|PDPOLAR<<7|POWDN<<6|CPTHREE<<5|COUNTRES<<4|0X4;

		/************Reg 5**************/ 

		// Reg05 = 0X5;     RESERVED


		/************Reg 6**************/
		int GBLED;
		int NEGBLED;
		int FEDSEL;
		int RFDIV;
		int CPBLEDCU;
		int MTLD;   //0 MUTE DISABLED
		int RFOUTB;
		int RFOUTBPOW;
		int RFOUT;
		int RFPOW;

		// Reg06 = GBLED<<30|NEGBLED<<29|FEDSEL<<24|RFDIV<<21|CPBLEDCU<<13|MTLD<<11|
		// RFOUTB<<9|RFOUTBPOW<<7|RFOUT<<6|RFPOW<<4|0X6;


		/************Reg 7**************/
		int LESYNC;
		int LDCCONT;
		int LOL;
		int LDPREC;
		int LDMOD;


		// Reg07 = LESYNC << 25| LDCCONT<< 8 |LOL << 7 |LDPREC << 5|LDMOD << 4|0X7;

		/************Reg 8**************/
      
      
      
		
		// Reg08 = 0X8;   RESERVED  

		/************Reg 9**************/
		int VCOBAND;  
		int TOUT;  
		int ATL;  
		int SYNLOCT;
		// Reg09 = VCOBAND<< 24| TOUT << 14|ATL<< 9|SYNLOCT<< 4|0X9; 

		/************Reg 10**************/
		int ADCDIV;  
		int ADCCONV;  
		int ADCEN;  

		// Reg10 = ADCDIV<< 6| ADCCONV << 5|ADCEN<< 4|10; 

		/************Reg 11**************/

		// Reg11 = 11;   RESERVED  

		/************Reg 12**************/
		int RESCLOC;  

		// Reg12 = RESCLOC<< 16|12; 



		/** **************************** */

		long Reg00;
		long Reg01;
		long Reg02;
		long Reg03;
		long Reg04;
		long Reg05;
		long Reg06;
		long Reg07;
		long Reg08;
		long Reg09;
		long Reg10;
		long Reg11;
		long Reg12;

    

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
