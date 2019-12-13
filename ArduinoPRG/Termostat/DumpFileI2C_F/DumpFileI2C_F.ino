#if defined(__SAM3X8E__) || defined(__SAM3A8C__)   // это если используется Arduino DUE
#define Set_DUE
#endif

#ifdef Set_DUE
#include <Wire.h>       // производим запись в flash память,
#else
#include <EEPROM.h>     //  иначе в EEPROM 
#endif

 extern byte ProfDate[10][33];
 extern char* AdrProfN[10];
 
// ----------------------------------------------------------------------

#define numMax 5          // Максимальное количество профилей
#define ArrMax 50           // Максимальное количество символов в названии профиля (в русских буквах в два раза меньше)
#define Adres 1000          // адрес начала записи в EPROM 
 
byte numProf;

 struct Profili_t {
   char HeadProf[ArrMax];   // заголовок профиля ArrMax символов
   byte TableSize;          // размер низа
   byte rampRateBOTTOM;     // скорсть нагрева низа 
   byte temperatureBOTTOM;  // температура низа в градусах
   byte dwellTimerBOTTOM;   // время в сек перехода к включения верха
   byte min_pwr_BOTTOM;     // мощность низа в % min
   byte max_pwr_BOTTOM;     //     --            max   
   byte rampRateStep[4];    // скорсть нагрева верхом по шагам
   byte temperatureStep[4]; // температура верха по шагам 
   byte dwellTimerStep[4];  // время в сек перехода на следующий шаг 
   byte min_pwr_TOPStep[4]; // min мощности по шагам
   byte max_pwr_TOPStep[4]; // max мощности по шагам
   byte kp1_ki1_kd1[3];     // коэф ПИД 1 верха  
   byte kp2_ki2_kd2[3];     // коэф ПИД 2 низа 
  };
 int SizePrrof = sizeof(Profili_t);
 union {                      // исходные данные
   byte Mode[sizeof(Profili_t)];
   Profili_t Profili;  
 } u;
byte i, j, k;
char buffer[ArrMax];  // make sure this is large enough for the largest string it must hold
String baff; 
byte DuB=0;
// ------------------------------
void PutMem (byte NnProf) {   // запись в память
    Serial.println(" Сохраняем профиль в EPROM "); 
    Serial.print(Adres+((NnProf-1)*SizePrrof));
    Serial.print(" ");
    Serial.print(NnProf-1); Serial.print(" ");
    Serial.println(SizePrrof);
            
    for (j=0; j<=SizePrrof-1; j++) {
      if (j%10 == 0) {
        Serial.print(Adres+((NnProf-1)*SizePrrof)+j); 
        Serial.print(" "); 
        }
      Serial.print(u.Mode[j]);
      Serial.print(" ");
      #ifdef Set_DUE
       i2c_eeprom_write_byte(0x57, Adres+((NnProf-1)*SizePrrof)+j, u.Mode[j]);
      #else
       EEPROM.update(Adres+((NnProf-1)*SizePrrof)+j, u.Mode[j]); 
      #endif
      //Serial.print(" "); 
      if (j%10 == 9) Serial.println("");   
      }
    Serial.println("");
}
// ------------------------------
void DumpMem (byte NnProf) {  // читаем память
    Serial.println("Читаем пзу ");
    byte DuBre=0;
    String DuStr=""; 
    char DuSS;
    for (j=0; j<SizePrrof; j++) {
      if (j%10 == 0) {
        Serial.print(Adres+((NnProf-1)*SizePrrof)+j); 
        Serial.print(" "); 
        }
        #ifdef Set_DUE
         DuBre = i2c_eeprom_read_byte(0x57, Adres+((NnProf-1)*SizePrrof)+j);
        #else
         DuBre = EEPROM.read(Adres+((NnProf-1)*SizePrrof)+j);
        #endif
      
      Serial.print(DuBre); 
      Serial.print(" "); 
      if (j%10 == 9) Serial.println(""); 
      DuSS = DuBre;
      DuStr += DuSS;
      if (j == ArrMax-1) {
         //Serial.print(Adres+((NnProf-1)*SizePrrof)+j); 
        Serial.print("-"); Serial.print(DuStr); Serial.println("-");       
        }   
        
     }
    DuStr="";  
    Serial.println("");
  }
// ------------------------------
void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) {
    int rdata = data;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(rdata);
    Wire.endTransmission();
  }
// ------------------------------
byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress,1);
    if (Wire.available()) rdata = Wire.read();
    return rdata;
  }  
// ------------------------------
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Wire.begin();        // join i2c bus (address optional for master)
  while (!Serial) { ; } // wait for serial port to connect. Needed for native USB port only
  Serial.println("Выводим имена профилей");
        //Serial.println(ProfN1[]);  
    for (i=0; i<numMax; i++) {
      for (j=0; j<ArrMax; j++) { buffer[j]=32; u.Profili.HeadProf[j]=32;}
      strcpy_P(u.Profili.HeadProf, (char *)pgm_read_word(&(AdrProfN[i])));  //  пишем в буфер
      strcpy_P(buffer, (char *)pgm_read_word(&(AdrProfN[i])));  //  пишем в буфер
     
    baff = "";
    for (j=0; j<ArrMax; j++) {
      baff += buffer[j];
      DuB = buffer[j];
      Serial.print(DuB);       
      if (j%10 == 9) Serial.println(""); 
        else Serial.print(" ");
      }
      baff.trim();  
      Serial.print(baff.length()); Serial.print(" -");
      Serial.print(baff); Serial.println("-");
    
    for (j=0; j<=(SizePrrof-ArrMax); j++) {
      if (j == 0) numProf = pgm_read_byte_near(ProfDate[i]+j);
        else {
          u.Mode[ArrMax+j-1] = pgm_read_byte_near(ProfDate[i]+j);
          Serial.print(u.Mode[ArrMax+j-1]); 
          Serial.print(" ");
          if (j%10 == 9) Serial.println("");
          }
      }
    Serial.println("- end prof -"); 
    if (numProf >= 1 && numProf <= numMax) PutMem(numProf);
    DumpMem(i+1);
    }  
 }
// ------------------------------
void loop() {
}
// end 
