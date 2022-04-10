//---------------------------------------------------------------------------

#ifndef TADT7310H
#define TADT7310H
//---------------------------------------------------------------------------
class ADT7310 {
public:
ADT7310();
~ADT7310();

int COMMAND[5];
double DTEMP;

double Tvalue(int DAT,int Regim);
int RCOM(int N);
};
#endif
