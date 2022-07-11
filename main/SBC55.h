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

//#define DEBUG_ON

// Relay module outputs
#define OUT_DOORLOCK 1
#define OUT_VENTVALVE 2
#define OUT_AIRVALVE 3
#define OUT_HEATER 4
#define OUT_AIRBLOWER 5 

class SBC55 {
    public:
        SBC55(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin);
        
        // Check condition and position all parts of machine.
        // Return 0 if check is Ok.
        uint8_t init();

        // 
        // Beacon: green
        void afterOn();

        //
        // Beacon: green
        void standBy();

        //
        uint8_t wash(uint16_t sec);

        // 
        uint8_t rinse(uint16_t sec);

        // 
        // Beacon: green & white
        uint8_t airBlast(uint16_t sec);

        // 
        uint8_t drip(uint8_t tank, uint16_t sec);

        //
        // Beacon: green & white
        uint8_t airBlow(uint16_t sec);

        // Beacon: green & white
        uint8_t drying(uint16_t sec);

    private:

        // Arduino pins for connecting to the relay module 
        // through the 74HC595 cascade.
        uint8_t _latchPin;  // ST_CP pin of 74HC595
        uint8_t _clockPin;  // SH_CP pin of 74HC595
        uint8_t _dataPin;   // DS pin of 74HC595
        
        uint16_t _outputs = 0xFFFF; // outputs state

        // Send outputs state to the relay module.
        // First - high bit, second - low bit.
        void setOutputs();
        
        /* Safety door lock */
        
        // Open safety door lock
        void setDoorLockOpen();
        
        // Close safety door lock
        void setDoorLockClose();

        
        /* Ventilation (exhaust) */
        
        // Open ventilation valve (Y023)
        void setVentValveOpen();
        
        // Close ventilation valve (Y023)
        void setVentValveClose();
        
        
        /* Spray tubing */
        
        // Open air valve (Y024)
        void setAirValveOpen();

        // Close air valve (Y024)
        void setAirValveClose();

        
        /* Hot air blow */

        // Heater on
        void setHeaterOn();

        // Heater off
        void setHeaterOff();

        // Air blower on
        void setAirBlowerOn();

        // Air blower off
        void setAirBlowerOff();
};

#endif // _DK_SBC55_h
