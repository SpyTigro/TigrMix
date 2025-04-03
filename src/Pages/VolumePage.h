#ifndef VolumePage_H
#define VolumePage_H
#include "Page.h"
#include "../util/VolumeTracker.h"
#include "lcdChar.h"

class VolumePage : public Page
{
private:
    VolumeTracker *pageVolume;
    bool isInput;

    bool selected = false;

public:
    VolumePage(String name, LiquidCrystal *display, Button *btn, Encoder *enc, VolumeTracker *volumeTracker, bool isInput);

    
    Page *load();

    void tick();
        
    void drawPage();
 
    VolumeTracker getPageVolumeTracker()
    {
        return *pageVolume;
    }

    virtual bool nextPage()
    {
        if (!selected && enc->pulseRight)
            return true;
        return false;
    }

    virtual bool prevPage()
    {
        if (!selected && enc->pulseLeft)
            return true;
        return false;
    }

    virtual bool homePage() { return btn->gotLongPressed(); }
};
#endif