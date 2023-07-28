// include the library code:
#include <LiquidCrystal.h>
#include <virtuabotixRTC.h>
#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT11 

virtuabotixRTC myRTC(6, 7, 8);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  //myRTC.setDS1302Time(00, 26, 21, 7, 24, 7, 2022);
  lcd.begin(16, 2);
  dht.begin();
}

void prikaziVreme1s(){
    myRTC.updateTime();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("Vreme: ");
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  lcd.print(myRTC.hours);
  lcd.print(":");
  if(myRTC.minutes<10){
    lcd.print(0);
  }
  lcd.print(myRTC.minutes);
  lcd.print(":");
  if(myRTC.seconds<10){
    lcd.print(0);
  }
  lcd.print(myRTC.seconds);
  lcd.setCursor(0, 1);
  lcd.print("Datum: ");
  lcd.print(myRTC.dayofmonth);
  lcd.print(".");
  lcd.print(myRTC.month);
  lcd.print(".");
  lcd.print(myRTC.year);
  lcd.print(".");
  lcd.print(" ");
  //lcd.print("Lana");

  delay(1000);

  lcd.clear();
}

void prikaziVlaznostItemperaturu5s(){
  lcd.setCursor(0,0);
  int h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.print(F("Failed to read from DHT sensor!"));
    lcd.setCursor(0,1);
    return;
  }

  lcd.print(F("Vlaznost: "));
  lcd.print(h);
  lcd.print(F(" %"));
  lcd.setCursor(0,1);
  lcd.print(F("Temp.: "));
  lcd.print(t);
  lcd.print(" ");
  lcd.print(char(223));
  lcd.print(F("C"));
  delay(5000);
  lcd.clear();
}

void loop() {

  for(int i=0; i<5; i++){
    prikaziVreme1s();
  }
  delay(100); 
  
  prikaziVlaznostItemperaturu5s();
  delay(100);
}
