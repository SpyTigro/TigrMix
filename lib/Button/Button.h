#ifndef Button_h
#define Button_h
#include <Arduino.h>


/**
 * Simple btn library for arduino
 * 
 * Updates whenever a check is called, so no need to poll the button or use interupts
 * used with INPUT_PULLUP so just connect the button to the given Digital pin and GND of the arduino
 */
class Button {
    private:
        byte pin;

        bool state;
        bool changed;
        unsigned long lastChangeTime;
        byte debounceDelay = 10;
        
        /**
         * @returns if the button has Changed without reading
         */
        bool hasChanged(); 

    public:
        /**
         * initializes button pin as INPUT_PULLUP, no extra hardware should be connected
         * so again just connect the button to the given Digital pin and GND of the arduino
         */
        Button(byte pin);

        /**
         * Reads and updates state and timers
         * @returns state
         */
        bool read();

        /**
         * @returns if the button got pressed in recently
         */
        bool gotPressed();

        /**
         * @returns if the button got released recently
         */
        bool gotReleased(); 

        /**
         * @returns if the button was changed states
         */
        bool gotChanged();

        /**
         * @returns time for how long the btn was pressed last time
         */
        long getTime();

        /**
         * @param unsigned time (optional) time between clicks in ms
         * @returns true if the button got clicked again within the time frame(default 250ms)
         */
        bool gotDoubleClicked(unsigned time);

        /**
         * @param unsigned int time (optional) time to hold the button in ms
         * @returns true if the button has been pressed for given time (default 3 sec)
         */
        bool gotLongPressed(unsigned time);

        /**
         * sets debounceDelay to custom value, default is 10 ms
         * @param unsigned delay
         */
        void setDebounceDelay(unsigned delay);

        /**
         * Compare with read() to check if button is closed
         */
        const static bool PRESSED = false;
        /**
         * Compare with read() to check if button is open
         */
        const static bool RELEASED = true; 
};
#endif