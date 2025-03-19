#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder(int pinA, int pinB) : pinA(pinA),
                                       pinB(pinB),
                                       state(0),
                                       prevState(0),
                                       busyCW(false),
                                       busyCCW(false),
                                       reachedCW(false),
                                       reachedCCW(false),
                                       pulseCW(false),
                                       pulseCCW(false)
{
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
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

int Encoder::getPulseDir()
{
    if (pulseCCW)
    {
        pulseCCW = false;
        return -1;
    }
    if (pulseCW)
    {
        pulseCW = false;
        return 1;
    }
    return 0;
}