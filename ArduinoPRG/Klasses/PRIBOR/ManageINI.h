//---------------------------------------------------------------------------

#ifndef ManageINIH
#define ManageINIH
#include <stdio.h>
#include <string.h>
#include <vcl.h>
#include "IniFiles.hpp"
//---------------------------------------------------------------------------

 enum OPTIONS_ELEMENT_TYPE
{
  OET_STRING,
  OET_INT,
  OET_DOUBLE,
  OET_FLOAT,
  OET_UNSIGNED,
  OET_BOOL,
  OET_COLOR,
  OET_STRINGS
};

class OPTIONS_ELEMENT
{
public:
  OPTIONS_ELEMENT_TYPE type;
  void *address;
  String sector, key;

  OPTIONS_ELEMENT()
  {
    address = NULL;
    sector = key = NULL;
  };
};

class OPTIONS_ELEMENTS
{
  friend class OPTIONS_BASE;

private:
 // std::vector<OPTIONS_ELEMENT> items;


public:
  void add(TStrings *address, const char *sector, const char *key);
  void add(String &address, const char *sector, const char *key);
  void add(int &address, const char *sector, const char *key);
  void add(double &address, const char *sector, const char *key);
  void add(float &address, const char *sector, const char *key);
  void add(unsigned &address, const char *sector, const char *key);
  void add(bool &address, const char *sector, const char *key);
  void add(TColor &address, const char *sector, const char *key);
};

class OPTIONS_BASE
{
protected:
  String last_file_name;
  char* Opc1;
  char* Opc2;
  virtual void save_additional_info(TIniFile *ini) {};
  virtual void load_additional_info(TIniFile *ini) {};

  virtual void before_save(TIniFile *ini) {};
  virtual void before_load(TIniFile *ini) {};

public:
  OPTIONS_BASE(const String &file_name);
  ~OPTIONS_BASE();
  void  WriteDouble(const char *sector, const char *key, double val);
  double ReadDouble(const char *sector, const char *key, double Default);
  void  WriteString(const char *sector, const char *key, String Default);
  String ReadString(const char *sector, const char *key, String Default);
  String PAthRead();
  void  TWriteDouble(int secTape,const char *sector, const char *key, double val);
  double TReadDouble(int secTape,const char *sector, const char *key, double Default);
  void  TWriteString(int secTape,const char *sector, const char *key, String Default);
  String TReadString(int secTape,const char *sector, const char *key, String Default);
  void save() { save(last_file_name); };
  void save(const String &file_name);
  void load(const String &file_name);
  void save(TIniFile *ini);
  void load(TIniFile *ini);
  void PAthSet(const String &file_name);
  void MPAthSet(const String &file_name);
};


#endif
