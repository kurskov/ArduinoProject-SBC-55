#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "SBC55.h"

/* DEBUG MODE */
#define DEBUG_ON 

#ifdef DEBUG_ON
  #define DEBUG(x) Serial.println(x)
#else
  #define DEBUG(x)
#endif

#define STOPERROR for(;;)

#define SBC_LATCH_PIN 8     // ST_CP pin of 74HC595
#define SBC_CLOCK_PIN 12    // SH_CP pin of 74HC595
#define SBC_DATA_PIN 11     // DS pin of 74HC595

LiquidCrystal_I2C lcd(0x27, 16, 2);

SBC55 sbc(SBC_LATCH_PIN, SBC_CLOCK_PIN, SBC_DATA_PIN);

void setup() {
  #ifdef DEBUG_ON
    Serial.begin(9600);
  #endif
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Data load...");
  
  if (sbc.init()) STOPERROR;
  sbc.afterOn();
  lcd.print(" Ok");
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air blast");
  sbc.airBlast(3);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stand by");
  sbc.standBy();

  delay(5000);
}
