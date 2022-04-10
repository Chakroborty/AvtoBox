//---------------------------------------------------------------------------

#pragma hdrstop
#include "TADT7310.h"
//---------------------------------------------------------------------------
ADT7310::ADT7310()
{
//SIGN = 0;
COMMAND[0] = 0x50;// 01010000 50 REG 0x02
} 
ADT7310::~ADT7310()
{

}
double ADT7310::Tvalue(int DAT,int Regim)
{
		switch (Regim)
	{
	case 10: 	DTEMP = DAT>>3/2;	 break;
	case 13:
			switch (DAT&0x8000)
		{
		case 0: DTEMP = (DAT>>3)/64;   break;      //
		case 0x80: DTEMP = -1*(DAT>>3-8192)/64;   break;
		default:  DTEMP = DAT>>3/64;  break; 
		}
	break;
	case 16:  DTEMP = DAT/128; break;
	default:  DTEMP = DAT>>3/64;  break;
	}
	return DTEMP;
}
int ADT7310::RCOM(int N)
{
	return COMMAND[N];
}
#pragma package(smart_init)
