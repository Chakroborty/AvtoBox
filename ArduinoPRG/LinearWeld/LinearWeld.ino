#include <EEPROM.h>

 

#define Forward 9

#define Back 10

#define Start 11

#define Stop 12

#define Weld 13

//---------------------------------------------------

 

#define TIGRelay 0

#define PneumaticRelay 17

#define PneumaticEndstop 8

//---------------------------------------------------

#define DIR 15

#define PUL 16

//---------------------------------------------------

 

#define StepsPerMM 160

#define CW LOW

#define CCW HIGH

 

 

#include <Keypad.h>

const byte ROWS = 4;

const byte COLS = 3;

char keys[ROWS][COLS] = {

{'1','2','3',},

{'4','5','6',},

{'7','8','9',},

{'*','0','#'}

};

byte rowPins[ROWS] = {1,2, 3, 4};

byte colPins[COLS] = {5, 6, 7};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//--------------------------------------------------------------------------

 

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

//------------------------------------------------------------------------------

float buf;

char key;

String intervalue ;

int temp;

int Mode = 1;

int Set = 0;

 

float AutoSpeed = 1;

float AutoDistance = 1;

float DelayFeed = 0.1;

float OffWeldDistance = 1;

 

float SpotSpeed = 0.1;

float StepDistance = 1;

float TimeWelding = 0.1;

 

unsigned long ReturnSpeed = 30;

float ManualSpeed = 0.1;

 

 

 

 

float intervalue_menu()

{

float rez;

bool dotblock = false;

lcd.clear();

lcd.setCursor(4,0);

lcd.print("Entered value");

lcd.setCursor(7,2);

 

intervalue = "";

temp = 0;

 

while(true)

{

key = keypad.getKey();

if(key)

{

 

if (key == '*')

{

if (dotblock == false && intervalue != "" )

{

key = '.';

dotblock = true;

}

else

{

continue;

}

}

 

 

if (key == '#')

{

delay(200);

rez = intervalue.toFloat();

return rez ;

}

if (temp<=3)

{

intervalue = intervalue + key;

lcd.print(key);

temp = temp+1;

}

}

}

}

//------------------------------------------------------------------------------

 

void first_menu()

{

lcd.clear();

lcd.setCursor(8,0 );

lcd.print("MODE-");

lcd.print(Mode);

 

lcd.setCursor(0, 1);

lcd.print("AUTO ");

 

lcd.setCursor(0, 2);

lcd.print("SPOT ");

 

lcd.setCursor(0, 3);

lcd.print("MANUAL");

 

lcd.setCursor(8,Mode);

lcd.print("[]");

}

 

 

void Auto_menu()

{

if (Set == 0)

{

lcd.clear();

lcd.setCursor(7, 0); //

lcd.print("SPEED"); //

lcd.setCursor(7, 2); //

lcd.print(AutoSpeed); //

lcd.print(" mm/sec");

}

 

else if (Set == 1)

{

lcd.clear();

lcd.setCursor(6, 0);

lcd.print("DISTANCE");

lcd.setCursor(7, 2);

lcd.print(AutoDistance);

lcd.print(" mm");

}

 

 

else if (Set == 2)

{

lcd.clear();

lcd.setCursor(5, 0);

lcd.print("DELAY FEED");

lcd.setCursor(7, 2);

lcd.print(DelayFeed);

lcd.print(" sec");

}

 

else if (Set == 3)

{

lcd.clear();

lcd.setCursor(2, 0);

lcd.print("OFF WELD DISTANCE");

lcd.setCursor(7, 2);

lcd.print(OffWeldDistance);

lcd.print(" mm");

}

}

 

void Spot_menu()

{

if (Set == 0)

{

lcd.clear();

lcd.setCursor(7, 0);

lcd.print("SPEED");

lcd.setCursor(7, 2);

lcd.print(SpotSpeed);

lcd.print(" mm/sec");

}

 

else if (Set == 1)

{

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("STEP DISTANCE");

lcd.setCursor(7, 2);

lcd.print(StepDistance);

lcd.print(" mm");

}

 

 

else if (Set == 2)

{

lcd.clear();

lcd.setCursor(4, 0);

lcd.print("TIME WELDING");

lcd.setCursor(7, 2);

lcd.print(TimeWelding);

lcd.print(" sec");

}

}

 

 

void ManualMenu()

{

if (Set == 0)

{

lcd.clear();

lcd.setCursor(4, 0);

lcd.print("MANUAL SPEED");

lcd.setCursor(7, 2);

lcd.print(ManualSpeed);

lcd.print(" mm/sec");

}

 

else if (Set == 1)

{

lcd.clear();

lcd.setCursor(4, 0);

lcd.print("RETURN SPEED");

lcd.setCursor(7, 2);

lcd.print(ReturnSpeed);

lcd.print(" mm/sec");

}

}

 

 

