//---------------------------------------------------------------------------

#include "DiapazonSearch.h"
#pragma hdrstop
#include "Adf4159.h"
#include "MFC1VK.h"

//---------------------------------------------------------------------------


MFC1VK::MFC1VK()
   {
	 Fget1 = 2300;
	 AdrMod = 0xD<<28;
	 AdrMod = Adress::OBSH;

	 UPR = 0;// Переключатель опорной частоты
	 NumDapazon = 10;//Номер диапазона
	 Nsys = 40;// Системный делитель
	 Sint1_HMC830 = new HMC830(2350,120,48,100);
	 Sint1_ADF4159 = new ADF4159(3500, 8, 39, 0, 100,0);
	 Sint1_ADF4002 = new ADF4002(2,7,1,100);
Polosa[12].DFv = 8186; Polosa[12].DNSys = 40;     //if (Fg4159<=8186){NumDapazon = 12;}     	12 Initfreq(Fg4159,0,1,2,40,1,1);
Polosa[12].DK1 = 0;   Polosa[12].DK2 = 1; Polosa[12].Dndel = 2;
Polosa[11].DFv = 7582; Polosa[11].DNSys = 40;		//if (Fg4159<=7582){NumDapazon = 11;} 11 Initfreq(Fg4159,1,1,3,40,1,1);
Polosa[11].DK1 = 1;   Polosa[11].DK2 = 1;Polosa[11].Dndel = 3;
Polosa[10].DFv = 7000; Polosa[10].DNSys = 40; 		//if (Fg4159<7000) {NumDapazon = 10;} 10 Initfreq(Fg4159,1,1,4,40,1,1);
Polosa[10].DK1 = 1;    Polosa[10].DK2 = 1; Polosa[10].Dndel = 4;
Polosa[9].DFv = 6700; Polosa[9].DNSys = 40; 		//if (Fg4159<6700) {NumDapazon = 9;}  9 Initfreq(Fg4159,1,1,5,40,1,1);
Polosa[9].DK1 = 1;    Polosa[9].DK2 = 1; Polosa[9].Dndel = 5;
Polosa[8].DFv = 6400; Polosa[8].DNSys = 40; 		//if (Fg4159<6400) {NumDapazon = 8;}  8 Initfreq(Fg4159,1,1,7,40,1,1);
Polosa[8].DK1 = 1;    Polosa[8].DK2 = 1; Polosa[8].Dndel = 7;
Polosa[7].DFv = 6050; Polosa[7].DNSys = 40; 		//if (Fg4159<6050) {NumDapazon = 7;}  7 Initfreq(Fg4159,0,1,8,40,1,1);
Polosa[7].DK1 = 0;    Polosa[7].DK2 = 1; Polosa[7].Dndel = 8;
Polosa[6].DFv = 5700; Polosa[6].DNSys = 40; 		//if (Fg4159<5700) {NumDapazon = 6;}  6 Initfreq(Fg4159,0,1,16,40,1,1);
Polosa[6].DK1 = 0;    Polosa[6].DK2 = 1; Polosa[6].Dndel = 16;
Polosa[5].DFv = 5335; Polosa[5].DNSys = 40; 		//if (Fg4159<5335) {NumDapazon = 5;}  5 Initfreq(Fg4159,0,0,16,40,1,1);
Polosa[5].DK1 = 0;    Polosa[5].DK2 = 0; Polosa[5].Dndel = 16;
Polosa[4].DFv = 4970; Polosa[4].DNSys = 40; 		//if (Fg4159<4970) {NumDapazon = 4;}  4 Initfreq(Fg4159,0,0,8,40,1,1);
Polosa[4].DK1 = 0;    Polosa[4].DK2 = 0; Polosa[4].Dndel = 8;
Polosa[3].DFv = 4650; Polosa[3].DNSys = 40;		//if (Fg4159<4650) {NumDapazon = 3;}  3 Initfreq(Fg4159,0,0,6,40,1,1);
Polosa[3].DK1 = 0;    Polosa[3].DK2 = 0; Polosa[3].Dndel = 6;
Polosa[2].DFv = 4550; Polosa[2].DNSys = 40; 		//if (Fg4159<4550) {NumDapazon = 2;}  2 Initfreq(Fg4159,0,0,5,40,1,1);
Polosa[2].DK1 = 0;    Polosa[2].DK2 = 0; Polosa[2].Dndel = 5;
Polosa[1].DFv = 4250; Polosa[1].DNSys = 40; 		//if (Fg4159<4250) {NumDapazon = 1;}  1 Initfreq(Fg4159,0,0,4,40,1,1);
Polosa[1].DK1 = 0;    Polosa[1].DK2 = 0; Polosa[1].Dndel = 4;  
}
MFC1VK::~MFC1VK()
{

}


struct Divider
{

