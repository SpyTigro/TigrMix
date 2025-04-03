#ifndef Page_H
#define Page_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Encoder.h"
#include "Button.h"

class Page
{
protected:
    String name;
    LiquidCrystal *display;
    Button *btn;
    Encoder *enc;

public:
    Page(String name, LiquidCrystal *display, Button *btn, Encoder *enc) : name(name),
                                                                           display(display),
                                                                           btn(btn),
                                                                           enc(enc)
    {}

    String getName()
    {
        return name;
    }

    virtual void drawPage() {}

    virtual void tick() {}

    /**
     * this function always returns the 'this' pointer but lets implmentations do things once for setup like setting custom lcd chars
     */
    virtual Page *load(){
        return this;
    }

    virtual bool nextPage() { return false; }

    virtual bool prevPage() { return false; }

    virtual bool homePage() { return false; }
};
#endif