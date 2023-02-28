//sketch created by Akshay Joseph
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String str = "bike met with an minor-accident";
void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("7901427367");
   // set cursor to first column, second row
  // print scrolling message
  scrollText(1, str, 320, 16);
}
void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void lcdprint(String str){
  lcd.print(str);
}
