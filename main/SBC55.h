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
        SBC55();
        
        // Check condition and position all parts of machine.
        uint8_t init();
};

#endif // _DK_SBC55_h
