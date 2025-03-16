#include "Button.h"
#include <Arduino.h>

Button::Button(int pin){
    pinMode(pin, INPUT_PULLUP);
    state = false;
    prevState = false;
    lastChangeTime = 0;
}

void Button::tick() {
    state = digitalRead(pin);

    if(state != prevState){
        lastDebounceTime = millis();
    }
    if((millis() - lastDebounceTime) > debounceDelay){
        lastChangeTime = millis();
    }
    prevState = state;
}

bool Button::getState() {
    return state;
}

long Button::getTimer() {
    return millis() - lastChangeTime;
}

void Button::setDebounceDelay(unsigned int delay){
    debounceDelay = delay;
}