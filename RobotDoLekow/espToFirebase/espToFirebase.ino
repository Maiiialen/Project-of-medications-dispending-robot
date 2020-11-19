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
void pobranieAlarmu();
void wysylLiczbaDawek();
void czytajRTC();
void zapiszRTC();
void wlaczAlarm();
void wylaczAlarm();

void wysylPoziom(int value);
void wysylAlarm(int value);

void setup() {  
  Serial.begin(9600);
  Serial.println("! - - ");
  
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
  
  // łączenie z firebase
  Firebase.begin(FIREBASE_BAZA, FIREBASE_KLUCZ);
  delay(100);

  if(pamiec_RTC.nastepnyAlarm != 0 && pamiec_RTC.nastepnyAlarm != 1 && pamiec_RTC.nastepnyAlarm != 2 && pamiec_RTC.nastepnyAlarm != 3 && pamiec_RTC.nastepnyAlarm != 4 && pamiec_RTC.nastepnyAlarm != 5 && pamiec_RTC.nastepnyAlarm != 6 && pamiec_RTC.nastepnyAlarm != 7 && pamiec_RTC.nastepnyAlarm != 8 && pamiec_RTC.nastepnyAlarm != 9 && pamiec_RTC.nastepnyAlarm != 10 && pamiec_RTC.nastepnyAlarm != 11 && pamiec_RTC.nastepnyAlarm != 12 && pamiec_RTC.nastepnyAlarm != 13 && pamiec_RTC.nastepnyAlarm != 14 && pamiec_RTC.nastepnyAlarm != 15 && pamiec_RTC.nastepnyAlarm != 16 && pamiec_RTC.nastepnyAlarm != 17 && pamiec_RTC.nastepnyAlarm != 18 && pamiec_RTC.nastepnyAlarm != 19 && pamiec_RTC.nastepnyAlarm != 20 && pamiec_RTC.nastepnyAlarm != 21 && pamiec_RTC.nastepnyAlarm != 22 && pamiec_RTC.nastepnyAlarm != 23){
    pobranieAlarmu();
  }
  
  Serial.print("godzina alarmu: ");
  Serial.println(pamiec_RTC.nastepnyAlarm);
  
  // spanie jeśli czekamy na alarm
  spanie();
  
  Serial.println("po spaniu");
  
  // ruch silnikiem krokowym
  ruchSilnika();
  delay(100);
  
  Serial.println("po ruchu silnika");
  
  // zasilenie buzzera i diody w przycisku
  wlaczAlarm();
  
  Serial.println("dioda wlaczona");
  
  // zczytywanie kiedy wciśnięty zostanie przycisk
  kiedyWcisniety();
  
  Serial.println("po przycisku");
  
  // wyłączeine buzzera i diody
  wylaczAlarm();
  
  Serial.println("dioda wylaczona");
  Serial.println("teraz wifi");

  // łączenie z wifi
  wifiConnect();

  Serial.println("teraz firebase");
  
  // przesył danych do bazy
  przesylNowychDanych();

  // pobieranie ustawień na następny alarm
  pobranieAlarmu();

  // zmiejszenie ilości dostępnych dawek leków o 1
  wysylLiczbaDawek();

  spanie();
}


void loop() {}


void spanie(){
  Serial.print("start spania: ");
  if(abs(pamiec_RTC.nastepnyAlarm - obecnaChwila.hour()) > 1) {   // godzina spania
    //wysylPoziom(60);
    Serial.println("1 godzina");
    ESP.deepSleep(CZAS_SPANIA_60 * 1e6);
  } else if(pamiec_RTC.nastepnyAlarm - obecnaChwila.hour() < 0) {   // godzina spania
    //wysylPoziom(60);
    Serial.println("1 godzina");
    ESP.deepSleep(CZAS_SPANIA_60 * 1e6);
  } else if(obecnaChwila.minute() < 15){                          // 45 min spania
    //wysylPoziom(45);
    Serial.println("45 min");
    ESP.deepSleep(CZAS_SPANIA_45 * 1e6);
  } else if(obecnaChwila.minute() < 30){                          // 30 min spania
    //wysylPoziom(30);
    Serial.println("30 min");
    ESP.deepSleep(CZAS_SPANIA_30 * 1e6);
  } else if(obecnaChwila.minute() < 40){                          // 20 min spania
    //wysylPoziom(20);
    Serial.println("20 min");
    ESP.deepSleep(CZAS_SPANIA_20 * 1e6);
  } else if(obecnaChwila.minute() < 45){                          // 15 min spania
    //wysylPoziom(15);
    Serial.println("15 min");
    ESP.deepSleep(CZAS_SPANIA_15 * 1e6);
  } else if(obecnaChwila.minute() < 50){                          // 10 min spania
    //wysylPoziom(40);
    Serial.println("10 min");
    ESP.deepSleep(CZAS_SPANIA_10 * 1e6);
  } else if(obecnaChwila.minute() < 55){                           // 5 min spania
    //wysylPoziom(5);
    Serial.println("5 min");
    ESP.deepSleep(CZAS_SPANIA_5 * 1e6);
  } else if(obecnaChwila.minute() < 59){                           // 1 min spania
    //wysylPoziom(1);
    Serial.println("1 min");
    ESP.deepSleep(CZAS_SPANIA_1 * 1e6);
  }
  wysylPoziom(100);
}

