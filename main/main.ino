/*
    Cleaning machine Finnsonic SBC-55

    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
    GitHub: https://github.com/kurskov/ArduinoProject-SBC-55
 
    MIT license
*/

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/* DEBUG MODE */

#define DEBUG_ON 

#ifdef DEBUG_ON
    #define DEBUG(x) Serial.println(x)
#else
    #define DEBUG(x)
#endif


/* ARDUINO PINS */

// Relay
#define RELAY_LATCH_PIN 8   // ST_CP pin of 74HC595
#define RELAY_CLOCK_PIN 12  // SH_CP pin of 74HC595
#define RELAY_DATA_PIN  11  // DS pin of 74HC595

// Hard buttons
#define EMS_BUTTON
#define RUN_BUTTON
#define START_BUTTON
#define STOP_BUTTON


/* RELAY OUTPUTS */

#define OUT_REDGREEN    0   // Turns off red and lights up green beacon (-Y27+Y25)
#define OUT_DOORLOCK    1   // Opens the door and lights white beacon (+Y17 +Y26)
#define OUT_VENTVALVE   2   // Ventilation open
#define OUT_AIRVALVE    3
#define OUT_AIRBLOWER   4   // Turn on hot air blower 
#define OUT_HEATER      5   // Turn on heating for hot air
#define OUT_HEATTANK_1  6   // Turn on heating of tank 1 (wash)
#define OUT_HEATTANK_2  7   // Turn on heating of tank 2 (rinse)



LiquidCrystal_I2C lcd(0x27, 16, 2);

uint16_t outputs = 0xFFFF; // relays outputs state

uint8_t mode = 0; 
uint8_t time = 0;

void setup() {

    #ifdef DEBUG_ON
        Serial.begin(9600);
    #endif

    // Run display
    lcd.init();
    lcd.backlight();
    lcd.setCursor(1, 0);
    lcd.print("Initialisation");

    // Set relay outputs
    pinMode(RELAY_LATCH_PIN, OUTPUT);
    pinMode(RELAY_CLOCK_PIN, OUTPUT); 
    pinMode(RELAY_DATA_PIN, OUTPUT);

    // Machine initialisation
    if (initialisation()) lcd.print(" Ok");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press run button");
    lcd.setCursor(2, 1);
    lcd.print("to continue");

    standBy();

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Stand by");
}

void loop() {
    
    if (mode) {
        time = 5;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Air blast    sec");
        lcd.setCursor(9, 0);
        lcd.print(time);
        airBlast(time);
        time = 10;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Air blow     sec");
        lcd.setCursor(9, 0);
        lcd.print(time);
        airBlow(time);
        time = 5;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Drying       sec");
        lcd.setCursor(9, 0);
        lcd.print(time);
        drying(time);
        mode = 0;
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Stand by");
        standBy();
        mode = 1;
    }

}


/* Safety door lock */
        
// Open safety door lock

void setDoorLockOpen(uint16_t time = 1000) {
    outputs |= (1<<OUT_DOORLOCK);
    setOutputs();
    DEBUG("...Open safety door lock");
    delay(time);
}

// Close safety door lock
void setDoorLockClose(uint16_t time = 1000) {
    outputs &= ~(1<<OUT_DOORLOCK);
    setOutputs();
    DEBUG("...Close safety door lock");
    delay(time);
}


/* Ventilation (exhaust) */
        
// Open ventilation valve (Y023)
void setVentValveOpen(uint16_t time = 1000) {
    outputs &= ~(1<<OUT_VENTVALVE);
    setOutputs();
    DEBUG("...Open ventilation valve (Y023 on)");
    delay(time);
}

// Close ventilation valve (Y023)
void setVentValveClose(uint16_t time = 1000) {
    outputs |= (1<<OUT_VENTVALVE);
    setOutputs();
    DEBUG("...Close ventilation valve (Y023 off)");
    delay(time);
}

/* Spray tubing */
        
// Open air valve (Y024)
void setAirValveOpen(uint16_t time = 1000) {
    outputs &= ~(1<<OUT_AIRVALVE);
    setOutputs();
    DEBUG("...Open air valve (Y024 off)");
    delay(time);
}

// Close air valve (Y024)
void setAirValveClose(uint16_t time = 1000) {
    outputs |= (1<<OUT_AIRVALVE);
    setOutputs();
    DEBUG("...Close air valve (Y024 off)");
    delay(time);
}

/* Hot air blow */

// Heater on
void setHeaterOn(uint16_t time = 1000) {
    outputs &= ~(1<<OUT_HEATER);
    setOutputs();
    DEBUG("...Heater on");
    delay(time);
}

// Heater off
void setHeaterOff(uint16_t time = 1000) {
    outputs |= (1<<OUT_HEATER);
    setOutputs();
    DEBUG("...Heater off");
    delay(time);
}

// Air blower on
void setAirBlowerOn(uint16_t time = 1000) {
    outputs &= ~(1<<OUT_AIRBLOWER);
    setOutputs();
    DEBUG("...Air blower on");
    delay(time);
}

// Air blower off
void setAirBlowerOff(uint16_t time = 1000) {
    outputs |= (1<<OUT_AIRBLOWER);
    setOutputs();
    DEBUG("...Air blower off");
    delay(time);
}


// Send outputs state to the relay module.
// First - high bit, second - low bit.
void setOutputs() {
    digitalWrite(RELAY_LATCH_PIN, LOW);
    shiftOut(RELAY_DATA_PIN, RELAY_CLOCK_PIN, MSBFIRST, (outputs >> 8));
    shiftOut(RELAY_DATA_PIN, RELAY_CLOCK_PIN, MSBFIRST, outputs);
    digitalWrite(RELAY_LATCH_PIN, HIGH);
}

/* Runtime program's functions */

// Check condition and position all parts of machine.
// Return 0 if check is Ok.
uint8_t initialisation() {
    DEBUG("\n> Check condition and position all parts of machine");
    setDoorLockClose();
    setAirValveClose();
    setVentValveOpen();
    setDoorLockOpen();
            
    return 0;
}

//
void standBy() {
    DEBUG("\n> Machine put on standby");
    setVentValveOpen();
    setDoorLockOpen();
}        

//
uint8_t wash(uint16_t sec) {}

// 
uint8_t rinse(uint16_t sec) {}

// 
uint8_t airBlast(uint16_t sec) {
    DEBUG("\n> Air blast");
    setDoorLockClose();
    setAirValveOpen(sec * 1000);
    setAirValveClose();
}

// 
uint8_t drip(uint8_t tank, uint16_t sec) {}

//
uint8_t airBlow(uint16_t sec) {
    DEBUG("\n> Air blow");
    setDoorLockClose();
    setAirValveOpen(sec * 1000);
    setAirValveClose();
}

// 
uint8_t drying(uint16_t sec) {
    DEBUG("\n> Drying");
    setDoorLockClose();
    setVentValveOpen();
    setAirBlowerOn();
    setHeaterOn(sec * 1000);
    setHeaterOff();
    setAirBlowerOff();
}
