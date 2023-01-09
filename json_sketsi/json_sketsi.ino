#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

WiFiClient client;

// Replace with your Raspberry Pi IP address
const char* server = "192.168.1.216";

// Replace with your server port number frequently port 80 - with Node-RED you need to use port 1880
int portNumber = 9000;

// Replace with your unique URL resource
const char* resource = "/api/sensors";

const unsigned long HTTP_TIMEOUT = 10000;  // max respone time from server
const size_t MAX_CONTENT_SIZE = 512;       // max size of the HTTP response


// ARDUINO entry point #1: runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  WiFi.begin("ASUS", "esP227#pih");
  Serial.println("connecting");
 while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  Serial.print("connected");
  Serial.println("Serial ready");
  
  Serial.println("Ethernet ready");
  delay(1000);
}

// ARDUINO entry point #2: runs over and over again forever
void loop() {
  if(connect(server, portNumber)) {
    if(sendRequest(server, resource) && skipResponseHeaders()) {
      Serial.print("HTTP POST request finished.");
    }
  }
  disconnect();
  wait();
}

// Open connection to the HTTP server (Node-RED running on Raspberry Pi)
bool connect(const char* hostName, int portNumber) {
  Serial.print("Connect to ");
  Serial.println(hostName);

  bool ok = client.connect(hostName, portNumber);

  Serial.println(ok ? "Connected" : "Connection Failed!");
  return ok;
}

// Send the HTTP POST request to the server
bool sendRequest(const char* host, const char* resource) {
  // Reserve memory space for your JSON data
  StaticJsonBuffer<200> jsonBuffer;
  
  // Build your own object tree in memory to store the data you want to send in the request
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = 10;
  root["humidity"]=10;
   
  // Generate the JSON string
  root.printTo(Serial);
  
  Serial.print("POST ");
  Serial.println(resource);

  client.print("POST ");
  client.print(resource);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.print(root.measureLength());
  client.print("\r\n");
  client.println();
  root.printTo(client);

  return true;
}

// Skip HTTP headers so that we are at the beginning of the response's body
bool skipResponseHeaders() {
  // HTTP headers end with an empty line
  char endOfHeaders[] = "\r\n\r\n";

  client.setTimeout(HTTP_TIMEOUT);
  bool ok = client.find(endOfHeaders);

  if(!ok) {
    Serial.println("No response or invalid response!");
  }
  return ok;
}

// Close the connection with the HTTP server
void disconnect() {
  Serial.println("Disconnect");
  client.stop();
}

// Pause for a 1 minute
void wait() {
  Serial.println("Wait 60 seconds");
  delay(60000);
}
