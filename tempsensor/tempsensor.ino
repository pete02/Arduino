#include <SimpleDHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <netti.h>
#define DHTPIN D1
#define DHTTYPE    DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);



float temp=0;
float hum=0;
float i=0;
char restul[8];
char result[8];
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


void setup() {
  Serial.begin(115200);
  netti.SetupWifi();
  dht.begin();
  Serial.println("setup");
}

void loop() {
  netti.ReconnectWifi();
  netti.ReconnectMqtt("in/reset");

 unsigned long now = millis();
  while(now - lastMsg > 30000){
    //measure temps
     sensors_event_t event;
    dht.temperature().getEvent(&event);
    temp=event.temperature;
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      Serial.print(temp);
      Serial.println(F("°C"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    hum=event.relative_humidity;
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      Serial.print(F("Humidity: "));
      Serial.print(hum);
      Serial.println(F("%"));
    
    
      dtostrf(temp, 6, 2, restul);    
      lastMsg = now;
  
      dtostrf(hum, 6, 2, result);
      Serial.print("Publish message: ");
      netti.mqttpublish("out/temp", restul);
      netti.mqttpublish("out/humidity", result);
         }  
    
        }
      }
 
