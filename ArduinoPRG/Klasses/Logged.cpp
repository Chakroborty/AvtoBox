//---------------------------------------------------------------------------

#pragma hdrstop
#include <iostream.h >
#include <fstream.h >
#include "Logged.h"
#include <string.h>
//---------------------------------------------------------------------------
   Log::Log()
  {


  }
   Log::~Log()
   {

  }


AnsiString Log::LogWriteString(AnsiString LogMessage,AnsiString Note)
 {
	  AnsiString DATE_TIME = FormatDateTime("YYYY-MM-DD",Date())+ "/"

                 +FormatDateTime("HH:NN:SS",Time());
      FILE *f = fopen("log.txt", "a");
		  if (f)
      {   MSGout  = MSGout.sprintf(":%s:%s:%s;", LogMessage,Note, DATE_TIME);
          fprintf (f, ":%s:%s- %s;\n", LogMessage,Note, DATE_TIME); // получение currentTime описывать не стал, оно тут просто для примера
          fclose(f);
      }
      return  MSGout;
 }
 long Log::LogWriteDat()
 {
		ofstream log("Mass.pdt",ios_base::app);

		log.write((char*)&X,sizeof X);
		log.close();


	  AnsiString DATE_TIME = FormatDateTime("YYYY-MM-DD",Date())+ "/"

				 +FormatDateTime("HH:NN:SS",Time());

 }
long Log::ReadDatSaze(AnsiString Path)
{      FILE *pFile = fopen(Path.c_str(), "rb");
		fseek (pFile, 0, SEEK_END);
		K = ftell(pFile)/sizeof(MyStruct);
		fclose(pFile);
	   return K;
}
long Log::LogReadDat(AnsiString Path)
 {
	FILE *pFile = fopen(Path.c_str(), "rb");
		fseek (pFile, 0, SEEK_END);
		K = ftell(pFile)/sizeof(MyStruct);
		fclose(pFile);
		ifstream log(Path.c_str(),ios_base::binary | ios_base::in);
		MyStruct *Y = new MyStruct[K];
		log.read((char*) Y, sizeof(MyStruct)*K);
		X.Fn =   Y[0].Fn;
		X.Fsp1 =   Y[1].Fn;
		X.Fsp2 =   Y[2].Fn;
		X.Fsp3 =   Y[3].Fn;
		log.close();


		AnsiString DATE_TIME = FormatDateTime("YYYY-MM-DD",Date())+ "/"

				 +FormatDateTime("HH:NN:SS",Time());

 }

#pragma package(smart_init)
