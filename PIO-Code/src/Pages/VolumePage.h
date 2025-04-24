#ifndef VolumePage_H
#define VolumePage_H
#include "../util/VolumeTracker.h"
#include "Page.h"

class VolumePage : public Page {
   private:
    VolumeTracker *pageVolume;
    bool isInput;

    bool selected = false;

    void printVolumeBar(uint8_t value, uint8_t width);
    String rightAllign(String str, uint8_t width);

   public:
    VolumePage(String name, LiquidCrystal *display, Button *btn, Encoder *enc,
               VolumeTracker *volumeTracker, bool isInput);

    Page *load();

    void tick();

    void drawPage();

    VolumeTracker getPageVolumeTracker() { return *pageVolume; }

    virtual bool nextPage() {
        if (!selected && enc->pulseLeft) return true;
        return false;
    }

    virtual bool prevPage() {
        if (!selected && enc->pulseRight) return true;
        return false;
    }

    virtual bool homePage() { return btn->gotLongPressed(); }
};
#endif