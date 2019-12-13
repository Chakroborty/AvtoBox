//Релиз от 22,11,2019    Ver.07
#include "Setting.h"

// Используемые библиотеки -----------------------------
#include <UTFT.h>
#include <AnalogKey5.h>
#include <stdint.h>
#include <RotaryEncoder.h>
#include "Cl_do_btn_long.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <EEPROM.h>

UTFT myGLCD(CTE40, 38, 39, 40, 41);

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t BigFontRus[];       //Кирилица
extern uint8_t SevenSegNumFont[];

byte Cgr, CTgr = 0;
int Xgr, XTgr = 2;                 // x координата графика
int er1 = 1, er2 = 1;
int reg1, reg2;
int pwr1, pwr2;
double prev_millis = 0;
boolean out1, out2;
boolean TopStart = false;
// ------------------TouchScreen ----------------------------------------------
#include "Touch.h"
// -------- энкодер --------------------------
Cl_do_btn_long Btn_ok(BTN_OK);
RotaryEncoder encoder(Enc_Clk, Enc_DT);   // пины подключения энкодера
static byte LastPos = 2;
byte K_Pos;
int NewPos, Pos_Mem;
//-------- Temp -------------------------------
#include "Temp6675.h"
//--------настройка кнопок управления------------------------------------
AnalogKey5 AKeys(SetRIGHT, SetUP, SetDOWN, SetLEFT, SetSELECT, 10);
boolean Key1_Old, Key2_Old, Key3_Old, Key4_Old, Key5_Old;
boolean T_KeyUp_Old = false, T_KeyDown_Old = false;
boolean T_KeyNext = false, T_KeyOk = false;
boolean T_KeyLeft_Old = false, T_KeyRight_Old = false;
boolean K_Kpres_ok = false, K_Lpres_ok = false;
// ----------------------------------------------------------------------
#ifdef Set_Picture
  extern unsigned int Graf[0xCC0];
  extern unsigned int Graf2[0xCC0];
  extern unsigned int Graf3[0xCC0];
  extern unsigned int Graf4[0xCC0];
  extern unsigned int Graf5[0x12C0];
#endif

// ------------ Профили -------------------------------------
#define numMax 10           // Максимальное количество профилей
#define ArrMax 50           // Максимальное количество символов в названии профиля (в русских буквах в два раза меньше)
#define Adres 1000          // адрес начала записи в EPROM 

bool stProf = false;
byte numProf;
struct Profili_t {         // основные поля профиля
  char HeadProf[ArrMax];   // заголовок профиля ArrMax символов
  byte TableSize;          // размер низа
  byte rampRateBOTTOM;     // скорсть нагрева низа
  byte temperatureBOTTOM;  // температура низа в градусах
  byte dwellTimerBOTTOM;   // время в сек перехода к включению верха
  byte min_pwr_BOTTOM;     // мощность низа в % min
  byte max_pwr_BOTTOM;     //     --            max
  byte rampRateStep[4];    // скорсть нагрева верхом по шагам
  byte temperatureStep[4]; // температура верха по шагам
  byte dwellTimerStep[4];  // время в сек перехода на следующий шаг
  byte min_pwr_TOPStep[4]; // min мощности по шагам
  byte max_pwr_TOPStep[4]; // max мощности по шагам
  byte kp1;                // коэф ПИД 1 верха
  byte ki1;
  byte kd1;
  byte kp2;                // коэф ПИД 2 низа
  byte ki2;
  byte kd2;
};
int SizePrrof = sizeof(Profili_t);
union {
  byte Mode[sizeof(Profili_t)];
  Profili_t Profili;
} u;
// --------- profile end ------------------------------
String DuStr = "";
byte currentProfile;
byte currentStep = 1, BrStep;
byte profileName;
double counter;
long previousMillis;          //это для счетчиков

// -------секция ввода/вывода для ПЭВМ-----------------
#ifdef SetConnectPC
char buf[20];   //буфер вывода сообщений через сом порт
#endif

typedef enum REFLOW_STATE {   // состояния контроллера
  REFLOW_STATE_IDLE,          // главный экран
  REFLOW_STATE_SETTING,       // меню настроек
  REFLOW_STATE_SET_EDIT,      // редактирование выбранной настройки
  REFLOW_STATE_PROFILE,       // просмотр профиля
  REFLOW_STATE_BRAZE_START,   // Старт пайки
  REFLOW_STATE_BRAZE_NOW,     // отработка профиля
  REFLOW_STATE_BRAZE_STOP,    // Стоп пайки
}
reflowState_t;
reflowState_t reflowState;          // Reflow oven controller state machine state variable

#define SENSOR_SAMPLING_TIME 250    //read tc every second
#define i_min 0.0//минимум И составляющей
#define i_max 100.0//максимум И составляющей

unsigned long nextRead1; //переменная для обновления текущей температуры
unsigned long WinStartTime, BrStartTime;
byte Setpoint1, Setpoint2, bottomMaxPwr;
byte Output1, Output2;
float Input_f1, Input_f2, Input_ft1, Input_ft2;
float integra, integra2, BrTg;
float e1, p1, d1, e2, p2, d2;
double Input1,  Setpoint1d;
double Input2, InputMA,  Setpoint2d;
double bottomTemp;
int SP1 = Setpoint1, SP2 = Setpoint2, Count1, Count2;
int tc1, tc2;                       // переменные для калмана
int i, j;
int tmp, DisXSize, DisYSize;

boolean alarmOn = false;
boolean updateScreen = true;        //Update whole screen boolean
// --------------------
#define VGA_ORAN 0xFD40
#define Draw_X 90
#define Draw_Y 80
#define Simb_X 18*16
#define Win1 4                                // всего вкладок меню
#define Win2 6                                // кол-во строк
#define K_line 12
#define Py_pr 31 //40
#define Yset 25                               // отступ сверху                          
#define Ysize 36                              // высота окна меню
#define Ywin0 Ysize+Yset+6                    // начало окна параметров
#define Ywin1 Ysize+Yset
#define X_graf 27
#define Y_graf Py_pr+246
#define T_SetY 293
#define B_SetX 3
#define B_SetY 140
#define BattX 87          // размер кнопки по X 
#define BattY 60          // размер кнопки по Y
#define TempY 30
int BattSet[5][4] = { {B_SetX, B_SetY + 10 + BattY, B_SetX + BattX, B_SetY + 10 + 2 * BattY},
  {B_SetX, B_SetY, B_SetX + BattX, B_SetY + BattY},
  {479 - B_SetX - BattX, B_SetY, 479 - B_SetX, B_SetY + BattY},
  {479 - B_SetX - BattX, B_SetY + 10 + BattY, 479 - B_SetX, B_SetY + 10 + 2 * BattY},
  {B_SetX, B_SetY + 20 + 2 * BattY, 479 - B_SetX, 319}
};

byte Edit_Byte, Edit_old, BrStepMax, ByteMax;
byte Obsi1 = 1, Obsi2 = 2, Obsi3 = 3, Obsi4 = 4, Obsi5 = 5, Obsi6 = 6;

int Xsize;                                    // ширина окна меню
int Y_S_win;                                  // высота строки
int Y_shift;
int8_t Vklad_G = 0, Vklad_G_old = 0, Vklad_G_Mem, Vklad_L_Mem;          // выбранная вкладка (новая, старая)
int8_t Vklad_L = 0, Vklad_L_old = 0;          // выбранная строка  (новая, старая)
int8_t Shag = 0, Shag_old = 0;
void *Wr_mem, *Wr_pr;
// -----------------
tmElements_t tm;
uint8_t hh, mm, ss;
#ifdef Set_TIME
// устанавливаем часы от времени компиляции / загрузки
uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
#endif

boolean initial = 1;
boolean RetGr;
float sx, sy, mx, my, hx, hy;
float sdeg, mdeg, hdeg, Fconst = 0.0174532925;
uint16_t osx, osy, omx, omy, ohx, ohy;
int16_t x0, x1, yy0, yy1;
uint16_t xpos; // x
uint16_t ypos; // y
bool Clock = false, Gt_Set = false, Svkl_L = false;  // Gt_Set=true;
static byte OldSek;

