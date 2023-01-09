void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  float memo = ESP.getFreeHeap();
  Serial.print("free memory ");
  Serial.println(memo);
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
