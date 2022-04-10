//---------------------------------------------------------------------------


#pragma hdrstop
#include "Adf4159.h"
#include "MFC2DG.h"

//---------------------------------------------------------------------------


MFC2DG::MFC2DG()
{
	Fget2 = 2300;
	AdrMod = 0xD<<28;
    	AdrMod = Adress::OBSH;
	UPR = 0;// Переключатель опорной частоты
	PCH1 = 1;//Номер диапазона
	Nsys = 12;// Системный делитель
	Sint2_HMC830 = new HMC830(2350,120,48,100);
	Sint2_ADF4159 = new ADF4159(3500, 3, 39, 0, 100,0);
	Sint2_ADF4002 	= new ADF4002(2,4,1,100); //PLL основной петли adr 0X8
	Sint2_ADF4002->ParamSET(1,8,1,2);
	Sint22_ADF4002 	= new ADF4002(0,2,1,100); //PLL 1ГГц петли adr 0XB
											  //(int I, int PN, bool Pol_PUS, double Ref);
	Sint22_ADF4002->ParamSET(1,3,10,20);       // ParamSET(int Pol, int Cur,int Rdiv, int Ndiv);
	Sint100_ADF4002 = new ADF4002(1,10,1,10);//PLL 100 мГц петли adr 0XA
    Sint100_ADF4002->ParamSET(1,3,1,10);

	Polosa[3].DFv = 4375;Polosa[3].DF830 = 1025.6410256410254; Polosa[3].DNSys = 8; //if (Fg4159==875) {NumDapazon = 3;}  3 Initfreq(Fg4159,0,0,6,40,1,1);
	Polosa[3].DK1 = 1;     Polosa[3].DNDel = 1;Polosa[3].DNOut = 5;
	Polosa[3].DFref = 112.1794872;//78;
	Polosa[2].DFv = 4700;Polosa[2].DF830 = 829.2682926829275; Polosa[2].DNSys = 8; //if (Fg4159==1175) {NumDapazon = 2;}  2 Initfreq(Fg4159,0,0,5,40,1,1);
	Polosa[2].DK1 = 0;     Polosa[2].DNDel = 1;Polosa[2].DNOut = 4;
	Polosa[2].DFref = 114.63425;//;  82

	Polosa[1].DFv = 4600;Polosa[1].DF830 = 1000; Polosa[1].DNSys = 9; //if (Fg4159==2300) {NumDapazon = 1;}  1 Initfreq(Fg4159,0,0,4,40,1,1);
	Polosa[1].DK1 = 0;     Polosa[1].DNDel = 1;Polosa[1].DNOut = 2;
	Polosa[1].DFref = 100;//112.195;


//	Polosa[1].DFv = 4600;Polosa[1].DF830 = 1024.3902439024387; Polosa[1].DNSys = 8; //if (Fg4159==2300) {NumDapazon = 1;}  1 Initfreq(Fg4159,0,0,4,40,1,1);
//	Polosa[1].DK1 = 0;     Polosa[1].DNDel = 1;Polosa[1].DNOut = 2;
//	Polosa[1].DFref = 112.195;

}
MFC2DG::~MFC2DG()
{

}




/**
 * [MFC2DG_Initfreq ]
 * @param  Freq [description]
 * @param  K1   [верхнее нижнее преобразование MIX1]
 * @param  K2   [верхнее нижнее преобразование MIX2]
 * @param  NDel [Делитель перед MIX2]
 * @param  SysN [Предустановка системного делителя 35,40,45]
 * @param  AR   [description]
 * @param  AN   [description]
 * @return      [Рассчитанная частота модуляции (HMC830)(Fz)]
 */

double MFC2DG::Initfreq(double Freq,int K1,int K2,double  NDel,int SysN,int AR,int AN)
{    switch(K1)
	  {   case 0:
		  Pol1 = -1;
		  break;
		  case 1:
		  Pol1 = 1;
		  break;  // TODO: Установка направления преобр MIX
	  }
	  switch(K2)
	  {   case 0:
		  Pol2 = -1;
		  break;
		  case 1:
		  Pol2 = 1;
		  break;
	  }

	Div= NDel; // TODO: Делитель перед MIX2
	Pr = SysN; // Делитель основы 35,40,45
	Nsys = SysN; // Делитель основы 35,40,45,50

	Fop = Freq* Pr*Div/(Pr*Div + Pr*Pol2 + Div*Pol1*Pol2);
	//Fopdiv = Fop/Div;
	FDIVocn = Fop/SysN; //Основа 5000+HMC830
	Fz = (Fop - 5000)*2;
	if (Pol1*Pol2>0) { ADPOL = 0; }
	else {ADPOL = 1;	}
	return Fz;//Рассчитанная частота модуляции (HMC830)

}


