#ifndef Button_h
#define Button_h
#include <Arduino.h>

class Button {
    private:
        byte pin;

        bool state;
        bool prevState;
        unsigned long long lastChangeTime;

        unsigned long long lastDebounceTime;
        byte debounceDelay = 10;

    public:
    /**
     * initializes button pin as INPUT_PULLUP, no extra hardware should be connected
     */
    Button(int pin);

    /**
     * Reads and updates state and timers;
     */
    void tick();

    /**
     * returns btn state
     */
    bool getState();

    /**
     * returns time since btn was pressed in/released in ms
     */
    long getTimer();

    /**
     * sets debounceDelay to custom value, default is 10 ms
     */
    void setDebounceDelay(unsigned int delay);
};
#endif