#include "Page.h"

void Page::drawPage()
{
    display->setCursor(0,0);
    display->print("should be overriden");
}