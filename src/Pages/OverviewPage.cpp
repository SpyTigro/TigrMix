#include "OverviewPage.h"

OverviewPage::OverviewPage(String name, LiquidCrystal *display, Button *btn, Encoder *enc, VolumeTracker *volumeTrackers[], bool areInput[]) : Page(name, display, btn, enc)
{
    // Copy the pointers from volumeTrackers to the member variable volumes
    for (int i = 0; i < 4; i++)
    {
        volumes[i] = volumeTrackers[i];
        areInputs[i] = areInput[i];
    }
    //swap 2 and 3 so it makes sense that volume 4 is the BR but so the arrow goes in a circle
    VolumeTracker *temp = volumes[2];
    volumes[2] = volumes[3];
    volumes[3] = temp;
}

Page *OverviewPage::load(){
    display->clear();
    selected = false;
    display->createChar((byte)0, arrowL);
	display->createChar(1, arrowR);
	display->createChar(2, speakerIcon);
	display->createChar(3, micIcon);
	display->createChar(4, speakerMute);
	display->createChar(5, micMute);

    return this;
}

void OverviewPage::tick()
{
    enc->tick();
    btn->tick();

    if (btn->gotPressed)
        selected = !selected;
    if (btn->gotDoubleClicked())
        volumes[arrowPos]->toggleMute();
    if (enc->pulseRight)
    {
        if (!selected)
            arrowPos = arrowPos - 1 < 0 ? 4 : arrowPos - 1;
        else
            volumes[arrowPos]->addVolume(2);
    }
    if (enc->pulseLeft)
    {
        if (!selected)
        arrowPos = arrowPos + 1 < 4 ? arrowPos + 1 : 0;
        else
            volumes[arrowPos]->addVolume(-2);
    }

    drawPage();
}

void OverviewPage::drawPage()
{
    for (int i = 0; i < 4; i++)
    {
        int x, y;
        bool leftFacing = false;
        switch (i)
        {
        case 0:
            x = 0;
            y = 0;
            leftFacing = false;
            break;
        case 1:
            x = 0;
            y = 1;
            leftFacing = false;
            break;
        case 2:
            x = 10;
            y = 1;
            leftFacing = true;
            break;
        case 3:
            x = 10;
            y = 0;
            leftFacing = true;
            break;
        }
        volChangePrint(volumes[i], areInputs[i], x, y, leftFacing);
        if (arrowPos == i)
            arrowPrinter(selected xor leftFacing);
    }
}

void OverviewPage::volChangePrint(VolumeTracker *tracker, bool isInput, byte x, byte y, bool leftFacing)
{

    display->setCursor(x, y);
    byte byteToWrite;
    byte volume = tracker->getVolume();
    bool muted = tracker->isMuted();
    if (isInput)
        byteToWrite = muted || volume == 0 ? 5 : 3;
    else
        byteToWrite = muted || volume == 0 ? 4 : 2;

    String volumeStr = (String)volume;
    String name = tracker->getName();
    String toPrint = "";
    if (!leftFacing)
    {
        display->write(byteToWrite);
        display->print(name.charAt(0));
        display->print(rightAllign(volumeStr, 4));
    }
    else
    {
        display->print(leftAllign(volumeStr, 4));
        display->print(name.charAt(0));
        display->write(byteToWrite);
    }
}

String OverviewPage::rightAllign(String str, uint8_t width){
    uint8_t len = str.length();
    if(len > width) return "";
    String res = "";
        for (int i = len; i < width; i++)
        {
            res += " ";
        }
    res += str;
    return res;
}

String OverviewPage::leftAllign(String str, uint8_t width){
    uint8_t len = str.length();
    if(len > width) return "";
    String res = str;
        for (int i = len; i < width; i++)
        {
            res += " ";
        }
    return res;
}

void OverviewPage::arrowPrinter(bool arrowLeft)
{
    if (prevArrowPos != arrowPos)
    {
        display->setCursor(arrowPosX, arrowPosY);
        display->print(" ");
        prevArrowPos = arrowPos;
    }
    switch (arrowPos)
    {
    case 0:
        arrowPosX = 6;
        arrowPosY = 0;
        break;
    case 1:
        arrowPosX = 6;
        arrowPosY = 1;
        break;
    case 2:
        arrowPosX = 9;
        arrowPosY = 1;
        break;
    case 3:
        arrowPosX = 9;
        arrowPosY = 0;
        break;
    }

    display->setCursor(arrowPosX, arrowPosY);
    if (arrowLeft)
        display->write(1);
    else
        display->write((byte)0);
}