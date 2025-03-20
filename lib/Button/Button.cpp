#include "Button.h"

Button::Button(byte pin) : pin(pin),
                           state(digitalRead(pin)),
                           lastChangeTime(0),
                           changed(false)
{
    pinMode(pin, INPUT_PULLUP);
}

bool Button::read()
{
    bool currentState = digitalRead(pin);

    if (currentState != state && (millis() - lastChangeTime) > debounceDelay)
    {
        lastChangeTime = millis();
        state = currentState;
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

bool Button::gotDoubleClicked(unsigned time)
{
    if (gotPressed())
    {
        if (waitingForSecondPress && (millis() - firstPressTime <= time))
        {
            waitingForSecondPress = false;
            return true;
        }

        firstPressTime = millis();
        waitingForSecondPress = true;
    }

    if (waitingForSecondPress && (millis() - firstPressTime > time))
    {
        waitingForSecondPress = false;
    }

    return false;
}

bool Button::gotLongPressed(unsigned time)
{
    return (getTime() >= time && state == PRESSED);
}

void Button::setDebounceDelay(unsigned delay)
{
    debounceDelay = delay;
}