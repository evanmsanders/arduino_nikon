/*
 * Nikon IR Remote Trigger Library
 * by Evan M. Sanders
 * based on code from outofjungle (github.com/outofjungle)
 */

#ifndef nikon_h
#define nikon_h

#include "Arduino.h"

class nikon {
    public:
        nikon(int irPin);
        void snap();
    private:
        int _irPin;
        void _pulseOn(int pulseTime);
        void _pulseOff(unsigned long startDelay);
};

#endif
