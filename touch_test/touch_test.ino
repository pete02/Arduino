#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
// Led->D0
#define CALIBRATION_FILE "/calibrationData"

void setup(void) {
  pinMode(D1,OUTPUT);
  digitalWrite(D1,HIGH);
  uint16_t calibrationData[5];
  uint8_t calDataOK = 0;

  Serial.begin(115200);
  Serial.println("starting");

  tft.init();

  tft.setRotation(1 );
  tft.fillScreen((0xFFFF));

  tft.setCursor(20, 0, 2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);  tft.setTextSize(1);
  tft.drawRect(100,100,100,100,TFT_RED);
}
void loop() {
  uint16_t x, y;
  if (tft.getTouch(&x, &y)) {

    if(x>100 && x<200){
      if(y>100 && y<200){
        Serial.print("x:");
        Serial.print(x);
        Serial.print(" y:");
        Serial.print(y);
        Serial.println();
        tft.fillScreen(TFT_BLUE);
        delay(3000);
        digitalWrite(D1,LOW);
        delay(3000);
        digitalWrite(D1,HIGH);
        tft.fillScreen((0xFFFF));
        tft.drawRect(100,100,100,100,TFT_RED);
      }
    }
  }

}
