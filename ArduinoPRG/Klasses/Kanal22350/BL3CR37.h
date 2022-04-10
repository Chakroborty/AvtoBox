//---------------------------------------------------------------------------

#ifndef BL3CR37H
#define BL3CR37H
#include "VirtBlock.h"
#include "PRC235.h"
#include "MFC1RR.h"
//#include "MFC2RR.h"

#define Interval 1
#define UDP_038_PORT 5024
#define UDP_038_PORTR 2424

#define HostADR "192.168.1.10"
//#define UDP_PERF_PORT 5001
//---------------------------------------------------------------------------


class BL3CR37: public IBLock
{
public:
BL3CR37();
~BL3CR37();


MPRC *PRC;
MMFC1RR *MFC1;
MMFC1RR *MFC11;
MMFC1RR *MFC2;


/****************************************************************/
void FriqSET(int Mod,int Kanal,double Fin,bool Ampl,int DB1,int DB2,int DB3,int DB4);
void SetFreq(double F,double ATT1,double ATT2, double DAT);
void SetFreq(double F,double Fat,int ATT1,int ATT2,int ATT3,int Kanal,int ALL,int BPERENOS);
void SetMFC1(double FM1,int DIV15,int BLUPR1,int BLUPR2);
void LoadBL3CR37();
void LoadBL3CR371();


/***************************************************************/

char *SENDLAN(int ADR,int data,bool Read);

void LoadMFC1();
void LoadMFC11(double F,int ADR);
void LoadMFC2(double F,int ADR);

void LoadLMX1();
void Load830UNO(int r);
void LoadLMXUNO(int X);
char *ReadLMXUNO(int X);


};




#endif
