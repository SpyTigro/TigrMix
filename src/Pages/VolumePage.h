#ifndef VolumePage_H
#define VolumePage_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Page.h"
#include "VolumeTracker.h"

class VolumePage : public Page
{
private:
    VolumeTracker pageVolume;
    bool isInput;

public:

    VolumePage(String name, LiquidCrystal *display, uint8_t volume = 50, bool isInput = false);

    void drawPage();

    // VOLUME

    /**
     * @returns current volume
     */
    uint8_t getVolume()
    {
        return pageVolume.getVolume();
    }

    /**
     * @returns if volume is muted
     */
    bool isMuted()
    {
        return pageVolume.isMuted();
    }

    /**
     * increases the displayed volume with the given value with overflow protection
     */
    void addVolume(int value)
    {
        pageVolume.addVolume(value);
    }

    /**
     * VolumeTracker.setVolume(value)
     */
    void setVolume(uint8_t value)
    {
        pageVolume.setVolume(value);
    }

    void toggleMute()
    {
        pageVolume.toggleMute();
    }
    void mute()
    {
        pageVolume.mute();
    }
    void unmute()
    {
        pageVolume.unmute();
    }
};
#endif