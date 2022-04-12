//---------------------------------------------------------------------------

#ifndef DiapazonSearchH
#define DiapazonSearchH
//---------------------------------------------------------------------------
//#include "BinSearch.h"
#include <stdio.h>
#include <string.h >
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include "AdvPageControl.hpp"
#include <Vcl.ComCtrls.hpp>
//#include "Test3DG1.h"
#include "Unit1.h"
#include "AdvUtil.hpp"
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TAdvStringGrid *advstrngrd1;
	TBitBtn *btn1;
	TOpenDialog *dlgOpen1;
	TSaveDialog *dlgSave1;
	TButton *btn2;
	TEdit *edt1;
	TEdit *edt2;
	TAdvPageControl *AdvPageControl1;
	TAdvTabSheet *AdvTabSheet1;
	TAdvTabSheet *AdvTabSheet2;
	TAdvStringGrid *AdvStringGrid1;
	TBitBtn *BitBtn1;
	TButton *Button3;
	TSpinEdit *SpinEdit1;
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall edt1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
	AnsiString Path;
	AnsiString Pint;
    	struct Diapazon
	{
		double DFv;
		double DFS;
		int DM;
		int K;
		int MOUT;
		int DN;
        int CAP1;
		int VCO;
	};
	Diapazon Polosa[270];
	Diapazon Point;
    int binary_search(double x, int l ,int r);
	//BinSH *Massive;
	int i;
	double Delta;
	char buffer[4]; //результат
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
