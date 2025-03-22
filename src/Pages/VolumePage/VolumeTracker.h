#ifndef VolumeTracker_H
#define VolumeTracker_H
#include <Arduino.h>

class VolumeTracker {
    private:
        String name;
        uint8_t volume = 50;
        bool muted = false;
    public:
        VolumeTracker(String name, uint8_t volume, bool mute);

        String getName();

        void setName(String name);
        /**
         * @returns current volume
         */
        uint8_t getVolume();

        /**
         * @returns if volume is muted
         */
        bool isMuted();


        /**
         * adds the given value to volume with overflow protection
         */
        void addVolume(uint8_t value);

        /**
         * set volume to given volume, fails if given volume isnt in range of [0, 100]
         */
        void setVolume(uint8_t volume);

        /**
         * switched mute state;
         */
        void toggleMute();

        /**
         * mutes the sound if unmuted before, otherwise does nothing
         */
        void mute();

        /**
         * unmutes the sound if muted before, otherwise does nothing
         */
        void unmute();
};
#endif