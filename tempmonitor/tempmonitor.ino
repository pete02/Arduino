#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <hd44780.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);
static const char ntpServerName[] = "us.pool.ntp.org";
const char* ssid PROGMEM = "peten purkki";
const char* password PROGMEM= "secret";
const char* broker PROGMEM = "192.168.1.39";
int timeZone=2;
WiFiClient espClient;

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

int on=0;
time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

PubSubClient client(espClient);
void setupWifi(){
    delay(100);
    Serial.print("\nConnecting to");
    Serial.print(ssid);
    WiFi.hostname("ESP_host");
    
    WiFi.begin(ssid,password);
    
    while(WiFi.status() != WL_CONNECTED){
      lcd.setCursor(14,3);
      lcd.print("wf:oh ");
        Serial.print("-");
        delay(1000);
      }
      
      Serial.print("\nConnceted to ");
      Serial.print(ssid);
      lcd.setCursor(14,3);
      lcd.print("net:wf");
  }

void callback(char* topic, byte* payload, unsigned int length){
    Serial.print("messages ");
    Serial.println(topic);
    Serial.print(strlen(topic));
    if(strcmp(topic,"ulko/temp")==0){
      lcd.setCursor(0,1);
      lcd.print("          ");
     lcd.setCursor(0,1);
     lcd.print("Out:");
    for(int i=0; i<length; i++){
        Serial.print((char) payload[i]);
           lcd.print((char) payload[i]);
      }
      lcd.print(char(0xDF));
       lcd.print("C");
    }
    if(strcmp(topic,"ulko/low")==0){
    lcd.setCursor(0,2);
    lcd.print("          ");
    lcd.setCursor(0,2);
    lcd.print("Alin:");
    for(int i=0; i<length; i++){
        Serial.print((char) payload[i]);
           lcd.print((char) payload[i]);
      }
      lcd.print(char(0xDF));
      lcd.print("C");
    }
    if(strcmp(topic,"in/temp")==0){
      lcd.setCursor(0,0);
      lcd.print("         ");
     lcd.setCursor(0,0);
     lcd.print("In:");
    for(int i=0; i<length; i++){
        Serial.print((char) payload[i]);
           lcd.print((char) payload[i]);
      }
      lcd.print(char(0xDF));
      lcd.print("C");
      }
    if(strcmp(topic,"ulko/highest")==0){
    lcd.setCursor(0,3);
    lcd.print("           ");
    lcd.setCursor(0,3);
    lcd.print("Ylin:");
    for(int i=0; i<length; i++){
        Serial.print((char) payload[i]);
           lcd.print((char) payload[i]);
      }

      
      lcd.print(char(0xDF));
      lcd.print("C");
    }
    if(strcmp(topic,"on")==0){
          if(on==1){
          lcd.noBacklight();
          on=0;}
          else{
            lcd.backlight();
            on=1;
          }
         
      }

    if(strcmp(topic,"summertime")==0){
          if(timeZone==2){
              timeZone=3;
          }
          else if(timeZone==3){
              timeZone=2;
          }
         
      }

      if(strcmp(topic,"wind/out")==0){
        lcd.setCursor(11,0);
        lcd.print("          ");
        lcd.setCursor(11,0);
        lcd.print("w:");
        for(int i=0; i<length; i++){
           lcd.print((char) payload[i]);
      }
      lcd.print("m/s");
        }
        
       if(strcmp(topic,"wind/high")==0){
          lcd.setCursor(11,1);
        lcd.print("          ");
        lcd.setCursor(11,1);
        lcd.print("p:");
        for(int i=0; i<length; i++){
           lcd.print((char) payload[i]);
      }
      lcd.print("m/s");
        }

        
      Serial.println();
  }
  

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    if(WiFi.status() != WL_CONNECTED){
    lcd.setCursor(14,3);
    lcd.print("net:EI");
    setupWifi();
    }
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement..
      client.subscribe("ulko/temp");
      client.subscribe("ulko/low");
      client.subscribe("ulko/highest");
      client.subscribe("in/temp");
      client.subscribe("on");
      client.subscribe("wind/out");
      client.subscribe("wind/high");
      client.subscribe("summertime");
      lcd.setCursor(14,3);
      lcd.print("net:mq");
      delay(2000);
    } else {
      
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      lcd.setCursor(15,3);
      lcd.print("net:wf");;
      delay(5000);
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  setupWifi();
  client.setServer(broker, 1883);
  client.setCallback(callback);
  Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
   Wire.setClock(10000);
}

time_t prevDisplay = 0; // when the digital clock was displayed
void loop() {
  int prevtZ=timeZone;
  if(WiFi.status() != WL_CONNECTED){
    lcd.setCursor(14,3);
    lcd.print("net:EI");
    setupWifi();
    }
  if(!client.connected()){
     delay(5000);
      reconnect();
    }
    client.loop();
    if (timeStatus() != timeNotSet || timeZone !=prevtZ ) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();
    }
  }
  

}
void digitalClockDisplay()
{
  // digital clock display of the time
  lcd.setCursor(12,2);
  if(hour()+timeZone <10 ){
  lcd.print(0);
  lcd.print(hour()+timeZone);
  }else{
    lcd.print(hour()+timeZone);
  }
  
  lcd.print(":");
   if(minute() <10 ){
  lcd.print(0);
  lcd.print(minute());
  }else{
    lcd.print(minute());
  }

  lcd.print(":");
   if(second() <10 ){
  lcd.print(0);
  lcd.print(second());
  }else{
    lcd.print(second());
  }
;
}


/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
