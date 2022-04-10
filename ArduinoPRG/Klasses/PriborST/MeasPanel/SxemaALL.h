//---------------------------------------------------------------------------

#ifndef SxemaALLH
#define SxemaALLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <string.h>
#include "ManageINI.h"
#include "StendPR.h"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Grids.hpp>
#include "AdvUtil.hpp"
#include "AdvPageControl.hpp"
#include "W7Classes.hpp"
#include "W7Images.hpp"
#include <Vcl.ComCtrls.hpp>
#include "VirtBlock.h"
//#include "SINTH9910.h"
//---------------------------------------------------------------------------
//extern String DEV;
class TFormSH : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TButton *Button1;
	TLabel *Label8;
	TEdit *Edit1;
	TEdit *Edit7;
	TLabel *Label9;
	TEdit *EditIP;
	TEdit *Edit10;
	TLabel *Label11;
	TLabel *Label12;
	TComboBox *ComboBox1;
	TLabel *Label13;
	TEdit *Edit11;
	TGroupBox *GroupBox1;
	TEdit *Edit9;
	TEdit *Edit8;
	TComboBox *ComboBox2;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TComboBox *cbb1;
	TComboBox *ComboBox3;
	TComboBox *cbb2;
	TComboBox *cbb3;
	TComboBox *cbb4;
	TComboBox *cbb5;
	TEdit *EditBPadr;
	TComboBox *ComboBPN6700;
	TLabel *Label1;
	TComboBox *ComboBox16;
	TLabel *Label2;
	TAdvStringGrid *AdvStringGrid1;
	TLabel *Label10;
	TAdvPageControl *AdvPageControl1;
	TAdvTabSheet *AdvTabSheet1;
	TAdvTabSheet *Настройки;
	TW7Image *W7Image1;
	TW7Image *W7Image2;
	TAdvTabSheet *Калибровка;
	TW7Image *W7Image3;
	TW7Image *W7Image4;
	TW7Image *W7Image5;
	TW7Image *W7Image6;
	TW7Image *W7Image7;
	TW7Image *W7Image8;
	TW7Image *W7Image9;
	TLabel *Label17;
	TButton *Button2;
	TEdit *Edit12;
	TLabel *Label18;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBox3Change(TObject *Sender);
	void __fastcall ComboBPN6700Change(TObject *Sender);
	void __fastcall cbb3Change(TObject *Sender);
	void __fastcall cbb5Change(TObject *Sender);
	void __fastcall cbb4Change(TObject *Sender);
	void __fastcall ComboBox16Change(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations

	OPTIONS_BASE *MemINI;
	StendPRibor *Stend;
  //  BL9910 *STRPU16;
	  double Pw;
	  double Rf;
	  double Rf10M;
	  double Sp;
	  double RB;
	  String PAth;
	  String DEV;
      String DEVXXX;
 void TFormSH_INIT(String PDEV,String PDEVL,IBLock* Block);
 void DEFPath();
	__fastcall TFormSH(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSH *FormSH;
//---------------------------------------------------------------------------
#endif
