//---------------------------------------------------------------------------


#pragma hdrstop
#include "Adf4159.h"
#include "MFCGDG.h"

//---------------------------------------------------------------------------


MFCG::MFCG()
{
		Fget1 = 2300;
		AdrMod = 0xD<<28;
		ATTSW = 0X1F;//Аттенюатор выходной
		UPR4 = 1;// CE ADF4159_1
		UPR1 = 1;// CE ADF4159_1
		CED18 = 1;
		CED86 = 1;
		NumDapazon = 10;//Номер диапазона
		Nsys = 40;// Системный делитель
		Sint1_HMC830 = new HMC830(2350,120,48,100);
		Sint2_ADF4159 = new ADF4159(3500, 3, 60, 0, 100,0);  //ADF4159(double F, int I, int N, bool Pol_PUS, double Ref,int Dabl);
		//Sint2_ADF4159->NRSEt4159(4,64,0);
		Sint2_ADF4002 = new ADF4002(2,7,1,100);
		Sint1_ADF4159 = new ADF4159(3500, 15, 39, 0, 100,0);
		Sint1_ADF4002 = new ADF4002(2,7,1,100);
		Sint1000_ADF4002 = new ADF4002(0,2,1,100); //PLL 1ГГц петли adr 0XB  ADF4002(int I, int PN, bool Pol_PUS, double Ref);
		Sint1000_ADF4002->ParamSET(1,3,10,20);     //ParamSET(int Pol, int Cur,int Rdiv, int Ndiv)
		//Sint1000_ADF4002->ParamSET(1,3,2,4);
		Sint100_ADF4002 = new ADF4002(1,10,1,10);//PLL 100 мГц петли adr 0XA
		Sint100_ADF4002->ParamSET(1,3,1,10);

}
MFCG::~MFCG()
{

}



