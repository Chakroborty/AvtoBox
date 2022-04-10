//---------------------------------------------------------------------------

#pragma hdrstop

#include "Diapazon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void TForm1::NeMenee(TAdvStringGrid* MyGrid, int Tcol,int Trow,double Param){
		if (MyGrid->Cells[Tcol][Trow].ToDouble()<(Param-2))
	{
		  MyGrid->Colors[Tcol][Trow] = clRed;
	} else
	 {
					if (MyGrid->Cells[Tcol][Trow].ToDouble()<Param) {
			  MyGrid->Colors[Tcol][Trow] = clWebPeachPuff;
		  } else {
			  MyGrid->Colors[Tcol][Trow] = clSkyBlue;
		  }
	 }


 }
void TForm1::Diapazon(TAdvStringGrid* MyGrid, int Tcol,int Trow,double Verx, double Niz){

			 if (MyGrid->Cells[Tcol][Trow].ToDouble()<Verx&MyGrid->Cells[Tcol][Trow].ToDouble()>Niz)
	 {

		  MyGrid->Colors[Tcol][Trow] = clSkyBlue;
	 } else
	 {

		  MyGrid->Colors[Tcol][Trow] = clWebPeachPuff;

	 }
}
void TForm1::NeMenee28(double MyRez, double Param){
		if (MyRez<Param)
	 {
		  Collor = clWebPeachPuff;
	 } else
	 {
		  Collor = clSkyBlue;

	 }


 }
void TForm1::NeBolee(TAdvStringGrid* MyGrid, int Tcol,int Trow,double Param){
	  if (MyGrid->Cells[Tcol][Trow].ToDouble()>(Param+2))
	 {
		  MyGrid->Colors[Tcol][Trow] = clRed;
	 } else
	 {
			if (MyGrid->Cells[Tcol][Trow].ToDouble()>Param)
		  {
			  MyGrid->Colors[Tcol][Trow] = clWebPeachPuff;
		  } else
		  {
			  MyGrid->Colors[Tcol][Trow] = clSkyBlue;
		  }
	 }
}

double TForm1::Delt(double IN1,double IN2){
		   Rez = IN1 - IN2;
			if (Rez<0) {
	   Rez = -Rez;
	  }
	   return 0.1*floor(10*Rez+0.5);
}
