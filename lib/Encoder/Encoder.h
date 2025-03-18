#ifndef Encoder_h
#define Encoder_h
#include <Arduino.h>

/**
 * Encoder library, poll state of encoder with tick() and read the state with the getters
 * 
 * The pins get set to INPUT_PULLUP so no additional hardware is needed
 */
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
         * or use the built in flags
         */
        byte getPulseDir();

        /**
         * Compare with getPulseDir() to check for CCW rotation
         */
        const static byte CCW = -1;
        /**
         * Compare with getPulseDir() to check if the encoder stayed stationary
         */
        const static byte STATIONARY = 0;
        /**
         * Compare with getPulseDir() to check for CW rotation
         */
        const static byte CW = 1;
};
#endif