#include <ESP8266WiFi.h>
#include "netti.h"
#include "Arduino.h"
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

IPAddress ip(192, 168, 1, 100);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer TelnetServer(23);
WiFiClient Telnet;
char* resettopic="placeholder will be remoden";


std::unordered_map<char* ,byte*>callbak;
void(* resetFunc) (void) = 0;

void handleTelnet(char* w){
  //Telnet.println("test");
  if(w != "es print tehst"){
    Telnet.println(w);
  }
  Serial.print("telnet handler called: ");
  Serial.println(w);
  if (TelnetServer.hasClient()){
    if (!Telnet || !Telnet.connected()){
      if(Telnet) Telnet.stop();
      Serial.println("telnet available");
      Telnet =TelnetServer.available();
      
    }else {
      TelnetServer.available().stop();
      Serial.println("telnet in use");
    }
  }
};

WiFiClient netti_::retClient(){
  return espClient;
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("incominc from ");
  Serial.println(topic);

  if(strcmp(topic, resettopic) == 0){
    Serial.println("tested");
    ESP.restart();
  }else{
    callbak[topic]=payload;
  }
}
std::unordered_map<char* ,byte*> payloadret(){
  return callbak;
}

void netti_::SetupWifi() {
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println("peten purkki");
  WiFi.hostname("ESP_host");
  WiFi.config(ip, gateway, subnet);
  WiFi.begin("peten purkki","secret");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  };
  client.setServer("192.168.0.100",1883);
  client.setCallback(callback);
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //TelnetServer.begin();
  //TelnetServer.setNoDelay(true);
};

int twi=0;
float lt=0;
float avg =0;

void netti_::TestWifi(){
  twi++;
  unsigned long now=millis();
  while(WiFi.status() == WL_CONNECTED){
    delay(10);
  }
  float time = millis()-now;
  time= time/1000;
  avg +=  time;
  float avt= avg/twi;
  if(time >lt){
    lt=time;
  }
  Serial.print("average time:");
  Serial.println(avt);
  Serial.print("longes:");
  Serial.println(lt);
  delay(1000);
  SetupWifi();
}

void netti_::ReconnectWifi() {
  int i=0;
  if(WiFi.status() != WL_CONNECTED){
    delay(5000);
      SetupWifi();
    };
    //handleTelnet("es print tehst");
  // Loop until we're reconnected
};


void netti_::mqttpublish(char* sub, char* msg){
  client.publish(sub, msg);
}

void netti_::Mqttsub(char* sub){
  if((sub != NULL) && (sub[0] != '\0')){
      client.subscribe(sub);
    }
}
void netti_::ReconnectMqtt(char* sub) {
  while(!client.connected()){
    int i=0;
    String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
    if(client.connect(clientId.c_str())) {
        Serial.println("connected");
        if((sub != NULL) && (sub[0] != '\0')){
          Serial.print("resettopic:");
          Serial.println(sub);
          client.subscribe(sub);
          resettopic=sub;
        }
        // Once connected, publish an announcement...
    
      } else {
        i=i+1;
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(50);
      }
      if (i == 5){
        ESP.restart();
        }
  }
  client.loop();
}

void netti_::SetupMobile() {
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println("peten puhelin");
  WiFi.hostname("ESP_host");
  WiFi.begin("Samsung_9","");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  };

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  TelnetServer.begin();
  TelnetServer.setNoDelay(true);
};


void netti_::ReconnectMobile() {
  int i=0;

  if(WiFi.status() != WL_CONNECTED){
    delay(5000);
    SetupMobile();
  }
  handleTelnet("es print tehst");
};

void netti_::write(char* w){
  handleTelnet(w);
}

netti_ &netti_::getInstance(){
  static netti_ instance;
  return instance;
}

netti_ &netti = netti.getInstance();