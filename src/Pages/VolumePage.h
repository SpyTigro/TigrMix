#ifndef VolumePage_H
#define VolumePage_H
#include "Page.h"
#include "../util/VolumeTracker.h"

class VolumePage : public Page
{
private:
    VolumeTracker *pageVolume;
    bool isInput;

public:

    VolumePage(String name, LiquidCrystal *display,Button *btn, Encoder * enc, VolumeTracker *volumeTracker, bool isInput);

    void drawPage();

    void tick();

    VolumeTracker *getPageVolumeTracker(){
        return pageVolume;
    }
};
#endif