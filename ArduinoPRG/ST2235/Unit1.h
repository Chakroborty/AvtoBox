//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
// #include "DiapazonLoad.h"
#include "DiapazonSearch.h"
#include "DialogSave.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtBlock.h"
#include "BL3CR37.h"
#include "SxemaALL.h"
#include "AdvPageControl.hpp"
#include <Vcl.ComCtrls.hpp>
#include "Unit2.h"
#include "Unit3.h"
#include "DialogSave.h"
#include "SxemaALL.h"
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include "AdvSpin.hpp"
#include <Vcl.Mask.hpp>
#include "AdvPicture.hpp"
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TAdvPageControl *AdvPageControl1;
	TAdvTabSheet *AdvTabSheet1;
	TAdvTabSheet *AdvTabSheet2;
	TAdvTabSheet *AdvTabSheet3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TButton *Button2;
	TLabel *Label4;
	TLabel *Label5;
	TButton *Button3;
	TButton *Button4;
	TComboBox *ComboBox3;
	TButton *Button5;
	TButton *Button6;
	TEdit *Edit2;
	TLabel *Label6;
	TButton *Button7;
	TMainMenu *MainMenu1;
	TMenuItem *Open1;
	TMenuItem *Config1;
	TMenuItem *LMX25941;
	TEdit *Edit3;
	TEdit *Edit4;
	TMenuItem *HMC831;
	TAdvSpinEdit *AdvSpinEdit1;
	TLabel *Label8;
	TMenuItem *MFC11;
	TButton *Button8;
	TRichEdit *RichEdit1;
	TImage *Image1;
	TImage *Image2;
	TAdvSpinEdit *AdvSpinEdit2;
	TAdvSpinEdit *AdvSpinEdit3;
	TAdvSpinEdit *AdvSpinEdit4;
	TComboBox *ComboBox4;
	TAdvSpinEdit *AdvSpinEdit5;
	TComboBox *ComboBox5;
	TComboBox *ComboBox6;
	TComboBox *ComboBox7;
	TComboBox *ComboBox8;
	TEdit *Edit5;
	TEdit *Edit6;
	TLabel *Label1;
	TComboBox *ComboBox9;
	TGroupBox *GroupBox1;
	TCheckBox *CheckBox3;
	TAdvSpinEdit *AdvSpinEdit6;
	TButton *Button9;
	TComboBox *ComboBox11;
	TMenuItem *N1;
	TComboBox *ComboBox12;
	TButton *Button10;
	TComboBox *ComboBox13;
	TLabel *Label2;
	TComboBox *ComboBox14;
	TLabel *Label3;
	TCheckBox *CheckBox4;
	TAdvSpinEdit *AdvSpinEdit7;
	TStringGrid *StringGrid1;
	TComboBox *CmB17;
	TButton *btn1;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TButton *Button17;
	TComboBox *ComboBox10;
	TEdit *Edit12;
	TButton *Button18;
	TLabel *Label62;
	TLabel *Label21;
	TLabel *Label19;
	TLabel *Label18;
	TLabel *Label17;
	TLabel *Label15;
	TLabel *Label14;
	TAdvSpinEdit *AdvSpinEdit8;
	TStringGrid *StringGrid2;
	TStringGrid *StringGrid3;
	TStringGrid *StringGrid4;
	TButton *Button19;
	TAdvSpinEdit *AdvSpinEdit9;
	TRichEdit *RichEdit2;
	TStringGrid *StringGrid5;
	TLabel *Label7;
	TButton *Button20;
	TButton *Button21;
	TButton *Button22;
	TLabel *Label9;
	TButton *Button23;
	TStringGrid *StringGrid6;
	TOpenDialog *OpenDialog1;
	TLabel *Label10;
	TPopupMenu *PopupMenu1;
	TMenuItem *N2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall LMX25941Click(TObject *Sender);
	void __fastcall HMC831Click(TObject *Sender);
	void __fastcall MFC11Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall ComboBox4Change(TObject *Sender);
	void __fastcall AdvSpinEdit2Change(TObject *Sender);
	void __fastcall AdvSpinEdit3Change(TObject *Sender);
	void __fastcall AdvSpinEdit4Change(TObject *Sender);
	void __fastcall AdvSpinEdit5Change(TObject *Sender);
	void __fastcall ComboBox5Change(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall ComboBox11Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall ComboBox6Change(TObject *Sender);
	void __fastcall ComboBox7Change(TObject *Sender);
	void __fastcall ComboBox12Change(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall ComboBox13Change(TObject *Sender);
	void __fastcall ComboBox14Change(TObject *Sender);
	void __fastcall AdvSpinEdit7Change(TObject *Sender);
	void __fastcall AdvSpinEdit8Change(TObject *Sender);
	void __fastcall CmB17Change(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall AdvSpinEdit9Change(TObject *Sender);
	void __fastcall AdvSpinEdit1Change(TObject *Sender);
	void __fastcall Edit12KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall StringGrid1DblClick(TObject *Sender);
	void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall StringGrid5DblClick(TObject *Sender);
	void __fastcall StringGrid5SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);
	void __fastcall StringGrid6DblClick(TObject *Sender);
	void __fastcall StringGrid6SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall AdvPageControl1Change(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall ComboBox10Change(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
		TGridRect SelectedRect;
		BL3CR37 * BLOK37;
		AnsiString StTAB, param, stparam, Modul, CuMod,Protokol,Path;
		String PathINI;
        void RelBlokRRINI(int Priemka);
		int osob,i, j, k, l, m,ADR, ModTip, Kanal,Zatvor ;
		double Kmin, Kmax,F,Volt,Amper,Icur,Param;
		void MEASPROGON(int Row, TStringGrid* Grid,int GRNUM);
		void RelRPURRINI(int Priemka);
		void Kpdelta(TStringGrid *Grid,int R);
		void Kpmin1();
		double Kpmin(int Col,int Row, TStringGrid* Grid);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
