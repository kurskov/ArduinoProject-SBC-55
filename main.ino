#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "SBC55.h"

/* DEBUG MODE */
//#define DEBUG_ON 

#ifdef DEBUG_ON
  #define DEBUG(x) Serial.println(x)
#else
  #define DEBUG(x)
#endif

#define STOPERROR for(;;)

LiquidCrystal_I2C lcd(0x27, 16, 2);

SBC55 sbc();

setup() {
  #ifdef DEBUG_ON
    Serial.begin(9600);
  #endif
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Loading... ");
  
  if (sbc.init()) STOPERROR;
  lcd.print("Ok");
}

loop() {
  
}
