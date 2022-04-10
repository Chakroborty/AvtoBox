// ---------------------------------------------------------------------------

#ifndef Switch34980AH
#define Switch34980AH
#include "visa.h"
#include <stdio.h>
#include <string.h>
#include <vcl.h>
// ---------------------------------------------------------------------------
int SW947ST[17][16] =
     //1|2|3|4|5|6|7|8|9|1|1|1|1|1|1|
     // | | | | | | | | |0|1|2|3|4|5|
{	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//0
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//1
	{0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//2
	{0,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1},//3
	{0,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1},//4
	{0,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1},//5
	{0,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1},//6
	{0,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1},//7
	{0,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1},//8
	{0,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1},//9
	{0,1,1,1,1,2,1,1,2,1,2,1,1,1,1,1},//10
	{0,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1},//11
	{0,1,1,1,1,1,2,1,1,2,1,2,1,1,1,1},//12
	{0,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1},//13
	{0,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1},//14
	{0,1,1,1,1,1,1,1,1,1,1,2,2,1,2,1},//15
	{0,1,1,1,1,1,1,1,1,1,1,2,2,1,2,2}//16
};
int SW941ST[17][9] =
     //1|2|3|4|5|6|7|8|
     // | | | | | | | |
{	{0,1,1,1,1,1,1,1,1},//0
	{0,1,1,2,1,1,1,1,1},//1
	{0,1,1,2,1,2,1,1,1},//2
	{0,1,1,2,1,3,1,1,1},//3
	{0,1,1,2,1,4,1,1,1},//4
	{0,1,1,4,1,1,1,1,1},//5
	{0,1,1,4,1,1,2,1,1},//6
	{0,1,1,4,1,1,3,1,1},//7
	{0,1,1,4,1,1,4,1,1},//8
	{0,1,1,1,1,1,1,1,1},//9
	{0,1,1,1,1,1,1,2,1},//10
	{0,1,1,1,1,1,1,3,1},//11
	{0,1,1,1,1,1,1,4,1},//12
	{0,1,1,3,1,1,1,1,1},//13
	{0,1,1,3,1,1,1,1,2},//14
	{0,1,1,3,1,1,1,1,3},//15
	{0,1,1,3,1,1,1,1,4}//16
};

class Switch34980 {
public:
	Switch34980(int Gadr, char* Ip);

	~Switch34980();

	char* PriborLoad();
	bool Connect(ViStatus ST);
	/**
	 * <url>element://model:project::Exsampl/design:node:::ukxjdpzsw8j_n:x48cccebnjs_n</url>
	 */
	int Lan_GPIB;
	void GPIB_Set(AnsiString  Adr, AnsiString Ip);
	void IP_Set(AnsiString Ip);
	/**
	 * <url>element://model:project::PrBL3PX1/design:node:::64eawu55gzed0jvmi_n</url>
	 */
	long CommSet(int K21, int K22, int K23, int K61, int K62, int K63, int K64);
	long CommSetK16(int K221,int K222,int K223,int K224,int K61,int K62,int K63,int K64,int K71,int K72,int K73,int K74);
	long KanalSet(int Knum);
	long KanalSet16(int Knum);
	long KanalSet12(int Knum);
	long KanalSet16HF(int Knum);
	long KanalGset(int Knum);
	int ControlDiap(int K, int Pred, int& Com);
	/*

		####  ##   ####  ####
		## ## ##   ## ## ## ##
		####  ##   ## ## ## ##
		## ## ##   ####  ####
		## ## ##   ## ## ## ##
		####  #### ## ## ## ##

	*/
    long CommSetK16HF(int KANAL);
	char ARRAY947[16][3][6];//3x2
    char ARRAY941[9][5][6];//4X4
	char* GetGPIB(void);
	char* GetIPlok();
	char* COMdef(int Pos);

	// ****************************************************************************
private:
	char ipAdres[100];
	char ipLok[100];
protected:

	int ControlCom(int K, int Pred, int &);

	char* GPIB;
	int SWKANAL;
	int Gadr;
	int Com21;
	int Com22;
	int Com23;


	int Com61;


	int Com62;


	int Com63;


	int Com64;

	int Com221;
	int Com222;
	int Com223;
	int Com224;

	int Com71;
	int Com72;
	int Com73;
	int Com74;


	ViSession defaultRM, vi; // Declares a variable of type ViSession
	ViByte buffer[256]; // for instrument communication
	char rezult[256];
	ViStatus status;
	ViUInt32 retCnt;
};

#endif
