//---------------------------------------------------------------------------

#ifndef KalibrH
#define KalibrH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TFormKalibr1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TButton *Button1;
private:	// User declarations
public:		// User declarations
	__fastcall TFormKalibr1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKalibr1 *FormKalibr1;
//---------------------------------------------------------------------------
#endif
