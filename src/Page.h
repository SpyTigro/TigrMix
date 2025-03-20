#ifndef Page_H
#define Page_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "VolumeTracker.h"

class Page
{
private:
    String name;
    LiquidCrystal *display;
    VolumeTracker pageVolume;
    bool isInput;

public:
    Page(String name, LiquidCrystal *display, uint8_t volume = 50, bool isInput = false);

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