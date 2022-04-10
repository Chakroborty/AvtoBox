// ---------------------------------------------------------------------------
#include "HMC830.h"

#include "Adf4159.h"

#include "CADF4002.h"
#ifndef MFCGDGH
#define MFCGDGH

// ---------------------------------------------------------------------------
class MFCG
{
public:
     MFCG();
	~MFCG();

	double Fget1,FS;


struct Diapazon
{
	int DNdiap;
	double DFv;
	int DK1;
	int DK2;
	int Dndel;
	int DNSys;
};
	/*=============================================*/
	  int AdrPR;
	/*=============================================
	=            ���������� ������ �����          =
	=============================================*/
		double Fz;	//������� ��������� (HMC830) 
		double F1;	//������� ��������� (HMC830)*2 
		double F2;	//������� ������� 5000+Fz
		double F3;	//������� ������� (5000+Fz)+-(5000+Fz)/A
		double Fop;	//������� ������� 5000+Fz
		int D117108,ZZ;//����������� �117,108
		int N45;    //�������� D45
		int CED18;  // ���������� Adf4002 D17
		int CED86;	// ���������� Adf4002 D85

		double InitfreqOP(double Freq,int K1,int K2,double  NDel,int Ocn,int AR,int AN);

		struct Diapazon20
	{
		int DNdiap;
		double DFv;   //F       ���
		int DK1;
		int DK2;
		int DK12P;//���������� Adf4002 D85
		int DK3;
		int DK3P;//���������� Adf4002 D85
		int DK4;
		int DK4P;//����� ������� 5000+-HMC830
		int Dndel;
		int DN18;
		int DN45;
		int Cur;

	};
	Diapazon20 PolosaFCG[32];
	Diapazon20 Point;
	int binary_searchFCHG(double x, int l ,int r);
	struct Divider
	{

		int DIV1 ;
		int S0 	 ;
		int N0 	 ; // TODO: ��������� ��������
		int N1 	 ;
		int N2 	 ;
		int BYP  ;

	};
	Divider   D45,D67;
	/*=====  End of ���������� ������ �����======*/
	/*===============================================
	=            ���������� ������ �����.            =
	================================================*/

		double FDIVocn; //����� �������� �� Ocn
		int N67;    	//�������� D45
		int Pol1;		// ���������� Adf4002 D85
		int Pol2;		// ���������� Adf4002 D85
		double Initfreq(double Freq,double K1,double K2,double K3,double K4,double  NDel,int Ocn,int AR,int AN);
	/*=====  End of ���������� ������ �����.  ======*/


	int ATTSW;//���������� �������� 	
	int UPR4,UPR1;// ����1,����2
	int DIV1,S0,N0,N1,N2,BYP; // �������� ���. ����� Mix2 

	int Cp; // ������������� CP
	int NumDapazon;//����� ���������
	int Nsys;// ��������� �������� 40,35,45
    int SetD117(int Num);
	void SetKLUCH(int UPRL,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP);
	void SSetKLUCH(struct Divider *DXX,int PDIV1,int PS0,int PN0,int PN1,int PN2,int PBYP);
	int SetNsys(int N);
	void SetFreq4359(double fget);
	long SintLOAD_L(int dev,int Poz);
	long SintLOAD_H(int dev);
	int Kluch(int Num);
	void DivSet (int Div);
	void SDivSet (struct Divider *DXX,int Div);
	int pol2m,Div,DivADF,ADPOL;
	void OGvnutr(OG);
	double Fopdiv;
	int Pr; // �������� ������ 35,40,45,50
	void AdrSet(int JGUT);


	
	
	/**
	 * [SetFreq description]
	 * @param  Fg4159 [������� ���������]
	 * @param  fget   [������������� ������� ��������� (HMC830)]
	 * @param  Fas1   [����1]
	 * @param  Fas2   [����2]
	 * @param  SysN   [������������� ���������� �������� 35,40,45]
	 * @return        [������������ ������� ��������� (HMC830)]
	 */
	double  SetFreq(double Fg4159,double fget,int Fas1,int Log);
	

	HMC830 *Sint1_HMC830;
	ADF4159 *Sint2_ADF4159;
	ADF4002 *Sint2_ADF4002;
	ADF4159 *Sint1_ADF4159;
	ADF4002 *Sint1_ADF4002;

	ADF4002 *Sint1000_ADF4002; //PLL 1��� ����� adr 0XB

	ADF4002 *Sint100_ADF4002;//PLL 100 ��� ����� adr 0XA
    long AdrMod;

private:



	enum Adress
	{
		OBSH = 0xD<<28,
		AMFCG = 0xF<<28,
		SH1 = 0x6<<28,
		SH2 = 0x7<<28
	};
	enum AdrDev
	{
		Kontr_I2C = 0x1,
		Perekl = 0x4, // 875
		Sint = 0xB,
		Kontrol = 0xE,
		PLL3 = 0x7, //  HMC830
		PLL4 = 0x5, //  ADF4002(D85)
		PLL2 = 0x8, //  ADF4002(D17)
		PLL5 = 0xA, //  ADF4002(D4)  �����  10
		PLL6 = 0xB, //  ADF4002(D46) �����  100
		PLL1 = 0x9, //  ADF4159(D18)
		PLL7 = 0x6, //  ADF4159(D86)
		
		//PLL7 = 0xA,//  ADF4159(D86)
		//PLL4 = 0xB,//  ADF4002(D85)

	};
		enum HMC345
	{
		BA1 = 0,//B00
		BA2 = 2,//B10
		BA3 = 1,//B01
		BA4 = 3,//B11

	};


};
#endif
