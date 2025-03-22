#include "OverviewPage.h"

OverviewPage::OverviewPage(String name, LiquidCrystal *display, VolumeTracker *volumeTrackers[4], bool areInput[4]) : Page(name, display),
                                                                                                                    volumes(volumeTrackers),
                                                                                                                    areInputs(areInput)
{
}