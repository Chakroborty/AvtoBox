//---------------------------------------------------------------------------

#ifndef LoggedH
#define LoggedH
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#include <iostream.h >
#include <fstream.h >
//---------------------------------------------------------------------------
class Log
 {
	public:
   Log();
   ~Log();

  AnsiString log,MSGout;
  AnsiString LogWriteString(AnsiString LogMessage,AnsiString Note);
  long LogWriteDat();
  long LogReadDat(AnsiString Path);
  long ReadDatSaze(AnsiString Path);
	struct MyStruct
	{    float Fus;
		 float Fn;
		 float AmplN;
		 float Fsp1;
		 float Amplsp1;
		 float Fsp2;
		 float Amplsp2;
		 float Fsp3;
		 float Amplsp3;
		 float Fsp4;
		 float Amplsp4;
		 float Fsp5;
		 float Amplsp5;
		 int Offs;
		 float Delta;
		 int K1;
		 int K2;
		 int POL;
		 int N;
		 int Nref;
		 int INV;
		 int PAmax;
		 int PBmax;

	};
	MyStruct X;
	int K;
   protected:
 };
#endif
