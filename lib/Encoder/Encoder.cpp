#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder(int pinA, int pinB)
{
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    state = 0;
    prevState = 0;
}

void Encoder::tick()
{
    bool A_State = digitalRead(pinA);
    bool B_State = digitalRead(pinB);

    state = (A_State << 1) | B_State;

    if (state != prevState)
    {
        if (!busyCCW && !busyCW)
        {
            if (state == 1)
                busyCCW = true;
            else if (state == 2)
                busyCW = true;
        }

        if (busyCW && (state == 1))
            reachedCW = true;
        if (busyCCW && (state == 2))
            reachedCCW = true;
        if (state == 0)
        {
            if (busyCW && reachedCW)
                pulseCW = true;
            if (busyCCW && reachedCCW)
                pulseCCW = true;

            busyCW = false;
            busyCCW = false;
            reachedCW = false;
            reachedCCW = false;
        }
    }
    prevState = state;
}

byte Encoder::getPulseDir(){
    if(pulseCCW)
        return -1;
    if(pulseCW)
        return 1;
    return 0;
}