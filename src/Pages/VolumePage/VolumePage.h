#ifndef VolumePage_H
#define VolumePage_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "../Page.h"
#include "VolumeTracker.h"

class VolumePage : public Page
{
private:
    VolumeTracker *pageVolume;
    bool isInput;

public:

    VolumePage(String name, LiquidCrystal *display, uint8_t volume = 50, bool isInput = false);

    void drawPage();

    VolumeTracker *getPageVolumeTracker(){
        return pageVolume;
    }
};
#endif