#include <netti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  netti.SetupWifi();
}
HTTPClient http;
WiFiClient clinet=netti.retClient();
void loop() {
  // put your main code here, to run repeatedly:
    Serial.print("[HTTP] begin...\n");
    if (http.begin(clinet, "http://192.168.1.39:1880/tieto")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          StaticJsonDocument<256> doc;

          DeserializationError error = deserializeJson(doc, payload);
          
          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            
            return;
          }
          
          float Current_in = doc["Current_in"]; // 24.9
          float Current_out = doc["Current_out"]; // 14.6
          int in_hum = doc["in_hum"]; // 100
          int out_hum = doc["out_hum"]; // 100
          float wind_avg = doc["wind_avg"]; // 12.59
          float wind_highest = doc["wind_highest"]; // 12.35
          float Highest = doc["Highest"]; // 17.6
          float Lowest = doc["Lowest"]; // 15.6
          Serial.print("current_in: ");
          Serial.println(Current_in);
          }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }

  delay(500);
}
