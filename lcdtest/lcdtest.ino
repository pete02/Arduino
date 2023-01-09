#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <hd44780.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.begin();                      // initialize the lcd 
  lcd.begin();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("hello everyone");
  lcd.setCursor(1,1);
  lcd.print("mitä kuuluu");
  lcd.setCursor(1,2);
  lcd.print("mitä kuuluu");
  lcd.setCursor(1,3);
  lcd.print("mitä kuuluu");
}


void loop()
{
  lcd.backlight();
  delay(2000);
  lcd.noBacklight();
  delay(2000);
}
