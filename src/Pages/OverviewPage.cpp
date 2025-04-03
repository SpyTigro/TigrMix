#include "OverviewPage.h"

OverviewPage::OverviewPage(String name, LiquidCrystal *display, Button *btn, Encoder *enc, VolumeTracker *volumeTrackers[], bool areInput[]) : Page(name, display, btn, enc)
{
    // Copy the pointers from volumeTrackers to the member variable volumes
    for (int i = 0; i < 4; i++)
    {
        volumes[i] = volumeTrackers[i];
        areInputs[i] = areInput[i];
    }
}

Page *OverviewPage::load(){
    display->createChar((byte)0, arrowL);
	display->createChar(1, arrowR);
	display->createChar(2, speaker);
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
        if (selected)
            arrowPos = arrowPos - 1 < 0 ? 4 : arrowPos - 1;
        else
            volumes[arrowPos]->addVolume(2);
    }
    if (enc->pulseLeft)
    {
        if (selected)
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
            y = 0;
            leftFacing = true;
            break;
        case 3:
            x = 10;
            y = 1;
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
    if (isInput)
        byteToWrite = tracker->isMuted() ? 5 : 3;
    else
        byteToWrite = tracker->isMuted() ? 4 : 2;

    String volumeStr = (String)tracker->getVolume();
    String name = tracker->getName();
    String toPrint;
    if (!leftFacing)
    {
        toPrint = volumeStr;
        for (int i = toPrint.length(); i < 4; i++)
        {
            toPrint += " ";
        }
        toPrint += name.charAt(0);

        display->print(toPrint);
        display->write(byteToWrite);
    }
    else
    {
        toPrint = name.charAt(0);
        for (int i = toPrint.length(); i < 4; i++)
        {
            toPrint += " ";
        }
        toPrint += volumeStr;

        display->write(byteToWrite);
        display->print(toPrint);
    }
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
        display->write((byte)0);
    else
        display->write(1);
}