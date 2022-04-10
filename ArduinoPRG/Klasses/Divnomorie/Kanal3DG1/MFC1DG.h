// ---------------------------------------------------------------------------
#include "HMC830.h"

#include "Adf4159.h"

#include "CADF4002.h"
#ifndef MFC1DGH
#define MFC1DGH

// ---------------------------------------------------------------------------
class MFC1DG
{
public:
     MFC1DG();
	~MFC1DG();

	double Fget1,F830;

		int AdrMod;
struct Diapazon
{
	int DNdiap;
	double DFv;
	int DK1;
	int DK2;
	int Dndel;
	int DNSys;

	
};
Diapazon Polosa[13];
	int UPR;// Ключ1,Ключ2
	int DIV1,S0,N0,N1,N2,BYP; // Делитель Упр. перед Mix2 
	void SetKLUCH(int UPRL,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP);
	int Cp; // Переключатель CP
	int NumDapazon;//Номер диапазона
	int Nsys;// Системный делитель 40,35,45

	int SetNsys(int N);
	void SetFreq4359(double fget);
	long SintLOAD_L(int dev,int Poz);
	long SintLOAD_H(int dev);
	int Kluch(int Num);
	void DivSet (int Div);
	int pol2m,Div,DivADF,Pol1,Pol2,ADPOL;

	double Fopdiv;
	int Pr; // Делитель основы 35,40,45,50
	double Fz;//частота модуляции (HMC830)
	double Fop;// Частота опорная 5000+Fz


	double FDIVocn; //Опора деленная на Ocn

	double Initfreq(double Freq,int K1,int K2,double  NDel,int Ocn,int AR,int AN);
	/**
	 * [SetFreq description]
	 * @param  Fg4159 [Частота настройки]
	 * @param  fget   [Предустановка частота модуляции (HMC830)]
	 * @param  Fas1   [Ключ1]
	 * @param  Fas2   [Ключ2]
	 * @param  SysN   [Предустановка системного делителя 35,40,45]
	 * @return        [Рассчитанная частота модуляции (HMC830)]
	 */
	double  SetFreq(double Fg4159,double fget,int Fas1,int Log);
	void AdrSet(int OBSH);

	HMC830 *Sint1_HMC830;
	ADF4159 *Sint1_ADF4159;
	ADF4002 *Sint1_ADF4002;

private:



	enum Adress
	{
		OBSH = 0xD<<28,
		MFC1 = 0x7<<28
	};

	enum AdrDev
	{
		Kontr_I2C = 0x1,
		Perekl = 0x4, // 875
		Sint = 0xB,
		Kontrol = 0xE,
		PLL1 = 0x9,//  ADF4159
		PLL2 = 0x8,//  ADF4002
		PLL3 = 0x7, //  HMC830

	
	};

};
#endif
