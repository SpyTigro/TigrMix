#include "Button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
    lastChangeTime = 0;
}

bool Button::read()
{

    if ((lastChangeTime + debounceDelay) > millis())
    {
    }

    if (digitalRead(pin) != state)
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

bool Button::doubleClicked(unsigned time = 250)
{
    if (getTime() <= time && state == RELEASED)
    {
        return gotPressed();
    }
    return false;
}

bool Button::longPressed(unsigned time = 3000)
{
    if (getTime() >= time && state == PRESSED)
    {
        return true;
    }
    return false;
}

void Button::setDebounceDelay(unsigned delay)
{
    debounceDelay = delay;
}