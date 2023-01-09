#include <netti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <WiFiUdp.h>
#include "FS.h"
#include <SPI.h>
#include <TimeLib.h>
#include <Pinger.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
extern "C"
{
  #include <lwip/icmp.h> // needed for icmp packet definitions
}

#define CALIBRATION_FILE "/calibrationData"

Pinger pinger;
WiFiUDP Udp;
unsigned int localPort = 8888;  
extern "C"
 float Current_in=0;
float Current_out = 0;
float in_hum = 0;
float out_hum = 0;
float wind_avg = 0;
float wind_highest = 0;
float Highest = 0;
float Lowest = 0;
int onn=1;
int server_on=1;
TFT_eSPI tft = TFT_eSPI();
const char ssid[] = "peten purkki";  //  your network SSID (name)
const char pass[] = "secret";       // your network password
String pva[]= {"Sunnuntai","Maanantai","Tiistai","Keskiviikko","Torstai","Perjantai","Lauantai"};
String pv[]= {"Su","Ma","Ti","Ke","To","Pe","La"};

uint16_t darkblue= tft.color565(0,0,60);
HTTPClient http;
WiFiClient clinet=netti.retClient();
const int timeZone = 1; 

time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);
static const char ntpServerName[] = "us.pool.ntp.org";
time_t prevDisplay = 0;

struct weather{
  int d;
  int tim;
  const char* temp;
  const char* rain_p;
  const char* rain_a;
};

struct server_t{
  float cpu;
  float temp;
  int mem;
  float disk;
  float portainer;
  float traefik;
  float kirja_b;
  float kirja_f;
  float selenium;
  float codes;
  float jellyfin;
  float grafana;
  float homeassistant;
  float prometheus;
  float influxdb;
  float watchtower;
  float zigbee;
};
server_t server;
unsigned long no=0; 
int fisrd=0;
unsigned long no2=0; 
int secdisp=0;
weather ennuste[10];
unsigned long touch = 0;
int page=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(D1,OUTPUT);
  digitalWrite(D1,LOW);
  tft.init();
  Serial.begin(115200);
  netti.SetupWifi();
  setWifi();
  tft.setRotation(3);
  tft.setTextColor(darkblue, TFT_WHITE); 

}
unsigned long n=0; 
unsigned long trige=0;

uint16_t x, y;
void loop() {
  if(onn==1){
    if(tft.getTouch(&x, &y)){
      if((touch<millis()-1000)){
        touch=millis();
        if(x<200 &&(page==1||page==0)){
          page++;
        }else{
          if(x>200 && (page==2|| page==1) ){
          page--;
          }
        }
      }
    }
    
    if(page==1){
      digitalWrite(D1,HIGH);
      firstdisp();
      secdisp=0;
    }else if(page==2){
      digitalWrite(D1,HIGH);
      seconddisp();
      temp_reset();
    }else if(page==0){
      digitalWrite(D1,LOW);
      }
  }else{
    page=1;
    if(tft.getTouch(&x, &y)&&(millis()-trige>2000)){
      Serial.println("touched");
      if(10<x<410 && 30<y<240){
        change();
        JsonFetch();
        trige=millis();
      }
    }
     if(millis()-n>=1000){
      sleepfetch();
      n=millis();
    }
    digitalWrite(D1,LOW);
  }
}