//##########################################################режим ручного перемещения########################################################################

void manualmove()

{

 

if (digitalRead(Forward)==0) digitalWrite(DIR,CW);

else if (digitalRead(Back)==0) digitalWrite(DIR,CCW);

delay(100);

unsigned long StepPer = ((1.0/(ManualSpeed*StepsPerMM))*1000000)/2.0;

unsigned long delaytime;

 

while ((digitalRead(Forward)==0) or (digitalRead(Back)==0))

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,HIGH);

while (micros()<delaytime)

{

}

 

 

 

delaytime = micros()+StepPer;

digitalWrite(PUL,LOW);

while (micros()<delaytime)

{

}

}

}

 

//###############################################################Режим работы Auto ###########################################################################

void Auto()

{

Set = 0;

bool EMStop = false;

Auto_menu();

while(true)

{

key = keypad.getKey();

 

 

if (key)

{

if (key == '6')

{

Set = Set+1;

if (Set>3) Set = 0;

Auto_menu();

}

else if (key == '4')

{

Set = Set-1;

if (Set<0) Set = 3;

Auto_menu();

}

 

else if (key == '#')

{

buf = intervalue_menu();

if (Set == 0 && buf != 0) AutoSpeed = buf;

else if (Set == 1&& buf != 0 ) AutoDistance = buf;

else if (Set == 2 && buf != 0) DelayFeed = buf;

else if (Set == 3 && buf != 0) OffWeldDistance = buf;

 

if (AutoSpeed>100) AutoSpeed = 100;

else if (AutoSpeed<0.1) AutoSpeed = 0.1;

 

if(AutoDistance>1000) AutoDistance = 1000;

else if (AutoDistance<0.1) AutoDistance = 0.1;

 

if (DelayFeed>10) DelayFeed = 10;

else if (DelayFeed<0.1) DelayFeed = 0.1;

 

if (OffWeldDistance>10) OffWeldDistance = 10;

else if (OffWeldDistance<0.1) OffWeldDistance = 0.1;

 

if (Set == 0 && buf != 0) EEPROM.put(1,AutoSpeed);

else if (Set == 1&& buf != 0 ) EEPROM.put(5,AutoDistance);

else if (Set == 2 && buf != 0) EEPROM.put(9,DelayFeed);

else if (Set == 3 && buf != 0) EEPROM.put(13,OffWeldDistance);

 

Auto_menu();

}

 

else if (key == '*') return;

}

 

 

 

if (digitalRead(Start)==0)

{

-------------------------------------------------------------------

 

if(AutoDistance < OffWeldDistance)

{

AutoDistance = OffWeldDistance;

}

 

unsigned long Steps = (StepsPerMM*AutoDistance)- (StepsPerMM*OffWeldDistance);

 

 

unsigned long OffWeldSteps = StepsPerMM*OffWeldDistance;

 

 

unsigned long StepPer = ((1.0/(AutoSpeed*StepsPerMM))*1000000)/2.0;

 

digitalWrite(PneumaticRelay,HIGH);

while(digitalRead(PneumaticEndstop)==LOW)

{

delay(200);

}

 

digitalWrite(LCDEnable,LOW);

delay(1500);

 

digitalWrite(TIGRelay,HIGH);

delay(DelayFeed*1000);

 

unsigned long delaytime;

 

 

digitalWrite(DIR,CW);

delay(100);

for(Steps;Steps>0;Steps--)

{

 

if (EMStop!=true)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,HIGH);

while (micros()<delaytime)

{

if (digitalRead(Stop) == 0)

{

digitalWrite(TIGRelay,LOW);

delay(5000);

digitalWrite(PneumaticRelay,LOW);

digitalWrite(PUL,LOW);

EMStop = true;

break;

}

}

}

 

if (EMStop!=true)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,LOW);

while (micros()<delaytime)

{

if (digitalRead(Stop) == 0)

{

digitalWrite(TIGRelay,LOW);

delay(5000);

digitalWrite(PneumaticRelay,LOW);

digitalWrite(PUL,LOW);

EMStop = true;

break;

}

}

}

}

 

digitalWrite(TIGRelay,LOW);

for(OffWeldSteps;OffWeldSteps>0;OffWeldSteps--)

{

 

if (EMStop!=true)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,HIGH);

while (micros()<delaytime)

{

if (digitalRead(Stop) == 0)

{

digitalWrite(TIGRelay,LOW);

delay(5000);

digitalWrite(PneumaticRelay,LOW);

digitalWrite(PUL,LOW);

EMStop = true;

break;

}

}

}

 

if (EMStop!=true)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,LOW);

while (micros()<delaytime)

