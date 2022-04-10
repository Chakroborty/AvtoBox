//---------------------------------------------------------------------------

#pragma hdrstop

#include "ManageINI.h"
//---------------------------------------------------------------------------


 //    class OPTIONS_ELEMENTS
//------------------------------

void OPTIONS_ELEMENTS::add(TStrings *address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_STRINGS;
  new_element.address = address;
  new_element.sector  = sector;
  new_element.key     = key;


}

void OPTIONS_ELEMENTS::add(bool &address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_BOOL;
  new_element.address = &address;
  new_element.sector  = sector;
  new_element.key     = key;

}

void OPTIONS_ELEMENTS::add(String &address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_STRING;
  new_element.address = &address;
  new_element.sector  = sector;
  new_element.key     = key;

}

void OPTIONS_ELEMENTS::add(int &address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_INT;
  new_element.address = &address;
  new_element.sector  = sector;
  new_element.key     = key;

}

void OPTIONS_ELEMENTS::add(double &address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_DOUBLE;
  new_element.address = &address;
  new_element.sector  = sector;
  new_element.key     = key;

}

void OPTIONS_ELEMENTS::add(float &address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_FLOAT;
  new_element.address = &address;
  new_element.sector  = sector;
  new_element.key     = key;

}

void OPTIONS_ELEMENTS::add(unsigned &address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_UNSIGNED;
  new_element.address = &address;
  new_element.sector  = sector;
  new_element.key     = key;

}

void OPTIONS_ELEMENTS::add(TColor &address, const char *sector, const char *key)
{
  OPTIONS_ELEMENT new_element;

  new_element.type    = OET_COLOR;
  new_element.address = &address;
  new_element.sector  = sector;
  new_element.key     = key;

}

//    class OPTIONS_BASE
//--------------------------
OPTIONS_BASE::OPTIONS_BASE(const String &file_name) {
   AnsiString ExecDir = ExtractFileDir(ParamStr(0));

   last_file_name = ExecDir+"\\"+file_name;
   Opc1 = "OTK";
   Opc2 = "BPMO";


}
OPTIONS_BASE::~OPTIONS_BASE() {}


void OPTIONS_BASE::save(TIniFile *ini)
{
  OPTIONS_ELEMENTS elements;
  OPTIONS_ELEMENT *element;
  int i, count;

  // переда сохранение файла
  before_save(ini);

  // получаем список элементов
 // get_elements_list(elements);


  // сохраняем информацию из общего списка
  for (i = 0; i < count; i++)
  {

    switch (element->type)
    {
		case OET_STRING:
			  ini->WriteString(element->sector, element->key, "\""+*(String*)element->address+"\"");
			  break;

		case OET_INT:
			  ini->WriteInteger(element->sector, element->key, *(int*)element->address);
			  break;

		case OET_DOUBLE:
			  ini->WriteFloat(element->sector, element->key, *(double*)element->address);
			  break;

		case OET_FLOAT:
			  ini->WriteFloat(element->sector, element->key, *(float*)element->address);
			  break;

		case OET_UNSIGNED:
			  ini->WriteInteger(element->sector, element->key, *(int*)element->address);
			  break;

		case OET_BOOL:
			  ini->WriteBool(element->sector, element->key, *(bool*)element->address);
			  break;

		case OET_COLOR:
			  ini->WriteInteger(element->sector, element->key, (int)(*(TColor*)element->address));
			  break;

		case OET_STRINGS:
			  ini->WriteString(element->sector, element->key, "\""+((TStrings*)element->address)->CommaText+"\"");
			  break;
    }
  }

  // сохраняем добавочную информацию
  save_additional_info(ini);
}

void OPTIONS_BASE::load(TIniFile *ini)
{
  OPTIONS_ELEMENTS elements;
  OPTIONS_ELEMENT *element;
  int i, count;

  // перед загрузкой файла
  before_load(ini);

  // получаем список элементов
 // get_elements_list(elements);


  // загружаем информацию из общего списка
  for (i = 0; i < count; i++)
  {


    try
    {
      switch (element->type)
      {
		case OET_STRING:
				*(String*)element->address = ini->ReadString(element->sector, element->key, *(String*)element->address);
				break;

		case OET_INT:
				*(int*)element->address = ini->ReadInteger(element->sector, element->key, *(int*)element->address);
				break;

		case OET_DOUBLE:
				*(double*)element->address = ini->ReadFloat(element->sector, element->key, *(double*)element->address);
				break;

		case OET_FLOAT:
				*(float*)element->address = ini->ReadFloat(element->sector, element->key, *(float*)element->address);
				break;

		case OET_UNSIGNED:
				*(int*)element->address = ini->ReadInteger(element->sector, element->key, *(int*)element->address);
				break;

		case OET_BOOL:
				*(bool*)element->address = ini->ReadBool(element->sector, element->key, *(bool*)element->address);
				break;

		case OET_COLOR:
				*(TColor*)element->address = (TColor)ini->ReadInteger(element->sector, element->key, *(TColor*)element->address);
				break;

		case OET_STRINGS:
				((TStrings*)element->address)->CommaText = ini->ReadString(element->sector, element->key, ((TStrings*)element->address)->CommaText);
				break;
      }
    }
    catch (...)
    {
      Beep(1000, 20); // ??? А это я не доделал
    }
  }

  // загружаем добавочную информацию
  load_additional_info(ini);
}

