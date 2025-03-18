#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Encoder.h"
#include "Button.h"

// initialize LCD
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 10
#define LCD_D5 9
#define LCD_D6 8
#define LCD_D7 7
LiquidCrystal lcd = LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#define ENC_BTN 4
#define ENC_PIN_A 2
#define ENC_PIN_B 3
Encoder enc = Encoder(ENC_PIN_A, ENC_PIN_B);
Button encBtn = Button(ENC_BTN);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  enc.tick();
  enc.CW;
}
