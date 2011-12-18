/*
 * Nikon Intervalometer Library
 * by Evan M. Sanders
 * based on code from outofjungle (github.com/outofjungle)
 */

#include "Arduino.h"
#include "nikon.h"

nikon::nikon(int irPin) {
    _irPin = irPin;
    // initialise our IR pin
    pinMode(_irPin, OUTPUT);
}

void nikon::_pulseOn(int pulseTime) {
    // create the microseconds to pulse for
    unsigned long endPulse = micros() + pulseTime;        
    while( micros() < endPulse) {
        // turn IR on
        digitalWrite(_irPin, HIGH);                       
        // half the clock cycle for 38Khz (26.32×10-6s) - e.g. the 'on' part of our wave
        delayMicroseconds(13);                              
        // turn IR off
        digitalWrite(_irPin, LOW);                        
        // delay for the other half of the cycle to generate wave/ oscillation
        delayMicroseconds(13);                              
    }
}

void nikon::_pulseOff(unsigned long startDelay) {
    unsigned long endDelay = micros() + startDelay;
    while(micros() < endDelay);
}

void nikon::snap() {
    // loop the signal twice
    for (int i=0; i < 2; i++) {
        // pulse for 2000 uS (Microseconds)
        this->_pulseOn(2000);                                      
        // turn pulse off for 27850 us
        this->_pulseOff(27850);                                    
        // and so on
        this->_pulseOn(390);                                       
        this->_pulseOff(1580);
        this->_pulseOn(410);
        this->_pulseOff(3580);
        this->_pulseOn(400);
        this->_pulseOff(63200);
    }    
}
