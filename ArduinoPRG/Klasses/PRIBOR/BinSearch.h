//---------------------------------------------------------------------------

#ifndef BinSearchH
#define BinSearchH
//---------------------------------------------------------------------------
#define NMAX 10
//using namespace std;
 class BinSH
{   
	public:
    BinSH();
	~BinSH();
	int a[NMAX];
	struct Diapazon
	{
		int DNdiap;
		double DFv;
		int DK1;
		int DK2;
		int Dndel;
		int DNSys;
		int DBad;
		int Pol;
		int Fil;
		int Cur;

	};
	Diapazon Polosa[512];
	Diapazon Point;
	int binary_search(double x, int l ,int r);

};
#endif
