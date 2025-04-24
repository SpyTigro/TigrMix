#include "Button.h"

Button::Button(byte pin) : pin(pin),
                           changed(false),
                           lastChangeTime(0),
                           state(digitalRead(pin))
{
    pinMode(pin, INPUT_PULLUP);
}

void Button::tick()
{
    bool currentState = digitalRead(pin);

    if (currentState != state && (millis() - lastChangeTime) > debounceDelay)
    {
        lastChangeTime = millis();
        state = currentState;
        changed = true;
    }

    if (hasChanged())
    {
        if (state == PRESSED)
            gotPressed = true;
        else
            gotReleased = false;
    }
    else
    {
        gotPressed = false;
        gotReleased = false;
    }
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

unsigned Button::getTime()
{
    return millis() - lastChangeTime;
}

bool Button::gotDoubleClicked(unsigned time)
{
    // Check for a button press
    if (gotPressed)
    {
        if (waitingForSecondPress && (millis() - firstPressTime <= time))
        {
            waitingForSecondPress = false; // Reset after detecting double-click
            return true;                   // Double-click detected
        }

        // Record the time of the first press and start waiting for the second press
        firstPressTime = millis();
        waitingForSecondPress = true;
    }

    // Reset if the time window expires
    if (waitingForSecondPress && (millis() - firstPressTime > time))
    {
        waitingForSecondPress = false;
    }

    return false;
}

bool Button::gotLongPressed(unsigned time)
{

    if (getTime() >= time && state == PRESSED)
    {
        if (!longPressed)
        {
            longPressed = true;
            return true;
        }
    }
    else if (state == RELEASED)
        longPressed = false;
    return false;
}

void Button::setDebounceDelay(unsigned delay)
{
    debounceDelay = delay;
}