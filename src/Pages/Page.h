#ifndef Page_H
#define Page_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "VolumeTracker.h"

class Page
{
protected:
    String name;
    LiquidCrystal *display;

public:
	Page(String name, LiquidCrystal *display);
	
    String getName(){
        return name;
    }

    virtual void drawPage();
};
#endif