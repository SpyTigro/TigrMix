#ifndef Encoder_h
#define Encoder_h
#include <Arduino.h>

class Encoder {
    private:
        byte pinA, pinB;

        
        bool busyCCW;
        bool busyCW;
        bool reachedCCW;
        bool reachedCW;

        bool pulseCW;
        bool pulseCCW;

        byte state;
        byte prevState;

    public:
        /**
         * Constructor that sets the pinmodes of the given pins for use with encoder
         */
        Encoder(int pinA, int pinB);

        /**
         * updates the encoder state
         */
        void tick();
        
        /**
         * returns enc pulse with Dir as described below
         * CCW = -1 | stationary | CW = 1
         */
        byte getPulseDir();


};
#endif