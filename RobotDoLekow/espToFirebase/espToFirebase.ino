#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include <Stepper.h>
#include "DS1307.h"
#include "PCF8574.h"

#define WIFI_NAZWA "DESKTOP"
#define WIFI_HASLO "m&k$0001"
#define FIREBASE_BAZA "robotdowydawanialekow.firebaseio.com"
#define FIREBASE_KLUCZ "HHdjaAsoNlfx7vMf7ht73WEzNGa7KK5TtcRbN9uy"

#define CZAS_SPANIA 3600        //CZAS_SPANIA to czas sekund jednego cyklu spania - docelowo godzina 60*60 = 3600 sekund

DS1307 zegar;
PCF8574 ekspander(0x20);

typedef struct {
  int nastepnyAlarm;
} skladowanie_RTC;

skladowanie_RTC pamiec_RTC;
int obecnaGodzina;

void spanie();
void ruchSilnika();
void kiedyWcisniety();
void wifiConnect();
void przesylNowychDanych();
void pobranieNastepnegoAlarmu();

void setup() {
  // do testu --------
  //pamiec_RTC.nastepnyAlarm = 23;
  
  // inicjalizacja ekspandera
  ekspander.begin();    //A0, A1, A2 równe 0
  
  // inicjalizacja zegara i pobranie obecnej godziny
  zegar.begin();
  obecnaGodzina = zegar.hour + zegar.minute/60; //pobranie obecnej godziny z RTC

  pinMode(A0, INPUT);

  // to chyba niepotrzebne? ----------
  //pinMode(D1, OUTPUT);      // do I2C
  //digitalWrite(D1, HIGH);
  //pinMode(D2, OUTPUT);      // do I2C
  //digitalWrite(D2, HIGH);
  
  ekspander.pinMode(0, OUTPUT);       // buzzer
  ekspander.digitalWrite(0, HIGH);
  ekspander.pinMode(1, OUTPUT);       // dioda
  ekspander.digitalWrite(1, HIGH);
  ekspander.pinMode(2, INPUT);        // przycisk
  
  ekspander.pinMode(4, OUTPUT);       // IN1 silnik
  ekspander.digitalWrite(4, LOW);
  ekspander.pinMode(5, OUTPUT);       // IN2
  ekspander.digitalWrite(5, LOW);
  ekspander.pinMode(6, OUTPUT);       // IN3
  ekspander.digitalWrite(6, LOW);
  ekspander.pinMode(7, OUTPUT);       // IN4
  ekspander.digitalWrite(7, LOW);
  
  // spanie jeśli czekamy na alarm
  spanie();
  
  
  // ruch silnikiem krokowym X
  ruchSilnika();
  
  // zasilenie buzzera i diody w przycisku
  ekspander.digitalWrite(0, HIGH);
  ekspander.digitalWrite(1, HIGH);
  
  // zczytywanie kiedy wciśnięty zostanie przycisk
  kiedyWcisniety();   // moze do poprawienia? ---------
  
  // wyłączeine buzzera i diody
  ekspander.digitalWrite(0, LOW);
  ekspander.digitalWrite(1, LOW);

  // łączenie z wifi
  wifiConnect();

  // łączenie z firebase
  Firebase.begin(FIREBASE_BAZA, FIREBASE_KLUCZ);
  delay(100);
  
  // przesył danych do bazy
  przesylNowychDanych();

  // pobieranie ustawień na następny alarm
  pobranieNastepnegoAlarmu();

  // zmiejszenie ilości dostępnych dawek leków o 1
  int pozostaleDawki = Firebase.getInt("/Ustawienia/iloscPozostalychDawek")-1;
  Firebase.setInt("/Ustawienia/iloscPozostalychDawek", pozostaleDawki);
}

void loop() {

}

void spanie(){
  if(abs(pamiec_RTC.nastepnyAlarm - obecnaGodzina) > 1) {                 // godzina spania
    ESP.deepSleep(CZAS_SPANIA * 1e6);
  } else if(abs(pamiec_RTC.nastepnyAlarm - obecnaGodzina) > 0.75) {       // 45 min spania
    ESP.deepSleep(0.75 * CZAS_SPANIA * 1e6);
  } else if(abs(pamiec_RTC.nastepnyAlarm - obecnaGodzina) > 0.5) {        // 30 min spania
    ESP.deepSleep(0.5 * CZAS_SPANIA * 1e6);
  } else if(abs(pamiec_RTC.nastepnyAlarm - obecnaGodzina) > 0.25) {       // 25 min spania
    ESP.deepSleep(0.25 * CZAS_SPANIA * 1e6);
  } else if(abs(pamiec_RTC.nastepnyAlarm - obecnaGodzina) > 0.16) {       // ok 10 min spania
    ESP.deepSleep(0.16 * CZAS_SPANIA * 1e6);
  } else if(abs(pamiec_RTC.nastepnyAlarm - obecnaGodzina) > 0.08) {       // ok 5 min spania
    ESP.deepSleep(0.08 * CZAS_SPANIA * 1e6);
  }
}

