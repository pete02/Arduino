#include <SimpleDHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
// Update these with values suitable for your network.
#define DHTPIN D1
#define DHTTYPE    DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

const char* ssid PROGMEM = "peten purkki";
const char* password PROGMEM= "secret";
const char* mqtt_server PROGMEM = "192.168.1.39";
float temp=0;
float hum=0;
float i=0;
char restul[8];
char result[8];
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int ms=0;
void wifi_status_led_uninstall();

void setup_wifi() {

  delay(100);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("ESP_host");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.print("resetting ESP");
  ESP.restart();

 

}
void(* resetFunc) (void) = 0;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
      if(WiFi.status() != WL_CONNECTED){
    delay(5000);
      setup_wifi();
    }
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("in/reset");
      // Once connected, publish an announcement...
    } else {
      i=i+1;
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    if (i == 5){
      ESP.restart();
      }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  dht.begin();
  Serial.println("setup");
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    delay(5000);
      setup_wifi();
    }  
 if (!client.connected()) {
    delay(5000);
    reconnect();
  }
  delay(100);
  client.loop();
   i=0;
  float memo = ESP.getFreeHeap();
    if(memo < 1000){
      resetFunc();
    }
  
 
  while ms
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
    unsigned long now = millis();
    if (now - lastMsg > 2000) {
      dtostrf(temp, 6, 2, restul);    lastMsg = now;
  
      dtostrf(hum, 6, 2, result);
      Serial.print("Publish message: ");
      client.publish("inside/temp", restul);
      client.publish("inside/humidity", result);
      
  
   delay(15000);
  }
}
}
