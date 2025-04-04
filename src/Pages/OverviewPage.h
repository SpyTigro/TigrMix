#ifndef OverviewPage_H
#define OverviewPage_H
#include "Page.h"
#include "../util/VolumeTracker.h"

/**
 * this type of page displays 4 volume trackers and makes them quickly accesible
 * but only for muting or changing volume other functions have to be done on the volumes main page
 */
class OverviewPage : public Page
{
private:
    VolumeTracker *volumes[4];
    bool areInputs[4];

    //extra lcd functions
    void volChangePrint(VolumeTracker *tracker, bool isInput, byte x, byte y, bool leftFacing);

    //arrowPrinter variables
    byte arrowPos = 0;
    bool selected = false;
    byte prevArrowPos = 0;
    int arrowPosX = 6; 
    int arrowPosY = 0;
    void arrowPrinter(bool arrowLeft);

    String rightAllign(String str, uint8_t width);
    String leftAllign(String str, uint8_t width);
public:
    OverviewPage(String name, LiquidCrystal *display, Button *btn, Encoder *enc, VolumeTracker *volumeTrackers[], bool areInput[]);

    Page *load();

    void tick();

    void drawPage();

    VolumeTracker **getVolumeTrackers() { 
        return volumes;
    }

    bool homePage() { return btn->gotLongPressed(); }
};
#endif