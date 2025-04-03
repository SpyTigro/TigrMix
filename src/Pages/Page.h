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
	Page(String name, LiquidCrystal *display, Button *btn, Encoder *enc);
	
    String getName(){
        return name;
    }

    virtual void drawPage() = 0;

    virtual void tick() = 0;
};
#endif