/*
    See SBC55.h for all information.
    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
*/

#include "SBC55.h"

/* DEBUG_SBC MODE */
#ifdef DEBUG_ON
  #define DEBUG_SBC(x) Serial.println(x)
#else
  #define DEBUG_SBC(x)
#endif


// Constructor

SBC55::SBC55(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin) {
    #ifdef DEBUG_ON
        Serial.begin(9600);
    #endif

    _latchPin = latchPin;
    _clockPin = clockPin;
    _dataPin = dataPin;

    pinMode(_latchPin, OUTPUT);
    pinMode(_dataPin, OUTPUT); 
    pinMode(_clockPin, OUTPUT);
}

// Public functions

uint8_t SBC55::init() {
    DEBUG_SBC("\n> Check condition and position all parts of machine");
    setDoorLockClose();
    delay(1000);
    setAirValveClose();
    delay(1000);
    setVentValveOpen();
    delay(1000);
    setDoorLockOpen();
            
    return 0;
}

void SBC55::afterOn() {
    DEBUG_SBC("\n> After on");
    setVentValveOpen();
    delay(1000);
    setDoorLockOpen();
    delay(1000);
}

void SBC55::standBy() {
    DEBUG_SBC("\n> Stand by");
    setVentValveOpen();
    delay(1000);
    setDoorLockOpen();
    delay(1000);
}

uint8_t SBC55::airBlast(uint16_t sec) {
    DEBUG_SBC("\n> Air blast");
    setDoorLockClose();
    delay(1000);
    setAirValveOpen();
    delay(sec * 1000);
    setAirValveClose();
    delay(1000);
}

uint8_t SBC55::airBlow(uint16_t sec) {
    DEBUG_SBC("\n> Air blow");
    setDoorLockClose();
    delay(1000);
    setAirValveOpen();
    delay(sec * 1000);
    setAirValveClose();
    delay(1000);
}

uint8_t SBC55::drying(uint16_t sec) {
    DEBUG_SBC("\n> Drying");
    setDoorLockClose();
    delay(1000);
    setVentValveOpen();
    delay(1000);
    setAirBlowerOn();
    delay(1000);
    setHeaterOn();
    delay(sec * 1000);
    setHeaterOff();
    delay(5000);
    setAirBlowerOff();
    delay(1000);
}

// Private functions

void SBC55::setOutputs() {
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, MSBFIRST, (_outputs >> 8));
    shiftOut(_dataPin, _clockPin, MSBFIRST, _outputs);
    digitalWrite(_latchPin, HIGH);
}

void SBC55::setDoorLockOpen() {
    _outputs |= (1<<OUT_DOORLOCK);
    setOutputs();
    DEBUG_SBC("...Open safety door lock");
}

void SBC55::setDoorLockClose() {
    _outputs &= ~(1<<OUT_DOORLOCK);
    setOutputs();
    DEBUG_SBC("...Close safety door lock");
}

void SBC55::setVentValveOpen() {
    _outputs &= ~(1<<OUT_VENTVALVE);
    setOutputs();
    DEBUG_SBC("...Open ventilation valve (Y023 on)");
}

void SBC55::setVentValveClose() {
    _outputs |= (1<<OUT_VENTVALVE);
    setOutputs();
    DEBUG_SBC("...Close ventilation valve (Y023 off)");
}

void SBC55::setAirValveOpen() {
    _outputs &= ~(1<<OUT_AIRVALVE);
    setOutputs();
    DEBUG_SBC("...Open air valve (Y024 off)");
}

void SBC55::setAirValveClose() {
    _outputs |= (1<<OUT_AIRVALVE);
    setOutputs();
    DEBUG_SBC("...Close air valve (Y024 off)");
}

void SBC55::setHeaterOn() {
    _outputs &= ~(1<<OUT_HEATER);
    setOutputs();
    DEBUG_SBC("...Heater on");
}

void SBC55::setHeaterOff() {
    _outputs |= (1<<OUT_HEATER);
    setOutputs();
    DEBUG_SBC("...Heater off");
}

void SBC55::setAirBlowerOn() {
    _outputs &= ~(1<<OUT_AIRBLOWER);
    setOutputs();
    DEBUG_SBC("...Air blower on");
}

void SBC55::setAirBlowerOff() {
    _outputs |= (1<<OUT_AIRBLOWER);
    setOutputs();
    DEBUG_SBC("...Air blower off");
}


