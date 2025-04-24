// external libraries
#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

// my libraries
#include "Button.h"
#include "Encoder.h"
#include "Pages/OverviewPage.h"
#include "Pages/Page.h"
#include "Pages/VolumePage.h"
#include "util/VolumeTracker.h"

// load config
#include "config.h"

// initialize LCD
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 10
#define LCD_D5 9
#define LCD_D6 8
#define LCD_D7 7
LiquidCrystal *lcd =
    new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// initialize encoder
#define ENC_BTN 4
#define ENC_PIN_A 2
#define ENC_PIN_B 3
Encoder *enc = new Encoder(ENC_PIN_A, ENC_PIN_B);
Button *encBtn = new Button(ENC_BTN);

const size_t trackerSize = sizeof(VolumeTracker);

VolumeTracker *volumes[5] = {
    new VolumeTracker(VOLUME_NAME_1), new VolumeTracker(VOLUME_NAME_2),
    new VolumeTracker(VOLUME_NAME_3), new VolumeTracker(VOLUME_NAME_4),
    new VolumeTracker(VOLUME_NAME_5)};

bool areInputs[5] = {VOLUME_1_IS_INPUT, VOLUME_2_IS_INPUT, VOLUME_3_IS_INPUT,
                     VOLUME_4_IS_INPUT, VOLUME_5_IS_INPUT};

Page *pages[PAGE_AMOUNT] = {
    new OverviewPage("Volumes", lcd, encBtn, enc, volumes, areInputs),
    new VolumePage("Mic", lcd, encBtn, enc, volumes[4], areInputs[4]),
    new VolumePage("headset", lcd, encBtn, enc, volumes[3], areInputs[3]),
    new VolumePage("media", lcd, encBtn, enc, volumes[2], areInputs[2]),
    new VolumePage("chat", lcd, encBtn, enc, volumes[1], areInputs[1]),
    new VolumePage("gaming", lcd, encBtn, enc, volumes[0], areInputs[0])};
unsigned pageIdx = 1;  // cant be zero, which is the homepage only accesible by
                       // the action that the active page defined in homePage()
Page *curPage = pages[0]->load();

void sendVolumeValues();

void setup() {
    EEPROM.begin();

    lcd->begin(16, 2);

    Serial.begin(115200);

    if (EEPROM.read(1023) != 135) {
        EEPROM.write(1023, 135);
    } else {
        for (int i = 0; i < VOLUME_AMOUNT; i++) {
            EEPROM.get(i * trackerSize, *volumes[i]);
        }
    }
}

void loop() {
    curPage->tick();
    if (curPage->nextPage()) {
        pageIdx = pageIdx + 1 < PAGE_AMOUNT ? pageIdx + 1 : 1;
        curPage = pages[pageIdx]->load();
    }
    if (curPage->prevPage()) {
        pageIdx = pageIdx - 1 >= 1 ? pageIdx - 1 : PAGE_AMOUNT - 1;
        curPage = pages[pageIdx]->load();
    }
    if (curPage->homePage()) {
        if (curPage == pages[0])
            curPage = pages[pageIdx]->load();
        else
            curPage = pages[0]->load();
    }

    // EEPROM only saving volumetrackers
    for (int i = 0; i < VOLUME_AMOUNT; i++) {
        EEPROM.put(i * trackerSize, *volumes[i]);
    }

    sendVolumeValues();
}

void sendVolumeValues()  // uses deej to change the values on the pc
{
    String builtString = String("");
    for (unsigned i = 0; i < VOLUME_AMOUNT; i++) {
        builtString +=
            volumes[i]->isMuted()
                ? "0"
                : String(int((1023.0 / 100) * volumes[i]->getVolume() + 1));

        if (i < VOLUME_AMOUNT - 1) {
            builtString += String("|");
        }
    }

    Serial.println(builtString);
}