{

if (digitalRead(Stop) == 0)

{

digitalWrite(TIGRelay,LOW);

delay(5000);

digitalWrite(PneumaticRelay,LOW);

digitalWrite(PUL,LOW);

EMStop = true;

break;

}

}

}

}

 

 

 

 

 

if (EMStop != true)

{

 

digitalWrite(PneumaticRelay,LOW);

delay(1000);

digitalWrite(DIR,CCW);

delay(100);

 

Steps = (StepsPerMM*AutoDistance);

StepPer = ((1.0/(ReturnSpeed*StepsPerMM))*1000000)/2.0;

for(Steps;Steps>0;Steps--)

{

 

if (EMStop!=true)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,HIGH);

while (micros()<delaytime)

{

if (digitalRead(Stop) == 0)

{

EMStop = true;

digitalWrite(PUL,LOW);

break;

}

}

}

 

if (EMStop!=true)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,LOW);

while (micros()<delaytime)

{

if (digitalRead(Stop) == 0)

{

digitalWrite(PUL,LOW);

EMStop = true;

break;

}

}

}

}

}

 

digitalWrite(LCDEnable,HIGH);

lcd.init();

lcd.backlight();

lcd.clear();

lcd.home();

EMStop = false;

Auto_menu();

}

if ((digitalRead(Back)==0)or(digitalRead(Forward)==0)) manualmove();

}

}

 

 

 

 

 

 

//###############################################################Режим работы Spot ###########################################################################

void Spot()

{

Set = 0;

unsigned long stepbuf = 0;

unsigned long Steps;

unsigned long StepPer;

unsigned long delaytime;

Spot_menu();

while(true)

{

key = keypad.getKey();

 

 

if (key)

{

if (key == '6')

{

Set = Set+1;

if (Set>2) Set = 0;

Spot_menu();

}

else if (key == '4')

{

Set = Set-1;

if (Set<0) Set = 2;

Spot_menu();

}

 

else if (key == '#')

{

buf = intervalue_menu();

if (Set == 0 && buf != 0) SpotSpeed = buf;

else if (Set == 1&& buf != 0 ) StepDistance = buf;

else if (Set == 2 && buf != 0) TimeWelding = buf;

 

if (SpotSpeed>100) AutoSpeed = 100;

else if (SpotSpeed<0.1) AutoSpeed = 0.1;

 

if(StepDistance>100) StepDistance = 100;

else if (StepDistance<0.1) StepDistance = 0.1;

 

if (TimeWelding>10) TimeWelding = 10;

else if (TimeWelding < 0.1) TimeWelding = 0.1;

 

if (Set == 0 && buf != 0) EEPROM.put(17,SpotSpeed);

else if (Set == 1&& buf != 0 ) EEPROM.put(21,StepDistance);

else if (Set == 2 && buf != 0) EEPROM.put(25,TimeWelding);

Spot_menu();

}

 

else if (key == '*') return;

}

 

 

 

if(digitalRead(Start)==0)

{

 

if(digitalRead(PneumaticRelay) == LOW)

{

stepbuf = 0;

 

digitalWrite(LCDEnable,LOW);

delay(100);

digitalWrite(PneumaticRelay,HIGH);

while(digitalRead(PneumaticEndstop)==LOW)

{

delay(200);

}

}

 

else

{

StepPer = ((1.0/(SpotSpeed*StepsPerMM))*1000000)/2.0;

Steps = (StepsPerMM*StepDistance);

stepbuf = stepbuf+Steps;

digitalWrite(DIR,CW);

delay(100);

for(Steps;Steps>0;Steps--)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,HIGH);

while (micros()<delaytime)

{

}

 

delaytime = micros()+StepPer;

digitalWrite(PUL,LOW);

while (micros()<delaytime)

{

}

}

}

}

 

if((digitalRead(Weld) == 0 and (digitalRead(PneumaticEndstop)==HIGH)))

{

 

digitalWrite(TIGRelay,HIGH);

delay(500);

delay(TimeWelding*1000);

 

digitalWrite(TIGRelay,LOW);

}

 

if(digitalRead(Stop)== 0)

{

 

digitalWrite(PneumaticRelay,LOW);

delay(1000);

 

if(stepbuf>0)

{

digitalWrite(DIR,CCW);

delay(100);

StepPer = ((1.0/(ReturnSpeed*StepsPerMM))*1000000)/2.0;

for(stepbuf;stepbuf>0;stepbuf--)

{

 

delaytime = micros()+StepPer;

digitalWrite(PUL,HIGH);

while (micros()<delaytime)

{

}

 

delaytime = micros()+StepPer;

digitalWrite(PUL,LOW);

while (micros()<delaytime)

{

}

}

stepbuf = 0;

}

 

digitalWrite(LCDEnable,HIGH);

lcd.init();

lcd.backlight();

lcd.clear();

lcd.home();

Spot_menu();

}

