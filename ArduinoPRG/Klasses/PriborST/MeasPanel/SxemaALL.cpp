//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <string.h>
#include "SxemaALL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma link "AdvUtil"
#pragma link "AdvPageControl"
#pragma link "W7Classes"
#pragma link "W7Images"
#pragma resource "*.dfm"
TFormSH *FormSH;

//---------------------------------------------------------------------------
__fastcall TFormSH::TFormSH(TComponent* Owner)
	: TForm(Owner)
{
	Stend = new StendPRibor("10.29.31.160");
	//Stend = new StendPRibor("10.29.31.160", new BL9910());

	/*MemINI = new OPTIONS_BASE("Device.ini");
	String PathINI = MemINI->TReadString(0,"Blok","Path", "" );
	if (PathINI==""){  MemINI->TWriteString(0,"Blok","Path", ExtractFileDir(ParamStr(0)) + "\\Device.ini");	 }
	PathINI = MemINI->TReadString(0,"Blok","Path", "" );
	MemINI->PAthSet(PathINI);*/
}
//---------------------------------------------------------------------------
 void TFormSH::TFormSH_INIT(String PDEV,String PDEVL,IBLock* Block)
 {
		Stend->StBlock =  Block;
		DEV = PDEV+".ini";
		DEVXXX =  PDEV+".ini";
		//MemINI = new OPTIONS_BASE("Device.ini");
		MemINI = new OPTIONS_BASE(DEV);
		String PathINI = MemINI->TReadString(0,"Blok","Path", "" );
				if (PathINI=="")
		{ MemINI->TWriteString(0,"Blok","Path", ExtractFileDir(ParamStr(0)) + "\\Device.ini");}
		PathINI = MemINI->TReadString(0,"Blok","Path", "" );
	/*=====Считывание настроек ================*/
	//TODO: Вывод из INI настроек в стенд @INIT  (0)
	//DEV = "BL_.ini";
	PAth = MemINI->PAthRead();
	//MemINI->MPAthSet(DEV); // MemINI->MPAthSet("BL3DG1.ini")
	Stend->analiz =  MemINI->ReadDouble("Stend","analiz",0);
	ComboBox1->ItemIndex = Stend->analiz;
			switch (ComboBox1->ItemIndex)
	{
	 case 0:
	 	ComboBox3->ItemIndex =	1;
		 Stend->An8560->GPIB_Set(MemINI->ReadString("An8560","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		 ShowMessage("Установлен анализатор Agilent 8560SA");
		 Edit1->Text = Stend->An8560->GetGPIB();
	 break;

	 case 1:
		 //Stend->An9030->Lan_GPIB = MemINI->ReadDouble("An9030","LANGPIB",0);

		 ShowMessage("Установлен анализатор Agilent N9030A");
		 ComboBox3->ItemIndex = MemINI->ReadDouble("An9030","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->An9030->IP_Set(MemINI->ReadString("An9030","IP","10.29.31.21"));
		  Edit1->Text = Stend->An9030->GetIPlok();  break;
		  case 1:Stend->An9030->GPIB_Set(MemINI->ReadString("An9030","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->An9030->GetGPIB();  break;
		}

	 break;
	 case 2:
			ShowMessage("Установлен анализатор R&S FSU50");
			ComboBox3->ItemIndex = MemINI->ReadDouble("RS_FSUP50","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("RS_FSUP50","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("RS_FSUP50","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;


	 case 3:
			ShowMessage("Установлен анализатор R&S FSL18");
			ComboBox3->ItemIndex = MemINI->ReadDouble("RS_FSL18","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("RS_FSL18","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("RS_FSL18","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;

	 case 4:
			ShowMessage("Установлен анализатор Keysight E4407");
			ComboBox3->ItemIndex = MemINI->ReadDouble("AnE4407","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("AnE4407","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("AnE4407","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;
	 /********************************************************************************/
	case 5:
			ShowMessage("Установлен анализатор Keysight N9020B");
			ComboBox3->ItemIndex = MemINI->ReadDouble("Key9020","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("Key9020","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("Key9020","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;
	}

	Stend->get = MemINI->ReadDouble("Stend","get",1);
	ComboBox2->ItemIndex = Stend->get;
	 switch (ComboBox2->ItemIndex)
	{
		 case 0:
			ShowMessage("Гетеродин1 Agilent E4426B 4 ГГц");
			ShowMessage("Гетеродин2 Agilent E4425B 3 ГГц");
			Label16->Caption = "E4425B";
			//Stend->analiz =0;
			cbb1->ItemIndex = MemINI->ReadDouble("Ag4425","LANGPIB",0);
							switch(cbb1->ItemIndex)
			{
			 case 0:  Stend->Ag4425->IP_Set(MemINI->ReadString("Ag4425","IP","10.29.31.17"));
			 Edit8->Text = Stend->Ag4425->GetIPlok();break;
			 case 1:Stend->Ag4425->GPIB_Set(MemINI->ReadString("Ag4425","GPIB","17"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit8->Text = Stend->Ag4425->GetGPIB();break;
			}
			cbb2->ItemIndex = MemINI->ReadDouble("AE4426","LANGPIB",0);
							switch(cbb2->ItemIndex)
			{
			 case 0:  Stend->AE4426->IP_Set(MemINI->ReadString("AE4426","IP","10.29.31.22"));
			 Edit9->Text = Stend->AE4426->GetIPlok();break;
			 case 1:Stend->AE4426->GPIB_Set(MemINI->ReadString("AE4426","GPIB","22"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit9->Text = Stend->AE4426->GetGPIB();break;
			}
		 break;

		 case 1:
			 ShowMessage("Гетеродин1 SMU200 A 6 ГГц");
			 ShowMessage("Гетеродин2 SMU200 B 3 ГГц");
			 //Stend->analiz =1;
			 Label16->Caption = "R&&S    SMU200 B";
			 cbb1->ItemIndex = MemINI->ReadDouble("SMU200","LANGPIB",1);
			 				switch(cbb1->ItemIndex)
		   {
			 case 0:Stend->SMU200->IP_Set(MemINI->ReadString("SMU200","IP","10.29.31.28"));
			 		Edit9->Text = Stend->SMU200->GetIPlok();
					Edit8->Text = Stend->SMU200->GetIPlok();break;

			 case 1:Stend->SMU200->GPIB_Set(MemINI->ReadString("SMU200","GPIB","28"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 		Edit9->Text = Stend->SMU200->GetGPIB();
					Edit8->Text = Stend->SMU200->GetGPIB();  break;
		   }
		 break;

	}
			cbb3->ItemIndex = MemINI->ReadDouble("AE44XX","LANGPIB",1);
							switch(cbb3->ItemIndex)
			{
			 case 0:  Stend->AgE44XX->IP_Set(MemINI->ReadString("AE44XX","IP","10.29.31.22"));
			 Edit11->Text = Stend->AgE44XX->GetIPlok();break;
			 case 1:Stend->AgE44XX->GPIB_Set(MemINI->ReadString("AE44XX","GPIB","22"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit11->Text = Stend->AgE44XX->GetGPIB();break;
			}
			cbb4->ItemIndex = MemINI->ReadDouble("E5071B","LANGPIB",1);
							switch(cbb4->ItemIndex)
			{
			 case 0:  Stend->Vstende5071->IP_Set(MemINI->ReadString("E5071B","IP","10.29.31.20"));
			 Edit10->Text = Stend->Vstende5071->GetIPlok();break;
			 case 1:Stend->Vstende5071->GPIB_Set(MemINI->ReadString("E5071B","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit10->Text = Stend->Vstende5071->GetGPIB();break;
			}
			ComboBox16->ItemIndex = Stend->TCom;    /* Тип Коммутатора из INI*/


			ComboBox16->ItemIndex = MemINI->ReadDouble("Switch34980","COMTIP",1);   /* TODO -cIp ADR : Способ перекл. кан из ini */
            Stend->TCom = ComboBox16->ItemIndex;
			cbb5->ItemIndex = MemINI->ReadDouble("Switch34980","LANGPIB",1);
							switch(cbb5->ItemIndex)
			{
			 case 0:  Stend->KOM34980->IP_Set(MemINI->ReadString("Switch34980","IP","10.29.31.20"));
			 Edit7->Text = Stend->KOM34980->GetIPlok();break;
			 case 1:Stend->KOM34980->GPIB_Set(MemINI->ReadString("Switch34980","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit7->Text = Stend->KOM34980->GetGPIB();break;
			}


			ComboBPN6700->ItemIndex = MemINI->ReadDouble("BPN6700","LANGPIB",1);

           	switch (ComboBPN6700->ItemIndex)
	   { case 0:Stend->MP_N6702A->IP_Set(MemINI->ReadString("BPN6700","IP","10.29.31.20"));
	   			EditBPadr->Text = Stend->MP_N6702A->GetIPlok(); break; // MemINI->ReadDouble("An9030","GPIB",235);
		 case 1:Stend->MP_N6702A->GPIB_Set(MemINI->ReadString("BPN6700","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
				EditBPadr->Text = Stend->MP_N6702A->GetGPIB(); break; //MemINI->ReadString("An9030","IP","XXXXXX")
	   }
		ComboBox16->ItemIndex = Stend->TCom;    /* Тип Коммутатора из INI*/
		Stend->CTbl[0] = MemINI->ReadDouble("Kalibr","D100",0.1);
		Stend->CTbl[1] = MemINI->ReadDouble("Kalibr","D800",0.5);
		Stend->CTbl[2] = MemINI->ReadDouble("Kalibr","D2000",2.2);
		Stend->CTbl[3] = MemINI->ReadDouble("Kalibr","D3000",4);

		AdvStringGrid1->Cells[1][1] = Stend->CTbl[0];
		AdvStringGrid1->Cells[1][2] = Stend->CTbl[1];
		AdvStringGrid1->Cells[1][3] = Stend->CTbl[2];
		AdvStringGrid1->Cells[1][4] = Stend->CTbl[3];

		//	Stend->Stend_LimitRet(Pw,Rf,Rf10M,Sp,RB);
		Edit2->Text = MemINI->ReadDouble("Stend","POW",-50);
		Edit3->Text = MemINI->ReadDouble("Stend","RLWL",-20);
		Edit4->Text = MemINI->ReadDouble("Stend","RLWL10M",10);
		Edit5->Text = MemINI->ReadDouble("Stend","Span",0.1);
		Edit6->Text = MemINI->ReadDouble("Stend","RBW",3000);
		Edit12->Text = MemINI->ReadDouble("Stend","FOFS",100);
	 //	Edit7->Text = Stend->KOM34980->GetGPIB();
	 //	Edit11->Text = Stend->AgE44XX->GetGPIB();
		Stend->Stend_LimitLoad(MemINI->ReadDouble("Stend","POW",-50),MemINI->ReadDouble("Stend","RLWL",-20),
		MemINI->ReadDouble("Stend","RLWL10M",10),MemINI->ReadDouble("Stend","Span",0.1),
		MemINI->ReadDouble("Stend","RBW",3000),MemINI->ReadDouble("Stend","FOFS",100));
		MemINI->PAthSet(PAth);
	/*=====  End of Считывание настроек  ======*/
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::Button1Click(TObject *Sender)
{/* Предельные значения */
//CHANGED: Установка Запись настроек стенда в INI  @INI (1)
	Stend->Stend_LimitLoad(Edit2->Text.ToDouble(),Edit3->Text.ToDouble(),Edit4->Text.ToDouble(),Edit5->Text.ToDouble(),
	Edit6->Text.ToDouble(),Edit12->Text.ToDouble());
	Stend->Stend_PrAdress(ComboBox1->ItemIndex,ComboBox2->ItemIndex, ComboBox2->ItemIndex,
	ComboBox3->ItemIndex,Edit1->Text,
	cbb3->ItemIndex,Edit11->Text,//
	cbb1->ItemIndex,Edit8->Text,
	cbb2->ItemIndex,Edit9->Text,
	cbb5->ItemIndex,Edit7->Text,
	cbb4->ItemIndex,Edit10->Text,
	ComboBPN6700->ItemIndex,EditBPadr->Text, EditIP->Text);

//void StendPRibor::Stend_PrAdress(int An, int Get1, int Get2,
//		int ANLAN, AnsiString AdrAN,
//		int GENLAN, AnsiString AdrGEN,
//		int GEN1LAN,AnsiString AdrGEN1,
//		int GEN2LAN,AnsiString AdrGEN2,
//		int SWLAN, AnsiString AdrSW,
//		int PANLAN,	AnsiString AdrPan,
//		int BPLAN,	AnsiString AdrBP, AnsiString Ip)

/*Запись в INI*/
	PAth = MemINI->PAthRead();
  	MemINI->MPAthSet(DEV);
	MemINI->WriteDouble("Stend","analiz",ComboBox1->ItemIndex);
	 switch (ComboBox1->ItemIndex)
	{
		 case 0:
			MemINI->WriteDouble("Stend","An8560",Edit1->Text.ToDouble());
		 break;

		 case 1:MemINI->WriteDouble("An9030","LANGPIB",ComboBox3->ItemIndex);
		switch (ComboBox3->ItemIndex)
			{
				case 0:MemINI->WriteString("An9030","IP",Edit1->Text);	break;
				case 1:MemINI->WriteDouble("An9030","GPIB",Edit1->Text.ToDouble());break;
			}
		 break;

		 case 2:MemINI->WriteDouble("RS_FSUP50","LANGPIB",ComboBox3->ItemIndex);
		switch (ComboBox3->ItemIndex)
			{
				case 0:MemINI->WriteString("RS_FSUP50","IP",Edit1->Text);	break;
				case 1:MemINI->WriteDouble("RS_FSUP50","GPIB",Edit1->Text.ToDouble());break;
			}
		 break;
		 case 3:MemINI->WriteDouble("RS_FSL18","LANGPIB",ComboBox3->ItemIndex);
		switch (ComboBox3->ItemIndex)
			{
				case 0:MemINI->WriteString("RS_FSL18","IP",Edit1->Text);	break;
				case 1:MemINI->WriteDouble("RS_FSL18","GPIB",Edit1->Text.ToDouble());break;
			}
		 break;
		 case 4: MemINI->WriteDouble("AnE4407","LANGPIB",ComboBox3->ItemIndex);
		switch (ComboBox3->ItemIndex)
			{
				case 0:MemINI->WriteString("AnE4407","IP",Edit1->Text);	break;
				case 1:MemINI->WriteDouble("AnE4407","GPIB",Edit1->Text.ToDouble());break;
			}
		 break;
		 case 5: MemINI->WriteDouble("Key9020","LANGPIB",ComboBox3->ItemIndex);
				switch (ComboBox3->ItemIndex)
			{
				case 0:MemINI->WriteString("Key9020","IP",Edit1->Text);	break;
				case 1:MemINI->WriteDouble("Key9020","GPIB",Edit1->Text.ToDouble());break;
			}
		 break;


	}
	MemINI->WriteDouble("Stend","get",ComboBox2->ItemIndex);
	switch (ComboBox2->ItemIndex)
	{
		 case 0:
			MemINI->WriteDouble("Ag4425","LANGPIB",cbb1->ItemIndex);//Гетеродин1 запись в INI
			switch (cbb1->ItemIndex)
			  //TODO: Разобраться LAN генераторы гетеродина
			{
				case 0:
						MemINI->WriteString("Ag4425","IP",Edit8->Text);
				break;
				case 1:
						MemINI->WriteDouble("Ag4425","GPIB",Edit8->Text.ToDouble());
				break;
			}
			MemINI->WriteDouble("AE4426","LANGPIB",cbb2->ItemIndex);//Гетеродин2 запись в INI
					switch (cbb2->ItemIndex)
			{
				case 0:
						MemINI->WriteString("AE4426","IP",Edit9->Text);
				break;
				case 1:
						MemINI->WriteDouble("AE4426","GPIB",Edit9->Text.ToDouble());
				break;
			}
		 break;

		 case 1:
			MemINI->WriteDouble("SMU200","LANGPIB",cbb1->ItemIndex);//Гетеродин1 запись в INI
			switch (cbb1->ItemIndex)
			{
				case 0:
						MemINI->WriteString("SMU200","IP",Edit8->Text);
				break;  //Гетеродин2-1 запись в INI
				case 1:
						MemINI->WriteDouble("SMU200","GPIB",Edit9->Text.ToDouble());
				break;
			}
		 break;
	}
	MemINI->WriteDouble("AE44XX","LANGPIB",cbb3->ItemIndex);//Генератор сигнала запись в INI
		switch (cbb3->ItemIndex)
	{
		case 0:MemINI->WriteString("AE44XX","IP",Edit11->Text);	break;
		case 1:MemINI->WriteDouble("AE44XX","GPIB",Edit11->Text.ToDouble());break;
	}


	MemINI->WriteDouble("E5071B","LANGPIB",cbb4->ItemIndex);// Анализатор цепей запись в INI
		switch (cbb4->ItemIndex)
	{
		case 0:MemINI->WriteString("E5071B","IP",Edit10->Text);	break;
		case 1:MemINI->WriteDouble("E5071B","GPIB",Edit10->Text.ToDouble());break;
	}
	MemINI->WriteDouble("Switch34980","COMTIP",ComboBox16->ItemIndex);   /* TODO -cIp ADR : Способ перекл. кан в ini */
	Stend->TCom = ComboBox16->ItemIndex;
	MemINI->WriteDouble("Switch34980","LANGPIB",cbb5->ItemIndex);// Коммутатор запись в INI
		switch (cbb5->ItemIndex)
	{
		case 0:MemINI->WriteString("Switch34980","IP",Edit7->Text);	break;
		case 1:MemINI->WriteDouble("Switch34980","GPIB",Edit7->Text.ToDouble());break;
	}

	MemINI->WriteDouble("BPN6700","LANGPIB",ComboBPN6700->ItemIndex);   /* TODO -cIp ADR : Адрес БП в ini */
				switch (ComboBPN6700->ItemIndex)
	{
		case 0:MemINI->WriteString("BPN6700","IP",EditBPadr->Text);	break;
		case 1:MemINI->WriteDouble("BPN6700","GPIB",EditBPadr->Text.ToDouble());break;
	}


	MemINI->WriteDouble("Stend","POW",Edit2->Text.ToDouble());
	MemINI->WriteDouble("Stend","RLWL",Edit3->Text.ToDouble());
	MemINI->WriteDouble("Stend","RLWL10M",Edit4->Text.ToDouble());
	MemINI->WriteDouble("Stend","Span",Edit5->Text.ToDouble());
	MemINI->WriteDouble("Stend","RBW",Edit6->Text.ToDouble());
	MemINI->WriteString("Stend","IP",EditIP->Text);
	MemINI->WriteString("Stend","FOFS",Edit12->Text);


	MemINI->WriteDouble("Kalibr","D100",AdvStringGrid1->Cells[1][1].ToDouble());
	MemINI->WriteDouble("Kalibr","D800",AdvStringGrid1->Cells[1][2].ToDouble());
	MemINI->WriteDouble("Kalibr","D2000",AdvStringGrid1->Cells[1][3].ToDouble());
	MemINI->WriteDouble("Kalibr","D3000",AdvStringGrid1->Cells[1][4].ToDouble());

	Stend->CTbl[0] = AdvStringGrid1->Cells[1][1].ToDouble();
	Stend->CTbl[1] = AdvStringGrid1->Cells[1][2].ToDouble();
	Stend->CTbl[2] = AdvStringGrid1->Cells[1][3].ToDouble();
	Stend->CTbl[3] = AdvStringGrid1->Cells[1][4].ToDouble();


	MemINI->PAthSet(PAth);



 // FormSH->Close();

}
//---------------------------------------------------------------------------
void  TFormSH::DEFPath()
{
    MemINI->MPAthSet(DEV);
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::ComboBox1Change(TObject *Sender)
{
		Stend->analiz = ComboBox1->ItemIndex;
		TJPEGImage *jpg = new TJPEGImage();
		TPngImage *png = new TPngImage();


//			switch (ComboBox4->ItemIndex)
//		{   case 0:
//			png->LoadFromFile("InstrumentIcons//E4402B.png");//       E4402B
//			W7Image1->Picture->Assign(png);
//			break;
//			case 1:
//			png->LoadFromFile("InstrumentIcons//E4402B.png");//       E4402B
//			W7Image1->Picture->Assign(png);
//			break;
//			case 2:
//			png->LoadFromFile("InstrumentIcons//E4402B.png");//       E4402B
//			W7Image1->Picture->Assign(png);
//			break;
//			case 3:
//			png->LoadFromFile("InstrumentIcons//N9020A.png");//
//			W7Image1->Picture->Assign(png);
//			break;
//			case 4:
//			png->LoadFromFile("InstrumentIcons//N9030A.png");//
//			W7Image1->Picture->Assign(png);
//			break;
//			case 5:
//			break;
//			case 6:
//			break;
//			case 7:
//			jpg->LoadFromFile("E5810.jpg");
//			W7Image1->Picture->Assign(jpg);
//			break;
//		}
//





			 switch (ComboBox1->ItemIndex)
		{
			case 0:
				ShowMessage("Установлен анализатор Agilent 8560SA");
				 W7Image1->Picture->Assign(NULL);

					 switch (ComboBox3->ItemIndex)
				{
					case 0:

					break;
					case 1:

					break;
				}
			break;

			case 1:
					ShowMessage("Установлен анализатор Agilent N9030A");
				   	png->LoadFromFile("InstrumentIcons//N9030A.png");//       E4402B
					W7Image1->Picture->Assign(png);

					 switch (ComboBox3->ItemIndex)
				{
					case 0:Edit1->Text = Stend->An9030->GetIPlok();break;
					case 1:Edit1->Text = Stend->An9030->GetGPIB();break;
				}

			break;
			case 2:
			ShowMessage("Установлен анализатор R&S FSUP50");
			W7Image1->Picture->Assign(NULL);
				 switch (ComboBox3->ItemIndex)
			{
				case 0:	Edit1->Text = Stend->RS_FSUP50->GetIPlok();break;
				case 1:	Edit1->Text = Stend->RS_FSUP50->GetGPIB();break;
			}
			break;
			case 3:
				 ShowMessage("Установлен анализатор R&S FSL18 ");
				  W7Image1->Picture->Assign(NULL);
				  switch (ComboBox3->ItemIndex)
			{
				case 0:Edit1->Text = Stend->RS_FSL->GetIPlok();break;
				case 1:Edit1->Text = Stend->RS_FSL->GetGPIB();break;
			}
			break;
			case 4:
				ShowMessage("Установлен анализатор Keysight E4407");
				png->LoadFromFile("InstrumentIcons//E4402B.png");//       E4402B
				W7Image1->Picture->Assign(png);
				 switch (ComboBox3->ItemIndex)
			{
				case 0:Edit1->Text = Stend->AnE4407->GetIPlok();break;
				case 1:Edit1->Text = Stend->AnE4407->GetGPIB();	break;
			}
			break;
			case 5:
			ShowMessage("Установлен анализатор Keysight N9020B");
             W7Image1->Picture->Assign(NULL);
				switch (ComboBox3->ItemIndex)
			{
				case 0:Edit1->Text = Stend->Key9020->GetIPlok();break;
				case 1:Edit1->Text = Stend->Key9020->GetGPIB();break;
			}
	break;

		}
     delete png;
	 delete jpg;
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::ComboBox2Change(TObject *Sender)
{      Stend->get = ComboBox2->ItemIndex;
			 switch (ComboBox2->ItemIndex)
		{
			 case 0:
			 ShowMessage("Гетеродин1 Agilent E4426B 4 ГГц");
			 ShowMessage("Гетеродин2 Agilent E4425B 3 ГГц");
			 Label16->Caption = "E4426B";
					switch(cbb1->ItemIndex)
			{
			 case 0: Edit8->Text = Stend->Ag4425->GetIPlok();break;
			 case 1: Edit8->Text = Stend->Ag4425->GetGPIB();break;
			}
					switch(cbb2->ItemIndex)
			{
			 case 0: Edit9->Text = Stend->AE4426->GetIPlok();break;
			 case 1: Edit9->Text = Stend->AE4426->GetGPIB();break;
			}


			 break;

			 case 1:
			 ShowMessage("Гетеродин1 SMU200 A 6 ГГц");
			 ShowMessage("Гетеродин2 SMU200 B 3 ГГц");

			 Label16->Caption = "R&&S    SMU200 B";
			 cbb2->ItemIndex = cbb1->ItemIndex;
					switch(cbb1->ItemIndex)
			{
			 case 0:
					Edit9->Text = Stend->SMU200->GetIPlok();
					Edit8->Text = Stend->SMU200->GetIPlok();break;

			 case 1:Edit9->Text = Stend->SMU200->GetGPIB();
					Edit8->Text = Stend->SMU200->GetGPIB();  break;
			}
			 break;
			 case 2:
			 ShowMessage("Гетеродин1 Agilent N5183A 32 ГГц");
			 ShowMessage("Гетеродин2 Agilent E4425B 3 ГГц");
			 Label16->Caption = "E4426B";
					switch(cbb1->ItemIndex)
			{
			 case 0: Edit8->Text = Stend->NN5183->GetIPlok();break;
			 case 1: Edit8->Text = Stend->NN5183->GetGPIB();break;
			}
					switch(cbb2->ItemIndex)
			{
			 case 0: Edit9->Text = Stend->AE4426->GetIPlok();break;
			 case 1: Edit9->Text = Stend->AE4426->GetGPIB();break;
			}
			 break;



		}
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::FormCreate(TObject *Sender)
{
//TODO: Вывод из INI настроек в стенд @СТАРТ  (0)
DEVXXX = "BL_.ini";
/*PAth = MemINI->PAthRead();
//MemINI->MPAthSet(DEV); // MemINI->MPAthSet("BL3DG1.ini")
Stend->analiz =  MemINI->ReadDouble("Stend","analiz",0);
ComboBox1->ItemIndex = Stend->analiz;
			switch (ComboBox1->ItemIndex)
	{
	 case 0:
	 	ComboBox3->ItemIndex =	1;
		 Stend->An8560->GPIB_Set(MemINI->ReadString("An8560","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		 ShowMessage("Установлен анализатор Agilent 8560SA");
		 Edit1->Text = Stend->An8560->GetGPIB();
	 break;

	 case 1:
		 //Stend->An9030->Lan_GPIB = MemINI->ReadDouble("An9030","LANGPIB",0);

		 ShowMessage("Установлен анализатор Agilent N9030A");
		 ComboBox3->ItemIndex = MemINI->ReadDouble("An9030","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->An9030->IP_Set(MemINI->ReadString("An9030","IP","10.29.31.21"));
		  Edit1->Text = Stend->An9030->GetIPlok();  break;
		  case 1:Stend->An9030->GPIB_Set(MemINI->ReadString("An9030","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->An9030->GetGPIB();  break;
		}

	 break;
	 case 2:
			ShowMessage("Установлен анализатор R&S FSU50");
			ComboBox3->ItemIndex = MemINI->ReadDouble("RS_FSUP50","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("RS_FSUP50","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("RS_FSUP50","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;


	 case 3:
			ShowMessage("Установлен анализатор R&S FSL18");
			ComboBox3->ItemIndex = MemINI->ReadDouble("RS_FSL18","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("RS_FSL18","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("RS_FSL18","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;

	 case 4:
			ShowMessage("Установлен анализатор Keysight E4407");
			ComboBox3->ItemIndex = MemINI->ReadDouble("AnE4407","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("AnE4407","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("AnE4407","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;
	 //********************************************************************************
	/*case 5:
			ShowMessage("Установлен анализатор Keysight N9020B");
			ComboBox3->ItemIndex = MemINI->ReadDouble("Key9020","LANGPIB",0);//Stend->An9030->Lan_GPIB;
		 		switch (ComboBox3->ItemIndex)
		{
		  case 0:Stend->RS_FSUP50->IP_Set(MemINI->ReadString("Key9020","IP","10.29.31.21"));
		  Edit1->Text = Stend->RS_FSUP50->GetIPlok();  break;
		  case 1:Stend->RS_FSUP50->GPIB_Set(MemINI->ReadString("Key9020","GPIB","18"), MemINI->ReadString("Stend","IP","10.29.31.160"));
		  Edit1->Text = Stend->RS_FSUP50->GetGPIB();  break;
		}

	 break;
	}

	Stend->get = MemINI->ReadDouble("Stend","get",1);
	ComboBox2->ItemIndex = Stend->get;
	 switch (ComboBox2->ItemIndex)
	{
		 case 0:
			ShowMessage("Гетеродин1 Agilent E4426B 4 ГГц");
			ShowMessage("Гетеродин2 Agilent E4425B 3 ГГц");
			Label16->Caption = "E4425B";
			//Stend->analiz =0;
			cbb1->ItemIndex = MemINI->ReadDouble("Ag4425","LANGPIB",0);
							switch(cbb1->ItemIndex)
			{
			 case 0:  Stend->Ag4425->IP_Set(MemINI->ReadString("Ag4425","IP","10.29.31.17"));
			 Edit8->Text = Stend->Ag4425->GetIPlok();break;
			 case 1:Stend->Ag4425->GPIB_Set(MemINI->ReadString("Ag4425","GPIB","17"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit8->Text = Stend->Ag4425->GetGPIB();break;
			}
			cbb2->ItemIndex = MemINI->ReadDouble("AE4426","LANGPIB",0);
							switch(cbb2->ItemIndex)
			{
			 case 0:  Stend->AE4426->IP_Set(MemINI->ReadString("AE4426","IP","10.29.31.22"));
			 Edit9->Text = Stend->AE4426->GetIPlok();break;
			 case 1:Stend->AE4426->GPIB_Set(MemINI->ReadString("AE4426","GPIB","22"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit9->Text = Stend->AE4426->GetGPIB();break;
			}
		 break;

		 case 1:
			 ShowMessage("Гетеродин1 SMU200 A 6 ГГц");
			 ShowMessage("Гетеродин2 SMU200 B 3 ГГц");
			 //Stend->analiz =1;
			 Label16->Caption = "R&&S    SMU200 B";
			 cbb1->ItemIndex = MemINI->ReadDouble("SMU200","LANGPIB",1);
			 				switch(cbb1->ItemIndex)
		   {
			 case 0:Stend->SMU200->IP_Set(MemINI->ReadString("SMU200","IP","10.29.31.28"));
			 		Edit9->Text = Stend->SMU200->GetIPlok();
					Edit8->Text = Stend->SMU200->GetIPlok();break;

			 case 1:Stend->SMU200->GPIB_Set(MemINI->ReadString("SMU200","GPIB","28"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 		Edit9->Text = Stend->SMU200->GetGPIB();
					Edit8->Text = Stend->SMU200->GetGPIB();  break;
		   }
		 break;

	}
			cbb3->ItemIndex = MemINI->ReadDouble("AE44XX","LANGPIB",1);
							switch(cbb3->ItemIndex)
			{
			 case 0:  Stend->AgE44XX->IP_Set(MemINI->ReadString("AE44XX","IP","10.29.31.22"));
			 Edit11->Text = Stend->AgE44XX->GetIPlok();break;
			 case 1:Stend->AgE44XX->GPIB_Set(MemINI->ReadString("AE44XX","GPIB","22"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit11->Text = Stend->AgE44XX->GetGPIB();break;
			}
			cbb4->ItemIndex = MemINI->ReadDouble("E5071B","LANGPIB",1);
							switch(cbb4->ItemIndex)
			{
			 case 0:  Stend->Vstende5071->IP_Set(MemINI->ReadString("E5071B","IP","10.29.31.20"));
			 Edit10->Text = Stend->Vstende5071->GetIPlok();break;
			 case 1:Stend->Vstende5071->GPIB_Set(MemINI->ReadString("E5071B","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit10->Text = Stend->Vstende5071->GetGPIB();break;
			}
			ComboBox16->ItemIndex = Stend->TCom;    // Тип Коммутатора из INI


			ComboBox16->ItemIndex = MemINI->ReadDouble("Switch34980","COMTIP",1);   //TODO: -cIp ADR : Способ перекл. кан из ini 
            Stend->TCom = ComboBox16->ItemIndex;
			cbb5->ItemIndex = MemINI->ReadDouble("Switch34980","LANGPIB",1);
							switch(cbb5->ItemIndex)
			{
			 case 0:  Stend->KOM34980->IP_Set(MemINI->ReadString("Switch34980","IP","10.29.31.20"));
			 Edit7->Text = Stend->KOM34980->GetIPlok();break;
			 case 1:Stend->KOM34980->GPIB_Set(MemINI->ReadString("Switch34980","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
			 Edit7->Text = Stend->KOM34980->GetGPIB();break;
			}


			ComboBPN6700->ItemIndex = MemINI->ReadDouble("BPN6700","LANGPIB",1);

           	switch (ComboBPN6700->ItemIndex)
	   { case 0:Stend->MP_N6702A->IP_Set(MemINI->ReadString("BPN6700","IP","10.29.31.20"));
	   			EditBPadr->Text = Stend->MP_N6702A->GetIPlok(); break; // MemINI->ReadDouble("An9030","GPIB",235);
		 case 1:Stend->MP_N6702A->GPIB_Set(MemINI->ReadString("BPN6700","GPIB","20"), MemINI->ReadString("Stend","IP","10.29.31.160"));
				EditBPadr->Text = Stend->MP_N6702A->GetGPIB(); break; //MemINI->ReadString("An9030","IP","XXXXXX")
	   }
		ComboBox16->ItemIndex = Stend->TCom;    // Тип Коммутатора из INI
		Stend->CTbl[0] = MemINI->ReadDouble("Kalibr","D100",0.1);
		Stend->CTbl[1] = MemINI->ReadDouble("Kalibr","D800",0.5);
		Stend->CTbl[2] = MemINI->ReadDouble("Kalibr","D2000",2.2);
		Stend->CTbl[3] = MemINI->ReadDouble("Kalibr","D3000",4);

		AdvStringGrid1->Cells[1][1] = Stend->CTbl[0];
		AdvStringGrid1->Cells[1][2] = Stend->CTbl[1];
		AdvStringGrid1->Cells[1][3] = Stend->CTbl[2];
		AdvStringGrid1->Cells[1][4] = Stend->CTbl[3];

		//	Stend->Stend_LimitRet(Pw,Rf,Rf10M,Sp,RB);
		Edit2->Text = MemINI->ReadDouble("Stend","POW",-50);
		Edit3->Text = MemINI->ReadDouble("Stend","RLWL",-20);
		Edit4->Text = MemINI->ReadDouble("Stend","RLWL10M",10);
		Edit5->Text = MemINI->ReadDouble("Stend","Span",0.1);
		Edit6->Text = MemINI->ReadDouble("Stend","RBW",3000);
		Edit12->Text = MemINI->ReadDouble("Stend","FOFS",100);
	 //	Edit7->Text = Stend->KOM34980->GetGPIB();
	 //	Edit11->Text = Stend->AgE44XX->GetGPIB();
		Stend->Stend_LimitLoad(MemINI->ReadDouble("Stend","POW",-50),MemINI->ReadDouble("Stend","RLWL",-20),
		MemINI->ReadDouble("Stend","RLWL10M",10),MemINI->ReadDouble("Stend","Span",0.1),
		MemINI->ReadDouble("Stend","RBW",3000),MemINI->ReadDouble("Stend","FOFS",100));
		MemINI->PAthSet(PAth);

		*/
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::ComboBox3Change(TObject *Sender)
{
					switch(ComboBox1->ItemIndex)
   {case 0:Edit1->Text = Stend->An8560->GetGPIB();
	break;
	case 1:
				switch (ComboBox3->ItemIndex)
			{
				case 0:Edit1->Text = Stend->An9030->GetIPlok(); break; // MemINI->ReadDouble("An9030","GPIB",235);
				case 1:Edit1->Text = Stend->An9030->GetGPIB(); break; //MemINI->ReadString("An9030","IP","XXXXXX")
			}
	break;
	case 2:
				switch (ComboBox3->ItemIndex)
			{

				case 0:Edit1->Text = Stend->RS_FSUP50->GetIPlok(); break; // MemINI->ReadDouble("An9030","GPIB",235);
				case 1:Edit1->Text = Stend->RS_FSUP50->GetGPIB(); break; //MemINI->ReadString("An9030","IP","XXXXXX")

			}
	break;
	case 3:
				switch (ComboBox3->ItemIndex)
			{
				case 0:Edit1->Text = Stend->RS_FSL->GetIPlok();break;
				case 1:Edit1->Text = Stend->RS_FSL->GetGPIB();break;
			}
	break;
	case 4:
				switch (ComboBox3->ItemIndex)
			{
				case 0:Edit1->Text = Stend->AnE4407->GetIPlok();break;
				case 1:Edit1->Text = Stend->AnE4407->GetGPIB();break;
			}
	break;
	case 5:
				switch (ComboBox3->ItemIndex)
			{
				case 0:Edit1->Text = Stend->Key9020->GetIPlok();break;
				case 1:Edit1->Text = Stend->Key9020->GetGPIB();break;
			}
	break;

   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::ComboBPN6700Change(TObject *Sender)
{
			switch (ComboBPN6700->ItemIndex)
		   { case 0:EditBPadr->Text = Stend->MP_N6702A->GetIPlok();break; // MemINI->ReadDouble("An9030","GPIB",235);
			 case 1:EditBPadr->Text = Stend->MP_N6702A->GetGPIB();break; //MemINI->ReadString("An9030","IP","XXXXXX")
		   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::cbb3Change(TObject *Sender)
{          /*Генератор вх*/
			switch (cbb3->ItemIndex)
   { case 0:Edit11->Text = Stend->AgE44XX->GetIPlok(); break; // MemINI->ReadDouble("An9030","GPIB",235);
	 case 1:Edit11->Text = Stend->AgE44XX->GetGPIB(); break; //MemINI->ReadString("An9030","IP","XXXXXX")
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::cbb5Change(TObject *Sender)
{
		   /*Коммутатор*/
			switch (cbb5->ItemIndex)
   { case 0:Edit7->Text = Stend->KOM34980->GetIPlok(); break; // MemINI->ReadDouble("An9030","GPIB",235);
	 case 1:Edit7->Text = Stend->KOM34980->GetGPIB(); break; //MemINI->ReadString("An9030","IP","XXXXXX")
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::cbb4Change(TObject *Sender)
{
			  /*Панорама*/
			switch (cbb4->ItemIndex)
   { case 0:Edit10->Text = Stend->Vstende5071->GetIPlok(); break; // MemINI->ReadDouble("An9030","GPIB",235);
	 case 1:Edit10->Text = Stend->Vstende5071->GetGPIB(); break; //MemINI->ReadString("An9030","IP","XXXXXX")
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::ComboBox16Change(TObject *Sender)
{
		  Stend->TCom = ComboBox16->ItemIndex ;    /* Тип Коммутатора из INI*/
}
//---------------------------------------------------------------------------
void __fastcall TFormSH::Button2Click(TObject *Sender)
{
		Label17->Caption = Stend->An9030->GETIDN();
}
//---------------------------------------------------------------------------