double MFCG::Initfreq(double Freq,double K1,double K2,double K3,double K4,double  NDel,int SysN,int AR,int AN)
{            /*План_МФЧГ*/
 


/*====================  Лишние переменные  =================================*/


/*====================  End Лишние переменные ==============================*/





	Div= NDel; // TODO: Делитель перед MIX2
	Pr = SysN; // Делитель основы 35,40,45
	Nsys = SysN; // Делитель основы 35,40,45,50
					switch(Pr)
	{
		case 35:

		D67.S0 = 1;
		D67.N0 = 0;
		D67.N1 = 1;
		D67.N2 = 0;

		break;
		case 40:

		D67.S0 = 0;
		D67.N0 = 1;
		D67.N1 = 1;
		D67.N2 = 0;


		break;
		case 45:

		D67.S0 = 1;// TODO: Init freq
		D67.N0 = 1;
		D67.N1 = 1;
		D67.N2 = 0;

		break;
		case 50:

		D67.S0 = 0;
		D67.N0 = 0;
		D67.N1 = 0;
		D67.N2 = 1;

		break;

	}
	//Fop = Freq* Pr*Div/(Pr*Div + Pr*Pol2 + Div*Pol1*Pol2);
	F3 = Freq/(3 + K2/Div + K1*K2/40); // F3 = Freq/(3 + K2/Div + K1*K2/40);

	F2 = F3/(1+K3/(5*PolosaFCG[NumDapazon].DN45));   // F2 = F3/(1+K3/40);
	F1 = (F2*2/K4) - (K4*10000);
	Fz = F1;
				/*Установка фильтра Z D117_108*/
					switch(PolosaFCG[NumDapazon].DK4P)
   {  case 0:if(F2>4660)
	 {
			SetD117(4);//4660-4805
			ZZ = 3;
	 }
	 else
	 {
			SetD117(2);//4500-4660
			 ZZ = 1;
	 }
				 
	  break;

	  case 1:if(F2>5250)
	 { 		
			SetD117(3);//5250-5500
			ZZ = 2;
	 }
	 else
	 {
	 		SetD117(1);//5110-5250
			ZZ = 0;
	 }
				
	  break;
   }

DivSet(PolosaFCG[NumDapazon].DN45);
SDivSet(&D67, PolosaFCG[NumDapazon].Dndel);
	//Fopdiv = Fop/Div;
	//FDIVocn = Fop/SysN; //Основа 5000+HMC830
	//Fz = (Fop - 5000)*2;
	//ADPOL = 0;
	return Fz;//Рассчитанная частота модуляции (HMC830)

}
void MFCG::OGvnutr(OG)
{
	if(OG) 
	{
		UPR1 = 0;
		
	}
	else 
	{

		UPR1 = 1;
		

	}
}
int MFCG::SetNsys(int N)
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
double InitfreqOP(double Freq,int K1,int K2,double  NDel,int Ocn,int AR,int AN)
	{/* План1 */
	

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
double MFCG::SetFreq(double Fg4159,double fget,int Fas1,int Log)
	{
		if(Fg4159>=10000) 
		{
			FS = Fg4159;
			UPR4 = 0;

		}
		else
		{
			FS = Fg4159*2;
			UPR4 = 1;
		}

		Fget1 =  Fg4159/(1+Fas1);

		NumDapazon = binary_searchFCHG(FS,0,16);

					if (Log)
	  {
		Initfreq(FS,PolosaFCG[NumDapazon].DK1,PolosaFCG[NumDapazon].DK2,PolosaFCG[NumDapazon].DK3,PolosaFCG[NumDapazon].DK4,PolosaFCG[NumDapazon].Dndel,PolosaFCG[NumDapazon].Dndel,1,1);
	  }
	  	UPR4 = Fas1;
        Pol1 = PolosaFCG[NumDapazon].DK12P;
		Pol2 = PolosaFCG[NumDapazon].DK3P;
		Sint1_HMC830->SetFreq(Fz);
		//Sint1_ADF4159->NRSEt4159(2,PolosaFCG[NumDapazon].DN18*2,0);
		Sint1_ADF4159->SetFreq(F3,(F2/(5*PolosaFCG[NumDapazon].DN45)),false); // Sint1_ADF4159->SetFreq(F3,(F2/40),false);

		Sint1_ADF4002->ParamSET(PolosaFCG[NumDapazon].DK3P,1,1,1); //ParamSET(int Pol, int Cur,int Rdiv, int Ndiv);
		////  ADF4002_1  внутр
		Sint2_ADF4159->SetFreq(FS/4,(F3/40),false);//Установка F ADF4159_2

		Sint2_ADF4002->ParamSET(PolosaFCG[NumDapazon].DK12P,1,1,1);    //  ADF4002_2  посл
		return  Fz;
	}

int MFCG::SetD117(int Num)
{
					switch(Num)
   {
		case 1:D117108 = HMC345::BA4<<2|HMC345::BA1; break;//B11//B00  5110-5250
		case 2:D117108 = HMC345::BA3<<2|HMC345::BA2;  break;//B01//B10 4500-4660
		case 3:D117108 = HMC345::BA2<<2|HMC345::BA3;  break;//B10//B01 5250-5500
		case 4:D117108 = HMC345::BA1<<2|HMC345::BA4;  break;//B00//B11 4660-4805
   }
		return D117108;
}

int MFCG::Kluch(int Num)
   {
	 switch(Num)
	 {	case 0:
		return  AdrMod|0x4<<24|0x16<<16|D45.S0<<15|D45.N0<<14|D45.N1<<13|D45.N2<<12|D117108<<8|UPR4<<7|UPR1<<6|D67.DIV1<<5|D67.S0<<4|D67.N0<<3|D67.N1<<2|D67.N2<<1|D67.BYP ;
		break;
		case 1:
		return  AdrMod|0x4<<24|0x14<<16|CED18;
		break;
		case 2:
		return  AdrMod|0x4<<24|0x13<<16|CED86;
		break;
		case 3:
		return  AdrMod|0x4<<24|0x12<<16|ATTSW;
		break;
	 }
   }
void MFCG::SetKLUCH(int UPRL,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP)
   {/*----------  Процедура SetKLUCH  ----------*/
   
	 UPR4 = UPRL;
	 D45.DIV1 = PDIV1;
	 D45.S0 = PS0;
	 D45.N0 = PN0;
	 D45.N1 = PN1;
	 D45.N2 = PN2;
	 D45.BYP = PBYP;

   }
void MFCG::SSetKLUCH(struct Divider *DXX,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP)
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
void MFCG::DivSet (int Div)
  {
		switch(Div-1)
	 {
		 case 0:
		 SetKLUCH(1,0,0,0,0,0,1);
		 break;
		 case 1:
		 SetKLUCH(1,1,0,0,0,0,0);
		 break;
		 case 2:
		 SetKLUCH(1,1,1,0,0,0,0);
		 break;
		 case 3:
		 SetKLUCH(1,0,0,1,0,0,0);
		 break;
		 case 4:
		 SetKLUCH(1,0,1,1,0,0,0);
		 break;
		 case 5:
		 SetKLUCH(1,0,0,0,1,0,0);//Установка DIV1_16
		 break;
		 case 6:
		 SetKLUCH(1,0,1,0,1,0,0);
		 break;

		 case 7:
		 SetKLUCH(1,0,0,1,1,0,0);
		 break;
		 case 8:
		 SetKLUCH(1,0,1,1,1,0,0);
		 break;
		 case 9:
		 SetKLUCH(1,0,0,0,0,1,0);
		 break;
		 case 10:
		 SetKLUCH(1,0,1,0,0,1,0);
		 break;
		 case 11:
		 SetKLUCH(1,0,0,1,0,1,0);
		 break;
		 case 12:
		 SetKLUCH(1,0,1,1,0,1,0);
		 break;
		 case 13:
		 SetKLUCH(1,0,0,0,1,1,0);
		 break;
		 case 14:
		 SetKLUCH(1,0,1,0,1,1,0);
		 break;
		 case 15:
		 SetKLUCH(1,0,0,1,1,1,0);
		 break;
		 case 16:
		 SetKLUCH(1,0,1,1,1,1,0);
		 break;

	 }
   }
void MFCG::SDivSet (struct Divider *DXX,int Div)
   {/*HMC705SET*/
		switch(Div) // В МФЧ1 нумерация сдвинута н -1
	 {
		 case 1:
		 SSetKLUCH(DXX,0,0,0,0,0,1);
		 break;
		 case 2:
		 SSetKLUCH(DXX,1,0,0,0,0,0);
		 break;
		 case 3:
		 SSetKLUCH(DXX,1,1,0,0,0,0);
		 break;
		 case 4:
		 SSetKLUCH(DXX,0,0,1,0,0,0);
		 break;
		 case 5:
		 SSetKLUCH(DXX,0,1,1,0,0,0);
		 break;
		 case 6:
		 SSetKLUCH(DXX,0,0,0,1,0,0);//Установка DIV1_16
		 break;
		 case 7:
		 SSetKLUCH(DXX,0,1,0,1,0,0);
		 break;

		 case 8:
		 SSetKLUCH(DXX,0,0,1,1,0,0);
		 break;
		 case 9:
		 SSetKLUCH(DXX,0,1,1,1,0,0);
		 break;
		 case 10:
		 SSetKLUCH(DXX,0,0,0,0,1,0);
		 break;
		 case 11:
		 SSetKLUCH(DXX,0,1,0,0,1,0);
		 break;
		 case 12:
		 SSetKLUCH(DXX,0,0,1,0,1,0);
		 break;
		 case 13:
		 SSetKLUCH(DXX,0,1,1,0,1,0);
		 break;
		 case 14:
		 SSetKLUCH(DXX,0,0,0,1,1,0);
		 break;
		 case 15:
		 SSetKLUCH(DXX,0,1,0,1,1,0);
		 break;
		 case 16:
		 SSetKLUCH(DXX,0,0,1,1,1,0);
		 break;
		 case 17:
		 SSetKLUCH(DXX,0,1,1,1,1,0);
		 break;

	 }

   }
   /*=====  End of Section comment block  ======*/
   
int MFCG::binary_searchFCHG(double x, int l ,int r)
{   /*Поиск диапазона*/
	while(r - l > 1)
	//пока результат не станет однозначным
	{
		int mid = (l + r) / 2;
		//PolosaFCG[120].DFv;делим отрезок [l,r] пополам
		if(PolosaFCG[mid].DFv<x)
		//прверяем где находимся
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}

//				if(Polosa[r].DBad)
//	{
//						r=r+1;
//	}
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

void MFCG::AdrSet(int JGUT)
{
	switch(JGUT)
	{
		case 0:

		AdrMod = Adress::AMFCG;
		break;
		case 1:
		AdrMod = Adress::OBSH;
		break;
		case 2:
		AdrMod = AdrPR;
		break;
		case 6:
		AdrMod = Adress::SH1;
		break;
		case 7:
		AdrMod = Adress::SH2;
		break;

		default: AdrMod = Adress::OBSH;	break;
	}
}


long MFCG::SintLOAD_L(int dev,int Poz)
/*---------- Subsection SintLOAD_LCHG  ----------*/

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

			 case 2:  /*	TODO: прогрузка ADF4002_1 2 Внутр */

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
			    case 4:  /*	TODO: прогрузка ADF4159_2 */
		

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

			 case 5:  /*	TODO: прогрузка ADF4002_2  5 Посл */

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
 				case 6:  /*	TODO: прогрузка Sint100_ADF4002 */

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

			   } 	break;
			   case 7:  /*	TODO: прогрузка Sint1000_ADF4002 */

					switch (i)
			   {

				 case 0:

				 SW_SW = Sint1000_ADF4002->RegLoad4002(i);break;

				 case 1:

				 SW_SW = Sint1000_ADF4002->RegLoad4002(i);break;

				 case 2:

				 SW_SW = Sint1000_ADF4002->RegLoad4002(i);break;

				 case 3:

				 SW_SW = Sint1000_ADF4002->RegLoad4002(i);break;

				 default : SW_SW = Sint1000_ADF4002->RegLoad4002(0);break;

			   } 	break;


		}

	return  SW_SW;

   }
