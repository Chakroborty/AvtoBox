//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "DiapazonSearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma link "AdvPageControl"
#pragma link "AdvUtil"
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
   //	Massive = new BinSH();
	advstrngrd1->Cells[0][0] = "F";
	advstrngrd1->Cells[1][0] = "M";
	advstrngrd1->Cells[2][0] = "K";
	advstrngrd1->Cells[3][0] = "OUT";
	advstrngrd1->Cells[4][0] = "N";
	advstrngrd1->Cells[5][0] = "OUT2";
	advstrngrd1->Cells[6][0] = "CAP1";
	advstrngrd1->Cells[7][0] = "CAP2";
	advstrngrd1->Cells[8][0] = "CAP3";

	AdvStringGrid1->Cells[0][0] = "DFv";
	AdvStringGrid1->Cells[1][0] = "DK1";
	AdvStringGrid1->Cells[2][0] = "DK2";
	AdvStringGrid1->Cells[3][0] = "DK12P";
	AdvStringGrid1->Cells[4][0] = "DK3";
	AdvStringGrid1->Cells[5][0] = "DK3P";
	AdvStringGrid1->Cells[6][0] = "DK4";
	AdvStringGrid1->Cells[7][0] = "DK4P";
	AdvStringGrid1->Cells[8][0] = "Dndel";
	AdvStringGrid1->Cells[9][0] = "DN18";
	AdvStringGrid1->Cells[10][0] = "DN45";




}
//---------------------------------------------------------------------------
void __fastcall TForm4::btn1Click(TObject *Sender)
{      /*Открыть xls*/
 if (!dlgOpen1->Execute()) return;
					switch(AdvPageControl1->ActivePageIndex)
   {
	case 0:
		advstrngrd1->LoadFromXLSSheet(dlgOpen1->FileName,"Лист1");
	break;
	case 1:
		AdvStringGrid1->LoadFromXLSSheet(dlgOpen1->FileName,"Лист4");
	break;
	case 3:  break;
	case 4:  break;
	case 5:  break;
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{
					 if(!dlgSave1->Execute())
		 {
					return;
		 }
//		 else
//		 {
//			FILE *pfile ;
//			Path = dlgSave1->FileName;
//			pfile = fopen(Path.c_str(), "w+b");
//			fwrite(&Polosa, sizeof(Polosa), 1, pfile);
//
//			fclose(pfile);
//
//		 }
			   /*Создать bin*/
			 FILE *pfile ;
					switch(AdvPageControl1->ActivePageIndex)
   {
		case 0:

			Path = dlgSave1->FileName;
			pfile = fopen(Path.c_str(), "w+b");
			fwrite(&Polosa, sizeof(Polosa), 1, pfile);

			fclose(pfile);
		break;
		case 1:

			Path = dlgSave1->FileName;
			pfile = fopen(Path.c_str(), "w+b");
			fwrite(&Form1->BLOK37->MFC1->Polosa830, sizeof(Form1->BLOK37->MFC1->Polosa830), 1, pfile);
			fclose(pfile);

		break;
		case 3:  break;
		case 4:  break;
		case 5:  break;
   }



}
//---------------------------------------------------------------------------


void __fastcall TForm4::Button1Click(TObject *Sender)
{
				   /*Открыть bin*/

//					Path = ExtractFilePath(Application->ExeName);
//					Path = Path +"MFC1.bin";
//					FILE *pfile ;
//					pfile = fopen(Path.c_str(), "r+b");
//					fread(&Polosa, sizeof(Polosa), 1, pfile);

					switch(AdvPageControl1->ActivePageIndex)
   {
		case 0:
				if(!dlgOpen1->Execute())
				 {
							return;
				 }
				 else
				 {
					FILE *pfile ;
					Path = dlgOpen1->FileName;
					pfile = fopen(Path.c_str(), "r+b");
					fread(&Polosa, sizeof(Polosa), 1, pfile);
				 }


					  for (i = 0; i < 269; i++)
			 {

				advstrngrd1->Cells[0][i+1] = Polosa[i].DFv;
				advstrngrd1->Cells[1][i+1] = Polosa[i].DM;
				advstrngrd1->Cells[2][i+1] = Polosa[i].K;
				advstrngrd1->Cells[3][i+1] = Polosa[i].MOUT;
				advstrngrd1->Cells[4][i+1] = Polosa[i].DN;
				advstrngrd1->Cells[5][i+1] = Polosa[i].CAP1;
				advstrngrd1->Cells[6][i+1] = Polosa[i].VCO;
			 }
												break;

		case 1:
				if(!dlgOpen1->Execute())
				 {
							return;
				 }
				 else
				 {
					FILE *pfile ;
					Path = dlgOpen1->FileName;
					pfile = fopen(Path.c_str(), "r+b");
					fread(&Form1->BLOK37->MFC1->Polosa830, sizeof(Form1->BLOK37->MFC1->Polosa830), 1, pfile);
				 }


					  for (i = 0; i < 32; i++)
			 {

				// AdvStringGrid1->Cells[0][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DFv;
				// AdvStringGrid1->Cells[1][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK1;
				// AdvStringGrid1->Cells[2][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK2;
				// AdvStringGrid1->Cells[3][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK12P;//  ADF4002_2  посл
				// AdvStringGrid1->Cells[4][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK3;
				// AdvStringGrid1->Cells[5][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK3P;//  ADF4002_1  внутр
				// AdvStringGrid1->Cells[6][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK4;
				// AdvStringGrid1->Cells[7][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK4P;
				// AdvStringGrid1->Cells[8][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].Dndel;
				// AdvStringGrid1->Cells[9][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DN18;
				// AdvStringGrid1->Cells[10][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DN45;
			   //	AdvStringGrid1->Cells[10][i+1] = Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].Cur;

			 }
												break;
		case 3:  break;
		case 4:  break;
		case 5:  break;
   }



//					sBlack TempBlack;
//		if((fp=fopen("d.bin", "rb"))==NULL)
//		{
//			//file not open
//		}
//		else
//		{
//			fread(&TempBlack, sizeof(TempBlack), 1, fp);
//		}
//		fclose(fp);

}
//---------------------------------------------------------------------------

void __fastcall TForm4::btn2Click(TObject *Sender)
{
					switch(AdvPageControl1->ActivePageIndex)
   {
		case 0:
						  for (i = 0; i < 267; i++)
			{
			   if(!advstrngrd1->Cells[0][i+1].IsEmpty())
				   {
					  Polosa[i].DFv =   advstrngrd1->Cells[0][i+1].ToDouble();
					  Polosa[i].DM =  advstrngrd1->Cells[1][i+1].ToInt();
					  Polosa[i].K = advstrngrd1->Cells[2][i+1].ToInt();
					  Polosa[i].MOUT = advstrngrd1->Cells[3][i+1].ToInt();
					  Polosa[i].DN = advstrngrd1->Cells[4][i+1].ToInt();
					  Polosa[i].CAP1 = advstrngrd1->Cells[5][i+1].ToInt();
					  Polosa[i].VCO = advstrngrd1->Cells[6][i+1].ToInt();
					//  Polosa[i].DFS = advstrngrd1->Cells[7][i+1].ToDouble();//
				   }
//					Polosa[i].DFv = Point.DFv;
//					Polosa[i].DM = Point.DM;
//					Polosa[i].K = Point.K;
//					Polosa[i].MOUT = Point.MOUT;
//					Polosa[i].DN = Point.DN;
//					Polosa[i].MOUT2 = Point.MOUT2;
//					Polosa[i].CAP1 = Point.CAP1;
//					Polosa[i].CAP2 = Point.CAP2;
//					Polosa[i].CAP3 = Point.CAP3;
			}
		break;
		case 1:
						  for (i = 0; i < 32; i++)
			{
			   if(!AdvStringGrid1->Cells[0][i+1].IsEmpty())
				   {                            /*МФЧГ массив заполнить*/
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DFv =   AdvStringGrid1->Cells[0][i+1].ToDouble();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK1 =  AdvStringGrid1->Cells[1][i+1].ToInt();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK2 = AdvStringGrid1->Cells[2][i+1].ToInt();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK12P = AdvStringGrid1->Cells[3][i+1].ToInt(); //ADF4002_2  5 Последняя
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK3 = AdvStringGrid1->Cells[4][i+1].ToInt();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK3P = AdvStringGrid1->Cells[5][i+1].ToInt();  //ADF4002_1 2 Внутр
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK4 = AdvStringGrid1->Cells[6][i+1].ToInt();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DK4P = AdvStringGrid1->Cells[7][i+1].ToInt();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].Dndel = AdvStringGrid1->Cells[8][i+1].ToInt();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DN18 = AdvStringGrid1->Cells[9][i+1].ToInt();
						// Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].DN45 = AdvStringGrid1->Cells[10][i+1].ToInt();
						// //Form1->Stend->VstendeBL3DG1->ModulFCHG->PolosaFCG[i].Cur = AdvStringGrid1->Cells[10][i+1].ToInt();
				   }

			}


		break;
		case 3:  break;
		case 4:  break;
		case 5:  break;
	}
	 /* TODO: Создать файл МФЧ1 (1) */
//		 if(!dlgSave1->Execute())
//		 {
//					return;
//		 }
//		Path = dlgSave1->FileName;
//		ofstream strm(Path.c_str());
//		for(i=0; i< 267; i++)
//		{
//		  itoa(i,buffer,10);
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].F = "+Polosa[i].DFS+(AnsiString)"; ";
//		  strm << Pint.c_str();
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].FVCO = "+Polosa[i].DFv+(AnsiString)"; ";
//		  strm << Pint.c_str();
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].M = "+Polosa[i].DM +(AnsiString)"; ";
//		  strm << Pint.c_str();
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].K = "+Polosa[i].K+(AnsiString)"; ";
//		  strm << Pint.c_str();
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].OUTM = "+Polosa[i].MOUT +(AnsiString)"; ";
//		  strm << Pint.c_str();
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].N = "+Polosa[i].DN+(AnsiString)"; ";
//		  strm << Pint.c_str();
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].CAP = "+Polosa[i].CAP1+(AnsiString)"; ";
//		  strm << Pint.c_str();
//		  Pint = (AnsiString)"PLAN[" + buffer + (AnsiString)"].VCO = "+Polosa[i].VCO+(AnsiString)";";
//		  strm << Pint.c_str() << '\n';
//		}

          Delta =  Delta;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::edt1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{

			 if(Key==13)
 {
	advstrngrd1->TopRow = binary_search(edt1->Text.ToDouble(),0,511)+1;//установить строку i вверху окна
	edt2->Text = Polosa[advstrngrd1->TopRow-1].DFv;
 }
 else
 {


 }
}
//---------------------------------------------------------------------------
int TForm4::binary_search(double x, int l ,int r)
{
	while(r - l > 1)
	//пока результат не станет однозначным
	{
		int mid = (l + r) / 2; 	//Polosa[120].DFv;делим отрезок [l,r] пополам
		if(Polosa[mid].DFv<x)
		//прверяем где находимся
		{
            l = mid;
		}
        else
        {
            r = mid;
		}
	}
//
//				if(Polosa[r].DBad)
//	{
//						r=r+1;
//    }
//	else
//	{
//
//
//	}
	//цикл нужен, чтобы не править код
	//в случае увелечения интервала
	//[l,r]
	//for(int i = l; i <= r; i++)
	//    if(a[i]==x)
			return r;
	//return -1; не нашли такого элемента

}
//----------------------------------------------------------------------------

