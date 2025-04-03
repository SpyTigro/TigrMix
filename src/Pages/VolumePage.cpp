#include "VolumePage.h"

VolumePage::VolumePage(String name, LiquidCrystal *display, Button *btn, Encoder *enc, VolumeTracker *volumeTracker, bool isInput) : Page(name, display, btn, enc),
                                                                                                                                     pageVolume(volumeTracker),
                                                                                                                                     isInput(isInput)
{
}

Page *VolumePage::load()
{
    display->clear();
    selected = false;
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

    if (btn->gotPressed)
        selected = !selected;
    if (btn->gotDoubleClicked())
        pageVolume->toggleMute();
    if (enc->pulseRight)
    {
        if (selected)
            pageVolume->addVolume(2);
    }
    if (enc->pulseLeft)
    {
        if (selected)
            pageVolume->addVolume(-2);
    }

    drawPage();
}

void VolumePage::drawPage()
{
    uint8_t volume = pageVolume->getVolume();
    String name = pageVolume->getName();

    display->setCursor(0, 0);
    display->print("(");
    printVolumeBar(volume, 5);
    display->print(")");

    display->print(" " + rightAllign(name, 7) + " ");
    display->setCursor(2, 1);
    display->print(rightAllign((String)volume, 3));
    display->setCursor(11, 1);
    display->write(2);
    if (pageVolume->isMuted())
        display->write(1);
    else
        display->write((byte)0);
    if (selected)
        display->write(5);
    else
        display->write(4);
    display->write(3);
}

String VolumePage::rightAllign(String str, uint8_t width)
{
    uint8_t len = str.length();
    if (len > width)
        return "";
    String res = "";
    for (int i = len; i < width; i++)
    {
        res += " ";
    }
    res += str;
    return res;
}

void VolumePage::printVolumeBar(uint8_t value, uint8_t width)
{
    uint8_t percentage = value;
    uint8_t squarePercentage = 100 / width;
    uint8_t count = 0;
    while (percentage >= squarePercentage)
    {
        display->write((byte)255);
        percentage -= squarePercentage;
        count++;
    }

    if (squarePercentage / 2 < percentage && percentage < squarePercentage)
        display->write(7);
    else if (0 < percentage && percentage <= squarePercentage / 2)
        display->write(6);
    if(percentage != 0) count++;

    while (count < width)
    {
        display->print(" ");
        count++;
    }
    return;
}