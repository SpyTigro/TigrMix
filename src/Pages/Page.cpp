#include "Page.h"

Page::Page(String name, LiquidCrystal *display, Button *btn, Encoder *enc) : name(name),
                                                                             display(display),
                                                                             btn(btn),
                                                                             enc(enc)

{
}