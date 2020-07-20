#include <LiquidCrystal.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#define przekaznik 6
#define przycisk 8
#define kontrast 9
#define bckLight 10
String isSafe;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int iloscWody = 0;

byte kropla[8] = {
  0b00100,
  0b00100,
  0b01110,
  0b01110,
  0b10111,
  0b10111,
  0b01110,
  0b00000
};

void setup() {
  
 setSyncProvider(RTC.get);
  
 pinMode(przekaznik,OUTPUT);
 pinMode(przycisk, INPUT_PULLUP);
 pinMode(kontrast,OUTPUT);
 pinMode(bckLight,OUTPUT);
 pinMode(A3,INPUT);

 digitalWrite(przekaznik,HIGH);
 analogWrite(kontrast,600 /4);
 digitalWrite(bckLight,LOW);

  lcd.begin(16, 2);
  lcd.createChar(0, kropla);
 }

void loop() {

//lcdRefresh();
podswietlenie();
digitalClockDisplay();
godzinyWody();
testIlosci();
 
}
void lcdRefresh(){
  if(second()%30 == 0){
    lcd.clear();  
  }
}

void LCDprint2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);  
}

void digitalClockDisplay(){
    lcd.home();
    lcd.print("BERTRAND WODA ");
    lcd.print(isSafe);
   // if( timeStatus()== timeSet){
      lcd.setCursor (0, 1);
    LCDprint2digits(hour());
    lcd.print(':');
    LCDprint2digits(minute());
    lcd.print(':');
    LCDprint2digits(second());
    lcd.print(" ");
    lcd.write((byte)0); // rzutuję ikonę termomrtr na typ byte i wyświetlam ją na lcd
    lcd.print(iloscWody);
    if(iloscWody<10){
      lcd.print(" ml  ");
    }
    if(iloscWody<100){
      lcd.print(" ml ");
    }   
    if(iloscWody<1000){
      lcd.print(" ml");
    } 
}

void podswietlenie(){
  if( hour()>=7 && hour()<=21) {
      digitalWrite(bckLight, HIGH);
  }else digitalWrite(bckLight,LOW);

  if(hour()==0 && minute()==0 && second()== 1){
    iloscWody = 0;
  }
}

void godzinyWody(){
  woda(6,0,0);
  woda(9,0,0);
  woda(11,0,0);
  woda(13,0,0);
  woda(15,0,0);
  woda(17,0,0);
  woda(19,0,0);
  woda(21,0,0);
  woda(21,30,0);
}

void woda(int godzina, int minuta, int sekunda){
  if( hour() == godzina && minute() == minuta && second() == sekunda){
      digitalWrite(przekaznik,LOW);
      delay(2000);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
  }
}
void testIlosci(){
      delay(1000);
      digitalWrite(przekaznik,LOW);
      delay(6500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 25 ;  
}
