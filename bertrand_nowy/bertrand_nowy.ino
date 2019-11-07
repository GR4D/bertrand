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
bool zabezpieczenie = false;

void setup() {
  
 setSyncProvider(RTC.get);
  
 pinMode(przekaznik,OUTPUT);
 pinMode(przycisk, INPUT_PULLUP);
 pinMode(kontrast,OUTPUT);
 pinMode(bckLight,OUTPUT);
 pinMode(A3,INPUT);

 digitalWrite(przekaznik,HIGH);
 analogWrite(kontrast,500 /4);
 digitalWrite(bckLight,HIGH);

  lcd.begin(16, 2);
  lcd.createChar(0, kropla);
 }

void loop() {

przyciskZabezpieczenie();
//lcdRefresh();
podswietlenie();
digitalClockDisplay();
godzinyWody();
 
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

void przyciskZabezpieczenie(){
  if(analogRead(A3)>100){
            zabezpieczenie = false;
            isSafe = "NO ";
          }
           
  if(analogRead(A3)<100){
    zabezpieczenie = true;
    isSafe = "OK";
  }
   
  if(!digitalRead(przycisk) && zabezpieczenie){
    digitalWrite(przekaznik,LOW);
     }
 if(digitalRead(przycisk) || zabezpieczenie==false){
    digitalWrite(przekaznik,HIGH);
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
   // 6:00 AM 50ml 
     if( hour() == 6 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }
     //6:30 AM 50ml
     if( hour() == 6 && minute() == 30 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }/////////////////100ml
     //9:00 AM 50ml
     if( hour() == 9 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }/////////////////150ml    
    ///11:00 50ml
    if( hour() == 11 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody +=50 ;
     }/////////////////200ml
    ///13:00 50ml
    if( hour() == 13 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }////////////////////250ml
    ///15:00 50ml
    if( hour() == 15 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }/////////////////300ml 
     ///17:00 50ml
    if( hour() == 17 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }/////////////////350ml
     ///19:00 50ml
    if( hour() == 19 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }/////////////////400ml 
    ///21:00 50ml
    if( hour() == 21 && minute() == 0 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }//////////////////450ml
      ///21:30 50ml
    if( hour() == 21 && minute() == 30 && second() == 0 && zabezpieczenie){
      digitalWrite(przekaznik,LOW);
      delay(3500);
      digitalWrite(przekaznik,HIGH);
      iloscWody+= 50 ;
     }/////////////////500ml
}
