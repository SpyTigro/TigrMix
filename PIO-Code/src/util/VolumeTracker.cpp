#include "VolumeTracker.h"

VolumeTracker::VolumeTracker(String name, uint8_t volume, bool mute) : name(name),
                                                                       volume(volume),
                                                                       muted(mute)
{
}

String VolumeTracker::getName()
{
    return name;
}

void VolumeTracker::setName(String name)
{
    this->name = name;
}

uint8_t VolumeTracker::getVolume()
{
    return volume;
}

bool VolumeTracker::isMuted()
{
    return muted;
}

void VolumeTracker::addVolume(int8_t value)
{
    if ((int8_t)volume + value < 0)
    {
        volume = 0;
        return;
    }
    else if (volume + value > 100)
    {
        volume = 100;
        return;
    }
    volume += value;
    return;
}

void VolumeTracker::setVolume(uint8_t volume)
{
    if (0 > volume && volume > 100)
        return;
    this->volume = volume;
}

void VolumeTracker::mute()
{
    muted = true;
}

void VolumeTracker::unmute()
{
    muted = false;
}

void VolumeTracker::toggleMute()
{
    muted = !muted;
}