	int DIV1 ;
	int S0 	 ;
	int N0 	 ; // TODO: структура делителя
	int N1 	 ;
	int N2 	 ;
	int BYP  ;

}D36,D45;
/**
 * [MFC1VK_Initfreq ]
 * @param  Freq [description]
 * @param  K1   [верхнее нижнее преобразование MIX1]
 * @param  K2   [верхнее нижнее преобразование MIX2]
 * @param  NDel [Делитель перед MIX2]
 * @param  SysN [Предустановка системного делителя 35,40,45]
 * @param  AR   [description]
 * @param  AN   [description]
 * @return      [Рассчитанная частота модуляции (HMC830)(Fz)]
 */

double MFC1VK::Initfreq(double Freq,int K1,int K2,double  NDel,int SysN,int AR,int AN)
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
	DivSet (Div);
					switch(Pr)
	{
		case 35:

		D45.S0 = 1;
		D45.N0 = 0;
		D45.N1 = 1;
		D45.N2 = 0;

		break;
		case 40:

		D45.S0 = 0;
		D45.N0 = 1;
		D45.N1 = 1;
		D45.N2 = 0;


		break;
		case 45:

		D45.S0 = 1;// TODO: Init freq
		D45.N0 = 1;
		D45.N1 = 1;
		D45.N2 = 0;

		break;
		case 50:

		D45.S0 = 0;
		D45.N0 = 0;
		D45.N1 = 0;
		D45.N2 = 1;

		break;

	}
	Fop = Freq* Pr*Div/(Pr*Div + Pr*Pol2 + Div*Pol1*Pol2);
	//Fopdiv = Fop/Div;
	FDIVocn = Fop/SysN; //Основа 5000+HMC830
	Fz = (Fop - 5000)*2;

	/************************************************************/
	if (Pol1*Pol2>0) { ADPOL = 0; }
	else {ADPOL = 1;	}


	/************************************************************/

	return Fz;//Рассчитанная частота модуляции (HMC830)

}

int MFC1VK::SetNsys(int N)
	{/*----------  Процедура SetNsys ----------*/
	
		if (N == 40)
		{
			Nsys = 40;
		}
		 else
		{	if (N == 45)
			{
				Nsys = 45;
			}
			else
			{ 	if(N == 50) 
				{
				Nsys = 50;
				}
				else 
				{
				Nsys = 35;
				}
				
			}
		}
		return Nsys;
	}
/**
 * [SetFreq рассчет]
 * @param  Fg4159 [Частота настройки]
 * @param  fget   [Предустановка частота модуляции (HMC830)]
 * @param  Fas1   [Ключ1]
 * @param  Fas2   [Ключ2]
 * @param  SysN   [Предустановка системного делителя 35,40,45]
 * @return        [Рассчитанная частота модуляции (HMC830)]
 */
double MFC1VK::SetFreq(double Fg4159,double fget,int Fas1,int Log)
	{
		F830 = fget;
		Fget1 = Fg4159/2;




	   //	NumDapazon = Form6->Massive->binary_search(Fg4159,0,511);
//			for (int i = 12; i > 0; --i)
//		{
//			if (Fg4159<Polosa[i].DFv) NumDapazon = i;
//		}

		NumDapazon = Form6->Massive->binary_search(Fget1,0,511);      /* TODO -oУстановка частоты -c1 : Выбор из массива */

					if (Log)
	  {
	   //		Initfreq(Fg4159,Polosa[NumDapazon].DK1,Polosa[NumDapazon].DK2,Polosa[NumDapazon].Dndel,Polosa[NumDapazon].DNSys,1,1);

	   Initfreq(Fg4159,Form6->Massive->Polosa[NumDapazon].DK1,Form6->Massive->Polosa[NumDapazon].DK2,Form6->Massive->Polosa[NumDapazon].Dndel,Form6->Massive->Polosa[NumDapazon].DNSys,Form6->Massive->Polosa[NumDapazon].Fil,1);
       // Initfreq(double Freq,int K1,int K2,double  NDel,int SysN,int AR,int AN)
	  }
	 //UPR = Fas1;Управление фильтром пин 41
//	  if(Fz>500) { 	UPR = 0;   }
//	  else {	  	UPR = 1;  }

			UPR = Form6->Massive->Polosa[NumDapazon].Fil;

		Sint1_HMC830->SetFreq(Fz);
		Sint1_ADF4159->SetFreq(Fg4159,(Fop/Nsys),false); // Fop = 0
		Sint1_ADF4002->ParamSET(ADPOL,8,1,1);//8 - CP-> TryState
		//Sint1_ADF4002->ParamSET();
		return  Fz;
	}



