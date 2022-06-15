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

#define ON 1
#define OFF 0

// Short types names
#define ui8 uint8_t
#define ui16 uint16_t

class SBC55 {
    public:
        SBC55();
        
        // Check condition and position all parts of machine.
        ui8 init();

        // 
        ui8 afterOn();

        //
        ui8 standBy();

        //
        ui8 wash(ui16 sec);

        // 
        ui8 rinse(ui16 sec);

        //
        ui8 airBlast(ui16 sec);

        // 
        ui8 drip(ui8 tank, ui16 sec);

        //
        ui8 airBlow(ui16 sec);

        //
        ui8 drying(ui16 sec);

    private:

        //
        void setDoorLock(ui8 action);

        //
        void setVentilationValve(ui8 action);
};

#endif // _DK_SBC55_h
