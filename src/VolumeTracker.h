#ifndef VolumeTracker_H
#define VolumeTracker_H
#include <Arduino.h>

class VolumeTracker {
    private:
        int volume = 50;
        bool muted = false;
    public:
        int getVolume();
        bool isMuted();
};
#endif