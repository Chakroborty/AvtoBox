//---------------------------------------------------------------------------

#ifndef MUXM20H
#define MUXM20H
//---------------------------------------------------------------------------
class UXM20
{
public:
	UXM20();
	~UXM20();

int N20[6];
int SETUXM20(int N);
int RETURNCOD();
private:
int COD;
int NDIV;
};

#endif
