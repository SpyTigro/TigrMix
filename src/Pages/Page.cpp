#include "Page.h"

Page::Page(String name, LiquidCrystal *display) : name(name),
													display(display)
{
}

void Page::drawPage()
{
    display->setCursor(0,0);
    display->print("should be overriden");
}