//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "SxemaALL.h"
#include "DialogSave.h"
#include <ComObj.hpp>
//#include "UsbDefines.h"
#include <utilcls.h>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSNSW *FormSNSW;
//---------------------------------------------------------------------------
__fastcall TFormSNSW::TFormSNSW(TComponent* Owner)
	: TForm(Owner)
{
//TODO: SAWESN CONSTR @INI  (DialogSave.cpp)
DEVICESTR = "\\Device.ini";
DEVICESTR_ = "\\Device_";
}
//---------------------------------------------------------------------------
void TFormSNSW::INITsave(AnsiString DEV)
{
DEVICESTR = "\\"+DEV+".ini";
DEVICESTR_ = "\\"+DEV+"_";
}
//---------------------------------------------------------------------------

void __fastcall TFormSNSW::Button1Click(TObject *Sender)
{
	if (Edit1->Text!= "")
	{
//TODO: ПУТЬ @INI (DialogSave.cpp)
		AnsiString ExecDir = ExtractFileDir(ParamStr(0));
//---------------------------------------------------------------------------
		// AnsiString AIn = ExecDir + "\\BL3VK1.ini" ;
		AnsiString AIn = ExecDir + DEVICESTR ;
//---------------------------------------------------------------------------
	    FormSH->MemINI->PAthSet(AIn);
		AnsiString PUT;
		PUT = ExecDir + DEVICESTR_ +Edit1->Text+".ini" ;
		FormSH->MemINI->TWriteString(0,"Blok","Path",PUT);
		FormSH->MemINI->PAthSet(PUT);
		FormSH->MemINI->WriteDouble("Blok","Зав№", StrToFloat(Edit1->Text));
	//MemINI->WriteDouble("Priemka","Tipe", ComboBox1->ItemIndex);
	//RelBlok3Vk1INI(ComboBox4->ItemIndex);
	 /*//switch(Form1->PageControl1->ActivePageIndex)
		 switch(1)
		 {
			case 4:
		   PUT = ExecDir + "\\BL3VK1_" +Edit1->Text+".ini" ;  //4  7
		  // Form1->MemINI->TWriteString(0,"Blok","Path",PUT);
			break;
			case 7:
		   PUT = ExecDir + "\\BL3VK11_" +Edit1->Text+".ini" ;  // 3 6
		  // Form1->MemINI->TWriteString(0,"Blok11","Path",PUT);
			break;
		 }*/

		//switch(Form1->PageControl1->ActivePageIndex)
//---------------------------------------------------------------------------
	/*		switch(1)
		 {
			case 4:
			Form1->Edit1->Text = "";
			Form1->Edit1->Text = Edit1->Text;
			break;
			case 7:
			Form1->Edit29->Text = "";
			Form1->Edit29->Text = Edit1->Text;
			break;
		 }*/

	}//---------------------------------------------------------------------------

	if (CheckBox1->Checked) {
	 //Form1->Stend->VstendeBL3VK1->WriteBlokSN(Edit1->Text.ToInt());  //>DeviceUSB->WriteSNVer(,0);
	 //Form1->StatusBar1->Panels->Items[0]->Text = "Блок " + IntToStr((int) Form1->Stend->VstendeBL3VK1->ReadBlokSN());

	}
 FormSNSW->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSNSW::Button2Click(TObject *Sender)
{

 FormSNSW->Close();

}
//---------------------------------------------------------------------------


void __fastcall TFormSNSW::FormShow(TObject *Sender)
{
    	DWORD t=0;
//  if (Form1->Stend->VstendeBL3VK1->DeviceUSB!=NULL)
//  {
//
//   t=Form1->Stend->VstendeBL3VK1->DeviceUSB->ReadSN();
//   VerEdit->Caption=IntToStr((int)(t));
//   t= Form1->Stend->VstendeBL3VK1->DeviceUSB->ReadSN();
//   SNEdit->Caption=IntToStr((int)t);
//   Edit1->Text = IntToStr((int)(t));
//  }
}
//---------------------------------------------------------------------------

