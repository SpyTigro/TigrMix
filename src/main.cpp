// external libraries
#include <Arduino.h>
#include <LiquidCrystal.h>

// my libraries
#include "Pages/Page.h"
#include "Pages/VolumePage.h"
#include "Pages/OverviewPage.h"
#include "util/VolumeTracker.h"
#include "Encoder.h"
#include "Button.h"

//load config
#include "config.h"

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

VolumeTracker volumes[5] = {
	VolumeTracker(VOLUME_NAME_1),
	VolumeTracker(VOLUME_NAME_2),
	VolumeTracker(VOLUME_NAME_3),
	VolumeTracker(VOLUME_NAME_4),
	VolumeTracker(VOLUME_NAME_5),
};
unsigned pageIdx = 0;

void sendVolumeValues();

void setup()
{
	lcd.begin(16, 2);

	Serial.begin(115200);
}

void loop()
{
	enc.tick();
	encBtn.tick();

	if (encBtn.gotDoubleClicked())
		Serial.println("btn got double pressed");
	if (encBtn.gotPressed)
		Serial.println("btn got pressed");
	if (encBtn.gotLongPressed())
		Serial.println("btn got long pressed");

	if (enc.pulseLeft)
		Serial.println("turned left");
	if (enc.pulseRight)
		Serial.println("turned right");

	sendVolumeValues();
}

void sendVolumeValues() // uses deej to change the values on the pc
{
	String builtString = String("");
	size_t amountOfVolumes = sizeof(volumes) / sizeof(volumes[0]);
	for (unsigned i = 0; i < amountOfVolumes; i++)
	{
		builtString += String(volumes[i].getVolume());

		if (i < amountOfVolumes - 1)
		{
			builtString += String("|");
		}
	}

	Serial.println(builtString);
}
