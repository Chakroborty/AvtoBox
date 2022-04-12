//---------------------------------------------------------------------------

#ifndef MHMC394H
#define MHMC394H
//---------------------------------------------------------------------------
class HMC394
{
public:
	HMC394();
	~HMC394();
long SET394(int DIV);
int RETURNCOD();
private:
int N394[32];
int COD;
int NDIV;
};
#endif