void ruchSilnika(){
  for(int i=0; i<128; ++i){
    ekspander.digitalWrite(4, HIGH);
    ekspander.digitalWrite(5, HIGH);
    ekspander.digitalWrite(6, LOW);
    ekspander.digitalWrite(7, LOW);
    
    ekspander.digitalWrite(4, LOW);
    ekspander.digitalWrite(5, HIGH);
    ekspander.digitalWrite(6, HIGH);
    ekspander.digitalWrite(7, LOW);
    
    ekspander.digitalWrite(4, LOW);
    ekspander.digitalWrite(5, LOW);
    ekspander.digitalWrite(6, HIGH);
    ekspander.digitalWrite(7, HIGH);
    
    ekspander.digitalWrite(4, HIGH);
    ekspander.digitalWrite(5, LOW);
    ekspander.digitalWrite(6, LOW);
    ekspander.digitalWrite(7, HIGH);
  }
}

void kiedyWcisniety(){
  while(1){
    if(ekspander.digitalRead(2)){    // czy chce odczytać 1 czy 0?
      break;
    }
  }
}

void wifiConnect(){
  WiFi.begin(WIFI_NAZWA, WIFI_HASLO);

  int teller = 0;
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
  }
}

void przesylNowychDanych(){
  int iloscDanych = Firebase.getInt("/Dane/iloscDanych") + 1;
  String nazwa = "dane" + String(iloscDanych);

  Firebase.setInt("/Dane/"+nazwa+"/dzien", zegar.dayOfMonth);       // gdy zegar będzie działać - zamienić
  Firebase.setInt("/Dane/"+nazwa+"/miesiac", zegar.month);
  Firebase.setInt("/Dane/"+nazwa+"/rok", zegar.year+2000);
  Firebase.setInt("/Dane/"+nazwa+"/godziny", zegar.hour);
  Firebase.setInt("/Dane/"+nazwa+"/minuty", zegar.minute);
  Firebase.setInt("/Dane/iloscDanych", iloscDanych);

  // do testu --------
  Firebase.setInt("/Dane/"+nazwa+"/dzien", 27);
  Firebase.setInt("/Dane/"+nazwa+"/miesiac", 10);
  Firebase.setInt("/Dane/"+nazwa+"/rok", 2020);
  Firebase.setInt("/Dane/"+nazwa+"/godziny", 14);
  Firebase.setInt("/Dane/"+nazwa+"/minuty", 56);
  Firebase.setInt("/Dane/iloscDanych", iloscDanych);
  
}


void pobranieNastepnegoAlarmu(){
  int ilosc = Firebase.getInt("/Ustawienia/ilosc");
  
  String sh1, sh2, sh3;
  int h1, h2, h3;       // godziny alarmów
  char temp1;           // zmienne tymczasowe
  char temp2;
  sh1 = Firebase.getString("/Ustawienia/godziny1");
  temp1 = sh1[0];
  temp2 = sh1[1];
  sh1 = "";
  sh1 += temp1;
  if(temp2 != ':'){
    sh1 += temp2;
  }
  sh2 = Firebase.getString("/Ustawienia/godziny2");
  temp1 = sh2[0];
  temp2 = sh2[1];
  sh2 = "";
  sh2 += temp1;
  if(temp2 != ':'){
    sh2 += temp2;
  }
  sh3 = Firebase.getString("/Ustawienia/godziny3");
  temp1 = sh3[0];
  temp2 = sh3[1];
  sh3 = "";
  sh3 += temp1;
  if(temp2 != ':'){
    sh3 += temp2;
  }
  h1 = sh1.toInt();
  h2 = sh2.toInt();
  h3 = sh3.toInt();

  // ustawienie godziny następnego alarmu
  if(ilosc == 2){
    if(h1 != pamiec_RTC.nastepnyAlarm){
      pamiec_RTC.nastepnyAlarm = h1;
    } else {
      pamiec_RTC.nastepnyAlarm = h2;
    }
  } else if(ilosc == 3){
    if(h1 == pamiec_RTC.nastepnyAlarm){
      pamiec_RTC.nastepnyAlarm = h2;
    } else if(h2 == pamiec_RTC.nastepnyAlarm){
      pamiec_RTC.nastepnyAlarm = h3;
    } else {
      pamiec_RTC.nastepnyAlarm = h1;
    }
  }
}
