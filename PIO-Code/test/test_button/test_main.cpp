#include <unity.h>
#include "Button.h"

// Mocked millis() counter
static unsigned long fakeMillis = 0;
unsigned long millis() { return fakeMillis; }

// Simulate time passing
void advanceTime(unsigned long ms) {
    fakeMillis += ms;
}

// Mock digitalRead() in test
bool fakeButtonState = false;
int digitalRead(int pin) { return fakeButtonState ? LOW : HIGH; }  // INPUT_PULLUP logic

void test_button_press() {
    Button button(2);
    
    fakeButtonState = false;  // Not pressed
    TEST_ASSERT_TRUE(button.read() == button.RELEASED);

    advanceTime(10);
    fakeButtonState = true;  // Pressed
    TEST_ASSERT_TRUE(button.read() == button.PRESSED);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_button_press);
    UNITY_END();
}

void loop() {}
