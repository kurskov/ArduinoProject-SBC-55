/*
    Cleaning machine Finnsonic SBC-55

    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
    GitHub: https://github.com/kurskov/ArduinoProject-SBC-55
    Version: 0.1.0

    MIT license
*/

#ifndef _DK_SBC55_h
#define _DK_SBC55_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

class SBC55 {
    public:
        SBC55() {}
        
        // Check condition and position all parts of machine.
        uint8_t init() {
            return 0;
        }

        // 
        // Beacon: white & green
        void afterOn() {
            setVentValveOpen();
            setDoorLockOpen();
            delay(1000);
        }

        //
        // Beacon: white & green
        void standBy() {
            setVentValveOpen();
            setDoorLockOpen();
            delay(1000);
        }

        //
        uint8_t wash(uint16_t sec);

        // 
        uint8_t rinse(uint16_t sec);

        //
        uint8_t airBlast(uint16_t sec);

        // 
        uint8_t drip(uint8_t tank, uint16_t sec);

        //
        uint8_t airBlow(uint16_t sec);

        //
        uint8_t drying(uint16_t sec);

    private:
        void setVentValveOpen() {}
        void setVentValveClose() {}
        void setDoorLockOpen() {}
        void setDoorLockClose() {}
};

#endif // _DK_SBC55_h
