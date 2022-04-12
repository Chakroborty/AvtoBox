//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "VirtBlock.h"
#include "Unit1.h"
#include "UdpClient.h"
#pragma package(smart_init)
#pragma link "AdvPageControl"
#pragma link "AdvSpin"
#pragma link "AdvPicture"
#pragma resource "*.dfm"
using namespace LightNetwork;
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	 BLOK37 = new BL3CR37();
    StringGrid1->ColWidths[0] = 55;
    StringGrid1->Cells[0][0] = "№";
	StringGrid1->Cells[1][0] = "K1.1";
	StringGrid1->Cells[2][0] = "K1.2";
	StringGrid1->Cells[3][0] = "K2.1";
	StringGrid1->Cells[4][0] = "K2.2";
	StringGrid1->Cells[5][0] = "K3.1";
	StringGrid1->Cells[6][0] = "K3.2";
	StringGrid1->Cells[7][0] = "K4.1";
	StringGrid1->Cells[8][0] = "K4.2";
	StringGrid1->Cells[9][0] = "K5.1";
	StringGrid1->Cells[10][0] = "K5.2";
	StringGrid1->Cells[11][0] = "K6.1";
	StringGrid1->Cells[12][0] = "K6.2";
	StringGrid1->Cells[13][0] = "K7.1";
	StringGrid1->Cells[14][0] = "K7.2";
	StringGrid1->Cells[15][0] = "K8.1";
	StringGrid1->Cells[16][0] = "K8.2";
	StringGrid1->Cells[17][0] = "Del";
	StringGrid1->Cells[0][1] = "30";
	StringGrid1->Cells[0][2] = "1000";
	StringGrid1->Cells[0][3] = "1750";
	StringGrid1->Cells[0][4] = "2200";
	//---------------------------------------------
	StringGrid6->ColWidths[0] = 45;
	StringGrid6->Cells[0][0] = "№";
	StringGrid6->Cells[1][0] = "K1.1";
	StringGrid6->Cells[2][0] = "K1.2";
	StringGrid6->Cells[3][0] = "K2.1";
	StringGrid6->Cells[4][0] = "K2.2";
	StringGrid6->Cells[5][0] = "K3.1";
	StringGrid6->Cells[6][0] = "K3.2";
	StringGrid6->Cells[7][0] = "K4.1";
	StringGrid6->Cells[8][0] = "K4.2";
	StringGrid6->Cells[9][0] = "K5.1";
	StringGrid6->Cells[10][0] = "K5.2";
	StringGrid6->Cells[11][0] = "K6.1";
	StringGrid6->Cells[12][0] = "K6.2";
	StringGrid6->Cells[13][0] = "K7.1";
	StringGrid6->Cells[14][0] = "K7.2";
	StringGrid6->Cells[15][0] = "K8.1";
	StringGrid6->Cells[16][0] = "K8.2";
  	StringGrid6->Cells[0][1] = "1750";
	//--------------Изм. 1.1.8---------------------
	StringGrid5->ColWidths[0] = 45;
	StringGrid5->Cells[0][0] = "№";
	StringGrid5->Cells[0][0] = "Kанал";
	StringGrid5->Cells[1][0] = "Sen 30 МГц";
	StringGrid5->Cells[2][0] = "Sen 1000 МГц";
	StringGrid5->Cells[3][0] = "Sen 1750 МГц";
	StringGrid5->Cells[4][0] = "Sen 2200 МГц";
	StringGrid5->Cells[5][0] = "P1 1000 МГц";
	//-----------------------------------
	StringGrid2->ColWidths[0] = 45;
	StringGrid2->Cells[0][0] = "№";
	StringGrid2->Cells[1][0] = "K1.1";
	StringGrid2->Cells[2][0] = "K1.2";
	StringGrid2->Cells[3][0] = "K2.1";
	StringGrid2->Cells[4][0] = "K2.2";
	StringGrid2->Cells[5][0] = "K3.1";
	StringGrid2->Cells[6][0] = "K3.2";
	StringGrid2->Cells[7][0] = "K4.1";
	StringGrid2->Cells[8][0] = "K4.2";
	StringGrid2->Cells[9][0] = "K5.1";
	StringGrid2->Cells[10][0] = "K5.2";
	StringGrid2->Cells[11][0] = "K6.1";
	StringGrid2->Cells[12][0] = "K6.2";
	StringGrid2->Cells[13][0] = "K7.1";
	StringGrid2->Cells[14][0] = "K7.2";
	StringGrid2->Cells[15][0] = "K8.1";
	StringGrid2->Cells[16][0] = "K8.2";
	StringGrid2->Cells[0][2] = "1000";
	StringGrid2->Cells[0][1] = "1000";
	//-----------------------------------
	StringGrid3->ColWidths[0] = 45;
	StringGrid3->Cells[0][0] = "№";
	StringGrid3->Cells[1][0] = "K1.1";
	StringGrid3->Cells[2][0] = "K1.2";
	StringGrid3->Cells[3][0] = "K2.1";
	StringGrid3->Cells[4][0] = "K2.2";
	StringGrid3->Cells[5][0] = "K3.1";
	StringGrid3->Cells[6][0] = "K3.2";
	StringGrid3->Cells[7][0] = "K4.1";
	StringGrid3->Cells[8][0] = "K4.2";
	StringGrid3->Cells[9][0] = "K5.1";
	StringGrid3->Cells[10][0] = "K5.2";
	StringGrid3->Cells[11][0] = "K6.1";
	StringGrid3->Cells[12][0] = "K6.2";
	StringGrid3->Cells[13][0] = "K7.1";
	StringGrid3->Cells[14][0] = "K7.2";
	StringGrid3->Cells[15][0] = "K8.1";
	StringGrid3->Cells[16][0] = "K8.2";
	StringGrid3->Cells[0][2] = "1000";
	StringGrid3->Cells[0][1] = "1000";
	//-----------------------------------
	StringGrid4->ColWidths[0] = 45;
	StringGrid4->Cells[0][0] = "№";
	StringGrid4->Cells[1][0] = "K1.1";
	StringGrid4->Cells[2][0] = "K1.2";
	StringGrid4->Cells[3][0] = "K2.1";
	StringGrid4->Cells[4][0] = "K2.2";
	StringGrid4->Cells[5][0] = "K3.1";
	StringGrid4->Cells[6][0] = "K3.2";
	StringGrid4->Cells[7][0] = "K4.1";
	StringGrid4->Cells[8][0] = "K4.2";
	StringGrid4->Cells[9][0] = "K5.1";
	StringGrid4->Cells[10][0] = "K5.2";
	StringGrid4->Cells[11][0] = "K6.1";
	StringGrid4->Cells[12][0] = "K6.2";
	StringGrid4->Cells[13][0] = "K7.1";
	StringGrid4->Cells[14][0] = "K7.2";
	StringGrid4->Cells[15][0] = "K8.1";
	StringGrid4->Cells[16][0] = "K8.2";
	StringGrid4->Cells[0][2] = "1000";
	StringGrid4->Cells[0][1] = "1000";
	//-----------------------------------
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{   ComboBox1Change(Sender);
	ComboBox2Change(Sender);
	CheckBox1Click(Sender);
	CheckBox2Click(Sender);

  //   switch (ComboBox11->ItemIndex)
		// {
		// case 0:  	BLOK37->MFC1->Sint1_HMC830->Xtal = 100;
		// 			BLOK37->MFC1->Set394(10);
		// break;
		// case 1:  	BLOK37->MFC1->Sint1_HMC830->Xtal = 90.9090909091;
		// 			BLOK37->MFC1->Set394(11);
		// break;
		// default:  BLOK37->MFC1->Sint1_HMC830->Xtal = 100;
		// 		  BLOK37->MFC1->Set394(10);
		// break;
		// }

					switch (ComboBox11->ItemIndex)
		{
		case 0:  	BLOK37->MFC1->Sint1_HMC830->SetREF(111.11111111,1);
					BLOK37->MFC1->Set394(18);
		break;
		case 1:  	BLOK37->MFC1->Sint1_HMC830->SetREF(105.26315789,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(19);
		break;
		case 2:  	BLOK37->MFC1->Sint1_HMC830->SetREF(100.00000000,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(20);
		break;
		case 3:  	BLOK37->MFC1->Sint1_HMC830->SetREF(95.23809524,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(21);
		break;
		case 4:  	BLOK37->MFC1->Sint1_HMC830->SetREF(90.90909091,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(22);
		break;
		case 5:  	BLOK37->MFC1->Sint1_HMC830->SetREF(86.95652174,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(23);
		break;
		default:  BLOK37->MFC1->Sint1_HMC830->SetREF(100.0,1);
				  BLOK37->MFC1->Set394(20);
		break;
		}

	BLOK37->MFC1->Sint1_HMC830->SetFreq(Edit4->Text.ToDouble());
	BLOK37->LoadMFC1();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{//TODO: INITSTEND @STEND (Unit1.cpp)
	   FormSH->TFormSH_INIT("BLOK37","B",BLOK37);
	   FormSNSW->INITsave("BLOK37");
	   Form4->Path = ExtractFilePath(Application->ExeName);
	   Form4->Path = Path +"MFC1.bin";
	   FILE *pfile ;
	   pfile = fopen(Form4->Path.c_str(), "r+b");
       fread(&Form4->Polosa, sizeof(Form4->Polosa), 1, pfile);

//					Path = ExtractFilePath(Application->ExeName);
//					Path = Path +"MFC1.bin";
//					FILE *pfile ;
//					pfile = fopen(Path.c_str(), "r+b");
//					fread(&Polosa, sizeof(Polosa), 1, pfile);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
	 FormSH->ShowModal();
}
//---------------------------------------------------------------------------
void TForm1::Kpdelta(TStringGrid *Grid,int R)
{//CHANGED: DELTA @MEAS (0)

 Kmin = Grid->Cells[1][R].ToDouble();
 Kmax = Grid->Cells[1][R].ToDouble();

	for (i = 1; i < 13; i++)
	{
				if (Grid->Cells[i][R]!="")
		{
				if (Grid->Cells[i][R].ToDouble()>Kmax)
				{  	Kmax = Grid->Cells[i][R].ToDouble();}
				if (Grid->Cells[i][R].ToDouble()<Kmin)
				{  	Kmin = Grid->Cells[i][R].ToDouble();}
		}
	}
 Grid->Cells[17][R] = 0.1*floor(10*(Kmax- Kmin));
}

//---------------------------------------------------------------------------

void TForm1::Kpmin1()
{
	Kmin = StringGrid1->Cells[i][1].ToDouble();
	for (i = 1; i < 13; i++)
	{
			if (StringGrid1->Cells[i][1]!="")
		{
				if (StringGrid1->Cells[i][1].ToDouble()<Kmin)
				{
					Kmin = StringGrid1->Cells[i][1].ToDouble();
				}
		}

	}
		 StringGrid1->Cells[13][1] = Kmin;

}


//---------------------------------------------------------------------------
double TForm1::Kpmin(int Col,int Row, TStringGrid* Grid)
{
   // Col =1;
	Kmin = Grid->Cells[Col][Row].ToDouble();

	for (i = Col; i < (Grid->ColCount-1); i++)//for (i = 1; i < (Grid->ColCount-1); i++)
	{
		if (!Grid->Cells[i][Row].IsEmpty())
		{
			if (Grid->Cells[i][Row].ToDouble()<Kmin)
			{
				Kmin = Grid->Cells[i][Row].ToDouble();
			}
		}

	}
	 return Kmin;
}
//---------------------------------------------------------------------------
void TForm1::MEASPROGON(int Row, TStringGrid* Grid,int GRNUM)
{//FUNC: MMEASPROGON @MEAS (1)
 Zatvor=0;
	/* if (!BlokSNchek())
	{
		  if(mrNo==MessageDlg("Зав. номера разные. Продолжить?", mtInformation,
				TMsgDlgButtons() << mbNo << mbYes, 0))
				{	 //ShowMessage("Зав. номера разные");
				 return;
				}
	}*/

	 for (osob = 1; osob < 17; osob++)
	{        if (Zatvor)
				{
				 Zatvor=0;
				 return;
				}
						/*if (Stend->TCom==0)
			{
				 if (Stend->ChekCon(1000,osob))
				 {
					ShowMessage("Подключить кабели к каналу " + IntToStr(osob));
						// return;
				 }
			}*/

			SelectedRect.Left=osob; //Левая граница
			SelectedRect.Top=Row; //Верхняя граница
			SelectedRect.Right=osob; //Правая граница
			SelectedRect.Bottom=Row; //Нижняя граница
			Grid->Selection = SelectedRect;
			Grid->Cells[osob][Row] = FormSH->Stend->GeinAnGen(1000.0,255.0,0,0,FormSH->Stend->TCom,osob,1)+FormSH->Stend->CTbl[1];
			param = "Kp" +  IntToStr(Row) + IntToStr(osob);
			stparam = "Tabl"+IntToStr(GRNUM);
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,stparam.c_str(),param.c_str(),Grid->Cells[osob][Row].ToDouble());
			Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------
void TForm1::RelBlokRRINI(int Priemka)
{//CHANGED: RELOAD @INI (0)
	Edit12->Text = FormSH->MemINI->ReadDouble("Blok","Зав№", 22);
 //----------------------------Восстановление табл.1----------------------------------
	//AnsiString ExecDir = ExtractFileDir(ParamStr(0));
	AnsiString param;
	for (i = 1; i < 17; i++)
	{//NOTE: REL T1 @INI (0)
		param = "Kp" +  IntToStr(i) + "30";
		StringGrid1->Cells[i][1] = FormSH->MemINI->TReadString(Priemka,"Tabl1",param.c_str(),"");
		param = "Kp" +  IntToStr(i) + "1000";
		StringGrid1->Cells[i][2] = FormSH->MemINI->TReadString(Priemka,"Tabl1",param.c_str(),"");
		param = "Kp" +  IntToStr(i) + "1750";
		StringGrid1->Cells[i][3] = FormSH->MemINI->TReadString(Priemka,"Tabl1",param.c_str(),"");
		param = "Kp" +  IntToStr(i) + "2200";
		StringGrid1->Cells[i][4] = FormSH->MemINI->TReadString(Priemka,"Tabl1",param.c_str(),"");
	}
	for (int i = 1; i < 5; ++i)
	  {
		param = "KpDEL" + IntToStr(i) ;
		StringGrid1->Cells[17][i] =  FormSH->MemINI->TReadString(Priemka,"Tabl1",param.c_str(),"");
	  }
//-------------------------------------1750 МГц------------------------------------------
	for (i = 1; i < 17; i++)
	{//NOTE: REL T2 @INI (0)
		param = "Kp" +  IntToStr(i) + "_1750";
		StringGrid6->Cells[i][1] = FormSH->MemINI->TReadString(Priemka,"Tabl2",param.c_str(),"");
	}
//--------------------------------SENS------------------------------------------------
		param = "Sens30";
		StringGrid5->Cells[1][1] = FormSH->MemINI->TReadString(Priemka,"Tabl3",param.c_str(),"");
		param = "Sens1000";
		StringGrid5->Cells[2][1] = FormSH->MemINI->TReadString(Priemka,"Tabl3",param.c_str(),"");
		param = "Sens1750";
		StringGrid5->Cells[3][1] = FormSH->MemINI->TReadString(Priemka,"Tabl3",param.c_str(),"");
		param = "Sens2200";
		StringGrid5->Cells[4][1] = FormSH->MemINI->TReadString(Priemka,"Tabl3",param.c_str(),"");
		param = "IP1";
		StringGrid5->Cells[5][1] = FormSH->MemINI->TReadString(Priemka,"Tabl3",param.c_str(),"");
//--------------------------------0-8------------------------------------------------
	for(j = 1; j < 3; ++j)
	{

	for (i = 1; i < 17; i++)
		{//NOTE: REL T4 @INI (0)
			param = "Kp" +  IntToStr(j) + IntToStr(i);
			StringGrid2->Cells[i][j] = FormSH->MemINI->TReadString(Priemka,"Tabl4",param.c_str(),"");
		}
	}
//--------------------------------8-16-----------------------------------------------
	for(j = 1; j < 3; ++j)
	{

	for (i = 1; i < 17; i++)
		{//NOTE: REL T5 @INI (0)
			param = "Kp" +  IntToStr(j) + IntToStr(i);
			StringGrid3->Cells[i][j] = FormSH->MemINI->TReadString(Priemka,"Tabl5",param.c_str(),"");
		}
	}
//---------------------------------16-24-----------------------------------------
	for(j = 1; j < 3; ++j)
	{

	for (i = 1; i < 17; i++)
		{//NOTE: REL T6 @INI (0)
			param = "Kp" +  IntToStr(j) + IntToStr(i);
			StringGrid4->Cells[i][j] = FormSH->MemINI->TReadString(Priemka,"Tabl6",param.c_str(),"");
		}
	}

}

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
			if(CheckBox1->Checked)
		{
			BLOK37->MFC1->UPR2 = 1;
		}
			else
		{
			BLOK37->MFC1->UPR2 = 0;
		}


}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
			if(CheckBox2->Checked)
		{
			BLOK37->MFC1->UPR1 = 1;
		}
			else
		{
			BLOK37->MFC1->UPR1 = 0;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
		BLOK37->MFC1->SetUXM15(ComboBox1->Text.ToInt());  //if 15
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{
		BLOK37->MFC1->SetUXD20(ComboBox2->Text.ToInt());	// UXL20


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
			BLOK37->LoadLMX1();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
		BLOK37->MFC1->Sint1_LMX2594->REG[0] = 0x00241A;
		BLOK37->LoadLMXUNO(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
		BLOK37->MFC1->Sint1_LMX2594->REG[0] = 0x00248;
		BLOK37->LoadLMXUNO(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
		//BLOK37->MFC1->Sint1_LMX2594->REG[0] = 0x002418;
		BLOK37->LoadLMXUNO(ComboBox3->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	   //	BLOK37->MFC1->Sint1_LMX2594->REG[0] = 0x002514;
	Edit3->Text = BLOK37->ReadLMXUNO(ComboBox3->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
if(Edit2->Text.ToDouble()==7775) {	i=0;}
if(Edit2->Text.ToDouble()==7820) {	i=1;}
if(Edit2->Text.ToDouble()==8020) {	i=2;}else{i=5;}
							switch (i)
			{
				case 0:
					BLOK37->MFC1->Sint1_LMX2594->SetFreq(Edit2->Text.ToDouble());
					Form2->AdvSpinEdit4->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST;
					Form2->AdvSpinEdit3->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_ST;
					BLOK37->MFC1->Sint1_LMX2594->NSET(117);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_FORCE(1);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(Form2->AdvSpinEdit4->Value - AdvSpinEdit1->Value);
					BLOK37->LoadLMX1();
				break;
				case 1:
					BLOK37->MFC1->Sint1_LMX2594->SetFreq(Edit2->Text.ToDouble());
					Form2->AdvSpinEdit4->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST;
					Form2->AdvSpinEdit3->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_ST;
					BLOK37->MFC1->Sint1_LMX2594->NSET(63);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_FORCE(1);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(Form2->AdvSpinEdit4->Value - AdvSpinEdit1->Value);
					BLOK37->LoadLMX1();

				break;
				case 2:
					BLOK37->MFC1->Sint1_LMX2594->SetFreq(Edit2->Text.ToDouble());
					Form2->AdvSpinEdit4->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST;
					Form2->AdvSpinEdit3->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_ST;
					BLOK37->MFC1->Sint1_LMX2594->NSET(51);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_FORCE(1);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(Form2->AdvSpinEdit4->Value - AdvSpinEdit1->Value);
					BLOK37->LoadLMX1();
				break;
				default:
					BLOK37->MFC1->Sint1_LMX2594->SetFreq(7820);
					Form2->AdvSpinEdit4->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST;
					Form2->AdvSpinEdit3->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_ST;
					ComboBox1->ItemIndex = 2;
					Edit4->Text = 7820/(ComboBox1->ItemIndex + 4) - 7820/63 -1000;

					// 			switch (ComboBox11->ItemIndex)
					// {
					// case 0:  	BLOK37->MFC1->Sint1_HMC830->Xtal = 100;
					// 			BLOK37->MFC1->Set394(10);
					// break;
					// case 1:  	BLOK37->MFC1->Sint1_HMC830->Xtal = 90.9090909091;
					// 			BLOK37->MFC1->Set394(11);
					// break;
					// default:  BLOK37->MFC1->Sint1_HMC830->Xtal = 100;
					// 		  BLOK37->MFC1->Set394(10);
					// break;
					// }
									switch (ComboBox11->ItemIndex)
					{
					case 0:  	BLOK37->MFC1->Sint1_HMC830->SetREF(111.11111111,1);
								BLOK37->MFC1->Set394(18);
					break;
					case 1:  	BLOK37->MFC1->Sint1_HMC830->SetREF(105.26315789,1); // SetREF(double INREF, double INR)
								BLOK37->MFC1->Set394(19);
					break;
					case 2:  	BLOK37->MFC1->Sint1_HMC830->SetREF(100.00000000,1); // SetREF(double INREF, double INR)
								BLOK37->MFC1->Set394(20);
					break;
					case 3:  	BLOK37->MFC1->Sint1_HMC830->SetREF(95.23809524,1); // SetREF(double INREF, double INR)
								BLOK37->MFC1->Set394(21);
					break;
					case 4:  	BLOK37->MFC1->Sint1_HMC830->SetREF(90.90909091,1); // SetREF(double INREF, double INR)
								BLOK37->MFC1->Set394(22);
					break;
					case 5:  	BLOK37->MFC1->Sint1_HMC830->SetREF(86.95652174,1); // SetREF(double INREF, double INR)
								BLOK37->MFC1->Set394(23);
					break;
					default:  BLOK37->MFC1->Sint1_HMC830->SetREF(100.0,1);
							  BLOK37->MFC1->Set394(20);
					break;
					}


					BLOK37->MFC1->Sint1_HMC830->SetFreq(Edit4->Text.ToDouble());
					BLOK37->LoadMFC1();

					BLOK37->MFC1->SetUXM15(ComboBox1->ItemIndex + 4);
					BLOK37->MFC1->Sint1_LMX2594->NSET(63);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_FORCE(1);
					BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(Form2->AdvSpinEdit4->Value - AdvSpinEdit1->Value);


			   		BLOK37->LoadLMX1();

				break;
			}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMX25941Click(TObject *Sender)
{
         Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HMC831Click(TObject *Sender)
{
		 Form3->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::MFC11Click(TObject *Sender)
{
	   Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
			BLOK37->MFC1->SetAUTOCOR(0,0);
  			BLOK37->LoadLMXUNO(19);

			BLOK37->MFC1->Sint1_LMX2594->SetFreq(Edit2->Text.ToDouble());
			Form2->AdvSpinEdit4->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST;
			Form2->AdvSpinEdit3->Value = BLOK37->MFC1->Sint1_LMX2594->VCO_DACISET_ST;
			BLOK37->LoadLMX1();
			BLOK37->MFC1->Sint1_LMX2594->MoUTLD(1);
			BLOK37->LoadLMXUNO(0);
			i = Form4->binary_search(Edit2->Text.ToDouble(),0,29)-1;

			RichEdit1->Clear();
			RichEdit1->Lines->Add(i);

			RichEdit1->Lines->Add("Fl=" + FloatToStr(Form4->Polosa[i].DFv));
			RichEdit1->Lines->Add("Fp=" + FloatToStr(Form4->Polosa[i+1].DFv));
			RichEdit1->Lines->Add("M=" + IntToStr(Form4->Polosa[i].DM));
			RichEdit1->Lines->Add("K=" + IntToStr(Form4->Polosa[i].K));
			RichEdit1->Lines->Add("OUT=" + IntToStr(Form4->Polosa[i].MOUT));
			RichEdit1->Lines->Add("N=" + IntToStr(Form4->Polosa[i].DN));
			RichEdit1->Lines->Add("CAP1=" + IntToStr(Form4->Polosa[i].CAP1));
			RichEdit1->Lines->Add("VCO=" + IntToStr(Form4->Polosa[i].VCO));
			//BLOK37->MFC1->SetUXM15(ComboBox1->Text.ToInt());  //if 15

            		switch (Form4->Polosa[i].DM)
            {	case 4:ComboBox1->ItemIndex = 0;    break;
	            case 5:ComboBox1->ItemIndex = 1;    break;
	            case 6:ComboBox1->ItemIndex = 2;    break;
	            case 7:ComboBox1->ItemIndex = 3;    break;
				case 8:ComboBox1->ItemIndex = 4;    break;
	            case 9:ComboBox1->ItemIndex = 5;    break;

	            default:  ComboBox1->ItemIndex = 4;    break;
            }
				CheckBox1->Checked = true;
					if(Form4->Polosa[i].K>0)
			{
				CheckBox2->Checked = true;
			}
				else
			{
				CheckBox2->Checked = false;
			}

//					switch (Form4->Polosa[i].MOUT2)
//			{	case 1:ComboBox2->ItemIndex = 0;    break;
//				case 2:ComboBox2->ItemIndex = 1;    break;
//				case 4:ComboBox2->ItemIndex = 2;    break;
//				case 5:ComboBox2->ItemIndex = 3;    break;
//				default:  ComboBox1->ItemIndex = 0;    break;
//			}

            Edit4->Text	= 2000-Edit2->Text.ToDouble()*(Form4->Polosa[i].K*Form4->Polosa[i].DN - Form4->Polosa[i].DM)/(Form4->Polosa[i].K*Form4->Polosa[i].DN*Form4->Polosa[i].DM);

            ComboBox11Change(Sender);
			BLOK37->MFC1->Sint1_LMX2594->NSET(Form4->Polosa[i].DN);
			BLOK37->LoadLMXUNO(34);
			BLOK37->LoadLMXUNO(36);
			BLOK37->MFC1->Sint1_LMX2594->FRSET(0);
			BLOK37->LoadLMXUNO(42);
			BLOK37->LoadLMXUNO(43);
			BLOK37->LoadLMXUNO(BLOK37->MFC1->Sint1_LMX2594->VCO_SEL_FORCE(1));
			BLOK37->LoadLMXUNO(BLOK37->MFC1->Sint1_LMX2594->VCO_SEL(Form4->Polosa[i].VCO));

			Form2->ComboBox1->ItemIndex	= Form4->Polosa[i].VCO;
			BLOK37->LoadLMXUNO(BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_FORCE(1));


					switch (Form4->Polosa[i].MOUT)
					{
					case 1:
					Form2->ComboBox11->ItemIndex=1;
					Form2->ComboBox12->ItemIndex=1;
					//0: Channel divider 1: VCO
					BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTAMUX(1)); //R45
					BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTBMUX(1)); //R46
					break;
					case 2:
					Form2->ComboBox10->ItemIndex=0;
					Form2->ComboBox11->ItemIndex=0;
					Form2->ComboBox12->ItemIndex=0;
					BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->CHANDiV(0)); //R75[10:6]
					BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTAMUX(0)); //R45
					BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTBMUX(0)); //R46
					break;
					default:
					Form2->ComboBox11->ItemIndex=1;
					Form2->ComboBox12->ItemIndex=1;
					//0: Channel divider 1: VCO
					BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTAMUX(1)); //R45
					BLOK37->LoadLMXUNO(Form1->BLOK37->MFC1->Sint1_LMX2594->OUTBMUX(1)); //R46
					break;
					}



			Button1Click(Sender);
			BLOK37->LoadMFC1();
			BLOK37->LoadLMX1();

//					switch (CheckBox3->Checked)
//		{
//		case 0:  BLOK37->MFC1->SetAUTOCOR(0,ComboBox10->ItemIndex);  break;
//		case 1:  BLOK37->MFC1->SetAUTOCOR(1,ComboBox10->ItemIndex);  break;
//		default:  BLOK37->MFC1->SetAUTOCOR(0,ComboBox10->ItemIndex);  break;
//		}
//		BLOK37->LoadLMXUNO(BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(Form4->Polosa[i].CAP1 + AdvSpinEdit1->Value));  /* TODO -cПрогрузка LMX : Подставить из таблицы */
//		Form2->AdvSpinEdit1->Value = Form4->Polosa[i].CAP1; //VCO_CAPCTRL

			Button9Click(Sender);

//		BLOK37->MFC1->Sint1_LMX2594->MoUTLD(1);
//		BLOK37->LoadLMXUNO(0);
//		BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(Form4->Polosa[i].CAP1 + AdvSpinEdit1->Value);
//						switch (CheckBox3->Checked)
//		{
//		case 0:  BLOK37->MFC1->SetAUTOCOR(0,ComboBox10->ItemIndex);  break;
//		case 1:  BLOK37->MFC1->SetAUTOCOR(1,ComboBox10->ItemIndex);  break;
//		default:  BLOK37->MFC1->SetAUTOCOR(0,ComboBox10->ItemIndex);  break;
//		}
//		BLOK37->LoadLMXUNO(19);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox4Change(TObject *Sender)
{

	BLOK37->PRC->SetFriq(0,ComboBox9->ItemIndex,35,ComboBox5->ItemIndex,AdvSpinEdit2->Value,AdvSpinEdit3->Value,AdvSpinEdit4->Value,63-AdvSpinEdit5->Value,1); //int Mod,int Kanal,double Fin,bool Ampl_,int DB1,int DB2,int DB3,int DB4
	BLOK37->PRC->BL_NumModul = AdvSpinEdit8->HexValue<<28;
	BLOK37->PRC->MKanal->KanalNum_B_Mod = ComboBox9->ItemIndex;
	BLOK37->PRC->MKanal->PRESELSET(ComboBox4->ItemIndex);
	Edit5->Text = IntToHex(BLOK37->PRC->LoadKL(1),8);
	BLOK37->PRC->MKanal->AmplifSET(ComboBox5->ItemIndex);  //1 Вкл

	BLOK37->LoadBL3CR37();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AdvSpinEdit2Change(TObject *Sender)
{
	   //	ComboBox4Change(Sender);
		BLOK37->PRC->MKanal->ATT1_SET(AdvSpinEdit2->Value);
		BLOK37->LoadBL3CR37();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvSpinEdit3Change(TObject *Sender)
{
	   //	ComboBox4Change(Sender);
		BLOK37->PRC->MKanal->ATT2_SET(AdvSpinEdit3->Value);
		BLOK37->LoadBL3CR37();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvSpinEdit4Change(TObject *Sender)
{
		//ComboBox4Change(Sender);
		BLOK37->PRC->MKanal->ATT3_SET(AdvSpinEdit4->Value);
		BLOK37->LoadBL3CR37();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvSpinEdit5Change(TObject *Sender)
{
		//ComboBox4Change(Sender);
        BLOK37->PRC->MKanal->ATT4_SET(63-AdvSpinEdit5->Value);
		BLOK37->LoadBL3CR37();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox5Change(TObject *Sender)
{
        ComboBox4Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
//		BLOK37->MFC1->Sint1_LMX2594->MoUTLD(0);
//		BLOK37->LoadLMXUNO(0);
		BLOK37->MFC1->Sint1_LMX2594->MoUTLD(1);
		BLOK37->LoadLMXUNO(0);

		BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL(AdvSpinEdit6->Value);
		// 				switch (CheckBox3->Checked)
		// {
		// case 0:  BLOK37->MFC1->SetAUTOCOR(0,ComboBox10->ItemIndex);  break;
		// case 1:  BLOK37->MFC1->SetAUTOCOR(1,ComboBox10->ItemIndex);  break;
		// default:  BLOK37->MFC1->SetAUTOCOR(0,ComboBox10->ItemIndex);  break;
		// }

	BLOK37->MFC1->SetAUTOCOR(CheckBox3->Checked,CheckBox4->Checked);
	BLOK37->LoadLMXUNO(19);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox11Change(TObject *Sender)
{
					switch (ComboBox11->ItemIndex)
		{
		case 0:  	BLOK37->MFC1->Sint1_HMC830->SetREF(111.11111111,1);
					BLOK37->MFC1->Set394(18);
		break;
		case 1:  	BLOK37->MFC1->Sint1_HMC830->SetREF(105.26315789,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(19);
		break;
		case 2:  	BLOK37->MFC1->Sint1_HMC830->SetREF(100.00000000,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(20);
		break;
		case 3:  	BLOK37->MFC1->Sint1_HMC830->SetREF(95.23809524,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(21);
		break;
		case 4:  	BLOK37->MFC1->Sint1_HMC830->SetREF(90.90909091,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(22);
		break;
		case 5:  	BLOK37->MFC1->Sint1_HMC830->SetREF(86.95652174,1); // SetREF(double INREF, double INR)
					BLOK37->MFC1->Set394(23);
		break;
		default:  BLOK37->MFC1->Sint1_HMC830->SetREF(100.0,1);
				  BLOK37->MFC1->Set394(20);
		break;
		}
		BLOK37->MFC1->Sint1_HMC830->SetFreq(Edit4->Text.ToDouble());
		BLOK37->LoadMFC1();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox6Change(TObject *Sender)
{
//				switch (ComboBox6->ItemIndex)
//		{
//		case 0:  	BLOK37->PRC->MKanal->NKanal[3].Pch1_Sw = 0;
//
//		break;
//		case 1:    BLOK37->PRC->MKanal->NKanal[3].Pch1_Sw = 1;
//		break;
//		default: BLOK37->PRC->MKanal->NKanal[3].Pch1_Sw =1;
//		break;
//		}
		BLOK37->PRC->MKanal->NKanal[2].Pch1_Sw = ComboBox6->ItemIndex;
		BLOK37->LoadBL3CR37();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox7Change(TObject *Sender)
{
		BLOK37->PRC->MKanal->PC2INSET(ComboBox7->ItemIndex);
		BLOK37->LoadBL3CR37();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox12Change(TObject *Sender)
{
				switch (ComboBox12->ItemIndex)     //Вход ПЧ2
		{
		case 0:  	BLOK37->PRC->MKanal->NKanal[2].Pch2_Sw = BLOK37->PRC->MKanal->NKanal[2].Pch2_Sw&0x1; 	break;
		case 1:    	BLOK37->PRC->MKanal->NKanal[2].Pch2_Sw = BLOK37->PRC->MKanal->NKanal[2].Pch2_Sw|0x2;  	break;
		default: 	BLOK37->PRC->MKanal->NKanal[2].Pch2_Sw = BLOK37->PRC->MKanal->NKanal[2].Pch2_Sw|0x2;  	break;
		}
	   //	BLOK37->PRC->MKanal->NKanal[3].Pch2_Sw = ComboBox7->ItemIndex;
		BLOK37->LoadBL3CR37();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{


		BLOK37->SENDLAN(StrToInt64("0x"+Edit5->Text)>>32,StrToInt64("0x"+Edit5->Text)&0xFFFFFFFF,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox13Change(TObject *Sender)
{
				switch (ComboBox13->ItemIndex)
	 {
		case 0:  BLOK37->PRC->BL_NumModul = 0xD<<28; break; //0-7 или D
		case 1:  BLOK37->PRC->BL_NumModul = 0x0<<28; break;
		case 2:  BLOK37->PRC->BL_NumModul = 0x1<<28; break;
		case 3:  BLOK37->PRC->BL_NumModul = 0x2<<28; break;
		case 4:  BLOK37->PRC->BL_NumModul = 0x3<<28; break;
		case 5:  BLOK37->PRC->BL_NumModul = 0x4<<28; break;
		case 6:  BLOK37->PRC->BL_NumModul = 0x5<<28; break;
		case 7:  BLOK37->PRC->BL_NumModul = 0x6<<28; break;
		case 8:  BLOK37->PRC->BL_NumModul = 0x7<<28; break;
		default: BLOK37->PRC->BL_NumModul = 0xD<<28; break;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox14Change(TObject *Sender)
{
			 switch (ComboBox14->ItemIndex)
	 {
		case 0:  BLOK37->MFC1->AdrMod = 0xE<<28; break; //0-7 или D
		case 1:  BLOK37->MFC1->AdrMod = 0xF<<28; break;
		default: BLOK37->MFC1->AdrMod = 0xF<<28; break;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvSpinEdit7Change(TObject *Sender)
{
	   BLOK37->MFC1->AdrMod = AdvSpinEdit7->HexValue<<28;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvSpinEdit8Change(TObject *Sender)
{
   BLOK37->PRC->BL_NumModul = AdvSpinEdit8->HexValue<<28;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CmB17Change(TObject *Sender)
{
	   FormSH->Stend->KOM34980->CommSetK16HF(CmB17->ItemIndex+1);
	   switch (CmB17->ItemIndex)
	   {
	  case 0: StringGrid5->Cells[0][1] = "K1.1";   break;
	  case 1: StringGrid5->Cells[0][1] = "K1.2";   break;
	  case 2: StringGrid5->Cells[0][1] = "K2.1";   break;
	  case 3: StringGrid5->Cells[0][1] = "K2.2";   break;
	  case 4: StringGrid5->Cells[0][1] = "K3.1";   break;
	  case 5: StringGrid5->Cells[0][1] = "K3.2";   break;
	  case 6: StringGrid5->Cells[0][1] = "K4.1";   break;
	  case 7: StringGrid5->Cells[0][1] = "K4.2";   break;
	  case 8: StringGrid5->Cells[0][1] = "K5.1";   break;
	  case 9: StringGrid5->Cells[0][1] = "K5.2";   break;
	  case 10: StringGrid5->Cells[0][1] = "K6.1";   break;
	  case 11: StringGrid5->Cells[0][1] = "K6.2";   break;
	  case 12: StringGrid5->Cells[0][1] = "K7.1";   break;
	  case 13: StringGrid5->Cells[0][1] = "K7.2";   break;
	  case 14: StringGrid5->Cells[0][1] = "K8.1";   break;
	  case 15: StringGrid5->Cells[0][1] = "K8.2";   break;

	   default:    break;
	   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
	 BLOK37->MFC1->BFCHP->SETFINE(AdvSpinEdit1->Value);
     BLOK37->MFC1->BFCHP->SETAUTO(CheckBox3->Checked,CheckBox4->Checked);
	 BLOK37->MFC1->BFCHP->PLMX2594->VCO_CAPCTRL(AdvSpinEdit6->Value);
	 RichEdit2->Clear();
	 RichEdit2->Lines->Add("Fl=" + FloatToStr(BLOK37->MFC1->SetFreq(AdvSpinEdit9->FloatValue,Edit2->Text.ToDouble(),0,0)));
	 BLOK37->FriqSET(0,0,AdvSpinEdit9->FloatValue,1,0,0,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvSpinEdit9Change(TObject *Sender)
{
	RichEdit2->Clear();
   //	BLOK37->MFC1->BFCHP->SETFINE(AdvSpinEdit1->Value);
	RichEdit2->Lines->Add("F830=" + FloatToStr(BLOK37->MFC1->SetFreq(AdvSpinEdit9->FloatValue,Edit2->Text.ToDouble(),0,0)));

	RichEdit2->Lines->Add(BLOK37->MFC1->NumDapazon);
	RichEdit2->Lines->Add("Fo=" + FloatToStr(BLOK37->MFC1->PLAN[BLOK37->MFC1->NumDapazon].F));
	RichEdit2->Lines->Add("Fl=" + FloatToStr(BLOK37->MFC1->PLAN[BLOK37->MFC1->NumDapazon].FVCO));
	RichEdit2->Lines->Add("Fp=" + FloatToStr(BLOK37->MFC1->PLAN[BLOK37->MFC1->NumDapazon+1].FVCO));
	RichEdit2->Lines->Add("M=" + IntToStr(BLOK37->MFC1->DEVFC1R[1].S15p));
	RichEdit2->Lines->Add("K=" + IntToStr(BLOK37->MFC1->DEVFC1R[1].PDP));
	RichEdit2->Lines->Add("OUT=" + IntToStr(BLOK37->MFC1->PLAN[BLOK37->MFC1->NumDapazon].OUTM));
	RichEdit2->Lines->Add("N=" + IntToStr(BLOK37->MFC1->PLAN[BLOK37->MFC1->NumDapazon].N));
	RichEdit2->Lines->Add("CAP1=" + IntToStr(BLOK37->MFC1->PLAN[BLOK37->MFC1->NumDapazon].CAP));
	RichEdit2->Lines->Add("CAP_M=" + IntToStr(BLOK37->MFC1->BFCHP->PLMX2594->VCO_CAPCTRL_ST));
	RichEdit2->Lines->Add("VCO=" + IntToStr(BLOK37->MFC1->PLAN[BLOK37->MFC1->NumDapazon].VCO));
	RichEdit2->Lines->Add("VCO_M=" + IntToStr(BLOK37->MFC1->BFCHP->PLMX2594->VCOSEL));
	RichEdit2->Lines->Add("N394=" + IntToStr(BLOK37->MFC1->DEVFC1R[1].F394));
	RichEdit2->Lines->Add("UMX20=" + IntToStr(BLOK37->MFC1->DEVFC1R[1].S20p));
	RichEdit2->Lines->Add("RSV=" + IntToStr(BLOK37->MFC1->DEVFC1R[1].RSV));

	//BLOK37->MFC1->DEVFC1R[1].S20p;
	//BLOK37->MFC1->DEVFC1R[1].RSV;
	//BLOK37->FriqSET(0,0,AdvSpinEdit9->FloatValue,1,0,0,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvSpinEdit1Change(TObject *Sender)
{
	   BLOK37->MFC1->BFCHP->SETFINE(AdvSpinEdit1->Value);
       BLOK37->MFC2->BFCHP->SETFINE(AdvSpinEdit1->Value);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit12KeyPress(TObject *Sender, System::WideChar &Key)
{
	//TODO: НомерБЛОКА-Пртокола @INI (Unit1.cpp)
	FormSNSW->ShowModal();
	//MemINI->PAthSet(ExtractFileDir(ParamStr(0)) + "\\RPU16.ini");
	//FormSH->MemINI->WriteDouble("Blok","Зав№", StrToFloat(Edit12->Text));
	FormSH->MemINI->WriteDouble("Priemka","Tipe", ComboBox10->ItemIndex);
	RelBlokRRINI(ComboBox10->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1DblClick(TObject *Sender)
{
//   if (!BlokSNchek())
//	{
//	  if(mrNo==MessageDlg("Зав. номера разные. Продолжить?", mtInformation,
//			TMsgDlgButtons() << mbNo << mbYes, 0))
//			{	 //ShowMessage("Зав. номера разные");
//			 return;
//			}
//	}

//	   if (Stend->ChekCon(1500,i)) {
//				   ShowMessage("USB кабель не подключен");
//				  // return;
//			   }

		 //FUNC: DBL (0)
					switch(j)
   {
	 case 1:
  // StringGrid1->Cells[i][j] = Stend->GeinAnGen(30,0,0,i,Stend->TCom)+Stend->CTbl[2];
	 StringGrid1->Cells[i][j] = FormSH->Stend->GeinAnGen(30.0,255.0,0,0,FormSH->Stend->TCom,i,1)+FormSH->Stend->CTbl[0];
	 Application->ProcessMessages();
	 param = "Kp" +  IntToStr(i) + "30";
	 break;
	 case 2:
 //	 StringGrid1->Cells[i][j] = Stend->GeinAnGen(1000,0,0,i,Stend->TCom)+Stend->CTbl[2];
	 StringGrid1->Cells[i][j] = FormSH->Stend->GeinAnGen(1000.0,255.0,0,0,FormSH->Stend->TCom,i,1)+FormSH->Stend->CTbl[1];
	 Application->ProcessMessages();
	 param = "Kp" +  IntToStr(i) + "1000";
	 break;
	 case 3:
 //	 StringGrid1->Cells[i][j] = Stend->GeinAnGen(2000,0,0,i,Stend->TCom)+Stend->CTbl[2];
	 StringGrid1->Cells[i][j] = FormSH->Stend->GeinAnGen(1750.0,255.0,0,0,FormSH->Stend->TCom,i,1)+FormSH->Stend->CTbl[2];
	 Application->ProcessMessages();
	 param = "Kp" +  IntToStr(i) + "1750";
	 break;
	 case 4:
//	 StringGrid1->Cells[i][j] = Stend->GeinAnGen(3000,0,0,i,Stend->TCom)+Stend->CTbl[2];
	 StringGrid1->Cells[i][j] = FormSH->Stend->GeinAnGen(2200.0,255.0,0,0,FormSH->Stend->TCom,i,1)+FormSH->Stend->CTbl[3];
	 Application->ProcessMessages();
	 param = "Kp" +  IntToStr(i) + "2200";
	 break;

   }

	FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl1",param.c_str(),StringGrid1->Cells[i][j].ToDouble());
	Kpdelta(StringGrid1,j);
	param = "KpDEL" + IntToStr(j);
	FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl1",param.c_str(),StringGrid1->Cells[17][j].ToDouble());

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	//FUNC: IJ @MEAS (0)
		i = ACol;
		j = ARow;
				if (i==0|i==17)
		{
			i = 1;
		}
				if (j==0)
		{
			j = 1;
		}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid5SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
		i = ACol;
		j = ARow;
				if (i==0|i==6)
		{
			i = 1;
		}
				if (j==0)
		{
			j = 1;
		}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button20Click(TObject *Sender)
{
		BLOK37->LoadMFC11(AdvSpinEdit9->FloatValue,AdvSpinEdit7->HexValue);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button21Click(TObject *Sender)
{
	BLOK37->LoadMFC2(AdvSpinEdit9->FloatValue,AdvSpinEdit7->HexValue);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
		//FUNC: MEASAUTO @MEAS (1)
		//NOTE: SET T1 @INI (0)
		Zatvor=0;
	/* if (!BlokSNchek())
	{
		  if(mrNo==MessageDlg("Зав. номера разные. Продолжить?", mtInformation,
				TMsgDlgButtons() << mbNo << mbYes, 0))
				{	 //ShowMessage("Зав. номера разные");
				 return;
				}
	}*/

	 for (osob = 1; osob < 17; osob++)
	{        if (Zatvor)
				{
				 Zatvor=0;
				 return;
				}
						/*if (Stend->TCom==0)
			{
				 if (Stend->ChekCon(1000,osob))
				 {
					ShowMessage("Подключить кабели к каналу " + IntToStr(osob));
						// return;
				 }
			}*/
			SelectedRect.Left=osob; //Левая граница
			SelectedRect.Top=1; //Верхняя граница
			SelectedRect.Right=osob; //Правая граница
			SelectedRect.Bottom=1; //Нижняя граница
			StringGrid1->Selection = SelectedRect;
			StringGrid1->Cells[osob][1] =  FormSH->Stend->GeinAnGen(30.0,255.0,0,0,FormSH->Stend->TCom,osob,1)+FormSH->Stend->CTbl[0];
			param = "Kp" +  IntToStr(osob) + "30";
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl1",param.c_str(),StringGrid1->Cells[osob][1].ToDouble());
			Application->ProcessMessages();

			SelectedRect.Left=osob; //Левая граница
			SelectedRect.Top=2; //Верхняя граница
			SelectedRect.Right=osob; //Правая граница
			SelectedRect.Bottom=2; //Нижняя граница
			StringGrid1->Selection = SelectedRect;
			StringGrid1->Cells[osob][2] =  FormSH->Stend->GeinAnGen(1000.0,255.0,0,0,FormSH->Stend->TCom,osob,1)+FormSH->Stend->CTbl[1];
			param = "Kp" +  IntToStr(osob) + "1000";
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl1",param.c_str(),StringGrid1->Cells[osob][2].ToDouble());
			Application->ProcessMessages();

			SelectedRect.Left=osob; //Левая граница
			SelectedRect.Top=3; //Верхняя граница
			SelectedRect.Right=osob; //Правая граница
			SelectedRect.Bottom=3; //Нижняя граница
			StringGrid1->Selection = SelectedRect;
			StringGrid1->Cells[osob][3] = FormSH->Stend->GeinAnGen(1750.0,255.0,0,0,FormSH->Stend->TCom,osob,1)+FormSH->Stend->CTbl[2];
			param = "Kp" +  IntToStr(osob) + "1750";
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl1",param.c_str(),StringGrid1->Cells[osob][3].ToDouble());
			Application->ProcessMessages();

			SelectedRect.Left=osob; //Левая граница
			SelectedRect.Top=3; //Верхняя граница
			SelectedRect.Right=osob; //Правая граница
			SelectedRect.Bottom=3; //Нижняя граница
			StringGrid1->Selection = SelectedRect;
			StringGrid1->Cells[osob][4] =  FormSH->Stend->GeinAnGen(2200.0,255.0,0,0,FormSH->Stend->TCom,osob,1)+FormSH->Stend->CTbl[3];
			param = "Kp" +  IntToStr(osob) + "2200";
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl1",param.c_str(),StringGrid1->Cells[osob][3].ToDouble());
			Application->ProcessMessages();
	}
	  i=1;
	  		for (int i = 1; i < 5; ++i)
	  {
		Kpdelta(StringGrid1, i);
		// Kpdelta(StringGrid7, i);
		param = "KpDEL" + IntToStr(i) ;
		FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl1",param.c_str(),StringGrid1->Cells[17][i].ToDouble());
	  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid5DblClick(TObject *Sender)
{    //Func: IP1 @MEAS (0)
	 CmB17Change(Sender);
					switch (i)
	{
			case 1:
			param = "Sens30";
			StringGrid5->Cells[i][1] =  FormSH->Stend->Sens(-70,-10,30,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[0];
			break;
			case 2:
			param = "Sens1000";
			StringGrid5->Cells[i][1] =  FormSH->Stend->Sens(-70,-10,1000,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[1];
			break;
			case 3:
			param = "Sens1750";
			StringGrid5->Cells[i][1] =  FormSH->Stend->Sens(-70,-10,1750,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[2];
			break;
			case 4:
			param = "Sens2200";
			StringGrid5->Cells[i][1] =  FormSH->Stend->Sens(-70,-10,2200,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[3];
			break;
			case 5:
			param = "IP1";
			StringGrid5->Cells[i][1] =  FormSH->Stend->SIP1(-27,25,1000,255,CmB17->ItemIndex+1);
			break;
	}

/*   				   switch (i)
	{
		case 1:
		param = "K1" + param;
		break;
		case 2:
		param = "K2" + param;
		break;
		case 3:
		param = "K2" + param;
		break;
		case 4:
		param = "K2" + param;
		break;
		case 5:
		param = "K2" + param;
		break;
	}
*/

	 	FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl3",param.c_str(),StringGrid5->Cells[i][1].ToDouble());

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button17Click(TObject *Sender)
{     //FUNC: MEASAUTO0 @MEAS (1)
//NOTE: SET T4 @INI (4)
	MEASPROGON(1, StringGrid2,4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{    //FUNC: MEASAUTO8 @MEAS (1)
	MEASPROGON(2, StringGrid2,4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{     //FUNC: MEASAUTO88 @MEAS (1)
	MEASPROGON(1, StringGrid3,5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{    //FUNC: MEASAUTO16 @MEAS (1)
	MEASPROGON(2, StringGrid3,5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{    //FUNC: MEASAUTO1616 @MEAS (1)
	MEASPROGON(1, StringGrid4,6);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{   //FUNC: MEASAUTO24 @MEAS (1)
	MEASPROGON(2, StringGrid4,6);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button22Click(TObject *Sender)
{  //FUNC: MEASAUTOIP @MEAS (1)
//NOTE: SET T3 @INI (3)
			 CmB17Change(Sender);
			param = "Sens30";
			StringGrid5->Cells[1][1] =  FormSH->Stend->Sens(-70,-10,30,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[0];
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl3",param.c_str(),StringGrid5->Cells[1][1].ToDouble());
			Application->ProcessMessages();
			param = "Sens1000";
			StringGrid5->Cells[2][1] =  FormSH->Stend->Sens(-70,-10,1000,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[1];
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl3",param.c_str(),StringGrid5->Cells[2][1].ToDouble());
			Application->ProcessMessages();
			param = "Sens1750";
			StringGrid5->Cells[3][1] =  FormSH->Stend->Sens(-70,-10,1750,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[2];
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl3",param.c_str(),StringGrid5->Cells[3][1].ToDouble());
			Application->ProcessMessages();
			param = "Sens2200";
			StringGrid5->Cells[4][1] =  FormSH->Stend->Sens(-70,-10,2200,255,CmB17->ItemIndex+1)-FormSH->Stend->CTbl[3];
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl3",param.c_str(),StringGrid5->Cells[4][1].ToDouble());
			Application->ProcessMessages();
			param = "IP1";
			StringGrid5->Cells[5][1] =  FormSH->Stend->SIP1(-27,25,1000,255,CmB17->ItemIndex+1);
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl3",param.c_str(),StringGrid5->Cells[5][1].ToDouble());
			Application->ProcessMessages();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button23Click(TObject *Sender)
{  // FUNC : M1750
			Zatvor=0;
	/* if (!BlokSNchek())
	{
		  if(mrNo==MessageDlg("Зав. номера разные. Продолжить?", mtInformation,
				TMsgDlgButtons() << mbNo << mbYes, 0))
				{	 //ShowMessage("Зав. номера разные");
				 return;
				}
	}*/

	 for (osob = 1; osob < 17; osob++)
	{        if (Zatvor)
				{
				 Zatvor=0;
				 return;
				}
						/*if (Stend->TCom==0)
			{
				 if (Stend->ChekCon(1000,osob))
				 {
					ShowMessage("Подключить кабели к каналу " + IntToStr(osob));
						// return;
				 }
			}*/        //NOTE: SET T2 @INI (2)
			SelectedRect.Left=osob; //Левая граница
			SelectedRect.Top=1; //Верхняя граница
			SelectedRect.Right=osob; //Правая граница
			SelectedRect.Bottom=1; //Нижняя граница
			StringGrid6->Selection = SelectedRect;
			StringGrid6->Cells[osob][1] =  FormSH->Stend->GeinAnGen(1750.0,255.0,0,0,FormSH->Stend->TCom,osob,0)+FormSH->Stend->CTbl[2];
			param = "Kp" +  IntToStr(osob) + "_1750";
			FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl2",param.c_str(),StringGrid6->Cells[osob][1].ToDouble());
			Application->ProcessMessages();
	}
		//Kpdelta(StringGrid6, 1);
		//param = "KpDEL1" ;
		//FormSH->MemINI->TWriteDouble(ComboBox4->ItemIndex,"Tabl2",param.c_str(),StringGrid6->Cells[17][1].ToDouble());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid6DblClick(TObject *Sender)
{
		StringGrid6->Cells[i][1] =  /*11;*/FormSH->Stend->GeinAnGen(1750.0,255.0,0,0,FormSH->Stend->TCom,i,0)+FormSH->Stend->CTbl[2];
		param = "Kp" +  IntToStr(i) + "_1750";
		FormSH->MemINI->TWriteDouble(ComboBox10->ItemIndex,"Tabl2",param.c_str(),StringGrid6->Cells[i][1].ToDouble());
		Application->ProcessMessages();

		//Kpdelta(StringGrid6, 1);
		//Kpdelta(StringGrid7, i);
		//param = "KpDEL1" ;
		//FormSH->MemINI->TWriteDouble(ComboBox4->ItemIndex,"Tabl2",param.c_str(),StringGrid6->Cells[17][1].ToDouble());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid6SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
		//FUNC: IJ @MEAS (2)
		i = ACol;
		j = ARow;
				if (i==0|i==17)
		{
			i = 1;
		}
				if (j==0)
		{
			j = 1;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvPageControl1Change(TObject *Sender)
{
			 switch (AdvPageControl1->ActivePageIndex)
	{   	/* case 1:
			   ComboBox15Change(Sender);
			 break;
			 case 2:
			   ComboBox_JGMFC2Change(Sender);
			 break;

			*/
			 case 2:
		  /*	switch (ComboBox12->ItemIndex)
			{
				  case 6:
				  ADR = 0XD;
				 switch (osob)
				 {
					  case 1: Kanal =  20;  break;
					  case 2: Kanal =  21;  break;
				 }
				 break;

				  default :  Kanal = ComboBox12->ItemIndex*2 + osob;ADR = ComboBox12->ItemIndex;break;
			}
			 Stend->VstendeBL3VK1->FriqSET(40,false,0,0,Kanal);    // дел на 0   FriqSET(double Fin1,bool Ampl,int DB1,int DB2,int Kanal)
			 */

			/*-------------------------------------------------------------------------------------
			 MemINI->MPAthSet("BL3VK1.ini"); //= new OPTIONS_BASE("BL3VK1.ini");


			 ComboBox13->ItemIndex = MemINI->ReadDouble("Protokol","ProtokolIt",0);
			 ComboBox14->ItemIndex = MemINI->ReadDouble("Protokol","Mod3VK6It",0);

			 Protokol = "Protokol"+ IntToStr(ComboBox13->ItemIndex);
			 Modul = "Modul"+ IntToStr(ComboBox14->ItemIndex);
			 PathINI = MemINI->TReadString(0,Protokol.c_str(),Modul.c_str(), "" );  //  ExtractFileDir(ParamStr(0)) + "\\RPU16_.ini"


				   if (PathINI=="")
			{
			 MemINI->TWriteString(0,Protokol.c_str(),Modul.c_str(), ExtractFileDir(ParamStr(0)) + "\\MOD3VK6_.ini");
			 MemINI->WriteDouble("Protokol","ProtokolIt",ComboBox13->ItemIndex);
			 MemINI->WriteDouble("Protokol","Mod3VK6It",ComboBox14->ItemIndex);

			}
			 PathINI = MemINI->TReadString(0,Protokol.c_str(),Modul.c_str(), "" );
			 MemINI->PAthSet(PathINI);
			 MemINI->WriteDouble("Priemka","Tipe", ComboBox11->ItemIndex);
			//MemINI->WriteDouble("Osnastka","Tipe", ComboBox12->ItemIndex);

			 Rel3VK6INI();

              ------------------------------------------------------------------------------*/
			 break;
			/* case 4:       //FUNC 3Вк1PageContr @INI (0)
			 // ADR = 0;
			 Stend->VstendeBL3VK1->blTupe = 0;
			 Stend->jgut = false;
			 Stend->VstendeBL3VK1->ModulFCH1->AdrSet(0);
			 Stend->VstendeBL3VK1->ModulFCH2->AdrSet(0);
			 MemINI->MPAthSet("BL3VK1.ini"); //= new OPTIONS_BASE("BL3VK1.ini");
			 PathINI = MemINI->TReadString(0,"Blok","Path", "" );  //  ExtractFileDir(ParamStr(0)) + "\\RPU16_.ini"
				   if (PathINI=="")
			 {
				MemINI->TWriteString(0,"Blok","Path", ExtractFileDir(ParamStr(0)) + "\\BL3VK1_.ini");
			 }
			 PathINI = MemINI->TReadString(0,"Blok","Path", "" );
			 MemINI->PAthSet(PathINI); // ComboBox1->ItemIndex = MemINI->ReadDouble("Priemka","Tipe",0);
			 Form1->StatusBar1->Panels->Items[0]->Text = "3Вк1 " + IntToStr((int)Stend->VstendeBL3VK1->ReadBlokSN());
			 RelBlok3Vk1INI(ComboBox4->ItemIndex);
			 break;

			 case 5:

			 Modul = "\\MFC1_";
			 CuMod = "CuModFC1";
			 MemINI->MPAthSet("BL3VK1.ini"); //= new OPTIONS_BASE("BL3VK1.ini");
			 PathINI = MemINI->TReadString(0,"CuModFC1","Path", "" );  //  ExtractFileDir(ParamStr(0)) + "\\RPU16_.ini"
				   if (PathINI=="")
			  {
				 MemINI->TWriteString(0,"CuModFC1","Path", ExtractFileDir(ParamStr(0)) + "\\MFC1_.ini");
				 PathINI = MemINI->TReadString(0,"CuModFC1","Path", "" );
				 MemINI->PAthSet(PathINI);
				 MemINI->WriteDouble("Priemka","Tipe", ComboBox10->ItemIndex);
				 MemINI->WriteDouble("Osnastka","Tipe", ComboBox9->ItemIndex);
			  }
			 PathINI = MemINI->TReadString(0,"CuModFC1","Path", "" );
			 MemINI->PAthSet(PathINI); // ComboBox1->ItemIndex = MemINI->ReadDouble("Priemka","Tipe",0);
			 //ComboBox10->ItemIndex = MemINI->ReadDouble("Priemka","Tipe",0);
			 RelMFC1INI();
				 switch (ComboBox9->ItemIndex)
				{
				 case 0:
				 ADR = 0XD;
				 break;
				 case 1:
				 ADR = 0XE;
				 break;
				}
			 Form1->StatusBar1->Panels->Items[0]->Text = "МФЧ1 "+ IntToStr(Stend->VstendeBL3VK1->ReadSN_Ver(ADR));
			 break;

			 case 6:
			 SpeedButton1->Down = false;
			 SpeedButton1Click(Sender);
			 Modul = "\\MFC2_";
			 CuMod = "CuModFC2";
			 MemINI->MPAthSet("BL3VK1.ini"); //= new OPTIONS_BASE("BL3VK1.ini");
			 PathINI = MemINI->TReadString(0,"CuModFC2","Path", "" );  //  ExtractFileDir(ParamStr(0)) + "\\RPU16_.ini"
				   if (PathINI=="")
			  {
				 MemINI->TWriteString(0,"CuModFC2","Path", ExtractFileDir(ParamStr(0)) + "\\MFC2_.ini");
				 PathINI = MemINI->TReadString(0,"CuModFC2","Path", "" );
				 MemINI->PAthSet(PathINI);
				 MemINI->WriteDouble("Priemka","Tipe", ComboBox8->ItemIndex);
				 MemINI->WriteDouble("Osnastka","Tipe", ComboBox5->ItemIndex);
			  }
			 PathINI = MemINI->TReadString(0,"CuModFC2","Path", "" );
			 MemINI->PAthSet(PathINI); // ComboBox1->ItemIndex = MemINI->ReadDouble("Priemka","Tipe",0);
			 ComboBox8->ItemIndex = MemINI->ReadDouble("Priemka","Tipe",0);
			 RelMFC2INI(ComboBox8->ItemIndex);
				 switch (ComboBox5->ItemIndex)
				{
				 case 0:
				 ADR = 0XD;
				 break;
				 case 1:
				 ADR = 0XF;
				 break;
				}
			 Form1->StatusBar1->Panels->Items[0]->Text = "МФЧ2 "+ IntToStr(Stend->VstendeBL3VK1->ReadSN_Ver(ADR));
			 break;

			 case 7:    //3Вк11PageContr
			 Stend->VstendeBL3VK1->blTupe = 1;
			 Stend->jgut = false;
             MemINI->MPAthSet("BL3VK1.ini"); //= new OPTIONS_BASE("BL3VK1.ini");
			 PathINI = MemINI->TReadString(0,"Blok11","Path", "" );  //  ExtractFileDir(ParamStr(0)) + "\\RPU16_.ini"
				   if (PathINI=="")
			 {
				MemINI->TWriteString(0,"Blok11","Path", ExtractFileDir(ParamStr(0)) + "\\BL3VK11_.ini");
			 }
			 PathINI = MemINI->TReadString(0,"Blok11","Path", "" );
			 MemINI->PAthSet(PathINI); // ComboBox1->ItemIndex = MemINI->ReadDouble("Priemka","Tipe",0);
			 Form1->StatusBar1->Panels->Items[0]->Text = "3Вк11 " + IntToStr((int)Stend->VstendeBL3VK1->ReadBlokSN());
			 RelBlok3Vk11INI(ComboBox20->ItemIndex);
			 break;
			  default : break; */
		}
		 i=1;
		 j=1;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
          OpenDialog1->FilterIndex = 1;
//
//
		if (!OpenDialog1->Execute()) return;
//
		   FormSH->DEFPath();
		   FormSH->MemINI->TWriteString(0,"Blok","Path", OpenDialog1->FileName);
		   FormSH->MemINI->PAthSet(OpenDialog1->FileName);
		   ComboBox10->ItemIndex = FormSH->MemINI->ReadDouble("Priemka","Tipe",0);
//
//
	i=1;
	j=1;
//
 RelBlokRRINI(ComboBox10->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox10Change(TObject *Sender)
{
	FormSH->MemINI->WriteDouble("Priemka","Tipe",ComboBox10->ItemIndex);
	RelBlokRRINI(ComboBox10->ItemIndex);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn1Click(TObject *Sender)
{
       Zatvor=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{   //StBlock->SetFreq(FrGen,0,ATT1,ATT2,ATT2,Kanal,63,PARAM);
	switch (j)
	{
	case 1:  BLOK37->SetFreq(30,0,0,0,0,i,63,1);
	break;
	case 2:  BLOK37->SetFreq(1000,0,0,0,0,i,63,1);
	break;
	case 3:  BLOK37->SetFreq(1750,0,0,0,0,i,63,1);
	break;
	case 4:  BLOK37->SetFreq(2200,0,0,0,0,i,63,1);
	break;
	default: BLOK37->SetFreq(1000,0,0,0,0,i,63,1);   break;
	}

}
//---------------------------------------------------------------------------