/**
 * [SetFreq рассчет]
 * @param  Fg4159 [Частота настройки]
 * @param  Fas1   [UPR опора внутр внеш]
 * @return        [Рассчитанная частота модуляции (HMC830)]
 */
double MFC2DG::SetFreq(double Fg4159,int Fas1,int Log)
	{
/**
*4800		12	2	200	4600	4600	2300	2	4500	4800
*4800		12	4	100	4700	4700	1175	4
*4605		10	2	230,25	4374,75	4375	875	5
*4605,263158	10	2	230,2631579	4375
*
*/
		
		if(Fg4159>2298 && Fg4159<2302)
	{
		PCH1 = 1;
		Fget2 = Fg4159;
	}
		else
	{
			if(Fg4159>1173 && Fg4159<1177)
		{
			PCH1 = 2;
		}
			else
		{
					if(Fg4159>873 && Fg4159<878)
			{
				PCH1 = 3;
			}
				else
			{
				PCH1 = 1;
			}
		}
	}
		Fget2 = Fg4159;
		//F830 = fget;
		Fz = Polosa[PCH1].DF830;
		Nsys = Polosa[PCH1].DNSys;
		UPR = Fas1;



					if (Log)
	  {
	   //	Initfreq(Fg4159,Polosa[NumDapazon].DK1,Polosa[NumDapazon].DK2,Polosa[NumDapazon].DNDel,Polosa[NumDapazon].DNSys,1,1);
	  }
	//		 Sint2_HMC830->SetFreq(Fg4159);
		Sint2_HMC830->SetFreq(Polosa[PCH1].DF830);

		DivSet(&D55,Polosa[PCH1].DNSys);

		Sint2_ADF4159->SetFreq(Polosa[PCH1].DFv,Polosa[PCH1].DFref,false);
		//Sint2_ADF4159->NRSEt4159(2,Polosa[PCH1].DFref,0,0); //   NRSEt4159(int PR,int PN,int PNF, int PREs)
		Sint2_ADF4002->ParamSET(Polosa[PCH1].DK1,8,1,1);  //8 - CP-> TryState
		DivSet(&D56,Polosa[PCH1].DNOut);
		return  Fz;
	}

void MFC2DG::OGvnutr(OG)
{
	if(OG) 
	{
		UPR = 0;
		
	}
	else 
	{

		UPR = 1;
		

	}
}
void MFC2DG::AdrSet(int JGUT)
{
	switch(JGUT)
	{
		case 0:
		AdrMod = Adress::MFC2;
		break;
		case 1:
		AdrMod = Adress::OBSH;
		break;
		case 2:
		AdrMod = 1<<28;
		break;
	}
}
int MFC2DG::Kluch(int Num)
   {
	 switch(Num)
	 {	case 0:
		return  AdrMod|0x4<<24|0x16<<16|D55.N2<<10|D55.N1<<9|D55.N0<<8|D55.S0<<7|UPR<<6|D56.DIV1<<5|D56.S0<<4|D56.N0<<3|D56.N1<<2|D56.N2<<1|D56.BYP ;
		break;
		case 1:
		return  AdrMod|0x4<<24|0x14<<16;
		break;
		case 2:
		return  AdrMod|0x4<<24|0x14<<16|1 ;
		break;
	 }
   }
void MFC2DG::SetKLUCH(struct Divider *DXX,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP)
   {/*----------  Процедура SetKLUCH  ----------*/
   
	// UPR = UPRL;
	 DXX->DIV1 = PDIV1;
	 DXX->S0 = PS0;
	 DXX->N0 = PN0;
	 DXX->N1 = PN1;
	 DXX->N2 = PN2;
	 DXX->BYP = PBYP;
   }
   /*=============================================
   =            Section  DivSet                 =
   =============================================*/
