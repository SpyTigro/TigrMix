#ifndef CUSTOM_LCDCHARS
#define CUSTOM_LCD_CHARS
#include <Arduino.h>

byte speakerIcon[] = {
    B00100,
    B01110,
    B11101,
    B11101,
    B11101,
    B11101,
    B01110,
    B00100};

byte micIcon[] = {
    B00100,
    B01110,
    B01110,
    B01110,
    B10101,
    B11011,
    B00100,
    B01110};

byte arrowL[] = {
    B00011,
    B00111,
    B01110,
    B11100,
    B11100,
    B01110,
    B00111,
    B00011};

byte arrowR[] = {
    B11000,
    B11100,
    B01110,
    B00111,
    B00111,
    B01110,
    B11100,
    B11000};

byte speakerMute[] = {
    B10100,
    B01100,
    B11100,
    B11100,
    B11100,
    B11110,
    B01110,
    B00101};
byte micMute[] = {
    B00100,
    B01010,
    B01010,
    B01010,
    B10101,
    B11011,
    B00100,
    B01110};

byte dotE[] = {
    B00000,
    B00000,
    B00100,
    B01010,
    B00100,
    B00000,
    B00000,
    B00000};

byte dotF[] = {
    B00000,
    B00000,
    B00100,
    B01110,
    B00100,
    B00000,
    B00000,
    B00000};

byte filled2W[] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000};

byte filled4W[] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110};

#endif