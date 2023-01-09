int val=0;
int prevval=0;
unsigned long tim;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  tim=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(D2)){
    val++;
    delay(10);
  }
  if(millis()-tim>30){
    if(val>3){
      Serial.println("got signal");
    }
    val=0;
    tim=millis();
  }
}
