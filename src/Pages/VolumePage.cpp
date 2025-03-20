#include "VolumePage.h"

VolumePage::VolumePage(String name, LiquidCrystal *display, uint8_t volume, bool isInput) : pageVolume(VolumeTracker(volume, false)),
                                                                                            isInput(isInput)
{
    this->name = name;
    this->display = display;
}

void VolumePage::drawPage()
{
    if (isInput)
    {
        byte micIcon[8] = {B00100, B01110, B01110, B01110, B10101, B11011, B00100, B01110};
        byte micMute[8] = {B00100, B01010, B01010, B01010, B10101, B11011, B00100, B01110};
        display->createChar(0, micIcon);
        display->createChar(1, micMute);
    }
    else
    {
        byte speakerIcon[8] = {B00100, B01110, B11101, B11101, B11101, B11101, B01110, B00100};
        byte speakerMute[8] = {B10100, B01100, B11100, B11100, B11100, B11110, B01110, B00101};
        display->createChar(0, speakerIcon);
        display->createChar(1, speakerMute);
    }
    static byte arrowL[8] = {B00011, B00111, B01110, B11100, B11100, B01110, B00111, B00011};
    static byte arrowR[8] = {B11000, B11100, B01110, B00111, B00111, B01110, B11100, B11000};

    static byte dotE[8] = {B00000, B00000, B00100, B01010, B00100, B00000, B00000, B00000};
    static byte dotF[8] = {B00000, B00000, B00100, B01110, B00100, B00000, B00000, B00000};

    static byte filled2W[8] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000};
    static byte filled4W[8] = {B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110};

    display->createChar(2, arrowL);
    display->createChar(3, arrowR);
    display->createChar(4, dotE);
    display->createChar(5, dotF);
    display->createChar(6, filled2W);
    display->createChar(7, filled4W);
}