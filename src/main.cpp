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

// load config
#include "lcdChar.h"
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

VolumeTracker *volumes[5] = {new VolumeTracker(VOLUME_NAME_1), new VolumeTracker(VOLUME_NAME_2), new VolumeTracker(VOLUME_NAME_3), new VolumeTracker(VOLUME_NAME_4), new VolumeTracker(VOLUME_NAME_5)};
bool areInputs[5] = {VOLUME_1_IS_INPUT, VOLUME_2_IS_INPUT, VOLUME_3_IS_INPUT, VOLUME_4_IS_INPUT, VOLUME_5_IS_INPUT};

Page *pages[PAGE_AMOUNT] = {new OverviewPage("Volumes", &lcd, &encBtn, &enc, volumes, areInputs),
							new VolumePage("Mic", &lcd, &encBtn, &enc, volumes[4], areInputs[4])};
unsigned pageIdx = 0;
Page *curPage = pages[pageIdx]->load();

void sendVolumeValues();

void setup()
{
	lcd.begin(16, 2);

	Serial.begin(115200);
}

void loop()
{
	curPage->tick();
	if (curPage->nextPage())
	{
		pageIdx = pageIdx + 1 < PAGE_AMOUNT ? pageIdx + 1 : 0;
		curPage = pages[pageIdx]->load();
	}
	if (curPage->prevPage())
	{
		pageIdx = pageIdx - 1 >= 0 ? pageIdx - 1 : PAGE_AMOUNT - 1;
		curPage = pages[pageIdx]->load();
	}

	sendVolumeValues();
}

void sendVolumeValues() // uses deej to change the values on the pc
{
	String builtString = String("");
	for (unsigned i = 0; i < VOLUME_AMOUNT; i++)
	{
		builtString += String(volumes[i]->getVolume());

		if (i < VOLUME_AMOUNT - 1)
		{
			builtString += String("|");
		}
	}

	Serial.println(builtString);
}