#define TimeSt_M 0
#define TempSt_M 1
#define TimeEnd_M 2
#define TempEnd_M 3
int Pr_Line_M[10][4];
// ----- для замера времени ------------
void Pr_WinTime() {
  Serial.print("time - ");
  Serial.println(micros() - WinStartTime);
}
// -----------------
void Pr_Line_Load(int i_i, int X_St, int Y_St, int X_En, int Y_En) {
  Pr_Line_M[i_i][0] =  X_St;
  Pr_Line_M[i_i][1] =  Y_St;
  Pr_Line_M[i_i][2] =  X_En;
  Pr_Line_M[i_i][3] =  Y_En;
}
// -----------------
double M_tg_Line(int i_i) {
  double Tg_ugla;
  Tg_ugla = 0;
  if (Pr_Line_M[i_i][2] != Pr_Line_M[i_i][0]) {
    Tg_ugla = Pr_Line_M[i_i][3] - Pr_Line_M[i_i][1];
    Tg_ugla = Tg_ugla / (Pr_Line_M[i_i][2] - Pr_Line_M[i_i][0]);
  }
  // Serial.print("Tg - "); Serial.println(Tg_ugla);
  return (Tg_ugla);
}
// -----------------
void M_ln_point (int X_tec, int XxSt, int YySt, int XxEn, int YyEn) {  // вывод линии попиксельно
  float Tg_ugla;
  if (X_tec - X_graf <= XxSt + 1 || X_tec - X_graf > XxEn + 1) return;
  // Serial.print(XxSt);  Serial.print("  ");  Serial.print(YySt);  Serial.print("  ");
  // Serial.print(XxEn);  Serial.print("  ");  Serial.println(YyEn);
  if (YySt == YyEn) {
    myGLCD.drawPixel(X_tec - 1, Y_graf - YySt);
    return;
  }
  float B_1 = XxEn - XxSt;
  float A_1 = YyEn - YySt;
  if (B_1 != 0) Tg_ugla = A_1 / B_1;
  else Tg_ugla = 0;                 // 30, 40, 210, 145
  int tt = Y_graf - (YySt + (X_tec - X_graf - XxSt) * Tg_ugla);
  // Serial.print(Tg_ugla,6);  Serial.print("  ");  Serial.println(tt);
  myGLCD.drawPixel(X_tec - 1, tt + 1);
  return;
}
// --------------------------------------------
void M_dr_line (int XxSt, int YySt, int XxEn, int YyEn) {   // рисуем линию на графике
  myGLCD.drawLine(X_graf + XxSt, Y_graf - YySt, X_graf + XxEn, Y_graf - YyEn);
  return;
}
// --------------------------------------------
void M_dr_point (int XxSt, int YySt) {                      // рисуем точку на графике
  myGLCD.drawPixel(X_graf + XxSt, Y_graf - YySt);
  return;
}
// --------------------------------------------
void M_dr_int (int IiInt, int XxSt, int YySt) {             // пишем число на графике
  myGLCD.printNumI(IiInt, X_graf + XxSt, Y_graf - YySt, 3);
  return;
}
//---------------------------------------------
void ButRight() {   //    "Button - RIGHT"
  if (reflowState == REFLOW_STATE_IDLE) {
    reflowState = REFLOW_STATE_PROFILE;
    updateScreen = true;
    return;
  }
  if (reflowState == REFLOW_STATE_PROFILE) {
    reflowState = REFLOW_STATE_SETTING;
    RetGr = true;
    updateScreen = true;
    return;
  }
  if (reflowState == REFLOW_STATE_SETTING) {
    if (Vklad_G == 1 && Shag < 3) {
      Shag += 1;
      return;
    }
    Shag = 0;  Shag_old = 0;
    Vklad_G += 1;
    if (Vklad_G >= Win1) Vklad_G = 0;
  }
}
//---------------------------------------------
void ButUp()    {    //    "Button - UP"
  if (reflowState == REFLOW_STATE_IDLE) {
    currentProfile = currentProfile + 1;
    if (currentProfile > numMax)  currentProfile = 1;
    loadProfile(currentProfile);
    VievTemp();
    PrPrint(B_SetX + 1, T_SetY);
    return;
  }
  if (reflowState == REFLOW_STATE_SETTING) {
    Vklad_L -= 1;
    if  (Vklad_G == 1) {
      if (Vklad_L < 1) Vklad_L = Win2 - 1;
      Shag_old = 9;
    }
    else if (Vklad_L < 0) Vklad_L = Win2 - 1;
    return;
  }
  if (reflowState == REFLOW_STATE_SET_EDIT) {
    ByteMax = 255;
    if (Vklad_G==0 || Vklad_G==1) {
      if (Vklad_G==0 && Vklad_L==0) ByteMax = 3;
      if (Vklad_L==1) ByteMax = 30;
      if (Vklad_L==4 || Vklad_L==5) ByteMax = 100;
      }     
      if (Edit_Byte < ByteMax) Edit_Byte += 1;
        else Edit_Byte = 0;
      return;     
  }
  if (reflowState == REFLOW_STATE_PROFILE) {
    currentProfile = currentProfile + 1;
    if (currentProfile > numMax)  currentProfile = 1;
    loadProfile(currentProfile);
    updateScreen = true;
    return;
  }
}
//---------------------------------------------
void ButDown()  {    //    "Button - DOWN"
  if (reflowState == REFLOW_STATE_IDLE) {
    currentProfile = currentProfile - 1;
    if (currentProfile <= 0) currentProfile = numMax;
    loadProfile(currentProfile);
    VievTemp();
    PrPrint(B_SetX + 1, T_SetY);
    return;
  }
  if (reflowState == REFLOW_STATE_SETTING) {
    Vklad_L += 1;
    if (Vklad_G == 1) {
      if (Vklad_L >= Win2) Vklad_L = 1;
      Shag_old = 8;
    }
    else if (Vklad_L >= Win2) Vklad_L = 0;
   return;
  }
  if (reflowState == REFLOW_STATE_SET_EDIT) {
    ByteMax = 255;
    if (Vklad_G==0 || Vklad_G==1) {
      if (Vklad_G==0 && Vklad_L==0) ByteMax = 3;
      if (Vklad_L==1) ByteMax = 30;
      if (Vklad_L==4 || Vklad_L==5) ByteMax = 99;
      }     
    if (Edit_Byte != 0) Edit_Byte -= 1;
      else Edit_Byte = ByteMax;
    return;
   
  }  
  if (reflowState == REFLOW_STATE_PROFILE) {
    currentProfile = currentProfile - 1;
    if (currentProfile <= 0) currentProfile = numMax;
    loadProfile(currentProfile);
    updateScreen = true;
    return;
  }
}
//---------------------------------------------
void ButLeft()  {    //    "Button - LEFT"
  if (reflowState == REFLOW_STATE_SETTING) {
    if (Vklad_G == 1 && Shag > 0) {
      if (Shag > 0)  Shag -= 1;
      return;
    }
    Vklad_G -= 1;
    if (Vklad_G < 0) {
      Vklad_G = 0;
      updateScreen = true;
      SaveProfile(currentProfile);
      if (RetGr == true) reflowState = REFLOW_STATE_PROFILE;
        else reflowState = REFLOW_STATE_IDLE;
      }
    return;
  }
  if (reflowState == REFLOW_STATE_IDLE) {
    reflowState = REFLOW_STATE_SETTING;
    RetGr = false;
    updateScreen = true;
    return;
  }
  if (reflowState == REFLOW_STATE_PROFILE) {
    reflowState = REFLOW_STATE_IDLE;
    updateScreen = true;
    RetGr = false;
    return;
  }
  if (reflowState == REFLOW_STATE_BRAZE_NOW) {
    updateScreen = true;
    reflowState = REFLOW_STATE_BRAZE_STOP;
    return;
  }
  if (reflowState == REFLOW_STATE_BRAZE_STOP) {
    reflowState = REFLOW_STATE_IDLE;
    updateScreen = true;
  }
}
//---------------------------------------------
void ButOk()    {    //    "Button - OK"
  if (reflowState == REFLOW_STATE_IDLE) {
    updateScreen = true;
    reflowState = REFLOW_STATE_BRAZE_START;
    return;
  }
  if (reflowState == REFLOW_STATE_SETTING) {   // переходим в режим редактирования
    reflowState = REFLOW_STATE_SET_EDIT;
    updateScreen = true;
    return;
  }
  if (reflowState == REFLOW_STATE_SET_EDIT) {  // возврат в меню настроек после редактирования
    *(byte*)Wr_mem = Edit_Byte;
    Vklad_L_old = 10;
    if (Vklad_G == 1) Shag_old = 8;
    reflowState = REFLOW_STATE_SETTING;
    myGLCD.setColor(VGA_BLACK);
    myGLCD.fillRoundRect(355, 240, 468, 308);
    return;
  }
  if (reflowState == REFLOW_STATE_PROFILE) {
    if (Gt_Set == false) Gt_Set = true;
    else Gt_Set = false;
  }
}
//---------------------------------------------
void Kn_work() {                    //  обработка нажатия кнопок
  if (AKeys.Key1() && !Key1_Old)  { //    "Button - RIGHT"
    Key1_Old = AKeys.Key1();         // отработка нажатия кнопки
    ButRight();
    //   Serial.println("Button - RIGHT");
    return;
  }
  if (AKeys.Key2() && !Key2_Old)  { //    "Button - UP"
    Key2_Old = AKeys.Key2();         // отработка нажатия кнопки
    // Serial.println("Button - UP");
    ButUp();
    return;
  }
  if (AKeys.Key3() && !Key3_Old)  { //    "Button - DOWN"
    Key3_Old = AKeys.Key3();        // отработка нажатия кнопки
    //   Serial.println("Button - DOWN");
    ButDown();
    return;
  }
  if (AKeys.Key4() && !Key4_Old)  { //    "Button - LEFT"
    Key4_Old = AKeys.Key4();           // отработка нажатия кнопки
    //   Serial.println("Button - LEFT");
    ButLeft();
    return;
  }
  if (AKeys.Key5() && !Key5_Old)  { //    "Button - OK"
    Key5_Old = AKeys.Key5();         // отработка нажатия кнопки
    //   Serial.println("Button - OK");
    ButOk();
    return;
  }
  return;
}
// --------------------------------------------
void TempRead() {                   //  чтение температуры
  if (Input1 == 0) Input1 = ReadCelsius(thermoCLK, thermoCS_T, thermoDO);
    else Input1 = Input1 * 0.8 + 0.2 * (ReadCelsius(thermoCLK, thermoCS_T, thermoDO) + Corect_T);
  if (Input2 ==0) Input2 = ReadCelsius(thermoCLK2, thermoCS_B, thermoDO2);
    else Input2 = Input2 * 0.8 + 0.2 * (ReadCelsius(thermoCLK2, thermoCS_B, thermoDO2) + Corect_B);
  tc1 = Input1;
  tc2 = Input2;
}
// --------------------------------------------
void VievTempGl() {
  if (isnan(Input1)) {
    myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_RED);
    myGLCD.print(F("ERORR"), 12, 37);
  }
  else {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(VGA_SILVER);
    myGLCD.printNumI(tc1, 5, 20, 3, '0');
  }
  if (isnan(Input2)) {
    myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_RED);
    myGLCD.print(F("ERORR"), 388, 37);
  }
  else {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(VGA_SILVER);
    myGLCD.printNumI(tc2, 380, 20, 3, '0');
  }
}
//---------------------------------------------
void ProfEdit_2() {                 //  начало экрана настроек
  Vklad_G = 0;
  Vklad_L = 0;
  myGLCD.clrScr();
  PrPrint(0, 2);
  Vklad_G_old = 15;
  Vklad_L_old = 15;
  Svkl_L = false;
  K_Kpres_ok = false;
  NewPos = 0; LastPos = 0;
  encoder.setPosition(0);
  updateScreen = false;
}
// --------------------------------------------
void Dimming() {
  OutPWR_TOP();
  OutPWR_BOTTOM();
}
// --------------------------------------------
void OutPWR_TOP() {
  reg1 = round(Output1) + er1; //pwr- задание выходной мощности в %,в текущем шаге профиля, er- ошибка округления
  if (reg1 < 50) {
    out1 = LOW;
    er1 = reg1; // reg- переменная для расчетов
  }
  else {
    out1 = HIGH;
    er1 = reg1 - 100;
  }
  digitalWrite(RelayPin1, out1); //пин через который осуществляется дискретное управление
}
//---------------------------------------------
void OutPWR_BOTTOM() {
  reg2 = round(Output2) + er2; //pwr- задание выходной мощности в %, er- ошибка округления
  if (reg2 < 50) {
    out2 = LOW;
    er2 = reg2; // reg- переменная для расчетов
  }
  else {
    out2 = HIGH;
    er2 = reg2 - 100;
  }
  digitalWrite(RelayPin2, out2); //пин через который осуществляется дискретное управление
}
//---------------------------------------------
byte Pid1(double temp, double ust, byte kP, byte kI, byte kd)   { // верх
  byte out = 0;
  static float ed = 0;
  e1 = (ust - temp); //ошибка регулирования
  p1 =  (kP * e1); //П составляющая
  integra = (integra < i_min) ? i_min : (integra > i_max) ? i_max : integra + (kI * e1) / 1000.0; //И составляющая
  d1 = kd * (e1 - ed); //Д составляющая
  ed = e1;
  out = (p1 + integra + d1 < u.Profili.min_pwr_TOPStep[currentStep - 1])
        ? u.Profili.min_pwr_TOPStep[currentStep - 1]
        : (p1 + integra + d1 > u.Profili.max_pwr_TOPStep[currentStep - 1])
        ? u.Profili.max_pwr_TOPStep[currentStep - 1] : p1 + integra + d1;
  return out;
}
//---------------------------------------------
byte Pid2(double temp, double ust, byte kP, byte kI, byte kd) {  // низ 
  byte out = 0;
  static float ed = 0;
  e2 = (ust - temp);   //ошибка регулирования
  p2 =  (kP * e2);     //П составляющая
  integra2 = (integra2 < i_min) ? i_min : (integra2 > i_max) ? i_max : integra2 + (kI * e2) / 1000.0; //И составляющая
  d2 = kd * (e2 - ed); //Д составляющая
  ed = e2;
  out = (p2 + integra2 + d2 < u.Profili.min_pwr_BOTTOM) ? u.Profili.min_pwr_BOTTOM : (p2 + integra2 + d2 > bottomMaxPwr) ? bottomMaxPwr : p2 + integra2 + d2;
  return out;
}
// --------------------------------------------
void Ramka(int i, word color) {
  myGLCD.setColor(color);
  myGLCD.drawRoundRect(BattSet[i][0], BattSet[i][1], BattSet[i][2], BattSet[i][3]);
  myGLCD.drawRoundRect(BattSet[i][0] + 1, BattSet[i][1] + 1, BattSet[i][2] - 1, BattSet[i][3] - 1);
}
// ---------------------------------------------------
void Zegar() {                      // рисуем циферблат

  myGLCD.setColor(VGA_LIME);
  myGLCD.drawCircle(xpos, ypos, ypos - 1);
  myGLCD.drawCircle(xpos, ypos, ypos - 2);
  myGLCD.setColor(VGA_RED);
  myGLCD.drawCircle(xpos, ypos, ypos - 5);
  myGLCD.drawCircle(xpos, ypos, ypos - 6);
  for (int i = 0; i < 360; i += 30) {       // Draw 12 lines
    sx = cos((i - 90) * Fconst);
    sy = sin((i - 90) * Fconst);
    x0 = sx * (ypos - 6) + xpos;
    yy0 = sy * (ypos - 6) + ypos;
    x1 = sx * (ypos - 22) + xpos;
    yy1 = sy * (ypos - 22) + ypos;
    myGLCD.drawLine(x0, yy0, x1, yy1);
  }
  myGLCD.setColor(VGA_WHITE);
  for (int i = 0; i < 360; i += 6) {        // Draw 60 dots
    sx = cos((i - 90) * Fconst);
    sy = sin((i - 90) * Fconst);
    x0 = sx * (ypos - 22) + xpos;
    yy0 = sy * (ypos - 22) + ypos;
    // Draw minute markers
    myGLCD.drawPixel(x0, yy0);
    // Draw main quadrant dots
    if (i == 0 || i == 90 || i == 180 || i == 270) myGLCD.fillCircle(x0, yy0, 4);
  }
  myGLCD.fillCircle(xpos, ypos, 7);

}
// --------------------------------------------
void VievTemp() {                   // вывод температуры профиля на главный экран
  myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_SILVER);
  myGLCD.printNumF(u.Profili.rampRateBOTTOM * 0.1, 0, 385, 75);
  myGLCD.printNumF(u.Profili.rampRateStep[0] * 0.1, 0, 0, 75);
  j = 0;
  for (i = 0; i < 4; i++) {
    if (u.Profili.temperatureStep[i] > j) j = u.Profili.temperatureStep[i];
  }
  myGLCD.printNumI(j, 0, 95, 3, '0');
  myGLCD.printNumI(u.Profili.temperatureBOTTOM, 410, 95, 3, '0');

}
// --------------------------------------------
void GlabPrint() {                  // главный экран
  Clock = true;
  myGLCD.clrScr();
  Zegar();
  myGLCD.setFont(BigFontRus);
  myGLCD.setColor(VGA_LIME);
  myGLCD.textRus(F("ВЕРХ "), 22, 2);
  myGLCD.textRus(F("НИЗ "), 404, 2);
  myGLCD.setColor(VGA_SILVER);
  myGLCD.textRus(F("` "), 55, 95);
  myGLCD.textRus(F("`/с "), 50, 75);
  myGLCD.textRus(F("` "), 460, 95);
  myGLCD.textRus(F("`/с "), 435, 75);
  VievTemp();
  K_Kpres_ok = false;
  PrPrint(B_SetX + 1, T_SetY);
  myGLCD.setColor(VGA_ORAN);
  for (i = 0; i < 5; i++) {
    if (i == LastPos) Ramka( i, VGA_RED);
    else Ramka( i, VGA_SILVER);
  }
#ifdef Set_Picture
  myGLCD.drawBitmap(BattSet[1][0] + 10, BattSet[1][1] + 7, 68, 48, Graf, 1);
  myGLCD.drawBitmap(BattSet[0][0] + 10, BattSet[0][1] + 7, 68, 48, Graf2, 1);
  myGLCD.drawBitmap(BattSet[2][0] + 10, BattSet[2][1] + 7, 68, 48, Graf3, 1);
  myGLCD.drawBitmap(BattSet[3][0] + 10, BattSet[3][1] + 7, 68, 48, Graf4, 1);
#endif
  updateScreen = false;
}
// --------------------------------------------
void PrPrint(int X, int Y) {        // номер и название профиля
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect(X, Y, 479 - X - 1, Y + 15);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_ORAN);
  myGLCD.printNumI(currentProfile, X, Y, 2);
  myGLCD.setFont(BigFontRus);
  myGLCD.setColor(VGA_LIME);
  myGLCD.textRus(DuStr, X + 40, Y);
}
// --------------------------------------------
void DumpMem (byte NnProf) {        // читаем ПЗУ в СОМ порт

  // Для экономии места все Serial закомментированы
  // для печати на экран все комменты < // > убрать
  // и в функции loadProfile снять комменты с вызова DumpMem

  //Serial.println("Читаем пзу ");
  byte DuBre = 0;
  String DuStr = "";
  for (byte j = 0; j <= SizePrrof - 1; j++) {
    if (j % 10 == 0) {
      //Serial.print(Adres+((NnProf-1)*SizePrrof)+j);
      //Serial.print(" ");
    }
    DuBre = EEPROM.read(Adres + ((NnProf - 1) * SizePrrof) + j);
    //Serial.print(DuBre);
    //Serial.print(" ");
    //if (j%10 == 9) Serial.println("");
    if (j == ArrMax - 1) {
      //Serial.println("");
      DuStr = String(u.Profili.HeadProf);
      //Serial.println(DuStr);
      //Serial.print(Adres+((NnProf-1)*SizePrrof)+j);
      //Serial.print(" ");
    }

  }
  Serial.println("");
}
// ------------------------------
void loadProfile(byte NnProf) {     //  загрузка текущего профиля
  DuStr = "";
  String DuVr;
  for (byte j = 0; j <= SizePrrof - 1; j++) {
    u.Mode[j] = EEPROM.read(Adres + ((NnProf - 1) * SizePrrof) + j);
  }
  DuVr = String(u.Profili.HeadProf);
  if (u.Mode[1] == 255)  DuStr += "НЕИЗВЕСТНЫЙ ПРОФИЛЬ " + String(NnProf) + " ";
  else {
    for (byte i = 0; i < ArrMax; i++) {
      if (DuVr.substring(i, i + 1) == "\0" || DuVr.substring(i, i + 1) == "\n") {
        DuStr += DuVr.substring(0, i);
        DuStr += "\n";
        i = ArrMax;
      }
    }
  }
  if (DuStr.length() == 0) DuStr += "НЕИЗВЕСТНЫЙ ПРОФИЛЬ " + String(NnProf) + " ";
  // Serial.print(DuStr.length()); Serial.print(" -"); Serial.println(DuStr);
  // DumpMem(NnProf);
}
// --------------------------------------------
void SaveProfile(byte NnProf) {     //  сохранение текущего профиля
  for (byte j = ArrMax - 1; j <= SizePrrof - 1; j++) {
    EEPROM.update(Adres + ((NnProf - 1)*SizePrrof) + j, u.Mode[j]);
 }
  // DumpMem(NnProf);
}
// --------------------------------------------
void In_Line(int t_start) {         //  рисуем профиль на графике
  int Temp_Start = t_start, Temp_End;
  int Time_Start = 0, Time_End;
  int Rt;
  // рисуем график температуры НИЗа
  myGLCD.setColor(VGA_RED);
  Temp_End = u.Profili.temperatureBOTTOM;
  Time_End = Time_Start + (10 * (Temp_End - t_start)) / u.Profili.rampRateBOTTOM;
  M_dr_line (Time_Start, Temp_Start, Time_End, u.Profili.temperatureBOTTOM);          // участок роста температуры
  Pr_Line_Load (0, Time_Start, Temp_Start, Time_End, u.Profili.temperatureBOTTOM);
  M_dr_int(u.Profili.dwellTimerBOTTOM, Time_End, u.Profili.temperatureBOTTOM - 3);    // надписи температуры и задержка
  M_dr_int(u.Profili.temperatureBOTTOM, Time_End - 26, u.Profili.temperatureBOTTOM + 10);
  Rt = Time_End;
  Time_End += u.Profili.dwellTimerBOTTOM;
  Time_Start = Time_End;
  Temp_Start = u.Profili.temperatureBOTTOM;

  // рисуем график температуры ВЕРХа по шагам
  myGLCD.setColor(VGA_ORAN);
  for (int i = 0; i < 4; i++) {
    if (u.Profili.rampRateStep[i] == 0) {
      BrStepMax = i * 2;
      break;
    }
    Temp_End = u.Profili.temperatureStep[i] - Temp_Start;
    if (Temp_End < 0) Temp_End = - Temp_End;
    Time_End = Time_Start + (10 * Temp_End) / u.Profili.rampRateStep[i];
    M_dr_line (Time_Start, Temp_Start, Time_End, u.Profili.temperatureStep[i]);
    Pr_Line_Load ((i + 1) * 2, Time_Start, Temp_Start, Time_End, u.Profili.temperatureStep[i]);

    M_dr_int(u.Profili.dwellTimerStep[i], Time_End, u.Profili.temperatureStep[i] - 3);
    M_dr_int(u.Profili.temperatureStep[i], Time_End - 26, u.Profili.temperatureStep[i] + 10);

    M_dr_line (Time_End, u.Profili.temperatureStep[i], Time_End + u.Profili.dwellTimerStep[i], u.Profili.temperatureStep[i]);
    Pr_Line_Load( (i + 1) * 2 + 1, Time_End, u.Profili.temperatureStep[i], Time_End + u.Profili.dwellTimerStep[i], u.Profili.temperatureStep[i]);
    Time_End += u.Profili.dwellTimerStep[i];
    Temp_Start = u.Profili.temperatureStep[i];
    Time_Start = Time_End;
  }
  myGLCD.setColor(VGA_RED);
  M_dr_line (Rt, u.Profili.temperatureBOTTOM, Time_Start, u.Profili.temperatureBOTTOM);    // горизонтальный участок низа
  Pr_Line_Load(1, Rt, u.Profili.temperatureBOTTOM, Time_Start, u.Profili.temperatureBOTTOM);

  /* for (i=0; i<10; i++) {    // вывод в порт массива
      for (int j=0; j<4; j++) {
       Serial.print(Pr_Line_M[i][j]);
       Serial.print("  ");
      }
      Serial.println("");
     } // */
}
// --------------------------------------------
void Sec_metr() {
  RTC.read(tm);
  if (OldSek != tm.Second) {
    OldSek = tm.Second;
    ss++;
    if (ss == 60) {
      ss = 0;
      mm++;
    }
    myGLCD.setColor(VGA_BLACK);
    myGLCD.fillRoundRect(432, TempY, 447, TempY + 16);
    myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_SILVER);

    myGLCD.printNumI(mm, 400, TempY, 2, '0');
    myGLCD.printNumI(ss, 448, TempY, 2, '0');
  }
}
// --------------------------------------------
void Pr_Stels () {                  //  движение стрелок в часах
  if (!RTC.read(tm))  Serial.println(" не прочитались часы");
  if (OldSek == tm.Second) return;
  ss = tm.Second;             // Advance second
  OldSek = ss;
  mm = tm.Minute;             // Advance minute
  hh = tm.Hour;               // Advance hour

  sdeg = ss * 6;                     // 0-59 -> 0-354
  mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds, but these increments are not used
  hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - includes minutes and seconds, but these increments are not used
  hx = cos((hdeg - 90) * Fconst);
  hy = sin((hdeg - 90) * Fconst);
  mx = cos((mdeg - 90) * Fconst);
  my = sin((mdeg - 90) * Fconst);
  sx = cos((sdeg - 90) * Fconst);
  sy = sin((sdeg - 90) * Fconst);

  myGLCD.setColor(VGA_BLACK);
  if (ss == 0 || initial) {
    initial = 0;
    // Erase hour and minute hand positions every minute
    myGLCD.drawLine(ohx, ohy, xpos, ypos);
    ohx = hx * (ypos / 2) + xpos + 1;
    ohy = hy * (ypos / 2) + ypos;
    myGLCD.drawLine(omx, omy, xpos, ypos);
    omx = mx * (ypos / 2 + 30) + xpos;
    omy = my * (ypos / 2 + 30) + ypos;
  }
  // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
  myGLCD.drawLine(osx, osy, xpos, ypos);
  osx = sx * (ypos / 2 + 40) + xpos + 1;
  osy = sy * (ypos / 2 + 40) + ypos;

  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawLine(ohx, ohy, xpos, ypos);  // часовая стрелка
  myGLCD.drawLine(omx, omy, xpos, ypos);  // минутная стрелка

  myGLCD.setColor(VGA_RED);               // секундная стрелка
  myGLCD.drawLine(osx, osy, xpos, ypos);
  myGLCD.fillCircle(xpos, ypos, 7);
}
// --------------------------------------------
void Pr_Ramka_Y (int i) {           //  рисуем желтую рамку большую
  myGLCD.setColor(VGA_BLACK);     // стираем староое
  myGLCD.drawLine(0, Ywin1, 479, Ywin1);
  myGLCD.drawLine(0, Ywin1 - 1, 479, Ywin1 - 1);
  myGLCD.drawLine(0, Ywin1 - 2, 479, Ywin1 - 2);

  myGLCD.setColor(VGA_ORAN);   // рисуем желтую рамку большую
  myGLCD.drawLine(Xsize * i + 1, Yset + 1, Xsize * i + 1, Ywin1 - 1);
  myGLCD.drawLine(Xsize * i + 2, Yset + 1, Xsize * i + 2, Ywin1 - 2); //2
  myGLCD.drawLine(Xsize * i, Ywin1 - 2, 1, Ywin1 - 2);
  myGLCD.drawLine(Xsize * i, Ywin1 - 1, 0, Ywin1 - 1); //2
  myGLCD.drawLine(0, Ywin1 - 2, 0, 318);
  myGLCD.drawLine(1, Ywin1, 1, 318);                     //2
  myGLCD.drawLine(1, 319, 478, 319);
  myGLCD.drawLine(1, 318, 478, 318);                            //2
  myGLCD.drawLine(479, 318, 479, Ywin1 - 1);
  myGLCD.drawLine(478, 318, 478, Ywin1 - 1);               //2
  myGLCD.drawLine(479, Ywin1 - 2, Xsize * (i + 1) - 2, Ywin1 - 2);
  myGLCD.drawLine(478, Ywin1 - 1, Xsize * (i + 1) - 2, Ywin1 - 1); //2
  myGLCD.drawLine(Xsize * (i + 1) - 2, Ywin1 - 2, Xsize * (i + 1) - 2, Yset + 2);
  myGLCD.drawLine(Xsize * (i + 1) - 3, Ywin1 - 2, Xsize * (i + 1) - 3, Yset + 2); //2
  myGLCD.drawLine(Xsize * i + 2, Yset, Xsize * (i + 1) - 3, Yset);
  myGLCD.drawLine(Xsize * i + 1, Yset + 1, Xsize * (i + 1) - 2, Yset + 1); //2
}
// --------------------------------------------
void K_Setka() {
  myGLCD.setFont(SmallFont);
  for (i = 0; i <= K_line; i++)  {      // рисуем горизонтальные линии
    myGLCD.setColor(VGA_ORAN);         // 250, 180, 000
    myGLCD.printNumI((K_line - i) * 20, 0, Py_pr + i * 20 , 3); //,'0'
    myGLCD.setColor(30, 30, 30);
    myGLCD.drawLine(X_graf, Py_pr + 6 + i * 20, 479, Py_pr + 6 + i * 20);
  }
  myGLCD.setColor(VGA_ORAN);
  myGLCD.drawLine(X_graf - 3, Y_graf, 479, Y_graf);
  myGLCD.drawLine(X_graf - 3, Y_graf + 1, 479, Y_graf + 1);
  byte nn = 0;
  for (i = 0; i <= 15; i++)  {           // рисуем нижнюю шкалу
    myGLCD.drawLine(X_graf + i * 30, Y_graf - 6, X_graf + i * 30, Y_graf - 1);
    if (i > 0) nn = 4;
    if (i > 3) nn = 8;
    myGLCD.printNumI(i * 30, nn + 9 + i * 30, Y_graf + 4 , 3);
  }
}
// --------------------------------------------
void press_ok() {               // обработчик короткого  ok()
  if (reflowState == REFLOW_STATE_IDLE)       {
    switch (LastPos)   {
      case 0: {
          if (!K_Kpres_ok) {   // ButLeft переход в настройки
            ButLeft();
            K_Kpres_ok = true;
            Svkl_L = false;
          }
          break;
        }
      case 1: {
          if (!K_Kpres_ok) {   // ButRight переход к графикам профиля
            ButRight();
            K_Kpres_ok = true;
          }
          break;
        }
      case 2: {
          ButUp();
          break;
        }
      case 3: {
          ButDown();
          break;
        }
      case 4: {
          ButOk();
          break;
        }
    }
  }
  if (reflowState == REFLOW_STATE_SETTING)    {
    if (!Svkl_L && !K_Kpres_ok)  {
      Vklad_G_Mem = Vklad_G;
      SetStrL(true);
      Vklad_L = 0;
      if (Vklad_G == 1) Vklad_L = 1;
      NewPos = Vklad_L;
      encoder.setPosition(NewPos);
      K_Kpres_ok = true;
    }
    if (Svkl_L && !K_Kpres_ok)  {     // переход в редактирование параметра
      Pos_Mem = LastPos;
      K_Kpres_ok = true;
      NewPos = 2;
      encoder.setPosition(NewPos);
      ButOk();
    }
  }
  if (reflowState == REFLOW_STATE_PROFILE)    {
    if (!K_Kpres_ok) {
      ButRight();
    }
  }
  if (reflowState == REFLOW_STATE_SET_EDIT)   {  // возврат в меню настроек после редактирования
    if (K_Kpres_ok) return;
    NewPos = Pos_Mem;
    encoder.setPosition(NewPos);
    ButOk();
  }
}
// --------------------------------------------
void longPress_ok() {           // обработчик длинного ok()
  if (reflowState == REFLOW_STATE_SETTING) {
    if (Svkl_L) {
      SetStrL(false);
      NewPos = Vklad_L;
      encoder.setPosition(NewPos);
      Shag_old = 10;
      Vklad_L = 0;
    }
    else {
      Vklad_G = -1;
      NewPos = 0;
      ButLeft();
    }
  return;
  }
  if (reflowState == REFLOW_STATE_PROFILE || reflowState == REFLOW_STATE_BRAZE_NOW
      || reflowState == REFLOW_STATE_BRAZE_STOP  )    {
    Vklad_G = -1;
    NewPos = 0;
    ButLeft();
  }
}
// --------------------------------------------
void TimeLine(int XT) {
  byte hh = 0;
  if (XT > 50 && XT < 146) hh = 50;
  if (XT >= 146 && XT < 182) hh = 17;
  myGLCD.setColor(VGA_BLACK);
  myGLCD.drawLine(XT - 1, Py_pr + hh + 1, XT - 1, 263); // стираем старую таймлайн линию
  myGLCD.setColor(VGA_SILVER);     // 250, 180, 000
  myGLCD.drawLine(XT, Py_pr + hh + 1, XT, 263);  // рисуем новую
  myGLCD.setColor(30, 30, 30);     // VGA_SILVER
  for (i = 0; i < K_line; i++)  {                 // восстанавливаем сетку
    myGLCD.drawPixel(XT - 1, Py_pr + 6 + i * 20);
  }
  myGLCD.setColor(VGA_ORAN);
}
// --------------------------------------------
void SetStrL (bool Vk_L) {
  Svkl_L = Vk_L;
  if (!Vk_L) myGLCD.setColor(VGA_BLACK);
  else myGLCD.setColor(VGA_RED);
  myGLCD.drawLine(3, Ywin1, 3, 316);
  myGLCD.drawLine(4, Ywin1, 4, 316);                     //2
  myGLCD.drawLine(5, Ywin1, 5, 316);
}
// --------------------------------------------
void TempBraze () {
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(VGA_RED);
  myGLCD.printNumI(tc2, 340, 200, 3, '0'); // выводим температуру низа
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(Output2 , 440, 200, 2, '0'); // выводим мощность низа
  if (TopStart == false)  myGLCD.setColor(VGA_SILVER);
  myGLCD.printNumI(Output1, 150, 30, 2, '0');   // выводим мощность верха
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(tc1, 50, 30, 3, '0'); // выводим температуру верха
}
// --------------------------------------------
void TonGo () {
  //Мелодия приветствия Марио
  tone(buzzerPin,1318,150);
  delay(150);
  tone(buzzerPin,1318,300);
  delay(300);
  tone(buzzerPin,1318,150);
  delay(300);
  tone(buzzerPin,1046,150);
  delay(150);
  tone(buzzerPin,1318,300);
  delay(300);
  tone(buzzerPin,1568,600);
  delay(600);
  tone(buzzerPin,784,600);
  delay(600);
  noTone(buzzerPin); 
  delay(2000);   
}
// --------------------------------------------
void HeartPic () {
   #ifdef SetPicHeater
    myGLCD.drawBitmap(65, 95, 64, 64, Heater2, 1);
    #define SsPic1 150
    #define SsPic2 170
   #else
    #define SsPic1 CENTER
    #define SsPic2 CENTER
  #endif
  myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_GREEN);
  myGLCD.print(F("ARDUINO MEGA2560"),SsPic1, 105);   //CENTER
  myGLCD.setColor(VGA_RED);
  myGLCD.print(F("REWORK STATION"),SsPic2, 140);     //
