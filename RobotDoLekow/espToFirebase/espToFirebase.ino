#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include <DS3231.h>
#include "PCF8574.h"

#define WIFI_NAZWA "DESKTOP"
#define WIFI_HASLO "m&k$0001"
#define FIREBASE_BAZA "robotdowydawanialekow.firebaseio.com"
#define FIREBASE_KLUCZ "HHdjaAsoNlfx7vMf7ht73WEzNGa7KK5TtcRbN9uy"

#define CZAS_SPANIA_60 3600        // godzina 60*60 = 3600 sekund
#define CZAS_SPANIA_45 2700
#define CZAS_SPANIA_30 1800
#define CZAS_SPANIA_20 1200
#define CZAS_SPANIA_15 900
#define CZAS_SPANIA_10 600
#define CZAS_SPANIA_5 300
#define CZAS_SPANIA_1 60

RTClib zegar;
PCF8574 ekspander(0x20);    //A0, A1, A2 równe 0

typedef struct {
  int nastepnyAlarm;
} skladowanie_RTC;

skladowanie_RTC pamiec_RTC;
DateTime obecnaChwila;

void spanie();
void ruchSilnika();
void kiedyWcisniety();
void wifiConnect();
void przesylNowychDanych();
void pobraniePierwszegoAlarmu();
void pobranieNastepnegoAlarmu();
void wysylIlosciDawek();
void wysylPoziomuBaterii();
void czytajRTC();
void zapiszRTC();

void setup() {  
  //Serial.begin(9600);
  //Serial.println("");
  //Serial.print("godzina alarmu: ");
  //Serial.println(pamiec_RTC.nastepnyAlarm);
  
  // inicjalizacja ekspandera
  ekspander.begin();

  //pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  ekspander.write(0, LOW);    // buzzer
  ekspander.write(1, LOW);    // dioda
  ekspander.write(4, LOW);    // IN1 silnik
  ekspander.write(5, LOW);    // IN2
  ekspander.write(6, LOW);    // IN3
  ekspander.write(7, LOW);    // IN4
  
  // inicjalizacja zegara i pobranie obecnej godziny
  obecnaChwila = zegar.now();

  // pobranie godziny najblizszego alarmu
  czytajRTC();

  if(pamiec_RTC.nastepnyAlarm != 0 && pamiec_RTC.nastepnyAlarm != 1 && pamiec_RTC.nastepnyAlarm != 2 && pamiec_RTC.nastepnyAlarm != 3 && pamiec_RTC.nastepnyAlarm != 4 && pamiec_RTC.nastepnyAlarm != 5 && pamiec_RTC.nastepnyAlarm != 6 && pamiec_RTC.nastepnyAlarm != 7 && pamiec_RTC.nastepnyAlarm != 8 && pamiec_RTC.nastepnyAlarm != 9 && pamiec_RTC.nastepnyAlarm != 10 && pamiec_RTC.nastepnyAlarm != 11 && pamiec_RTC.nastepnyAlarm != 12 && pamiec_RTC.nastepnyAlarm != 13 && pamiec_RTC.nastepnyAlarm != 14 && pamiec_RTC.nastepnyAlarm != 15 && pamiec_RTC.nastepnyAlarm != 16 && pamiec_RTC.nastepnyAlarm != 17 && pamiec_RTC.nastepnyAlarm != 18 && pamiec_RTC.nastepnyAlarm != 19 && pamiec_RTC.nastepnyAlarm != 20 && pamiec_RTC.nastepnyAlarm != 21 && pamiec_RTC.nastepnyAlarm != 22 && pamiec_RTC.nastepnyAlarm != 23){
    pobraniePierwszegoAlarmu();
  }
  
  // spanie jeśli czekamy na alarm
  spanie();
  
  Serial.println("po spaniu");
  
  // ruch silnikiem krokowym
  ruchSilnika();
  
  // zasilenie buzzera i diody w przycisku
  //Serial.println("Read1");
  ekspander.write(0, HIGH);
  ekspander.write(1, HIGH);
  
  // zczytywanie kiedy wciśnięty zostanie przycisk
  kiedyWcisniety();
  
  // wyłączeine buzzera i diody
  ekspander.write(0, LOW);
  ekspander.write(1, LOW);
  //Serial.println("Read2");

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
  wysylIlosciDawek();

  // wysłanie poziomu baterii
  wysylPoziomuBaterii();
}

