#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
//#include "DS1307.h"

#define WIFI_NAZWA "DESKTOP"
#define WIFI_HASLO "m&k$0001"
#define FIREBASE_BAZA "robotdowydawanialekow.firebaseio.com"
#define FIREBASE_KLUCZ "HHdjaAsoNlfx7vMf7ht73WEzNGa7KK5TtcRbN9uy"

#define CZAS_SPANIA 3600                              //CZAS_SPANIA to czas sekund jednego cyklu spania - docelowo godzina 60*60 = 3600 sekund

//DS1307 zegar;

typedef struct {
  int nastepnyAlarm;
} skladowanie_RTC;

skladowanie_RTC pamiec_RTC;

//int obecnaGodzina;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  //zegar.begin();
  pamiec_RTC.nastepnyAlarm = 23;
  //obecnaGodzina = zegar.hour + zegar.minute/60; //pobranie obecnej godziny z RTC
/*
  // spanie jeśli czekamy na alarm
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
  }*/
  
  // ruch silnikiem krokowym
  // ustawienie pinów z buzzerem i diodą na OUTPUT i zasilenie
  // ustawienie pinu z przyciskiem na INPUT i zczytywanie kiedy wyłączone

  wifiConnect();

  Firebase.begin(FIREBASE_BAZA, FIREBASE_KLUCZ);
  delay(100);

  // przesył danych do bazy
  int iloscDanych = Firebase.getInt("/Dane/iloscDanych") + 1;
  String nazwa = "dane" + String(iloscDanych);
  /*
  Firebase.setInt("/Dane/"+nazwa+"/dzien", zegar.dayOfMonth);       // gdy zegar będzie działać - zamienić
  Firebase.setInt("/Dane/"+nazwa+"/miesiac", zegar.month);
  Firebase.setInt("/Dane/"+nazwa+"/rok", zegar.year+2000);
  Firebase.setInt("/Dane/"+nazwa+"/godziny", zegar.hour);
  Firebase.setInt("/Dane/"+nazwa+"/minuty", zegar.minute);
  Firebase.setInt("/Dane/iloscDanych", iloscDanych);
  */
  /*
  Firebase.setInt("/Dane/"+nazwa+"/dzien", 27);
  Firebase.setInt("/Dane/"+nazwa+"/miesiac", 10);
  Firebase.setInt("/Dane/"+nazwa+"/rok", 2020);
  Firebase.setInt("/Dane/"+nazwa+"/godziny", 14);
  Firebase.setInt("/Dane/"+nazwa+"/minuty", 56);
  Firebase.setInt("/Dane/iloscDanych", iloscDanych);
  */
  
  
  // pobieranie ustawień na następny alarm
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
  //Serial.print(pamiec_RTC.nastepnyAlarm);

  // zmiejszenie ilości dostępnych dawek leków o 1
  //int pozostaleDawki = Firebase.getInt("/Ustawienia/iloscPozostalychDawek")-1;
  //Firebase.setInt("/Ustawienia/iloscPozostalychDawek", pozostaleDawki);
 
}

void loop() {
  /*
  Serial.println("Value: " + Firebase.getInt("LEDStatus"));
  if (Firebase.getInt("LEDStatus")) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  if (Firebase.failed()) { // Check for errors
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    //return;
  }
  delay(10);
  */
}

void wifiConnect() {
  WiFi.begin(WIFI_NAZWA, WIFI_HASLO);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_NAZWA); Serial.println(" ...");

  int teller = 0;
  while (WiFi.status() != WL_CONNECTED) {                                      // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}
/*
  void readFrompamiec_RTCory(){
  system_rtc_mem_read(pamiec_RTCORYSTART, &pamiec_RTC, sizeof(pamiec_RTC));
  yield();
  }

  void writeTopamiec_RTCory(){
  system_rtc_mem_write(pamiec_RTCORYSTART, &pamiec_RTC, 4);
  yield();
  }
*/
