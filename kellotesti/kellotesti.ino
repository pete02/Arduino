#include <netti.h>

int val=0;
unsigned long tim;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  netti.SetupWifi();
  Serial.println("start");
  tim=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(D2)){
    val++;
    delay(10);
  }
  if(millis()-tim>300){
    Serial.println(val);
    if(val>5){
      Serial.println("kello soi");
      netti.ReconnectWifi();
      netti.ReconnectMqtt("kello/rest");
      netti.mqttpublish("kello","soi");

    }
    val=0;
    tim=millis();
  }
}