void OPTIONS_BASE::PAthSet(const String &file_name){
   // AnsiString ExecDir = ExtractFileDir(ParamStr(0));

   last_file_name = file_name;
}
void OPTIONS_BASE::MPAthSet(const String &file_name){
   AnsiString ExecDir = ExtractFileDir(ParamStr(0));
   last_file_name = ExecDir+"\\"+file_name;

   // AnsiString ExecDir = ExtractFileDir(ParamStr(0));

  // last_file_name = file_name;
}
String OPTIONS_BASE::PAthRead(){
	return last_file_name;
}
void OPTIONS_BASE::WriteDouble(const char *sector, const char *key, double val){
 TIniFile *ini;
 ini = new TIniFile(last_file_name);
 ini->WriteFloat(sector, key, (double)val);
  delete ini;
}
double OPTIONS_BASE::ReadDouble(const char *sector, const char *key, double Default){
 double Rezult;
 TIniFile *ini;
 ini = new TIniFile(last_file_name);
 Rezult = ini->ReadFloat(sector, key, (double)Default);
 delete ini;
 return Rezult;
}
void OPTIONS_BASE::TWriteDouble(int secTape,const char *sector, const char *key, double val){
 TIniFile *ini;
 ini = new TIniFile(last_file_name);
 char str[100];
 strcpy(str,sector);
	 switch (secTape)
	{
		 case 0:
		 strcat(str, Opc1);
		 break;
		 case 1:
		 strcat(str, Opc2);
		 break;


		 default :strcat(str, Opc1); break;
	}
  ini->WriteFloat(str, key, (double)val);
  delete ini;
}
double OPTIONS_BASE::TReadDouble(int secTape,const char *sector, const char *key, double Default){
 double Rezult;
 TIniFile *ini;
 ini = new TIniFile(last_file_name);
 char str[100];
 strcpy(str,sector);
	 switch (secTape)
	{
		 case 0:
		 strcat(str, Opc1);
		 break;
		 case 1:
		 strcat(str, Opc2);
		 break;


		 default :strcat(str, Opc1); break;
	}
 Rezult = ini->ReadFloat(str, key, (double)Default);
 delete ini;
 return Rezult;
}
String OPTIONS_BASE::TReadString(int secTape,const char *sector, const char *key, String Default){
 String Rezult;
 TIniFile *ini;
 ini = new TIniFile(last_file_name);

 char str[100];
 strcpy(str,sector);
	 switch (secTape)
	{
		 case 0:
		 strcat(str, Opc1);
		 break;
		 case 1:
		 strcat(str, Opc2);
		 break;


		 default :strcat(str, Opc1); break;
	}

 Rezult = ini->ReadString(str, key, Default);
 delete ini;
 return Rezult;
}

void  OPTIONS_BASE::WriteString(const char *sector, const char *key, String Default){
 TIniFile *ini;
 ini = new TIniFile(last_file_name);

  ini->WriteString(sector, key,Default);
  delete ini;

}
String OPTIONS_BASE::ReadString(const char *sector, const char *key, String Default){
String Rezult;
 TIniFile *ini;
 ini = new TIniFile(last_file_name);


 Rezult = ini->ReadString(sector, key, Default);
 delete ini;
 return Rezult;
}
void  OPTIONS_BASE::TWriteString(int secTape,const char *sector, const char *key, String Default){
  TIniFile *ini;
 ini = new TIniFile(last_file_name);
 char str[100];
 strcpy(str,sector);
	 switch (secTape)
	{
		 case 0:
		 strcat(str, Opc1);
		 break;
		 case 1:
		 strcat(str, Opc2);
		 break;


		 default :strcat(str, Opc1); break;
	}
  ini->WriteString(str, key,Default);
  delete ini;

}

/* сохранение файла */
void OPTIONS_BASE::save(const String &file_name)
{
  TIniFile *ini;

  if ( file_name.Trim().IsEmpty() ) return;
  last_file_name = file_name;
  ini = new TIniFile(file_name);
  save(ini);
  delete ini;
}

/* загрузка файла */
void OPTIONS_BASE::load(const String &file_name)
{
  TIniFile *ini;
  if ( file_name.Trim().IsEmpty() ) return;
  last_file_name = file_name;
  ini = new TIniFile(file_name);
  load(ini);
  delete ini;
}







#pragma package(smart_init)
