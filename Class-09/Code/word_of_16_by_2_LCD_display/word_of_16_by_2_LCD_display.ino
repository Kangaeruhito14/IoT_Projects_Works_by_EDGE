#include <LiquidCrystal_I2C.h> // includes the I2C library



LiquidCrystal_I2C lcd(0x27, 16, 2); //set the address for the I2C module, and the lines and characters per line.



void setup()

{

lcd.init(); // initialize the lcd

lcd.backlight(); // turn on the backlight

}



void loop()

{

lcd.clear(); // clear display

lcd.setCursor(0, 0); // move cursor to (0, 0)

lcd.print("Group-4"); // print message at (0, 0)

lcd.setCursor(2, 1); // move cursor to (2, 1)

lcd.print("So,AP,HA,SA"); // print message at (2, 1)

delay(2000); // display the above for two seconds



lcd.clear(); // clear display

lcd.setCursor(3, 0); // move cursor to (3, 0)

lcd.print("lcd with I2C"); // print message at (3, 0)

lcd.setCursor(0, 1); // move cursor to (0, 1)

lcd.print("module"); // print message at (0, 1)

delay(2000); // display the above for two seconds

}