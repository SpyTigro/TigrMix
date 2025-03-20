#include "Page.h"

Page::Page(String name, LiquidCrystal *display, uint8_t volume, bool input) : name(name),
                                                                              display(display),
                                                                              pageVolume(VolumeTracker(volume, false)),
                                                                              input(input)
{
}