void loop() {}

void spanie(){
  if(pamiec_RTC.nastepnyAlarm - obecnaChwila.hour() > 1) {   // godzina spania
    ESP.deepSleep(CZAS_SPANIA_60 * 1e6);
  } else if(obecnaChwila.minute() < 15){                          // 45 min spania
    ESP.deepSleep(CZAS_SPANIA_45 * 1e6);
  } else if(obecnaChwila.minute() < 30){                          // 30 min spania
    ESP.deepSleep(CZAS_SPANIA_30 * 1e6);
  } else if(obecnaChwila.minute() < 40){                          // 20 min spania
    ESP.deepSleep(CZAS_SPANIA_20 * 1e6);
  } else if(obecnaChwila.minute() < 45){                          // 15 min spania
    ESP.deepSleep(CZAS_SPANIA_15 * 1e6);
  } else if(obecnaChwila.minute() < 50){                          // 10 min spania
    ESP.deepSleep(CZAS_SPANIA_10 * 1e6);
  } else if(obecnaChwila.minute() < 55){                           // 5 min spania
    ESP.deepSleep(CZAS_SPANIA_5 * 1e6);
  } else if(obecnaChwila.minute() < 59){                           // 1 min spania
    ESP.deepSleep(CZAS_SPANIA_1 * 1e6);
  }
}

void ruchSilnika(){
  for(int i=0; i<32; ++i){
    ekspander.write(4, HIGH);
    ekspander.write(5, HIGH);
    ekspander.write(6, LOW);
    ekspander.write(7, LOW);
    delay(10);
    
    ekspander.write(4, LOW);
    ekspander.write(5, HIGH);
    ekspander.write(6, HIGH);
    ekspander.write(7, LOW);
    delay(10);
    
    ekspander.write(4, LOW);
    ekspander.write(5, LOW);
    ekspander.write(6, HIGH);
    ekspander.write(7, HIGH);
    delay(10);
    
    ekspander.write(4, HIGH);
    ekspander.write(5, LOW);
    ekspander.write(6, LOW);
    ekspander.write(7, HIGH);
    delay(10);
  }
}

void kiedyWcisniety(){
  while(1){
    if(ekspander.read(2)){    // czy chce odczytać 1 czy 0?
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
  obecnaChwila = zegar.now();

  Firebase.setInt("/Dane/"+nazwa+"/dzien", obecnaChwila.year());       // gdy zegar będzie działać - zamienić
  Firebase.setInt("/Dane/"+nazwa+"/miesiac", obecnaChwila.month());
  Firebase.setInt("/Dane/"+nazwa+"/rok", obecnaChwila.year());
  Firebase.setInt("/Dane/"+nazwa+"/godziny", obecnaChwila.hour());
  Firebase.setInt("/Dane/"+nazwa+"/minuty", obecnaChwila.minute());
  Firebase.setInt("/Dane/iloscDanych", iloscDanych);
}

void wysylIlosciDawek(){
  int pozostaleDawki = Firebase.getInt("/Ustawienia/iloscPozostalychDawek")-1;
  Firebase.setInt("/Ustawienia/iloscPozostalychDawek", pozostaleDawki);
}

void wysylPoziomuBaterii(){
  //Firebase.setInt("/Ustawienia/poziom", analogRead(A0)*100/1023);
  Firebase.setInt("/Ustawienia/poziomBaterii", 20);            // do testu -------------
}

void pobraniePierwszegoAlarmu(){
  // łączenie z wifi
  wifiConnect();

  // łączenie z firebase
  Firebase.begin(FIREBASE_BAZA, FIREBASE_KLUCZ);
  delay(100);
  
  Serial.println("przed zapisem");
  int zmienna = Firebase.getString("/Ustawienia/godziny1").toInt();
  pamiec_RTC.nastepnyAlarm = zmienna;
  Serial.println(pamiec_RTC.nastepnyAlarm);
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
  zapiszRTC();
  Serial.println(pamiec_RTC.nastepnyAlarm);
}

void czytajRTC(){
  system_rtc_mem_read(65, &pamiec_RTC, sizeof(pamiec_RTC));
  yield();
}

void zapiszRTC(){
  system_rtc_mem_write(65, &pamiec_RTC, 4);
  yield();
}
