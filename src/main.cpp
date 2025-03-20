// external libraries
#include <Arduino.h>
#include <LiquidCrystal.h>

// my libraries
#include "Page.h"
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

// initialize encoder
#define ENC_BTN 4
#define ENC_PIN_A 2
#define ENC_PIN_B 3
Encoder enc = Encoder(ENC_PIN_A, ENC_PIN_B);
Button encBtn = Button(ENC_BTN);

Page pages[];
unsigned pageIdx = 0;

void setup()
{
	lcd.begin(16, 2);

	Serial.begin(115200);

	
}

void loop()
{
	enc.tick();

	if (encBtn.gotPressed())
		Serial.println("btn got pressed");
	if (encBtn.gotDoubleClicked())
		Serial.println("btn got double pressed");
	if (encBtn.gotLongPressed())
		Serial.println("btn got double pressed");

	if (enc.getPulseDir() == enc.CCW)
		Serial.println("turned CCW");
	if (enc.getPulseDir() == enc.CW)
		Serial.println("turned CW");
}