/***********************************************************************************/
long MFCG::SintLOAD_H(int dev)
   {
	switch(dev)
		{   case 1:
			return  AdrMod|MFCG::AdrDev::PLL1<<24;
			break;
			case 2:
			return  AdrMod|MFCG::AdrDev::PLL2<<24;
			break;
			case 3:
			return  AdrMod|MFCG::AdrDev::PLL3<<24;
			break;
			case 4:
			return  AdrMod|MFCG::AdrDev::PLL7<<24;
			break;
			case 5:
			return  AdrMod|MFCG::AdrDev::PLL4<<24;
			break;
			case 6://  ADF4002(D4)  опора  100
			return  AdrMod|MFCG::AdrDev::PLL5<<24;
			break;
			case 7://  ADF4002(D46) опора  1000
			return  AdrMod|MFCG::AdrDev::PLL6<<24;
			break;
		

		//PLL3 = 0x7,   HMC830
		//PLL4 = 0x5,  ADF4002(D85)
		//PLL2 = 0x8,  ADF4002(D17)
		//PLL5 = 0xA,  ADF4002(D4)  опора  10
		//PLL6 = 0xB,  ADF4002(D46) опора  100
		//PLL1 = 0x9,  ADF4159(D18)
		//PLL7 = 0x6,  ADF4159(D86)


			default: return  AdrMod|MFCG::AdrDev::PLL3<<24;
		}
   }
#pragma package(smart_init)
