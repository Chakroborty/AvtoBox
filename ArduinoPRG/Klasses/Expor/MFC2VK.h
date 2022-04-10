// ---------------------------------------------------------------------------
#include "HMC830.h"

#include "Adf4159.h"

#include "CADF4002.h"
#ifndef MFC2VKH
#define MFC2VKH

// ---------------------------------------------------------------------------
class MFC2VK
{
public:
	 MFC2VK();
	~MFC2VK();

	double Fget1,F830;

/**
 * @param  DNdiap [description]
 * @param  DFv   [������� ���������������� ��������]
 * @param  DF830   [������� HMC830]
 * @param  DK1   [������� ������ �������������� MIX1]
 * @param  Dndel [�������� R ADF4002]
 * @param  DNSys [������������� ���������� �������� 12,12,13]
 * @param  DNOut [������������� ��������� �������� 2,4,5]
 */
struct Diapazon
{
	int DNdiap;
	double DFv;
	double DF830;
	double DFref;
	int DK1;
	int DNDel;
	int DNSys;
	int DNOut;

	
};
struct Divider
{
	int DIV1 ;
	int S0 	 ;
	int N0 	 ; // TODO: ��������� ��������
	int N1 	 ;
	int N2 	 ;
	int BYP  ;

};
	Divider  D55,D56;
	Diapazon Polosa[4];
	int PCH1;//����� ��
	int UPR;// ����1,����2
	int DIV1,S0,N0,N1,N2,BYP; // �������� ���. ����� Mix2
	void SetKLUCH(struct Divider *DXX,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP);
	int Cp; // ������������� CP

	int Nsys;// ��������� �������� 40,35,45


	void SetFreq4359(double fget);
	long SintLOAD_L(int dev,int Poz);
	long SintLOAD_H(int dev);
	int Kluch(int Num);
	void DivSet (struct Divider *DXX,int Div);
	int pol2m,Div,DivADF,Pol1,Pol2,ADPOL;
	double Fget2;
	double Fopdiv;
	int Pr; // �������� ������ 35,40,45,50
	double Fz;//������� ��������� (HMC830)
	double Fop;// ������� ������� 5000+Fz


	double FDIVocn; //����� �������� �� Ocn
	void AdrSet(int JGUT);
	double Initfreq(double Freq,int K1,int K2,double  NDel,int Ocn,int AR,int AN);
	/**
	 * [ SetFreq_H ]
	 * @param  Fg4159 [������� ���������]
	 * @param  Fas1   [UPR ����� ����� ����]
	 * @return        [������������ ������� ��������� (HMC830)]
	 */
	double  SetFreq(double Fg4159,int Fas1,int Log);
	void OGvnutr(OG);

	HMC830 *Sint2_HMC830;
	ADF4159 *Sint2_ADF4159;
	ADF4002 *Sint2_ADF4002;	//PLL �������� ����� adr 0X8
	ADF4002 *Sint22_ADF4002;//PLL 1��� ����� adr 0XB
	ADF4002 *Sint100_ADF4002;//PLL 100 ��� ����� adr 0XA


private:


	long AdrMod;
	enum Adress
	{
		OBSH = 0XD<<28,
		MFC2 = 0XF<<28
	};
	enum AdrDev
	{
		Kontr_I2C = 0x1,
		Perekl = 0x4, // 875
		Sint = 0xB,
		Kontrol = 0xE,
		PLL1 = 0x9, // ADF4159
		PLL2 = 0x8, // ADF4002
		PLL3 = 0x7, // HMC830
		PLL4 = 0XB, // PLL 100 ��� ����� adr 0XB
		PLL5 = 0XA, // PLL 1��� ����� adr 0XA
	};

};
#endif
