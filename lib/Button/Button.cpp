#include "Button.h"
#include <Arduino.h>

Button::Button(byte pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
    lastChangeTime = 0;
    changed = false;
}

bool Button::read()
{

    if ((lastChangeTime + debounceDelay) > millis()) 
    {

    }

    else if (digitalRead(pin) != state)
    {
        lastChangeTime = millis();
        state = !state;
        changed = true;
    }
    return state;
}

bool Button::gotPressed()
{
    return (read() == PRESSED && hasChanged());
}

bool Button::gotReleased()
{
    return (read() == RELEASED && hasChanged());
}

bool Button::gotChanged()
{
    read();
    return hasChanged();
}

bool Button::hasChanged()
{
    if (changed)
    {
        changed = false;
        return true;
    }
    return false;
}

long Button::getTime()
{
    return millis() - lastChangeTime;
}

bool Button::gotClickedAgainWithin(unsigned time = 250)
{
    if(clickAgainOK && gotPressed())
        return true;
        
    if (getTime() <= time && read() == RELEASED)
        clickAgainOK = true;
    else
        clickAgainOK = false;
    
    return false;
}

bool Button::gotLongPressed(unsigned time = 3000)
{
    if (getTime() >= time && read() == PRESSED)
    {
        return true;
    }
    return false;
}

void Button::setDebounceDelay(unsigned delay)
{
    debounceDelay = delay;
}