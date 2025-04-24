#include "Encoder.h"

Encoder::Encoder(uint8_t RotL, uint8_t RotR) : pin_RotL(RotL), pin_RotR(RotR) {
    pinMode(pin_RotL, INPUT_PULLUP);
    pinMode(pin_RotR, INPUT_PULLUP);
}

void Encoder::tick() {
    pulseLeft = false;
    pulseRight = false;

    bool valueRead_RotL = digitalRead(pin_RotL);
    bool valueRead_RotR = digitalRead(pin_RotR);

    //////////////////////////////////////////////////////////
    /////// Handling of rotary encoder starts here ///////////
    //////////////////////////////////////////////////////////

    byte enc_pos = 0;  // Construct encoder-pos 0-1-2-3-0-1-2-3-0-....
    if (valueRead_RotL == false)
        enc_pos |= (1 << 0);  // Remark: ACTIVE-LOW handled here!
    if (valueRead_RotR == false) enc_pos |= (1 << 1);

    if (enc_pos != prev_enc_pos) {  // Handle when value changed
        if (!enc_rot_busy_Left &&
            !enc_rot_busy_Right) {  // Get initiated direction
            if (enc_pos == 1)
                enc_rot_busy_Left = true;
            else if (enc_pos == 2)
                enc_rot_busy_Right = true;
        }

        if (enc_rot_busy_Left && (enc_pos == 2))
            enc_reached_Right =
                true;  // When turning, check if opposite is reached
        if (enc_rot_busy_Right && (enc_pos == 1)) enc_reached_Left = true;

        if (enc_pos == 0) {  // When turning, wait till back at 0
            if (enc_rot_busy_Left && enc_reached_Right)
                pulseLeft =
                    true;  // If initiated som dir + reached opposite = pulse
            else if (enc_rot_busy_Right && enc_reached_Left)
                pulseRight = true;

            enc_rot_busy_Left = false;  // Clear all flags at 0
            enc_rot_busy_Right = false;
            enc_reached_Left = false;
            enc_reached_Right = false;
        }
    }
    prev_enc_pos = enc_pos;  // Remember state of encoder+button
}