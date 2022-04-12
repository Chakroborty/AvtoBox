//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvPageControl"
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_HMC830->SetBIT09(ComboBox3->ItemIndex,CheckBox1->Checked,CheckBox2->Checked,CheckBox3->Checked);    //(int Offset,int UP,int DN,int MHiKCP);
		Form1->BLOK37->MFC1->Sint1_HMC830->CURSet(ComboBox1->ItemIndex,ComboBox2->ItemIndex);
		Form1->BLOK37->Load830UNO(9);
		//Form1->BLOKRR->LoadMFC1();
}
//---------------------------------------------------------------------------

