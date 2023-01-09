#include <netti.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(112500);
  netti.SetupWifi();
   
}


int i =0;
int k=300;
float h=0;
int t=0;
unsigned long now=millis();



void loop() {
  netti.ReconnectWifi();
  netti.ReconnectMqtt("wind/reset");
   int test = analogRead(A0);
   if(test>1000){
      if( k<100){
          k=1000;
          i++;
        }
    }
    if(test<200){
        k=test;
      }
   if(millis()-now>30000){
      netti.ReconnectWifi();
      netti.ReconnectMqtt("wind/reset");
      float g=i/10;
      g=g*0.4492;
      i=0;
      char r[8];
      dtostrf(g,6,2,r);
     netti.mqttpublish("windspeed",r);
      h=h+g;
      t++;
      if(t>60){
        char a[8];
        h=h/60; 
        dtostrf(h,6,2,a);
        netti.mqttpublish("avgwindspeed", a);
        h=0;
        t=0;
        }
      now=millis();
   }
   delay(10);
  }
 
