#include "OverviewPage.h"

OverviewPage::OverviewPage(String name, LiquidCrystal *display, Button *btn, Encoder *enc, VolumeTracker *volumeTrackers[], bool areInput[]) : Page(name, display, btn , enc)
{
     // Copy the pointers from volumeTrackers to the member variable volumes
     for (int i = 0; i < 4; i++)
     {
         volumes[i] = volumeTrackers[i];
         areInputs[i] = areInput[i];
     }
}

void OverviewPage::tick(){
    enc->tick();
    btn->tick();

    drawPage();
}

void OverviewPage::drawPage()
{
    display->print("name");
}