//---------------------------------------------------------------------------

#ifndef MAX2870H
#define MAX2870H
//---------------------------------------------------------------------------
 class MAX2870
  {
	public:
	MAX2870(double F,int I,int N,double Ref);
	~MAX2870();
	double SetFreq(double fsint);
	 int  RegLoad2870(int Reg);
	void SetFreq(double F,int I,double PFD,double Ref);
	double FregSIN;
	void SetParam(int Pol,int Icp,int PowA,int PowB,int ADIV);
	double Xtal; //ֳּונצ
	private:
	double Nakt;
	double Pfd;
	double Nref;
	double Divison;
	int CurSet;

	unsigned int  SW_SW;
// regnum0
	   int	NF ;
	   int	Nint;
	   int	Nfrak;

//  regnum1
	   int	CPOC;
	   int	CPL;
	   int	CPT;
	   int	P;
	   int	Nmod;

// regnum2
	   int	LDS;
	   int	SDN;
	   int	MUX;
	   int	DBR;// Reference Doubler Mode  Sets reference doubler mode.  0 = Disable reference doubler  1 = Enable reference double
	   int	RDIV2;
	   int	R;
	   int	REG4DB;
	   int	CP;
	   int	LDF;
	   int	LDP;
	   int	PDP;
	   int	SHDN;
	   int	TRI;
	   int	RST;


// regnum3


		int VCO;           //Manual selection of VCO and VCO sub-band when VAS is disabled.
		int VAS_SHDN;  //0 = VAS enabled
		int RETUNE;
		int CDM;
		int CDIV;




// regnum4
		int Res4;
        int Res42;
		int BS_MSBs;
		int FB;           //Manual selection of VCO and VCO sub-band when VAS is disabled.
		int DIVA;
		int BS;
		int BDIV;
		int RFB_EN;
		int BPWR;
		int RFA_EN;
		int APWR;


 //	regnum5


		int F01;           //Manual selection of VCO and VCO sub-band when VAS is disabled.
		int LD;
		int MUX5;




  } ;
#endif