//  myGLCD.setColor(250, 180, 000);
//  myGLCD.print(F("TFT-LCD 480*320 MAX6675_Dimmer"),CENTER, 180);
  myGLCD.setColor(VGA_SILVER);
  myGLCD.print(F("Watashi Svs_V07"),CENTER, 210);
  TonGo();       //Мелодия приветствия Марио
}
// --------------------------------------------

#ifdef SetTouch1
bool TouchGet() {
  tp = ts.getPoint();   // tp.x, tp.y считываем тач
  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
    xpok = map(tp.x, TS_LEFT, TS_RT, 0, DisXSize);
    ypok = map(tp.y, TS_TOP, TS_BOT, 0, DisYSize);
    //Serial.println("xpok = " + String(xpok) + "  ypok = " + String(ypok));
    return (true);
  }
  return (false);
}
#endif  
// --------------------------------------------
#ifdef SetTouch2
bool TouchGet() {
  if (myTouch.dataAvailable() == true) {
    myTouch.read();
    xpok = myTouch.getX();
    ypok = myTouch.getY();
    if ((xpok != 0xFFFF) || (ypok != 0xFFFF))  {
//      Serial.print(xpok, HEX); Serial.print(" "); Serial.println(ypok);
      return (true);
      }
    }
  return (false);
}
#endif

