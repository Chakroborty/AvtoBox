//---------------------------------------------------------------------------

#pragma hdrstop

#include "MHMC394.h"
//---------------------------------------------------------------------------
HMC394::HMC394()
{

N394[0] = 0;
N394[1] = 0;
N394[2] = 0x8;
N394[3] = 0x4;
N394[4] = 0xC;
N394[5] = 0x2;
N394[6] = 0xA;
N394[7] = 0x6;
N394[8] = 0xE;
N394[9] = 0x1;
N394[10] = 0x9;
N394[11] = 0x5;

N394[18] = 0x11; //17 10001  10001 11
N394[19] = 0x9;  //18 10010  01001 9
N394[20] = 0x19; //19 10011  11001 19
N394[21] = 0x5;  //20 10100  00101 5
N394[22] = 0x15; //21 10101  10101 15

}
HMC394::~HMC394()
{

}
long HMC394::SET394(int DIV)
{
	switch (DIV)
		{
		case  0: NDIV =  0;COD = N394[ 0];  break;
		case  2: NDIV =  2;COD = N394[ 2];  break;
		case  3: NDIV =  3;COD = N394[ 3];  break;
		case  4: NDIV =  4;COD = N394[ 4];  break;
		case  5: NDIV =  5;COD = N394[ 5];  break;
		case  6: NDIV =  6;COD = N394[ 6];  break;
		case  7: NDIV =  7;COD = N394[ 7];  break;
		case  8: NDIV =  8;COD = N394[ 8];  break;
		case  9: NDIV =  9;COD = N394[ 9];  break;
		case 10: NDIV = 10;COD = N394[10];  break;
		case 11: NDIV = 11;COD = N394[11];  break;
		case 18: NDIV = 18;COD = N394[18];  break;
		case 19: NDIV = 19;COD = N394[19];  break;
		case 20: NDIV = 20;COD = N394[20];  break;
		case 21: NDIV = 21;COD = N394[21];  break;
		case 22: NDIV = 22;COD = N394[22];  break;
		default: NDIV = 0;COD = N394[0];  break;
		}

return COD;
}
int HMC394::RETURNCOD()
{
    return COD;
}


#pragma package(smart_init)
