//---------------------------------------------------------------------------

#pragma hdrstop

#include "MUXM15.h"
//---------------------------------------------------------------------------
UXM15::UXM15()
{

N15[0] = 0;
N15[1] = 0;
N15[2] = 0;
N15[3] = 0;
N15[4] = 0x3;
N15[5] = 0x7;
N15[6] = 0x1;
N15[7] = 0x5;
N15[8] = 0x0;
N15[9] = 0x4;


}
UXM15::~UXM15()
{

}
long UXM15::SETUXM15(int DIV)
{
  switch (DIV)
  {
  case 4: NDIV = DIV;COD = N15[4];0x3;   break;
  case 5: NDIV = DIV;COD = N15[5];0x7;   break;
  case 6: NDIV = DIV;COD = N15[6];0x1;   break;
  case 7: NDIV = DIV;COD = N15[7];0x5;   break;
  case 8: NDIV = DIV;COD = N15[8];0x0;   break;
  case 9: NDIV = DIV;COD = N15[9];0x4;   break;

  default:  NDIV = DIV;COD = N15[4];  break; // N = 9
  }
  	return COD;
}
int UXM15::RETURNCOD()
{
  return COD;
}
//--------------------------------------------------------------------------
#pragma package(smart_init)
