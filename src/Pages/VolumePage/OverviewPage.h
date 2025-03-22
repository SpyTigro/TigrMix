#ifndef OverviewPage_H
#define OverviewPage_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "../Page.h"
#include "VolumeTracker.h"

/**
 * this type of page displays 4 volume trackers and makes them quickly accesible
 * but only for muting or changing volume other functions have to be done on the volumes main page
 */
class OverviewPage : public Page
{
private:
    VolumeTracker *volumes[4];
    bool areInputs[4];

public:
    OverviewPage(String name, LiquidCrystal *display, VolumeTracker *volumeTrackers[], bool areInput[]);

    void drawPage();

    void getVolumeTrackers();
};
#endif