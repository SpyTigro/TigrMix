#include "VolumeTracker.h"

VolumeTracker::VolumeTracker(uint8_t volume, bool mute) : volume(volume),
                                                       muted(mute)
{
}

uint8_t VolumeTracker::getVolume()
{
    return volume;
}

bool VolumeTracker::isMuted()
{
    return muted;
}

void VolumeTracker::addVolume(uint8_t value)
{
    if (volume < abs(value))
    {
        volume = 0;
        return;
    }
    volume += value;
    if (volume > 100)
        volume = 100;
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