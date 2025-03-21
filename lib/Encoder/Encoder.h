#ifndef Encoder_h
#define Encoder_h
#include <Arduino.h>

class Encoder
{
public:
    //Setup
    Encoder(uint8_t RotL, uint8_t RotR);
    //encoder rotations
    bool enc_Pulse_Left = false;
    bool enc_Pulse_Right = false;
    // main loop
    void tick();

private:
    byte pin_RotL;
    byte pin_RotR;
    // enc rot variables
    byte prev_enc_pos = 0; // Encoder-states to remember
    bool enc_rot_busy_Left = false;
    bool enc_rot_busy_Right = false;
    bool enc_reached_Left = false;
    bool enc_reached_Right = false;
};
#endif