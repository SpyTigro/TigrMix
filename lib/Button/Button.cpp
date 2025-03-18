#include "Button.h"

#ifdef UNIT_TEST
static long fakeMillis = 0;
long millis() { return fakeMillis; }
static int fakeButtonState = HIGH;
int digitalRead(int pin) { return fakeButtonState; }
#endif

Button::Button(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
    lastChangeTime = 0;
    changed = false;
}

bool Button::read() {
    bool currentState = digitalRead(pin);

    if (currentState != state && (millis() - lastChangeTime) > debounceDelay) {
        lastChangeTime = millis();
        state = currentState;
        changed = true;  // Mark change, reset only when explicitly checked
    }

    return state;
}

bool Button::gotPressed() {
    return (read() == PRESSED && hasChanged());
}

bool Button::gotReleased() {
    return (read() == RELEASED && hasChanged());
}

bool Button::gotChanged() {
    read();
    return hasChanged();
}

bool Button::hasChanged() {
    if (changed) {
        changed = false;  // Reset only after being checked
        return true;
    }
    return false;
}

long Button::getTime() {
    return millis() - lastChangeTime;
}

bool Button::doubleClicked(unsigned time) {
    static long firstPressTime = 0;
    static bool waitingForSecondPress = false;

    if (gotPressed()) {  
        if (waitingForSecondPress && (millis() - firstPressTime <= time)) {  
            waitingForSecondPress = false;  // Reset after detecting a double click  
            return true;  // Double-click detected  
        }  

        // First press detected  
        firstPressTime = millis();
        waitingForSecondPress = true;
    }

    // Reset if time expires before the second press  
    if (waitingForSecondPress && (millis() - firstPressTime > time)) {  
        waitingForSecondPress = false;
    }

    return false;  
}

bool Button::longPressed(unsigned time) {
    return (getTime() >= time && state == PRESSED);
}

void Button::setDebounceDelay(unsigned delay) {
    debounceDelay = delay;
}