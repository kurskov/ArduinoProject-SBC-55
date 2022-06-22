/*
    Cleaning machine Finnsonic SBC-55

    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
    GitHub: https://github.com/kurskov/ArduinoProject-SBC-55
 
    MIT license
*/

#ifndef _DK_SBC55_h
#define _DK_SBC55_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif


#define DEBUG_ON
/* DEBUG_SBC MODE */
#ifdef DEBUG_ON
  #define DEBUG_SBC(x) Serial.println(x)
#else
  #define DEBUG_SBC(x)
#endif

// Relay module outputs
#define OUT_DOORLOCK 1
#define OUT_VENTVALVE 2
#define OUT_AIRVALVE 3
#define OUT_HEATER 4
#define OUT_AIRBLOWER 5 

class SBC55 {
    public:
        SBC55(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin) {
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
        
        // Check condition and position all parts of machine.
        uint8_t init() {
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

        // 
        // Beacon: green
        void afterOn() {
            DEBUG_SBC("\n> After on");
            setVentValveOpen();
            delay(1000);
            setDoorLockOpen();
            delay(1000);
        }

        //
        // Beacon: green
        void standBy() {
            DEBUG_SBC("\n> Stand by");
            setVentValveOpen();
            delay(1000);
            setDoorLockOpen();
            delay(1000);
        }

        //
        uint8_t wash(uint16_t sec);

        // 
        uint8_t rinse(uint16_t sec);

        // 
        // Beacon: green & white
        uint8_t airBlast(uint16_t sec) {
            DEBUG_SBC("\n> Air blast");
            setDoorLockClose();
            delay(1000);
            setAirValveOpen();
            delay(sec * 1000);
            setAirValveClose();
            delay(1000);
        }

        // 
        uint8_t drip(uint8_t tank, uint16_t sec);

        //
        // Beacon: green & white
        uint8_t airBlow(uint16_t sec) {
            DEBUG_SBC("\n> Air blow");
            setDoorLockClose();
            delay(1000);
            setAirValveOpen();
            delay(sec * 1000);
            setAirValveClose();
            delay(1000);
        }

        // Beacon: green & white
        uint8_t drying(uint16_t sec) {
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

    private:

        // Arduino pins for connecting to the relay module 
        // through the 74HC595 cascade.
        uint8_t _latchPin;  // ST_CP pin of 74HC595
        uint8_t _clockPin;  // SH_CP pin of 74HC595
        uint8_t _dataPin;   // DS pin of 74HC595
        
        uint16_t _outputs = 0; // outputs state

        // Send outputs state to the relay module.
        // First - high bit, second - low bit.
        void setOutputs() {
            digitalWrite(_latchPin, LOW);
            shiftOut(_dataPin, _clockPin, MSBFIRST, (_outputs >> 8));
            shiftOut(_dataPin, _clockPin, MSBFIRST, _outputs);
            digitalWrite(_latchPin, HIGH);
        }
        
        /* Safety door lock */
        
        // Open safety door lock
        void setDoorLockOpen() {
            _outputs &= ~(1<<OUT_DOORLOCK);
            setOutputs();
            DEBUG_SBC("...Open safety door lock");
        }
        
        // Close safety door lock
        void setDoorLockClose() {
            _outputs |= (1<<OUT_DOORLOCK);
            setOutputs();
            DEBUG_SBC("...Close safety door lock");
        }

        
        /* Ventilation (exhaust) */
        
        // Open ventilation valve (Y023)
        void setVentValveOpen() {
            _outputs |= (1<<OUT_VENTVALVE);
            setOutputs();
            DEBUG_SBC("...Open ventilation valve (Y023 on)");
        }
        
        // Close ventilation valve (Y023)
        void setVentValveClose() {
            _outputs &= ~(1<<OUT_VENTVALVE);
            setOutputs();
            DEBUG_SBC("...Close ventilation valve (Y023 off)");
        }
        
        
        /* Spray tubing */
        
        // Open air valve (Y024)
        void setAirValveOpen() {
            _outputs |= (1<<OUT_AIRVALVE);
            setOutputs();
            DEBUG_SBC("...Open air valve (Y024 off)");
        }

        // Close air valve (Y024)
        void setAirValveClose() {
            _outputs &= ~(1<<OUT_AIRVALVE);
            setOutputs();
            DEBUG_SBC("...Close air valve (Y024 off)");
        }

        
        /* Hot air blow */

        // Heater on
        void setHeaterOn() {
            _outputs |= (1<<OUT_HEATER);
            setOutputs();
            DEBUG_SBC("...Heater on");
        }

        // Heater off
        void setHeaterOff() {
            _outputs &= ~(1<<OUT_HEATER);
            setOutputs();
            DEBUG_SBC("...Heater off");
        }

        // Air blower on
        void setAirBlowerOn() {
            _outputs |= (1<<OUT_AIRBLOWER);
            setOutputs();
            DEBUG_SBC("...Air blower on");
        }

        // Air blower off
        void setAirBlowerOff() {
            _outputs &= ~(1<<OUT_AIRBLOWER);
            setOutputs();
            DEBUG_SBC("...Air blower off");
        }
};

#endif // _DK_SBC55_h
