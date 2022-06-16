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

/* DEBUG_SBC MODE */
#define DEBUG_SBC_ON 

#ifdef DEBUG_SBC_ON
  #define DEBUG_SBC(x) Serial.println(x)
#else
  #define DEBUG_SBC(x)
#endif

class SBC55 {
    public:
        SBC55() {
            #ifdef DEBUG_SBC_ON
                Serial.begin(9600);
            #endif
        }
        
        // Check condition and position all parts of machine.
        uint8_t init() {
            DEBUG_SBC("\n> Check condition and position all parts of machine");
            setDoorLockClose();
            setAirValveClose();
            setVentValveOpen();
            delay(1000);
            setDoorLockOpen();
            
            return 0;
        }

        // 
        // Beacon: white & green
        void afterOn() {
            DEBUG_SBC("\n> After on");
            setVentValveOpen();
            setDoorLockOpen();
            delay(1000);
        }

        //
        // Beacon: white & green
        void standBy() {
            DEBUG_SBC("\n> Stand by");
            setVentValveOpen();
            setDoorLockOpen();
            delay(1000);
        }

        //
        uint8_t wash(uint16_t sec);

        // 
        uint8_t rinse(uint16_t sec);

        // 
        // Beacon: green
        uint8_t airBlast(uint16_t sec) {
            DEBUG_SBC("\n> Air blast");
            setDoorLockClose();
            setAirValveOpen();
            delay(sec * 1000);
            setAirValveClose();
            delay(1000);
        }

        // 
        uint8_t drip(uint8_t tank, uint16_t sec);

        //
        // Beacon: green
        uint8_t airBlow(uint16_t sec) {
            DEBUG_SBC("\n> Air blow");
            setDoorLockClose();
            setAirValveOpen();
            delay(sec * 1000);
            setAirValveClose();
            delay(1000);
        }

        //
        uint8_t drying(uint16_t sec);

    private:
        
        /* Safety door lock */
        
        // Open safety door lock
        void setDoorLockOpen() {
            DEBUG_SBC("...Open safety door lock");
        }
        
        // Close safety door lock
        void setDoorLockClose() {
            DEBUG_SBC("...Close safety door lock");
        }

        
        /* Ventilation (exhaust) */
        
        // Open ventilation valve (Y023)
        void setVentValveOpen() {
            DEBUG_SBC("...Open ventilation valve (Y023 on)");
        }
        
        // Close ventilation valve (Y023)
        void setVentValveClose() {
            DEBUG_SBC("...Close ventilation valve (Y023 off)");
        }
        
        
        /* Spray tubing */
        
        // Open air valve (Y024)
        void setAirValveOpen() {
            DEBUG_SBC("...Open air valve (Y024 on)");
        }

        // Close air valve (Y024)
        void setAirValveClose() {
            DEBUG_SBC("...Close air valve (Y024 off)");
        }

        
        /*  */
};

#endif // _DK_SBC55_h

// autocreate
extern SBC55 SBC;
