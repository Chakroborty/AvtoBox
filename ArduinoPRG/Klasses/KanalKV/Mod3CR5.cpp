//---------------------------------------------------------------------------


#pragma hdrstop
#include <math.h>
#include "Mod3CR5.h"

//---------------------------------------------------------------------------
  Mod3CR5::Mod3CR5(int ADR, bool isp05)
 {

   SintKV  = new ADF4153(2500,0,80,false,10,0.2,1); //ADF4153(double F, int I, int N, bool Pol_PLUS,
													// double Ref,double ssHag,int Dabl)

  BWIF = 0; // – бит управления полосой пропускания ПЧ:
  HTDN = 0;//  - бит управления гетеродином:
  REFG = 1; //– бит управления опорным генератором:
  CLBR = 0;// – бит управления входами прием и калибровка:
  PrFVC = FVC::OTKL;
  NG = NG_ATT::GS_OTKL;
  ATTvhod = ATT_Pres::Att_0;
	if (ADR >= 0&&ADR < 16)
	{
	  AdresMod = ADR;
	}
	else
	{
	  AdresMod = 16;
	}
		if (isp05)
	{
		HTDN = 0; //- бит управления гетеродином:  0 внутр
		REFG = 1; //– бит управления опорным генератором:  0 внутр
		FHift =28;
	}
	else
	{
		HTDN = 1;
		REFG = 0;
		FHift = 27;
	}
 }
  Mod3CR5::~Mod3CR5()
  {

  }
void Mod3CR5::SetFriq(double Fset, int Kanal)
{      	if ( Kanal >= 0&& Kanal < 16)
	{
	  AdresMod =  Kanal;
	}


	if (Fset >= 1.5 && Fset <= 32)
	{
		 Fin = Fset*100;
		 Fin = floor(Fin);
		 Fin = 0.01*Fin;
	}
	else
	{
		 Fin = 15;
	}
	Fget = 20*(Fin + 70);
	SintKV->SetFreq(Fget);

}
int Mod3CR5::Load_sint(int tip)
{
	return  AdresMod<<FHift|Komanda::Sinz<<24|SintKV->RegLoad4153(tip);

}
/*********************************************************************************/
void  Mod3CR5::SetATT_UPC(double Db)
{   if (Db>=0&&Db<=31.5)
	 {
		 Att_UPC = 0.5*float(0.5+Att_UPC/0.5);
		 Att_UPC = 2*Db;
	 } else
	 {
		Att_UPC = 30;
	 }

}
int Mod3CR5::LoadATT_UPC(void)
{
	return  AdresMod<<FHift|Komanda::AT_UPC<<24|Att_UPC<<18;
}
/*********************************************************************************/
void Mod3CR5::SetAmpl_UPC(int Ampl)
{       if (Ampl>=0 && Ampl<255)
	{
		AMPL_UPC = Ampl;
	} else
	{
		AMPL_UPC = 254;
	}

}
int Mod3CR5::LoadAmpl_UPC(void)
{
	return   AdresMod<<FHift|Komanda::Amp_UPC<<24|AMPL_UPC<<16;
}
/*********************************************************************************/
void  Mod3CR5::SetFVC(int Fset)
{
if (Fset==0)
{
	PrFVC = FVC::OTKL;
}
else
{
	if (Fset==8)
	{
	  PrFVC = FVC::FV8;
	} else
	{
		 if (Fset==15)
		 {
			PrFVC = FVC::FVl5;
		 } else
		 {
			PrFVC = FVC::OTKL;
		 }
	}
}

}
void  Mod3CR5::SetPC(bool PC40)
{
	if (PC40)
	{
	  BWIF = 1;
	} else
	{
	  BWIF = 0;
	}

}
void  Mod3CR5::SetATT_Pres(int Db)
{
	if (Db==0)
	{
	 ATTvhod = ATT_Pres::Att_0;
	}
	else
 {
	if (Db==10)
	{
	  ATTvhod = ATT_Pres::Att_M10;
	} else
	{
		 if (Db==20)
		 {
			ATTvhod = ATT_Pres::Att_M20;
		 } else
		 {
			if (Db==30)
			{
				ATTvhod = ATT_Pres::Att_M30;
			} else
			{
				 if (Db==15)
				{
				   ATTvhod = ATT_Pres::Att_PL10;
				} else
				{
                   ATTvhod = ATT_Pres::Att_0;
				}
			}
		 }
	}
 }

}
void  Mod3CR5::SetVX(bool Priem,int DB )
{if (Priem)
	{
	  CLBR = 0;
	  NG = NG_ATT::GS_OTKL;
	} else
	{  CLBR = 1;
	 		
			if (DB==0)
	 { CLBR = NG_ATT::AttN_0;

	 } else
	 { if (DB==10)
		{ CLBR = NG_ATT::AttN_M10;
		}
	   else
		{ if (DB==20)
			{ CLBR = NG_ATT::AttN_M20;
			}
		 else
			{ if (DB==30)
				{ CLBR = NG_ATT::AttN_M30;
				}
			   else
			   {  CLBR = 0;
				NG = NG_ATT::GS_OTKL;
			   }
			}
		 }
	  }
	}
}
int Mod3CR5::LoadKL()
{
 return AdresMod<<FHift|Komanda::Kluc<<24|BWIF<<23|HTDN<<22|REFG<<21|PrFVC<<18|ATTvhod<<13|CLBR<<12|NG<<9;
  /**
 * Было 1<<24|AdresMod<<20|Komanda::Kluc<<16|BWIF<<15|HTDN<<14|REFG<<13|PrFVC<<10|ATTvhod<<5|CLBR<<4|NG<<1;  //pData[1] = (FASTLOCK << 7 | Synt_INT >> 2) & 0xFF;
* #define OTHER_MODE 3 
 * pData[0] = 1;
 * pData[1] = ReceiverNumber<<3 | OTHER_MODE;         //
 *
 * pData[2] = (( SpeedButton5 ->Down ? 0x20:0 ) |     // ОГ
 *             ( SpeedButton1 ->Down ? 0x40:0 ) |     // Гетеродин
 *             ( SpeedButton13->Down ? 0x80:0 ) |     // Полоса ПЧ
 *               RFAMP[ComboBox1->ItemIndex]<<2 |     // ФВЧ
 *             ( ATT[ComboBox2->ItemIndex] & 0x18) >>3 ) & 0xFF;
 *
 * pData[3] = (ComboBox6->ItemIndex == 1 ? 2:0) |     // ГШ
 *             (ComboBox6->ItemIndex == 2 ? 10:0)|    // -"-
 *             (ComboBox6->ItemIndex == 3 ? 6:0) |    // -"-
 *             (ComboBox6->ItemIndex == 4 ? 14:0)|    // -"-
 *            ((SpeedButton2 ->Down ? 1:0 ) << 4)|    // Прием/калибр
 *             (ATT[ComboBox2->ItemIndex]<<5);        // Аттенюатор;
 * ReadWritePipe(pData,OutPipe,dwSize,WRITE);
 *	//  WriteAndCheck(pData,OutPipe,dwSize,WRITE);
 *
 */



}

#pragma package(smart_init)