int MFC1VK::Kluch(int Num)
   {
	 switch(Num)
	 {	case 0:
		return  AdrMod|0x4<<24|0x16<<16|D45.S0<<10|D45.N0<<9|D45.N1<<8|D45.N2<<7|UPR<<6|D36.DIV1<<5|D36.S0<<4|D36.N0<<3|D36.N1<<2|D36.N2<<1|D36.BYP ;
		break;
		case 1:
		return  AdrMod|0x4<<24|0x14<<16;
		break;
	 }
   }
void MFC1VK::SetKLUCH(int UPRL,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP)
   {/*----------  Процедура SetKLUCH  ----------*/
   
	 UPR = UPRL;
	 D36.DIV1 = PDIV1;
	 D36.S0 = PS0;
	 D36.N0 = PN0;
	 D36.N1 = PN1;
	 D36.N2 = PN2;
	 D36.BYP = PBYP;
   }
   /*=============================================
   =            Section  DivSet                 =
   =============================================*/
void MFC1VK::DivSet (int Div)
  {
		switch(Div)
	 {
		 case 1:
		 SetKLUCH(1,0,0,0,0,0,1);
		 break;
		 case 2:
		 SetKLUCH(1,1,0,0,0,0,0);
		 break;
		 case 3:
		 SetKLUCH(1,1,1,0,0,0,0);
		 break;
		 case 4:
		 SetKLUCH(1,0,0,1,0,0,0);
		 break;
		 case 5:
		 SetKLUCH(1,0,1,1,0,0,0);
		 break;
		 case 6:
		 SetKLUCH(1,0,0,0,1,0,0);//Установка DIV1_16
		 break;
		 case 7:
		 SetKLUCH(1,0,1,0,1,0,0);
		 break;
	 	 case 8:
		 SetKLUCH(1,0,0,1,1,0,0);
		 break;
		 case 9:
		 SetKLUCH(1,0,1,1,1,0,0);
		 break;
		 case 10:
		 SetKLUCH(1,0,0,0,0,1,0);
		 break;
		 case 11:
		 SetKLUCH(1,0,1,0,0,1,0);
		 break;
		 case 12:
		 SetKLUCH(1,0,0,1,0,1,0);
		 break;
		 case 13:
		 SetKLUCH(1,0,1,1,0,1,0);
		 break;
		 case 14:
		 SetKLUCH(1,0,0,0,1,1,0);
		 break;
		 case 15:
		 SetKLUCH(1,0,1,0,1,1,0);
		 break;
		 case 16:
		 SetKLUCH(1,0,0,1,1,1,0);
		 break;
		 case 17:
		 SetKLUCH(1,0,1,1,1,1,0);
		 break;

	 }
   }
   /*=====  End of Section comment block  ======*/
   

 void MFC1VK::AdrSet(int JGUT)
{
	switch(JGUT)
	{
		case 0:

		AdrMod = Adress::MFC1;
		break;
		case 1:
		AdrMod = Adress::OBSH;
		break;
		default:AdrMod = (JGUT - 2)<<28;break;

	}
}
   
long MFC1VK::SintLOAD_L(int dev,int Poz)
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

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 2:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 3:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 4:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 5:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 6:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 7:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 8:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 9:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;

				 case 10:

				 SW_SW = Sint1_ADF4159->RegLoad4159(i);break;





				 default : SW_SW = Sint1_ADF4159->RegLoad4159(0);break;

			   } 	break;

			 case 2:  /*	TODO: прогрузка ADF4002 */

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint1_ADF4002->RegLoad4002(i);break;

				 case 1:

				 SW_SW = Sint1_ADF4002->RegLoad4002(i);break;

				 case 2:

				 SW_SW = Sint1_ADF4002->RegLoad4002(i);break;

				 case 3:

				 SW_SW = Sint1_ADF4002->RegLoad4002(i);break;

				 default : SW_SW = Sint1_ADF4002->RegLoad4002(0);break;

			   } 	break;

			case 3:   /*	TODO: прогрузка HMC830 */

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 1:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 2:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 3:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 4:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 5:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 6:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 7:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 8:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 9:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 10:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 11:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				  case 12:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 13:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 14:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;

				 case 15:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
				 case 16:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
				 case 17:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
				 case 18:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;
                 case 19:

				 SW_SW = Sint1_HMC830->RegLoad830(i);break;



				 default : SW_SW = Sint1_HMC830->RegLoad830(0);break;

			   }  		  SW_SW = SW_SW <<1;		 	break;

		}

	return  SW_SW;

   }
/***********************************************************************************/
long MFC1VK::SintLOAD_H(int dev)
   {
	switch(dev)
		{   case 1:
			return  AdrMod|MFC1VK::AdrDev::PLL1<<24;
			break;
			case 2:
			return  AdrMod|MFC1VK::AdrDev::PLL2<<24;
			break;
			case 3:
			return  AdrMod|MFC1VK::AdrDev::PLL3<<24;
			break;
			default: return  AdrMod|MFC1VK::AdrDev::PLL3<<24;
		}
   }
#pragma package(smart_init)
