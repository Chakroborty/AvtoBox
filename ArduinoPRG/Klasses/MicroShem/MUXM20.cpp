//---------------------------------------------------------------------------

#pragma hdrstop

#include "MUXM20.h"
//---------------------------------------------------------------------------

UXM20::UXM20()
{
	N20[0] =0;
	N20[1] =0;
	N20[2] =0x3;
	N20[3] =0;
	N20[4] =0x1;
	N20[5] =0x2;
}
UXM20::~UXM20()
{

}
int UXM20::SETUXM20(int N)
{
		switch (N)
	{
	case 1: NDIV = 1;COD = N20[1];   break;
	case 2: NDIV = 2;COD = N20[2];   break;
	case 4: NDIV = 4;COD = N20[4];   break;
	case 5: NDIV = 5;COD = N20[5];   break;
	default: NDIV = 1;COD = N20[1];   break; // N = 1
	}
	return COD;
}
int UXM20::RETURNCOD()
{
	return COD;
}

#pragma package(smart_init)
