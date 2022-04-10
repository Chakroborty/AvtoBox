//---------------------------------------------------------------------------

#ifndef BLKPRC51H
#define BLKPRC51H
#include "VirtBlock.h"
#include "PRCRR.h"
#include "MFC1RR.h"
#include "MFC2RR.h"
#include "PRC051.h"
#define Interval 1
#define UDP_038_PORT 5024
#define UDP_038_PORTR 2424
#define UDP_051_PORT 5000
#define HostADR "10.29.31.5"
//#define UDP_PERF_PORT 5001
//---------------------------------------------------------------------------


class RPURR: public IBLock
{
public:
RPURR();
~RPURR();


MPRC *PRC;
MMFC1RR *MFC1;
//MMFC2RR *MFC2;
PRC51 *TPRC51;

/****************************************************************/
void FriqSET(int Mod,int Kanal,double Fin,bool Ampl,int DB1,int DB2,int DB3,int DB4);
//'IBLock::SetFreq(double,double,int,int,int,int,int,int) = 0'
void SetFreq(double F,double Fr,int ATT1,int ATT2,int ATT3,int Kanal,int ATT4,int PERENOS);

void SetMFC1(double FM1,int DIV15,int BLUPR1,int BLUPR2);
void LoadRPURR();
char *LoadPRC51();//Load51
void LoadR018(int COM);
void LoadLMX051();
void LoadLMX051F();
/***************************************************************/
void LoadFCHPR();
/*
	## ##   ## ## ######
	## ###  ## ##   ##
	## ###  ## ##   ##
	## ## # ## ##   ##
	## ## # ## ##   ##
	## ##  ### ##   ##
	## ##  ### ##   ##
	## ##   ## ##   ##
*/

void PRC51FCHINIT();
/*



	 ####  ##### ######        #####
	##  ## ##      ##          ##
	###    ##      ##          ##
	 ####  #####   ##          ####
	   ### ##      ##          ##
	#   ## ##      ##          ##
	##  ## ##      ##          ##
	 ####  #####   ##          ##

	                    ######
*/

void PRC51FCHFRIQ(int NUM);
//------------------------------------------------------------
char *SENDLAN(int ADR,int data,bool Read);

void LoadMFC1();
void LoadLMX1();
void Load830UNO(int r);
void LoadLMXUNO(int X);
char *ReadLMXUNO(int X);
void PRC51PERENOS(int P);
void PRC51PRES(int P);
void PRC51INSW(int S);
void PRC51ATT1(int DB);
void PRC51ATT2(int DB);
void PRC51PMA32(int UPR);
void PRC51PHA3(int UPR);
void PRC51UPR1(int ST);
void PRC51UPR2(int ST);
void PRC51UXM15(int ST);
//---------------------------------------------------

};




#endif
