#include "OverviewPage.h"

OverviewPage::OverviewPage(String name, LiquidCrystal *display, VolumeTracker *volumeTrackers[4], bool areInput[4]) : Page(name, display)
{
     // Copy the pointers from volumeTrackers to the member variable volumes
     for (int i = 0; i < 4; i++)
     {
         volumes[i] = volumeTrackers[i];
         areInputs[i] = areInput[i];
     }
}