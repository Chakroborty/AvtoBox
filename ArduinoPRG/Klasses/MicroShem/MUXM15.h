//---------------------------------------------------------------------------

#ifndef MUXM15H
#define MUXM15H
//---------------------------------------------------------------------------

class UXM15
{

public:
UXM15();
~UXM15();

long SETUXM15(int DIV);
int RETURNCOD();
private:
int N15[10];
int COD;
int NDIV;
};

#endif
