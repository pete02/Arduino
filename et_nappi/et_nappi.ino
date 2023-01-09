
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>

const char* ssid PROGMEM = "peten purkki";
const char* password PROGMEM= "secrets";
const char* mqtt_server PROGMEM = "192.168.1.39";
char restul[8];
char result[8];
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
float i=0;


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
      resetFunc();
      }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.println("setup");
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    delay(5000);
      setup_wifi();
    }
  digitalWrite(2, HIGH);  
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
  int value = analogRead(A0);
    if(value == 1024){
      Serial.println(value);
    client.publish("nappi", 0);
    delay(1000);
  }
}
