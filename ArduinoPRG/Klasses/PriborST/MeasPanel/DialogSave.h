//---------------------------------------------------------------------------

#ifndef DialogSaveH
#define DialogSaveH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SxemaALL.h"
#include "Unit1.h"
//#include "UsbDefines.h"
//---------------------------------------------------------------------------
class TFormSNSW : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TLabel *SNEdit;
	TLabel *Label3;
	TLabel *VerEdit;
	TLabel *Label5;
	TCheckBox *CheckBox1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormSNSW(TComponent* Owner);
	AnsiString DEVICESTR, DEVICESTR_;
	void INITsave(AnsiString DEV);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSNSW *FormSNSW;
//---------------------------------------------------------------------------
#endif