void ruchSilnika(){
  for(int i=0; i<96; ++i){  //32?
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
  ekspander.write(4, LOW);
  ekspander.write(5, LOW);
  ekspander.write(6, LOW);
  ekspander.write(7, LOW);
  delay(10);
}

void wlaczAlarm(){
  ekspander.write(0, HIGH);
  ekspander.write(1, HIGH);
  
}

void wylaczAlarm(){
  ekspander.write(0, LOW);
  ekspander.write(1, LOW);
}

void kiedyWcisniety(){
  while(1){
    if(ekspander.read(2)){
      break;
    }
    delay(100);
  }
}

void wifiConnect(){
  WiFi.begin(WIFI_NAZWA, WIFI_HASLO);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
  }
}

void przesylNowychDanych(){
  int liczbaDanych = Firebase.getInt("/Dane/liczbaDanych") + 1;
  String nazwa = "dane" + String(liczbaDanych);
  obecnaChwila = zegar.now();

  Firebase.setInt("/Dane/"+nazwa+"/dzien", obecnaChwila.day());
  Firebase.setInt("/Dane/"+nazwa+"/miesiac", obecnaChwila.month());
  Firebase.setInt("/Dane/"+nazwa+"/rok", obecnaChwila.year());
  Firebase.setInt("/Dane/"+nazwa+"/godziny", obecnaChwila.hour());
  Firebase.setInt("/Dane/"+nazwa+"/minuty", obecnaChwila.minute());
  Firebase.setInt("/Dane/liczbaDanych", liczbaDanych);
}

void wysylLiczbaDawek(){
  int pozostaleDawki = Firebase.getInt("/Ustawienia/liczbaPozostalychDawek")-1;
  Firebase.setInt("/Ustawienia/liczbaPozostalychDawek", pozostaleDawki);
}

// ---------------
void wysylPoziom(int value){
  Firebase.setInt("/Ustawienia/czasSpania", value);
}


void wysylAlarm(int value){
  Firebase.setInt("/Ustawienia/najblizszyAlarm", value);
}
//-----------------

void pobranieAlarmu(){
  // łączenie z wifi
  wifiConnect();

  int liczba = Firebase.getInt("/Ustawienia/liczba");
  
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
  pamiec_RTC.nastepnyAlarm = h1;
  if(liczba == 2){
    if(h1 <= obecnaChwila.hour()){
      if(h2 <= obecnaChwila.hour()){
        pamiec_RTC.nastepnyAlarm = h1;
      } else {
        pamiec_RTC.nastepnyAlarm = h2;
      }
    }
  } else if(liczba == 3){
    if(h1 <= obecnaChwila.hour()){
      if(h2 <= obecnaChwila.hour()){
        if(h3 <= obecnaChwila.hour()){
          pamiec_RTC.nastepnyAlarm = h1;
        } else {
          pamiec_RTC.nastepnyAlarm = h3;
        }
      } else {
        pamiec_RTC.nastepnyAlarm = h2;
      }
    }
  }
  zapiszRTC();
  Serial.println(pamiec_RTC.nastepnyAlarm);
  wysylAlarm(pamiec_RTC.nastepnyAlarm);
}

void czytajRTC(){
  system_rtc_mem_read(65, &pamiec_RTC, sizeof(pamiec_RTC));
  yield();
}

void zapiszRTC(){
  system_rtc_mem_write(65, &pamiec_RTC, sizeof(pamiec_RTC));
  yield();
}
