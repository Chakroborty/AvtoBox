//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSpin"
#pragma link "AdvGroupBox"
#pragma link "AdvPageControl"
#pragma link "AdvCombo"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->Default();
		Form1->BLOK37->MFC1->Sint1_LMX2594->SetFreq(AdvSpinEdit6->FloatValue);
		Form1->BLOK37->LoadLMX1();
        Sleep(200);
		DATA = Form1->BLOK37->ReadLMXUNO(20);
		DATA = DATA.SubString(11,4);
		VREZ = StrToInt("0x"+DATA);
		VREZ = VREZ>>11&0x7;
		ComboBox1->ItemIndex = VREZ;
		Sleep(200);
        DATA = Form1->BLOK37->ReadLMXUNO(19);
		DATA = DATA.SubString(11,4);
		VREZ = StrToInt("0x"+DATA);
		VREZ = VREZ&0xFF;
		AdvSpinEdit1->Value = VREZ;
		Sleep(200);
		DATA = Form1->BLOK37->ReadLMXUNO(78);
		DATA = DATA.SubString(11,4);
		VREZ = StrToInt("0x"+DATA);
		VREZ = VREZ>>1&0xFF;
		AdvSpinEdit4->Value = VREZ;

		Sleep(200);
		DATA = Form1->BLOK37->ReadLMXUNO(34);
		DATA = DATA.SubString(11,4);
		VREZ = StrToInt("0x"+DATA);
		VREZ = (VREZ&0x7)<<16;
		DATA = Form1->BLOK37->ReadLMXUNO(36);
		DATA = DATA.SubString(11,4);
		NREZ = StrToInt("0x"+DATA);
		NREZ = NREZ&0xFFFF;
		VREZ = VREZ|NREZ;
		AdvSpinEdit8->Value = VREZ;

		Sleep(200);
		DATA = Form1->BLOK37->ReadLMXUNO(42);
		DATA = DATA.SubString(11,4);
		VREZ = StrToInt("0x"+DATA);
		VREZ = (VREZ&0xFFFF)<<16;
		DATA = Form1->BLOK37->ReadLMXUNO(43);
		DATA = DATA.SubString(11,4);
		NREZ = StrToInt("0x"+DATA);
		NREZ = NREZ&0xFFFF;
		VREZ = VREZ|NREZ;
		AdvSpinEdit9->Value = VREZ;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox4Click(TObject *Sender)
{
			switch (CheckBox4->Checked)
			{
			case 0: Form1->BLOK37->MFC1->Sint1_LMX2594->PDovn(0);   break;
			case 1: Form1->BLOK37->MFC1->Sint1_LMX2594->PDovn(1);   break;
			default:    break;
			}

		Form1->BLOK37->LoadLMXUNO(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox5Click(TObject *Sender)
{
				switch (CheckBox5->Checked)
			{
			case 0: Form1->BLOK37->MFC1->Sint1_LMX2594->FReset(0);   break;
			case 1: Form1->BLOK37->MFC1->Sint1_LMX2594->FReset(1);   break;
			default:    break;
			}

			Form1->BLOK37->LoadLMXUNO(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox2Change(TObject *Sender)
{
				switch (ComboBox2->ItemIndex)
			{
			case 0: Form1->BLOK37->MFC1->Sint1_LMX2594->MoUTLD(0);   break;
			case 1: Form1->BLOK37->MFC1->Sint1_LMX2594->MoUTLD(1);   break;
			default:    break;
			}

			Form1->BLOK37->LoadLMXUNO(0);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::ComboBox3Change(TObject *Sender)
{
			   	switch (ComboBox2->ItemIndex)
			{
			case 0: Form1->BLOK37->MFC1->Sint1_LMX2594->LDTupe(0);   break;
			case 1: Form1->BLOK37->MFC1->Sint1_LMX2594->LDTupe(1);   break;
			default:    break;
			}

			Form1->BLOK37->LoadLMXUNO(59);//    3B

}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit5Change(TObject *Sender)
{
		  Form1->BLOK37->MFC1->Sint1_LMX2594->LDDLY(AdvSpinEdit5->Value);
          Form1->BLOK37->LoadLMXUNO(60);//3C
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox1Click(TObject *Sender)
{
           switch (CheckBox1->Checked)
			{
			case 0: Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_FORCE(0);   break;
			case 1: Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_FORCE(1);   break;
			default:    break;
			}

			Form1->BLOK37->LoadLMXUNO(8);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox3Click(TObject *Sender)
{
         switch (CheckBox3->Checked)
			{
			case 0: Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_SEL_FORCE(0);   break;
			case 1: Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_SEL_FORCE(1);   break;
			default:    break;
			}

			Form1->BLOK37->LoadLMXUNO(20);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox2Click(TObject *Sender)
{
         switch (CheckBox2->Checked)
			{
			case 0: Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_STRT(0);   break;// нет процедуры
			case 1: Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_STRT(1);   break;
			default:    break;
			}

			Form1->BLOK37->LoadLMXUNO(17);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit1Change(TObject *Sender)
{
         Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(AdvSpinEdit1->Value);
         Form1->BLOK37->LoadLMXUNO(19);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{

		Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_SEL(ComboBox1->ItemIndex);  //
		Form1->BLOK37->LoadLMXUNO(20);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit4Change(TObject *Sender)
{
		 Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_STRT(AdvSpinEdit4->Value);
         Form1->BLOK37->LoadLMXUNO(78);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit2Change(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET(AdvSpinEdit2->Value);
        Form1->BLOK37->LoadLMXUNO(16);
}

//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit3Change(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_STRT(AdvSpinEdit4->Value);
		Form1->BLOK37->LoadLMXUNO(17);
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
		Edit1->Text = Form1->BLOK37->ReadLMXUNO(AdvSpinEdit7->Value);
		Edit1->Text = Edit1->Text.SubString(11,4);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit8Change(TObject *Sender)
{
	   Form1->BLOK37->MFC1->Sint1_LMX2594->NSET(AdvSpinEdit8->Value);
	   Form1->BLOK37->LoadLMXUNO(34);
	   Form1->BLOK37->LoadLMXUNO(36);
	   Form1->BLOK37->MFC1->Sint1_LMX2594->FCAL_EN(0);
	   Form1->BLOK37->LoadLMXUNO(0);
	   Form1->BLOK37->MFC1->Sint1_LMX2594->FCAL_EN(1);
	   Form1->BLOK37->LoadLMXUNO(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit9Change(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->FRSET(AdvSpinEdit9->Value);
		Form1->BLOK37->LoadLMXUNO(42);
		Form1->BLOK37->LoadLMXUNO(43);
		Form1->BLOK37->MFC1->Sint1_LMX2594->FCAL_EN(0);
		Form1->BLOK37->LoadLMXUNO(0);
		Form1->BLOK37->MFC1->Sint1_LMX2594->FCAL_EN(1);
		Form1->BLOK37->LoadLMXUNO(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox5Change(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->CURSET(ComboBox5->ItemIndex);
		Form1->BLOK37->LoadLMXUNO(14);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox6Change(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->FCALLPFDADJ(ComboBox6->ItemIndex);
		Form1->BLOK37->LoadLMXUNO(0);

}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox7Change(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->FCALHPFDADJ(ComboBox7->ItemIndex);
		Form1->BLOK37->LoadLMXUNO(0);

}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox8Change(TObject *Sender)
{
		Form1->BLOK37->MFC1->Sint1_LMX2594->CALCLKDIV(ComboBox8->ItemIndex);
		Form1->BLOK37->LoadLMXUNO(1);

}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox12Click(TObject *Sender)
{
			switch (CheckBox12->Checked)
	{
	case 0:		Form1->BLOK37->MFC1->Sint1_LMX2594->FCAL_EN(0);
				Form1->BLOK37->LoadLMXUNO(0);    break;
	case 1: 	Form1->BLOK37->MFC1->Sint1_LMX2594->FCAL_EN(1);
	   			Form1->BLOK37->LoadLMXUNO(0);   break;
	default: 	Form1->BLOK37->MFC1->Sint1_LMX2594->FCAL_EN(0);
	   			Form1->BLOK37->LoadLMXUNO(0);   break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox10Change(TObject *Sender)
{
  Form1->BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->CHANDiV(ComboBox10->ItemIndex)); //R75[10:6]
}
//-----
void __fastcall TForm2::CheckBox13Click(TObject *Sender)
{
			switch (CheckBox13->Checked) //R31[14]
	{
	case 0:	Form1->BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->SEG1EN(0));
			break;
	case 1: Form1->BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->SEG1EN(1));
			break;
	default:Form1->BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->SEG1EN(1));
			break;
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm2::ComboBox11Change(TObject *Sender)
{
Form1->BLOK37->MFC1->Sint1_LMX2594->OUTAMUX(ComboBox11->ItemIndex);
Form1->BLOK37->LoadLMXUNO(45);
//R45[12:11]
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox12Change(TObject *Sender)
{

Form1->BLOK37->MFC1->Sint1_LMX2594->OUTBMUX(ComboBox12->ItemIndex);
Form1->BLOK37->LoadLMXUNO(46);
//R46[1:0]
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvPageControl1Change(TObject *Sender)
{
				//AdvPageControl1->ActivePageIndex=1;
					switch (AdvPageControl1->ActivePageIndex)
		{
					case 0: AdvSpinEdit8Change(Sender);
							AdvSpinEdit9Change(Sender);
							CheckBox12Click(Sender);
							CheckBox13Click(Sender);
							ComboBox10Change(Sender);
                        	ComboBox11Change(Sender);
					break;
					case 1: ComboBox2Change(Sender);
							CheckBox4Click(Sender);
					break;
					default:    break;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit11Change(TObject *Sender)
{
	Form1->BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTAPWR(AdvSpinEdit11->Value));

}
//---------------------------------------------------------------------------

void __fastcall TForm2::AdvSpinEdit12Change(TObject *Sender)
{
	Form1->BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTBPWR(AdvSpinEdit12->Value));
}
//---------------------------------------------------------------------------

