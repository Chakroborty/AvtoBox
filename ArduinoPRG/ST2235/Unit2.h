//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvSpin.hpp"
#include <Vcl.Mask.hpp>
#include "AdvGroupBox.hpp"
#include "AdvPageControl.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include "AdvCombo.hpp"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TAdvSpinEdit *AdvSpinEdit1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TGroupBox *GroupBox2;
	TAdvSpinEdit *AdvSpinEdit2;
	TLabel *Label1;
	TLabel *Label2;
	TAdvSpinEdit *AdvSpinEdit3;
	TComboBox *ComboBox1;
	TGroupBox *GroupBox3;
	TAdvSpinEdit *AdvSpinEdit4;
	TCheckBox *CheckBox3;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TAdvGroupBox *AdvGroupBox1;
	TGroupBox *GroupBox4;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TGroupBox *GroupBox5;
	TLabel *Label6;
	TComboBox *ComboBox2;
	TButton *Button1;
	TGroupBox *GroupBox6;
	TLabel *Label7;
	TLabel *Label8;
	TComboBox *ComboBox3;
	TAdvSpinEdit *AdvSpinEdit5;
	TAdvSpinEdit *AdvSpinEdit6;
	TLabel *Label9;
	TEdit *Edit1;
	TAdvSpinEdit *AdvSpinEdit7;
	TButton *Button2;
	TAdvGroupBox *AdvGroupBox2;
	TAdvSpinEdit *AdvSpinEdit8;
	TLabel *Label10;
	TGroupBox *GroupBox7;
	TGroupBox *GroupBox8;
	TAdvSpinEdit *AdvSpinEdit9;
	TAdvSpinEdit *AdvSpinEdit10;
	TGroupBox *GroupBox9;
	TLabel *Label11;
	TComboBox *ComboBox4;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox7;
	TAdvPageControl *AdvPageControl1;
	TAdvTabSheet *AdvTabSheet1;
	TAdvTabSheet *AdvTabSheet2;
	TImage *Image1;
	TComboBox *ComboBox5;
	TCheckBox *CheckBox8;
	TComboBox *ComboBox6;
	TComboBox *ComboBox7;
	TComboBox *ComboBox8;
	TCheckBox *CheckBox9;
	TCheckBox *CheckBox10;
	TCheckBox *CheckBox11;
	TCheckBox *CheckBox12;
	TEdit *Edit2;
	TEdit *Edit3;
	TComboBox *ComboBox9;
	TEdit *Edit4;
	TComboBox *ComboBox10;
	TComboBox *ComboBox11;
	TComboBox *ComboBox12;
	TCheckBox *CheckBox13;
	TAdvSpinEdit *AdvSpinEdit11;
	TAdvSpinEdit *AdvSpinEdit12;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall CheckBox4Click(TObject *Sender);
	void __fastcall CheckBox5Click(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall ComboBox3Change(TObject *Sender);
	void __fastcall AdvSpinEdit5Change(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall AdvSpinEdit1Change(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall AdvSpinEdit4Change(TObject *Sender);
	void __fastcall AdvSpinEdit2Change(TObject *Sender);
	void __fastcall AdvSpinEdit3Change(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall AdvSpinEdit8Change(TObject *Sender);
	void __fastcall AdvSpinEdit9Change(TObject *Sender);
	void __fastcall ComboBox5Change(TObject *Sender);
	void __fastcall ComboBox6Change(TObject *Sender);
	void __fastcall ComboBox7Change(TObject *Sender);
	void __fastcall ComboBox8Change(TObject *Sender);
	void __fastcall CheckBox12Click(TObject *Sender);
	void __fastcall ComboBox10Change(TObject *Sender);
	void __fastcall CheckBox13Click(TObject *Sender);
	void __fastcall ComboBox11Change(TObject *Sender);
	void __fastcall ComboBox12Change(TObject *Sender);
	void __fastcall AdvPageControl1Change(TObject *Sender);
	void __fastcall AdvSpinEdit11Change(TObject *Sender);
	void __fastcall AdvSpinEdit12Change(TObject *Sender);
    private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	UnicodeString DATA;
	int VREZ,NREZ;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
