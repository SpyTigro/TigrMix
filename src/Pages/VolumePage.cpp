#include "VolumePage.h"

VolumePage::VolumePage(String name, LiquidCrystal *display, Button *btn, Encoder *enc, VolumeTracker *volumeTracker, bool isInput) : Page(name, display, btn, enc),
                                                                                                                                     pageVolume(volumeTracker),
                                                                                                                                     isInput(isInput)
{
}

Page *VolumePage::load()
{   
    display->clear();
    if (isInput)
    {
        display->createChar((byte)0, micIcon);
        display->createChar(1, micMute);
    }
    else
    {
        display->createChar((byte)0, speakerIcon);
        display->createChar(1, speakerMute);
    }

    display->createChar(2, arrowL);
    display->createChar(3, arrowR);
    display->createChar(4, dotE);
    display->createChar(5, dotF);
    display->createChar(6, filled2W);
    display->createChar(7, filled4W);

    return this;
}

void VolumePage::tick()
{
    enc->tick();
    btn->tick();

    drawPage();
}

void VolumePage::drawPage()
{
    display->print(name);
}