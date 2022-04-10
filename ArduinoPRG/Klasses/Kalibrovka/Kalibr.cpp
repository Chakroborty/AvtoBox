//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Kalibr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormKalibr1 *FormKalibr1;
//---------------------------------------------------------------------------
__fastcall TFormKalibr1::TFormKalibr1(TComponent* Owner)
	: TForm(Owner)
{    StringGrid1->ColWidths[0] = 55;
}
//---------------------------------------------------------------------------