void __fastcall TForm4::BitBtn1Click(TObject *Sender)
{
 				if(!dlgSave1->Execute())
		 {
					return;
		 }
             	switch(AdvPageControl1->ActivePageIndex)
   {
	case 0:
		advstrngrd1->SaveToXLS(dlgSave1->FileName,true);
	break;
	case 1:
		AdvStringGrid1->SaveToXLS(dlgSave1->FileName,true);
	break;
	case 3:  break;
	case 4:  break;
	case 5:  break;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button3Click(TObject *Sender)
{
					for (i = 0; i < 268; i++)
	{
		Delta = advstrngrd1->Cells[0][i+2].ToDouble()-advstrngrd1->Cells[0][i+1].ToDouble();
		Delta = Delta/6;
		Form1->BLOK37->MFC1->Sint1_LMX2594->SetFreq(advstrngrd1->Cells[0][i+1].ToDouble()+Delta);
		advstrngrd1->Cells[6][i+1] = Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST - SpinEdit1->Value;//Polosa[i].CAP1
		Form1->BLOK37->MFC1->Sint1_LMX2594->SetFreq(advstrngrd1->Cells[0][i+1].ToDouble()+3*Delta);
		advstrngrd1->Cells[7][i+1] = Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST - SpinEdit1->Value;//Polosa[i].CAP2
		Form1->BLOK37->MFC1->Sint1_LMX2594->SetFreq(advstrngrd1->Cells[0][i+1].ToDouble()+5*Delta);
		advstrngrd1->Cells[8][i+1] = Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST - SpinEdit1->Value;//Polosa[i].CAP3
	}
		Delta = 15000-advstrngrd1->Cells[0][269].ToDouble();
		Delta = Delta/6;
		Form1->BLOK37->MFC1->Sint1_LMX2594->SetFreq(advstrngrd1->Cells[0][269].ToDouble()+Delta);
		advstrngrd1->Cells[6][269] = Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST - SpinEdit1->Value;//Polosa[i].CAP1
		Form1->BLOK37->MFC1->Sint1_LMX2594->SetFreq(advstrngrd1->Cells[0][269].ToDouble()+3*Delta);
		advstrngrd1->Cells[7][269] = Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST - SpinEdit1->Value;//Polosa[i].CAP2
		Form1->BLOK37->MFC1->Sint1_LMX2594->SetFreq(advstrngrd1->Cells[0][269].ToDouble()+5*Delta);
		advstrngrd1->Cells[8][269] = Form1->BLOK37->MFC1->Sint1_LMX2594->VCO_CAPCTRL_ST - SpinEdit1->Value;//Polosa[i].CAP3


}
//---------------------------------------------------------------------------