void MFC2DG::DivSet (struct Divider *DXX,int Div)
  {               /*HMC705SET*/
		switch(Div) // В МФЧ1 нумерация сдвинута н -1
	 {
		 case 1:
		 SetKLUCH(DXX,0,0,0,0,0,1);
		 break;
		 case 2:
		 SetKLUCH(DXX,1,0,0,0,0,0);
		 break;
		 case 3:
		 SetKLUCH(DXX,1,1,0,0,0,0);
		 break;
		 case 4:
		 SetKLUCH(DXX,0,0,1,0,0,0);
		 break;
		 case 5:
		 SetKLUCH(DXX,0,1,1,0,0,0);
		 break;
		 case 6:
		 SetKLUCH(DXX,0,0,0,1,0,0);//Установка DIV1_16
		 break;
		 case 7:
		 SetKLUCH(DXX,0,1,0,1,0,0);
		 break;

		 case 8:
		 SetKLUCH(DXX,0,0,1,1,0,0);
		 break;
		 case 9:
		 SetKLUCH(DXX,0,1,1,1,0,0);
		 break;
		 case 10:
		 SetKLUCH(DXX,0,0,0,0,1,0);
		 break;
		 case 11:
		 SetKLUCH(DXX,0,1,0,0,1,0);
		 break;
		 case 12:
		 SetKLUCH(DXX,0,0,1,0,1,0);
		 break;
		 case 13:
		 SetKLUCH(DXX,0,1,1,0,1,0);
		 break;
		 case 14:
		 SetKLUCH(DXX,0,0,0,1,1,0);
		 break;
		 case 15:
		 SetKLUCH(DXX,0,1,0,1,1,0);
		 break;
		 case 16:
		 SetKLUCH(DXX,0,0,1,1,1,0);
		 break;
		 case 17:
		 SetKLUCH(DXX,0,1,1,1,1,0);
		 break;

	 }
   }
   /*=====  End of Section comment block  ======*/
   


   
long MFC2DG::SintLOAD_L(int dev,int Poz)
/*---------- Subsection SintLOAD_L  ----------*/

   {  int i;
			if (Poz>=0)
	  {  i = Poz;
	  }
		 long  SW_SW;

		switch(dev)
		{   case 1:  /*	TODO: прогрузка ADF4159 */
		

					switch (i)
			   {

				 case 1:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 2:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 3:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 4:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 5:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 6:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 7:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 8:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 9:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;

				 case 10:

				 SW_SW = Sint2_ADF4159->RegLoad4159(i);break;





				 default : SW_SW = Sint2_ADF4159->RegLoad4159(0);break;

			   } 	break;

			 case 2:  /*	TODO: прогрузка ADF4002 */

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint2_ADF4002->RegLoad4002(i);break;

				 case 1:

				 SW_SW = Sint2_ADF4002->RegLoad4002(i);break;

				 case 2:

				 SW_SW = Sint2_ADF4002->RegLoad4002(i);break;

				 case 3:

				 SW_SW = Sint2_ADF4002->RegLoad4002(i);break;

				 default : SW_SW = Sint2_ADF4002->RegLoad4002(0);break;

			   } 	break;

			case 3:   /*	TODO: прогрузка HMC830 */

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 1:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 2:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 3:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 4:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 5:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 6:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 7:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 8:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 9:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 10:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 11:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				  case 12:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 13:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 14:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;

				 case 15:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;
				 case 16:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;
				 case 17:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;
				 case 18:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;
                 case 19:

				 SW_SW = Sint2_HMC830->RegLoad830(i);break;



				 default : SW_SW = Sint2_HMC830->RegLoad830(0);break;

			   }    SW_SW = SW_SW <<1;	 	break;
			   	case 4:  /*	TODO: прогрузка ADF4002 PLL 1ГГц*/

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint22_ADF4002->RegLoad4002(i);break;

				 case 1:

				 SW_SW = Sint22_ADF4002->RegLoad4002(i);break;

				 case 2:

				 SW_SW = Sint22_ADF4002->RegLoad4002(i);break;

				 case 3:

				 SW_SW = Sint22_ADF4002->RegLoad4002(i);break;

				 default : SW_SW = Sint22_ADF4002->RegLoad4002(0);break;

			   }      	break;
				case 5:  /*	TODO: прогрузка ADF4002 PLL 100 МГц*/

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint100_ADF4002->RegLoad4002(i);break;

				 case 1:

				 SW_SW = Sint100_ADF4002->RegLoad4002(i);break;

				 case 2:

				 SW_SW = Sint100_ADF4002->RegLoad4002(i);break;

				 case 3:

				 SW_SW = Sint100_ADF4002->RegLoad4002(i);break;

				 default : SW_SW = Sint100_ADF4002->RegLoad4002(0);break;

			   }    	 	break;

		}

	return  SW_SW;

   }
/***********************************************************************************/
long MFC2DG::SintLOAD_H(int dev)
   {
	switch(dev)
		{   case 1:
			return  AdrMod|MFC2DG::AdrDev::PLL1<<24;
			break;
			case 2:
			return  AdrMod|MFC2DG::AdrDev::PLL2<<24;
			break;
			case 3:
			return  AdrMod|MFC2DG::AdrDev::PLL3<<24;
			break;
			case 4:
			return  AdrMod|MFC2DG::AdrDev::PLL4<<24;
			break;
			case 5:
			return  AdrMod|MFC2DG::AdrDev::PLL5<<24;
			break;
			default: return  AdrMod|MFC2DG::AdrDev::PLL3<<24;
		}
   }
#pragma package(smart_init)
