#include <LiquidCrystal_I2C.h> // includes the I2C library

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the address for the I2C module, and the lines and characters per line

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight(); // turn on the backlight
}

void loop()
{
  // First message scrolling
  lcd.clear();
  // lcd.setCursor(1, 0); // set cursor to (0,0)
  // lcd.print("Group-4"); // print message at (0,0)
  lcd.setCursor(2, 0); // set cursor to (2,1)
  lcd.print("Group-4"); // print message at (3,0)
  

  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft(); // scroll the display to the left
    delay(250); // wait for 250ms between scrolls
  }
  
  delay(1000); // hold the display for a second

  // Second message scrolling
  lcd.clear();
  lcd.setCursor(4, 1); // set cursor to (3,0)
  // lcd.print("Group-4"); // print message at (3,0)
  lcd.print("Sonali,Anup,Habiba,Sharmin"); // print message at (2,1)
  // lcd.setCursor(0, 1); // set cursor to (0,1)
  // lcd.print("module"); // print message at (0,1)

  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft(); // scroll the display to the left
    delay(250); // wait for 250ms between scrolls
  }
  
  delay(1000); // hold the display for a second
}
