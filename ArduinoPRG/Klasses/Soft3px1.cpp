
void __fastcall TForm1::SHDNCheckBoxClick(TObject *Sender)
{
  
  DWORD CMD=0;
  DWORD SW=0;
  DWORD SWADR=0;

  if(Chennel1RButt->Checked)
	{
	 if(SHDNCheckBox->Checked)Ch1_Pch1_Sw|=0x00000100;
						 else Ch1_Pch1_Sw&=(~0x00000100);
	 SW=Ch1_Pch1_Sw;
	 SWADR=0x0e;
	}
  else
	{
	if(SHDNCheckBox->Checked)Ch2_Pch1_Sw|=0x00000100;
						 else Ch2_Pch1_Sw&=(~0x00000100);
	 SW=Ch2_Pch1_Sw;
	 SWADR=0x0f;
	}
  CMD=(SelectedModul<<28)|(0x4<<24)|(SWADR<<16)|(SW<<7);
  SendDATA_SPI(CMD,0,CTL_20_ChBox->Checked);
}
 DWORDLONG __fastcall TForm1::SendDATA_SPI(DWORD DATH,DWORD DATL,bool by_way)
{
	 DWORDLONG RxDat;
	   if(by_way)
		{
		  if(DeviceUSB!=NULL)
		   {
			RxDat=SendDATA_SPI_USB(DATH,DATL);
		   }
		   else
		   {
			 ShowMessage("Устройство не подключено");
			 return 0;
		   }
		}
	   else
	   {
		if(dev!=NULL)
	   {
		 RxDat=SendDATA_SPI_PH4(DATH,DATL);
	   }
	   else
	   {
		 ShowMessage("Устройство не подключено");
		 return 0;
	   }

	  }

 return RxDat;
}

 DWORDLONG __fastcall  TForm1::SendDATA_SPI_USB(DWORD DATH,DWORD DATL)
{
 DWORDLONG res=0;
 DWORD retDH;
 DWORD retDL;
 DWORD dwData, dwAddr, dwStatus;
 dwData=0;
 Form1->DeviceUSB->WriteDword(0,DATH);
 Application->ProcessMessages();
 Form1->DeviceUSB->WriteDword(1,DATL);
 Application->ProcessMessages();
 Form1->WaitSPI_Timer->Enabled=TRUE;
 Wait_SPI=FALSE;
 while((dwData && 0x80000000)==0) //wait rdy SPI
 {
  dwStatus=Form1->DeviceUSB->ReadDword(2,dwData);
  if(Wait_SPI)
  {
   ShowMessage("Таймаут SPI");break;
  }
  Application->ProcessMessages();
 }
 Form1->WaitSPI_Timer->Enabled=FALSE;
  res=0;
  dwStatus=Form1->DeviceUSB->ReadDword(0,retDH);
  Application->ProcessMessages();
  dwStatus=Form1->DeviceUSB->ReadDword(1,retDL);
  Application->ProcessMessages();
  //res=retDH;
  res=retDL;
  res=(res<<32)|retDH;
 return res;
}