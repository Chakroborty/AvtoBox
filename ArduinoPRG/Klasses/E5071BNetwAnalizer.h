// ---------------------------------------------------------------------------
// #include <string.h>
// #include <stdio.h>

#ifndef E5071BNetwAnalizerH
#define E5071BNetwAnalizerH
#include <vcl.h>
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>

// ---------------------------------------------------------------------------
class E5071B {
public:
	E5071B(int Adr, char* Ip);
	~E5071B();

	char* PriborLoad();
	void StartStop_set(double Fin_centr, double Fout_centr, double SSpan,
		bool Reverse, double PowOUT);
	int ControlDiap(int K, int Pred, int& Com);

	void F_IN_set(double Fin, double Span);
	void F_OUT_set(double Fout, bool inv_Sp);
	void Span_set(double Span);
	// char* SetFormat(int FormNum);
	// char* ParDEF(int DefNum);
	double F_diapazon(double val);
	char* PriborSET(int i);
	// ****************************************************************************
	char* ParSEL(int NumPAR);
	char* CalkMark(int NumMARK);
	double CalkMarkD(int Meas, int NumMARK);
	void GPIB_Set(AnsiString Adr, AnsiString Ip);
	void IP_Set(AnsiString Ip);
	char* GetGPIB();
	char* GetIPlok();
	double Neravnom(int Meas, int NumMark1, int NumMark2, double Fstart,
		double Fstop, bool Revers);
	/**
	 * *************************************************************************<property></property><url>element://model:project::Exsampl/design:node:::ec7y0g9dz1suf3t8n_n:0w1acwyuhaj5cv2tl_n:mrb4r99gwrhiuu39j_n</url>
	 */
	void In_NEsim_perenos(double Fin_start, double Fin_stop, double Fnastr,
		double Fpc, bool inv_Sp, double PowOUT);
	/**
	 * <url>element://model:project::Exsampl/design:node:::pc5basm923duuea0r_n:0w1acwyuhaj5cv2tl_n:mrb4r99gwrhiuu39j_n</url>
	 * <url>element://model:project::Exsampl/design:node:::j2657r7axirf9gupj_n:0w1acwyuhaj5cv2tl_n:mrb4r99gwrhiuu39j_n</url>
	 */
	void In_No_perenos(double Fin_start, double Fin_stop, double PowOUT);

	/**
	 * <url>element://model:project::Exsampl/design:node:::4gz9r4gxlwr_n:lgoz0hma2oi_n:mrb4r99gwrhiuu39j_n</url>
	 */
	void Marker_set(double Fm1, double Fm2, double Fm3, double Fm4, double Fm5,
		double Fm6, double Fm7);
	char* MarkerONload(int i);
	char* MarkerFload(int i);
	/**
	 * **************************************************************************<url>element://model:project::Exsampl/design:node:::lclyafyicuaqsfjjm_n:d8nanyw33srr4dr2i_n</url><url>element://model:project::Exsampl/design:node:::17ek2psdbik_n</url>
	 */
	void SetLimitOc(double F0, double F1, double F2, double F3, double F4,
		double F5, double F6, double F7, double L0, double L1, double L2,
		double L3, double L4, double L5, double L6, double L7);
	/**
	 * <url>element://model:project::Exsampl/design:node:::zvyqh6hdcen_n:plzors9p6rm0trgor_n</url>
	 * <url>element://model:project::Exsampl/design:node:::zvyqh6hdcen_n:plzors9p6rm0trgor_n:mrb4r99gwrhiuu39j_n</url>
	 */
	void SetLimitzAZOR(double dF, double dL, double Lopor);
	/**
	 * <url>element://model:project::Exsampl/design:node:::xn3zp8wwbfp_n</url>
	 */
	void SetLimitProf(double P0, double P1, double P2, double P3, double P4,
		double P5, double P6, double P7);
	char* LoadLimit(int i, int numL, double G);
	/**
	 * <url>element://model:project::Exsampl/design:node:::7s544b42fkkinbm0o_n:0w1acwyuhaj5cv2tl_n</url>
	 */
	void DispleiSet(int Trase, int Par, int Form, double Div, int Pos, int Lev);
	/**
	 * <url>element://model:project::Exsampl/design:node:::v5xdh04ocnpjfllyr_n:0w1acwyuhaj5cv2tl_n</url>
	 */
	void NumTRsSET(int NumTR);
	char* IzmerenSet(int Nabor, int Shag);
	char* ParDEF(int DefNum);
	char* SetFormat(int FormNum);
	// ****************************************************************************
	double GetF_IN_Start(void);
	double GetF_IN_Stop(void);
	double GetF_OUT_Start(void);
	double GetF_OUT_Stop(void);
	double GetF_Get(void);
	AnsiString Zapt(AnsiString str);

	double Nerav, Threshold, Bwid, Cent, Q, Loss;

	double CalkMarkBW(int Meas, int NumMARK);
	double RazborStr(int poz, char* str);
	long SetMark(int Meas, int NumMark, int Tape);
	// ****************************************************************************
	int Lan_GPIB;
protected:
	void F_diapazon(double &, double val);
	void F_max(double &, double &, bool uvelic);
	void F_min(double &, double &, bool uvelic);

	ViSession defaultRM, vi; // Declares a variable of type ViSession
	ViByte buffer[256]; // for instrument communication
	char rezult[256];
	ViStatus status;
	ViUInt32 retCnt;
	
private:
	// void F_diapazon(double &,double val);

	bool Inv;
	bool Preob;
	bool PereVverx;
	double F_IN_Start;
	double F_IN_Stop;
	double F_OUT_Start;
	double F_OUT_Stop;
	double F_IN_Centr;
	double F_OUT_Centr;

	// *****************Limit Line***************************
	double LIM_Offset;
	double LIM_deltaF;
	double LIM_deltaL;
	int NumLin;
	double Flev[10][3];
	// *****************Limit Line***************************
	double F_Span;
	double F_Get;
	double Pow;
	// ****************************************************************************
	double Mark1_F;
	double Mark2_F;
	double Mark3_F;
	double Mark4_F;
	double Mark5_F;
	double Mark6_F;
	double Mark7_F;

	bool Mark1;
	bool Mark2;
	bool Mark3;
	bool Mark4;
	bool Mark5;
	bool Mark6;
	bool Mark7;

	// ****************************************************************************
	char GPIB[10];
	//char* ipAdres;
	char ipAdres[100];
	char ipLok[100];
	int Gadr;
	AnsiString ansi_string;

	/*****************************************************************************

	/**
	 * <url>element://model:project::Exsampl/design:node:::q5e5a8p98lm3gawvs_n:lgoz0hma2oi_n:mrb4r99gwrhiuu39j_n</url>
	 */
	double RascetFout(double F);


	long SetDiapazonBW(int Meas, double Fstart, double Fstop, bool Revers);

	int NumTrSEL; // Ќомер текущей трассы
	int Disp_Numtr;
	// ќпредел€ет измер€емый количество параметров:CALC1:PAR:COUN 3
	int Disp_par[4];
	// ќпредел€ет измер€емый параметр дл€ текущей трассы:CALC1:PAR1:DEF S21
	int Disp_form[4];
	// ќпредел€ет формат измер€емый параметр   :CALC1:FORM MLOG
	int Disp_pos[4];
	double Disp_div[4];
	int Disp_Lev[4]; /* TODO -cDisp : Format  переменные */

};

#endif
