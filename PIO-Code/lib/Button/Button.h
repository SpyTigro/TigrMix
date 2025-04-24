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
    bool changed;
    unsigned long lastChangeTime;
    byte debounceDelay = 10;

    unsigned long firstPressTime = 0;
    bool waitingForSecondPress = false;

    bool longPressed;

    bool hasChanged();

    public:

    Button(byte pin);

    void tick();
    
    bool state;
    bool gotPressed;
    bool gotReleased;

    unsigned getTime();

    bool gotDoubleClicked(unsigned time = 250);
    bool gotLongPressed(unsigned time = 3000);

    void setDebounceDelay(unsigned delay);

    const static bool PRESSED = false;
    const static bool RELEASED = true;

};
#endif