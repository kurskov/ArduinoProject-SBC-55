/*
    See SBC55.h for all information.

    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
*/

#include "SBC55.h"

// Constructor

SBC55::SBC55() {

}


// Machine initialization

ui8 SBC55::init() {
    return 0;
}


// Base functions

ui8 SBC55::afterOn() {
    setVentilationValve(ON);
    setDoorLock(OFF);

    return 0;
}

ui8 SBC55::standBy() {
    setVentilationValve(ON);
    setDoorLock(OFF);

    return 0;
}


// Drivers functions

void SBC55::setDoorLock(ui8 status) {

}

void SBC55::setVentilationValve(ui8 status) {

}