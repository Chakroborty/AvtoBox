// ---------------------------------------------------------------------------

#ifndef Mod3CR5H
#define Mod3CR5H
#include "ADF4153.h"

// ---------------------------------------------------------------------------
class Mod3CR5 {
public:
	Mod3CR5(int ADR, bool isp05);
	~Mod3CR5();

	ADF4153 *SintKV;

	void SetFriq(double Fset, int Kanal);
	int Load_sint(int tip);
	/*********************************************************************************/
	 void  SetATT_UPC(double Db);
	 int LoadATT_UPC(void);
	/*********************************************************************************/
	void SetAmpl_UPC(int Ampl);
	int LoadAmpl_UPC(void);
	/*********************************************************************************/
	 void  SetVX(bool Priem,int DB );
	 void  SetATT_Pres(int Db);
	 void  SetFVC(int Fset);
	 void  SetPC(bool PC40);
	 int LoadKL(void);
	/*********************************************************************************/

	enum FVC
	{
		OTKL = 0x0,
		FV8 = 0x5,
		FVl5 = 0x6

	};

	enum ATT_Pres
	{
		Att_PL10 = 0x10,
		Att_0 = 0x11,
		Att_M10 = 0x3,
		Att_M20 = 0x1B,
		Att_M30 = 0x17
	};

		enum Komanda
	{
		Sinz  =	0,
		AT_UPC  =	1,
		Amp_UPC  =	0x2,
		Kluc  =	0x3
	};

int BWIF; // Ц бит управлени€ полосой пропускани€ ѕ„:
// 0 Ц узка€ 0,04 ћ√ц;
// 1 Ц широка€ 4 ћ√ц.

int HTDN; // - бит управлени€ гетеродином:
// 0 Ц внутренний гетеродин;
// 1 Ц внешний гетеродин.

int REFG; // Ц бит управлени€ опорным генератором:
// 0 Ц внутренний опорный генератор;
// 1 Ц внешний опорный генератор;
int CLBR; // Ц бит управлени€ входами прием и калибровка:
// 0 Ц прием;
// 1 Ц калибровка.
int NG; // NG10, NG20 , NGON Ц биты управлени€ генератором шума (только в 3„р6)

enum NG_ATT
	{
		GS_OTKL = 0, // 0	0	0
		AttN_0 = 0x4, // 1	0	0
		AttN_M10 = 0x6, // 1	1	0
		AttN_M20 = 0x5, // 1	0	1
		AttN_M30 = 0x3 // 0   1	1
	};
int FHift;


int AdresMod;
int ATTvhod;
int Att_UPC;
int AMPL_UPC;
int PrFVC;
double Fin;
double Fget;

};
#endif