//       Pr_WinTime();    // на экран засеченное время в мсек
//       WinStartTime = micros();

// --------------------------------------------
void setup() {
  myGLCD.InitLCD();
  myGLCD.clrScr();
  HeartPic ();
  Serial.begin(9600);
#ifdef SetTouch1
  SetPinTouch1();
    switch (Orientation) {      // adjust for different aspects
    case 0:   break;          //no change,  calibrated for PORTRAIT
    case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
    case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
    case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
    } 
#endif
#ifdef SetTouch2
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
#endif
  //setup pins as input for buttons
  pinMode (buzzerPin, OUTPUT);
  pinMode(P1_PIN, OUTPUT);
  digitalWrite(P1_PIN, HIGH); 
  pinMode(P2_PIN, OUTPUT);
  digitalWrite(P2_PIN, HIGH); 
  pinMode(P3_PIN, OUTPUT);
  digitalWrite(P3_PIN, HIGH); 
  pinMode(P4_PIN, OUTPUT);
  digitalWrite(P4_PIN, HIGH); 
  Set_Pin_6675();             // настраиваем порты max6675
  //
  DisXSize = myGLCD.getDisplayXSize();
  DisYSize = myGLCD.getDisplayYSize();
  currentProfile = 1;
  loadProfile(currentProfile);
  Xsize = myGLCD.getDisplayXSize() / Win1;
  Y_S_win = (myGLCD.getDisplayYSize() - (Ywin0) - 2) / Win2;
  Y_shift = Ywin0 + (Y_S_win - 16) / 2;
  //setup ssr pins as outputs
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  encoder.setPosition(2 / ROTARYSTEPS); // start with the value of 1

#ifdef Set_TIME
  tm.Hour = conv2d(__TIME__);
  tm.Minute = conv2d(__TIME__ + 3);
  tm.Second = conv2d(__TIME__ + 6);
  RTC.write(tm);    // Записываем время в модуль:
#endif
  xpos = -1 + myGLCD.getDisplayXSize() / 2;
  ypos = -1 + (myGLCD.getDisplayYSize() - 50) / 2;

  nextRead1 = millis();
#ifdef SetInterrupt
  attachInterrupt(SetInterrupt, Dimming, RISING); // настроить порт прерывания(0 или 1) 2й или 3й цифровой пин
#else
  MsTimer2::set(10, Dimming); // 100ms period
  MsTimer2::start();
#endif
} // end  setup
// ------------------------------------------------------
void loop() {
  unsigned long currentMillis = millis();
  // Serial.println(analogRead(Knopki));
  if (AKeys.Refresh(analogRead(Knopki))) Kn_work();  // состояние кнопок, если нажата кнопка отрабатываем нажатие
  else {   // сброс флага нажатия
    if (!AKeys.Key1() && Key1_Old) Key1_Old = 0;
    if (!AKeys.Key2() && Key2_Old) Key2_Old = 0;
    if (!AKeys.Key3() && Key3_Old) Key3_Old = 0;
    if (!AKeys.Key4() && Key4_Old) Key4_Old = 0;
    if (!AKeys.Key5() && Key5_Old) Key5_Old = 0;
  }

  Btn_ok.run(&press_ok, &longPress_ok);              // опрашиваем кнопку энкодера
  encoder.tick();                                    // читаем енкодер
  NewPos = encoder.getPosition();
  // Serial.print(NewPos); Serial.print("  "); Serial.print(Svkl_L); Serial.print("  ");  Serial.println(reflowState);
  if (LastPos != NewPos) {
    if (reflowState == REFLOW_STATE_IDLE)       {
      if (NewPos > 4) {
        NewPos = 0;
        encoder.setPosition(NewPos);
      }
      if (NewPos < 0) {
        NewPos = 4;
        encoder.setPosition(NewPos);
      }
      Ramka(LastPos, VGA_SILVER);
      Ramka(NewPos, VGA_RED);
      LastPos = NewPos;
    }
    if (reflowState == REFLOW_STATE_SETTING)    {
      if (!Svkl_L) {
        //Serial.print("тут1  ");
        if (NewPos > 3) {
          NewPos = 0;
          encoder.setPosition(NewPos);
        }
        if (NewPos < 0) {
          NewPos = 3;
          encoder.setPosition(NewPos);
        }
        if (Vklad_G == 1) {
          if (NewPos > LastPos) {
            if (Shag != 3) {
              Shag += 1;
              encoder.setPosition(LastPos);
              return;
            }
          }
          if (NewPos < LastPos) {
            if (Shag != 0) {
              Shag -= 1;
              encoder.setPosition(LastPos);
              return;
            }
          }
        }
        Vklad_G = NewPos;
        Shag = 0;  Shag_old = 0;
        LastPos = NewPos;
      }
      else {
        K_Pos = 0;
        if (Vklad_G == 1) {
          K_Pos = 1;
          //Shag_old = 0;
        }
        if (NewPos > 5) {
          NewPos = K_Pos;
          encoder.setPosition(NewPos);
        }
        if (NewPos < K_Pos) {
          NewPos = 5;
          encoder.setPosition(NewPos);
        }
        Vklad_L = NewPos;
        LastPos = NewPos;
        Vklad_L_old = 15;
        return;
      }
    }
    if (reflowState == REFLOW_STATE_PROFILE)    {
      if (NewPos > numMax) {
        NewPos = 1;
        encoder.setPosition(NewPos);
      }
      if (NewPos < 1) {
        NewPos = numMax;
        encoder.setPosition(NewPos);
      }
      currentProfile = NewPos;
      loadProfile(currentProfile);
      updateScreen = true;
      LastPos = NewPos;
    }
    if (reflowState == REFLOW_STATE_SET_EDIT)   {
      if (NewPos > LastPos) {
        ButUp();
        encoder.setPosition(LastPos);
        return;
      }
      if (NewPos < LastPos) {
        ButDown();
        encoder.setPosition(LastPos);
        return;
      }
    }
  }

#ifdef Set_Touch
  if (TouchGet()) {                                // обработка нажатия на тач
    if (reflowState == REFLOW_STATE_IDLE)       {
      for (i = 0; i <= 4; i++) {
        if (xpok > BattSet[i][0] && xpok < BattSet[i][2] &&
            ypok > BattSet[i][1] && ypok < BattSet[i][3] ) {
          Ramka(LastPos, VGA_SILVER);
          Ramka(i, VGA_RED);
          LastPos = i; encoder.setPosition(i);
          switch (i)   {
            case 0: {
                ButLeft();
                i = 5;
                break;
              }
            case 1: {
                ButRight();
                i = 5;
                break;
              }
            case 2: {
                if (!T_KeyUp_Old) {
                  T_KeyUp_Old = true;
                  ButUp(); i = 5;
                }
                break;
              }
            case 3: {
                if (!T_KeyDown_Old) {
                  T_KeyDown_Old = true;
                  ButDown(); i = 5;
                  break;
                }
              }
            case 4: {
                ButOk();
                i = 5;
                break;
              }
          }
        }
      }
    }
    if (reflowState == REFLOW_STATE_PROFILE)    {
      if (xpok > 0 && xpok < 40 && ypok > 30 && ypok < 300) ButLeft();
      if (xpok > 430 && xpok < 478 && ypok > 30 && ypok < 300) ButRight();
    }
    if (reflowState == REFLOW_STATE_BRAZE_NOW || reflowState == REFLOW_STATE_BRAZE_STOP)  {
      if (xpok > 0 && xpok < 40 && ypok > 30 && ypok < 300) ButLeft();
    }
    if (reflowState == REFLOW_STATE_SETTING)    {
      for (i = 0; i < Win1; i++)  {
        if (xpok > Xsize * i && xpok < Xsize * (i + 1) && ypok > 0 && ypok < Ywin0) {
          Vklad_G = i;
          Shag = 0;  Shag_old = 0;
          encoder.setPosition(i);
          Svkl_L = false;
          break;
        }
      }
      for (i = 0; i <= Win2; i++) {
        if (xpok > 40 && xpok < 355 && ypok > i * Y_S_win + Ywin0 && ypok < (i + 1)*Y_S_win + Ywin0) {
          if (Vklad_G == 1 && Shag <= 3 && !T_KeyNext && i == 0) {
            if (Svkl_L) {
              T_KeyNext = true;
              SetStrL(false);
              LastPos = 0;
              Shag_old = 10;
              Vklad_L = 0;
              encoder.setPosition(1);
              break;
            }
            else {
              T_KeyNext = true;
              Shag += 1;
              if (Shag > 3)  Shag = 0;
              break;
            }
          }
          Vklad_L = i;
          encoder.setPosition(i);
          SetStrL(true);
          //Shag_old = 0;
          break;
        }
      }
      if (xpok > 355 && xpok < 468 && ypok > 166 && ypok < 235 && !T_KeyOk) {  // окно редактирования параметра
        T_KeyOk = true;
        ButOk();
      }
      if (xpok > 0 && xpok < 40 && ypok > 30 && ypok < 300) {
        Vklad_G = 0;
        ButLeft();
      }
    }
    if (reflowState == REFLOW_STATE_SET_EDIT)   {
      if (xpok > 355 && xpok < 468 && ypok > 166 && ypok < 235 && !T_KeyOk) {
        T_KeyOk = true;
        ButOk();
      }
      if (xpok > 411 && xpok < 468 && ypok > 240 && ypok < 308 && !T_KeyRight_Old) {
        T_KeyRight_Old = true;
        ButUp();
      }
      if (xpok > 355 && xpok < 410 && ypok > 240 && ypok < 308 && !T_KeyLeft_Old) {
        T_KeyLeft_Old = true;
        ButDown();
      }
    }
  }
  else {            // если тач не нажат сбрасываем флаги нажатия
    T_KeyUp_Old = false;
    T_KeyDown_Old = false;
    T_KeyNext = false;
    T_KeyOk = false;
    T_KeyRight_Old = false;
    T_KeyLeft_Old = false;
  }
#endif

  switch (reflowState)              {          //  переключатель состояния
    case REFLOW_STATE_IDLE:         {          //  Главный экран
        if (updateScreen) GlabPrint();           //  настройка экрана Рабочий режим
        Pr_Stels();                              //  стрелки часов тикают

        if (millis() > nextRead1) {
          nextRead1 = millis() + SENSOR_SAMPLING_TIME;
          TempRead();    //  считываем температуру
          VievTempGl();
        }
#ifdef SetConnectPC
        sprintf (buf, "OK%03d%03d%03d%03d%03d\r\n", (Output1), (Output2), tc1, tc2, (1)); // profileName
        Serial.print(buf);
#endif
        Output2 = 0;
        Output1 = 0;
      }
      break;
    case REFLOW_STATE_SETTING:      {          //  вход в меню настроек
        const char str_0[] PROGMEM = "НИЖНИЙ ";
        const char str_1[] PROGMEM = "ВЕРХ ";
        const char str_2[] PROGMEM = "ПИД ";
        const char str_3[] PROGMEM = "ОБЩИЕ ";
        const char* myStr2[4] PROGMEM = {str_0, str_1, str_2, str_3}; // адреса констант-заголовков меню
        const char stp_1[] PROGMEM = "РАЗМЕР НИЗА ";
        const char stp_2[] PROGMEM = "СК-ТЬ НАГРЕВА ";
        const char stp_3[] PROGMEM = "ТЕМПЕРАТУРА ";
        const char stp_4[] PROGMEM = "ВРЕМЯ ЗАДЕРЖКИ ";
        const char stp_5[] PROGMEM = "МОЩНОСТЬ МИН ";
        const char stp_6[] PROGMEM = "МОЩНОСТЬ МАХ ";
        const char stp_7[] PROGMEM = "ШАГ ПРОФИЛЯ  < > ";
        const char stp_8[] PROGMEM = "СК-ТЬ НАГРЕВА ";
        const char stp_9[] PROGMEM = "ВРЕМЯ ПЕРЕХОДА ";
        const char stp_10[] PROGMEM = "ВЕРХ ПРОПОРЦИОНАЛ ";
        const char stp_11[] PROGMEM = "    ИНТЕГРАЛ ";
        const char stp_12[] PROGMEM = "    ДИФФЕРЕНЦИАЛ ";
        const char stp_13[] PROGMEM = "НИЗ ПРОПОРЦИОНАЛ ";
        const char stp_14[] PROGMEM = "ЗАСТАВКА ";
        const char stp_15[] PROGMEM = "ЗВУКИ ";
        const char stp_16[] PROGMEM = "ЧАСЫ ";
        const char stp_17[] PROGMEM = "ЗАГРУЗКА С КАРТЫ ";
        const char stp_18[] PROGMEM = " -  ";
        const char* const myStr3[4][6] PROGMEM = {              // адреса констант-надписей меню
          { stp_1, stp_2, stp_3, stp_4, stp_5, stp_6 },
          { stp_7, stp_8, stp_3, stp_9, stp_5, stp_6 },
          { stp_10, stp_11, stp_12, stp_13, stp_11, stp_12 },
          { stp_14, stp_15, stp_16, stp_17, stp_18, stp_18 }
        };
        void *Adresa[4][6] = {              // адреса переменных для меню настроек
          {&u.Profili.TableSize, &u.Profili.rampRateBOTTOM, &u.Profili.temperatureBOTTOM, &u.Profili.dwellTimerBOTTOM, &u.Profili.min_pwr_BOTTOM, &u.Profili.max_pwr_BOTTOM },
          {&Shag, &u.Profili.rampRateStep[0], &u.Profili.temperatureStep[0], &u.Profili.dwellTimerStep[0], &u.Profili.min_pwr_TOPStep[0], &u.Profili.max_pwr_TOPStep[0]},
          {&u.Profili.kp1, &u.Profili.ki1, &u.Profili.kd1, &u.Profili.kp2, &u.Profili.ki2, &u.Profili.kd2},
          {&Obsi1, &Obsi2, &Obsi3, &Obsi4, &Obsi5, &Obsi6}
        };
        bool Cln_st = false;
        if (updateScreen) ProfEdit_2();
        myGLCD.setFont(BigFontRus);
        if (Vklad_G != Vklad_G_old) {       // рисуем заголовки страницы настроек
          //  Serial.println("рамка - OK");
          for (i = 0; i < Win1; i++)  {
            if (Vklad_G != i) {             // рамки заголовка
              myGLCD.setColor(VGA_SILVER);
              myGLCD.drawRoundRect(Xsize * i + 1, Yset, Xsize * (i + 1) - 2, Ywin1);
              myGLCD.drawRoundRect(Xsize * i + 2, Yset + 1, Xsize * (i + 1) - 3, Ywin1 - 1);
            }
            if (Vklad_G == i) myGLCD.setColor(VGA_LIME);
            int Xset2 = (Xsize - (strlen(myStr2[i]) * 8)) / 2;
            myGLCD.textRus(myStr2[i], Xsize * i + Xset2, Yset + (Ysize - 16) / 2); // текст в рамке
            Vklad_L_old = 15;
            Cln_st = true;
          }
          Pr_Ramka_Y(Vklad_G);    // рисуем желтую рамку
          Vklad_G_old = Vklad_G;
          if (Vklad_G == 1)  Shag_old = 10;
          Vklad_L = 0;
        }
        if (Vklad_L != Vklad_L_old || Shag != Shag_old) {       // пишем строки и заполняем данными
          K_Kpres_ok = false;
          for (i = 0; i < Win2; i++) {
            if (Cln_st) {                   // очистка строки
              myGLCD.setColor(VGA_BLACK);
              myGLCD.fillRoundRect(10, i * Y_S_win + Y_shift, 460, i * Y_S_win + Y_shift + 16);
            }
            myGLCD.setColor(VGA_SILVER);
            if (Vklad_L == i) {             // выбранный адрес параметра и строки подсвечиваем зеленым цветом
              myGLCD.setColor(VGA_LIME);
              if (Vklad_L == 0 && Vklad_G == 1) myGLCD.setColor(VGA_ORAN);
              Wr_mem = (byte*)Adresa[Vklad_G][i] + Shag;
            }
            myGLCD.textRus(myStr3[Vklad_G][i], 10, i * Y_S_win + Y_shift);
            if (Shag != Shag_old && Vklad_G == 1) {
              //Ssh = Shag;
              myGLCD.setColor(VGA_SILVER);
              for (j = 0; j < 4; j++) {
                if (Shag == j) {              // выбор ШАГ ПРОФИЛЯ
                  myGLCD.setColor(VGA_RED);
                  myGLCD.setBackColor(VGA_GRAY);
                }
                myGLCD.printNumI(j + 1, j * 40 + 318, i * Y_S_win + Y_shift);
                myGLCD.setColor(VGA_SILVER);
                myGLCD.setBackColor(VGA_BLACK);
              }
              Shag_old = Shag;
              continue;
            }
            Wr_pr = (byte*)Adresa[Vklad_G][i] + Shag;
            if (i == 1 && Vklad_G < 2) {
              myGLCD.printNumF(*(byte*)Wr_pr * 0.1, 0, 286, i * Y_S_win + Y_shift);
            }
            else myGLCD.printNumI(*(byte*)Wr_pr, 286, i * Y_S_win + Y_shift, 3, ' ');
          }
          myGLCD.setFont(SevenSegNumFont);                // выбранный параметр в окно редактирования
          myGLCD.printNumI(*(byte*)Wr_mem, 365, 176, 3, '0');

          myGLCD.setColor(VGA_LIME);
          myGLCD.drawRoundRect(355, 166, 468, 235);
          myGLCD.drawRoundRect(356, 167, 467, 234);

          Vklad_L_old = Vklad_L;
          Cln_st = false;
        }
      }
      break;
    case REFLOW_STATE_SET_EDIT:     {          //  редактирование параметра
        if (updateScreen) {
          //  Serial.println("редактируем");
          myGLCD.setColor(VGA_RED);
          myGLCD.drawRoundRect(355, 166, 468, 235);
          myGLCD.drawRoundRect(356, 167, 467, 234);
          myGLCD.setColor(VGA_SILVER);
          myGLCD.drawRoundRect(355, 240, 468, 308);
          myGLCD.drawRoundRect(356, 241, 467, 307);
#ifdef Set_Picture
          myGLCD.drawBitmap(364, 240 + 9, 96, 50, Graf5, 1);
#endif
          Edit_Byte = *(byte*)Wr_mem;
          Edit_old = Edit_Byte;
          K_Kpres_ok = false;
          updateScreen = false;
        }
        if (Edit_old != Edit_Byte) {
          myGLCD.setColor(VGA_ORAN);
          myGLCD.setFont(SevenSegNumFont);
          myGLCD.printNumI(Edit_Byte, 365, 176, 3, '0');
          Edit_old = Edit_Byte;
        }
      }
      break;
    case REFLOW_STATE_PROFILE:      {          //  просмотр профиля
        if (updateScreen) {
          myGLCD.clrScr();
          PrPrint(0, 2);
          updateScreen = false;
          K_Setka();
          K_Kpres_ok = false;
          In_Line(20);        // end  updateScreen
        }
      }
      break;
    case REFLOW_STATE_BRAZE_START:  {          // Старт пайки все начальные установки
        // Serial.println("я тут 1");
        if (updateScreen) {
          myGLCD.clrScr();
          PrPrint(0, 2);
          updateScreen = false;
          K_Setka();
          In_Line(tc2);
        }
        //  фиксируем размер стола
        if (u.Profili.TableSize >= 1)   digitalWrite(P1_PIN, LOW);
        if (u.Profili.TableSize >= 2)   digitalWrite(P2_PIN, LOW);
        if (u.Profili.TableSize >= 3)   digitalWrite(P3_PIN, LOW);

        tone(buzzerPin, 1045, 500);  //звуковой сигнал при старте профиля
        reflowState = REFLOW_STATE_BRAZE_NOW;
        TopStart = false;
        mm = 0; ss = 0;       // секундомер в ноль
        BrStartTime = millis();
        Count1 = 0; Count2 = 0; BrStep = 0;
        BrTg = M_tg_Line(BrStep);
        //Serial.print("Tg - "); Serial.println(BrTg);
#ifdef SetInterrupt
        attachInterrupt(SetInterrupt, Dimming, RISING); // настроить порт прерывания(0 или 1) 2й или 3й цифровой пин
#else
        MsTimer2::set(10, Dimming); // 10 ms period
        MsTimer2::start();
#endif
        integra = 0;
        integra2 = 0;
        bottomMaxPwr = u.Profili.max_pwr_BOTTOM;
        myGLCD.setColor(VGA_LIME);
        myGLCD.setFont(BigFontRus);
        myGLCD.textRus(F("НИЖНИЙ ПОДОГРЕВ ВКЛЮЧЕН "), 5, 302);

      }
      break;
    case REFLOW_STATE_BRAZE_NOW:    {          // процесс пайки графики
        if (millis() > nextRead1)     {          // график температуры nextRead1
          nextRead1 = millis() + SENSOR_SAMPLING_TIME;

          if (BrStep <= BrStepMax) {            // если не конец профиля
            Count1++;
            int chast = Count1 / 4;
            int kluch =  Count1 % 4;
            TempRead();    //  считываем температуру
            /*
                         // #define TimeSt_M 0
                         // #define TempSt_M 1
                         // #define TimeEnd_M 2
                         // #define TempEnd_M 3
            */
            InputMA = Input2;
            if (BrStep == 0) {                              // включение Нижнего подогрева
              if (chast < Pr_Line_M[BrStep][TimeEnd_M]) {   // рост температуры
                bottomTemp = Pr_Line_M[BrStep][TempSt_M] + BrTg * Count1 / 4;
                //InputMA = (Input1 + Input2)/2;
              }
              else bottomTemp = Pr_Line_M[0][TempEnd_M];   // удержание

              if (Input1 > Pr_Line_M[0][TempEnd_M] && Output1 == 0)  {       //
                Output1 = u.Profili.min_pwr_TOPStep[0];
                myGLCD.setColor(VGA_LIME);
                myGLCD.setFont(BigFontRus);
                myGLCD.textRus(F(" ПРЕДВАРИТЕЛЬНЫЙ НАГРЕВ ВЕРХА    "), 5, 302);
              }
              if (chast > Pr_Line_M[BrStep + 2][TimeSt_M] && BrStepMax >= 2) { // пора ли включать верх
                TopStart = true;
                BrStep = BrStep + 2;
                currentStep = BrStep/2;
                myGLCD.setColor(VGA_LIME);
                myGLCD.setFont(BigFontRus);
                myGLCD.textRus(F("ВЕРХНИЙ НАГРЕВАТЕЛЬ ВКЛЮЧЕН    "), 5, 302);
                BrTg = M_tg_Line(BrStep);
                Count2 = 0;
              }
            }
            else {                                         // включение Верхнего нагревателя
              if (chast <= Pr_Line_M[BrStep][TimeEnd_M] ) {
                //       Serial.print(BrStep); Serial.print(" "); Serial.println(BrTg);
                Count2++;
                Setpoint1 = Pr_Line_M[BrStep][TempSt_M] + BrTg * Count2 / 4; // рост температуры
              }
              else Setpoint1 = Pr_Line_M[BrStep][TempEnd_M];   // удержание
              if (chast > Pr_Line_M[BrStep + 1][TimeEnd_M]) { // пора ли переходить на следующий шаг
                BrStep = BrStep + 2;
                currentStep = BrStep/2;
                BrTg = M_tg_Line(BrStep);
                Count2 = 0;
              }
            }
            Output2 = Pid2(InputMA, bottomTemp, u.Profili.kp2, u.Profili.ki2, u.Profili.kd2);
            if (TopStart == true) Output1 = Pid1(Input1, Setpoint1, u.Profili.kp1, u.Profili.ki1, u.Profili.kd1);

            // вывод информации на экран и в монитор РС
            if (kluch == 0) {      // выводим показания секундомера
              Sec_metr();
            }
            if (kluch == 1) {
              // WinStartTime = micros();
              TimeLine(chast + X_graf);             // линия времени
              myGLCD.setColor(VGA_RED);
              M_dr_point(chast - 2, bottomTemp);    // рисуем ожидаемый график низа
              if (TopStart == true) {
                myGLCD.setColor(VGA_ORAN);
                M_dr_point(chast - 2, Setpoint1); // рисуем ожидаемый график верха
              }
              myGLCD.setColor(VGA_LIME);
              M_dr_point (chast - 1, tc2);           // рисуем график низ
              myGLCD.setColor(VGA_AQUA);
              M_dr_point (chast - 1, tc1);           // рисуем график верх
              TempBraze ();
              //  Pr_WinTime();    // на экран засеченное время в мсек
            }
            if (kluch == 2) {
              myGLCD.setFont(BigFontRus);
              myGLCD.setColor(VGA_SILVER);
              myGLCD.textRus(F(": "), 432, TempY);
#ifdef SetConnectPC
              sprintf (buf, "OK%03d%03d%03d%03d%03d\r\n", int(Output1), int(Output2), tc1, tc2, int(profileName)); // график ПК
              Serial.print(buf);
#endif
            }
          }
          else  {
            updateScreen = true;
            reflowState = REFLOW_STATE_BRAZE_STOP;   // завершение пайки
          }
        }
      }
      break;
    case REFLOW_STATE_BRAZE_STOP:   {           // STOP процесса пайки
        if (updateScreen) {
          digitalWrite(P1_PIN, HIGH);
          digitalWrite(P2_PIN, HIGH);
          digitalWrite(P3_PIN, HIGH);
          digitalWrite(P4_PIN, HIGH);
          TopStart = false;
          Output2 = 0;
          Output1 = 0;

#ifdef SetInterrupt
          detachInterrupt(SetInterrupt); // остановить порт прерывания(0 или 1) 2й или 3й цифровой пин
#else
          MsTimer2::stop();
#endif
          digitalWrite(RelayPin1, LOW);
          digitalWrite(RelayPin2, LOW);

          myGLCD.setColor(VGA_LIME);
          myGLCD.setFont(BigFontRus);
          myGLCD.textRus(F("         СТОП ПРОФИЛЯ        "), 5, 302);


          tone(buzzerPin, 945, 500);  //звуковой сигнал
          delay(150);
          tone(buzzerPin, 645, 500);  //звуковой сигнал
          updateScreen = false;

          // reflowState = REFLOW_STATE_IDLE;
        }
        if (millis() > nextRead1)     {          // график температуры nextRead1
          nextRead1 = millis() + SENSOR_SAMPLING_TIME;
          TempRead();    //  считываем температуру
          TempBraze ();
        }
        break;
      }
  }
}  // end loop