if ((digitalRead(Back)==0)or(digitalRead(Forward)==0)) manualmove();

}

}

 

 

//###################################режим настройки скорости ручного перемещения#################################################

void Manual()

{

Set = 0;

ManualMenu();

while(true)

{

key = keypad.getKey();

if (key)

{

 

if (key == '6')

{

Set = Set+1;

if (Set>1) Set = 0;

ManualMenu();

}

else if (key == '4')

{

Set = Set-1;

if (Set<0) Set = 1;

ManualMenu();

}

 

if (key == '#')

{

buf = intervalue_menu();

if (buf != 0 and Set == 0) ManualSpeed = buf;

else if (buf !=0 and Set ==1) ReturnSpeed = int(buf);

 

 

if (ManualSpeed>100) ManualSpeed = 100;

else if (ManualSpeed<0.1) ManualSpeed = 0.1;

 

if (ReturnSpeed>100) ReturnSpeed = 100;

else if(ReturnSpeed<1) ReturnSpeed = 1;

 

if (buf != 0 and Set == 0) EEPROM.put(33,ManualSpeed);

else if (buf !=0 and Set ==1) EEPROM.put(29,ReturnSpeed);

 

ManualMenu();

}

 

else if (key == '*') return;

}

if ((digitalRead(Back)==0)or(digitalRead(Forward)==0)) manualmove();

}

}

 

void setup()

{

 

pinMode(Forward,INPUT);

digitalWrite(Forward,HIGH);

pinMode(Back,INPUT);

digitalWrite(Back,HIGH);

pinMode(Start,INPUT);

digitalWrite(Start,HIGH);

pinMode(Stop,INPUT);

digitalWrite(Stop,HIGH);

pinMode(Weld,INPUT);

digitalWrite(Weld,HIGH);

 

pinMode(PneumaticEndstop,INPUT);

digitalWrite(PneumaticEndstop,HIGH);

 

pinMode(TIGRelay,OUTPUT);

digitalWrite(TIGRelay,LOW);

 

pinMode(PneumaticRelay,OUTPUT);

digitalWrite(PneumaticRelay,LOW);

 

pinMode(DIR,OUTPUT);

digitalWrite(DIR,LOW);

 

pinMode(PUL,OUTPUT);

digitalWrite(PUL,LOW);

 

 

 

 

EEPROM.get(1,AutoSpeed);

EEPROM.get(5,AutoDistance);

EEPROM.get(9,DelayFeed);

EEPROM.get(13,OffWeldDistance);

EEPROM.get(17,SpotSpeed);

EEPROM.get(21,StepDistance);

EEPROM.get(25,TimeWelding);

EEPROM.get(29,ReturnSpeed);

EEPROM.get(33,ManualSpeed);

 

if (SpotSpeed>100) AutoSpeed = 100;

else if (SpotSpeed<0.1) AutoSpeed = 0.1;

 

if(StepDistance>100) StepDistance = 100;

else if (StepDistance<0.1) StepDistance = 0.1;

 

if (TimeWelding>10) TimeWelding = 10;

else if (TimeWelding < 0.1) TimeWelding = 0.1;

 

if (AutoSpeed>100) AutoSpeed = 100;

else if (AutoSpeed<0.1) AutoSpeed = 0.1;

 

if(AutoDistance>1000) AutoDistance = 1000;

else if (AutoDistance<0.1) AutoDistance = 0.1;

 

if (DelayFeed>10) DelayFeed = 10;

else if (DelayFeed<0.1) DelayFeed = 0.1;

 

if (OffWeldDistance>10) OffWeldDistance = 10;

else if (OffWeldDistance<0.1) OffWeldDistance = 0.1;

 

 

lcd.init();

lcd.backlight();

lcd.clear();

lcd.home();

first_menu();

}

 

 

 

 

 

void loop() {

key = keypad.getKey();

 

if (key)

{

if (key == '6')

{

Mode = Mode+1;

if (Mode>3) Mode = 1;

first_menu();

}

else if (key == '4')

{

Mode = Mode-1;

if (Mode<1) Mode = 3;

first_menu();

}

}

 

 

//--------- выбран режим Auto ----------

if (key=='#'&&Mode==1)

{

Set = 0;

Auto();

first_menu();

}

 

//----------- выбран режим Spot -------------

else if (key=='#' && Mode==2)

{

Set = 0;

Spot();

first_menu();

}

 

//---------- выбран режим Manual ------------

else if (key == '#' && Mode==3)

{

Manual();

first_menu();

}

if ((digitalRead(Back)==0)or(digitalRead(Forward)==0)) manualmove();

}
