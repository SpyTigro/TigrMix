#ifdef ARDUINO
#include <Arduino.h>
#else
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;
#endif

#include <unity.h>
#include "Button.h"

// Namespace to avoid conflicts with Arduino millis()
#ifndef ARDUINO
namespace FakeTime {
    static long fakeMillis = 0;

    long millis() {
        return fakeMillis;
    }

    void delay(int ms) {
        fakeMillis += ms;
    }
}
using namespace FakeTime;
#endif

// Mocked Button class for testing
class TestButton : public Button {
public:
    TestButton(int pin) : Button(pin) {}

    bool simulatedState = RELEASED;

    int digitalRead(int pin) override {
        return simulatedState;
    }

    void simulatePress() {
        simulatedState = PRESSED;
    }

    void simulateRelease() {
        simulatedState = RELEASED;
    }
};

// Test button
TestButton button(2);

// Test: Initial state should be RELEASED
void test_initial_state() {
    TEST_ASSERT_EQUAL(button.RELEASED, button.read());
}

// Test: Press detection
void test_press() {
    fakeMillis = 0; // Reset time
    button.read();  // Initial read

    button.simulatePress();  // Simulate button press
    delay(51);  // Wait past debounce time
    button.read(); 

    TEST_ASSERT_TRUE(button.gotPressed());
}

// Test: Release detection
void test_release() {
    button.simulatePress();
    delay(100);
    button.read();

    button.simulateRelease(); // Simulate button release
    delay(51);
    button.read();

    TEST_ASSERT_TRUE(button.gotReleased());
}

// Test: Double Click Detection
void test_double_click() {
    button.simulatePress();
    delay(100); // First press
    button.read();

    button.simulateRelease();
    delay(200); // Release and second press
    button.read();

    button.simulatePress();
    delay(50);
    button.read();

    TEST_ASSERT_TRUE(button.gotDoubleClicked(250)); // Should detect double click
}

// Test: Long Press Detection
void test_long_press() {
    button.simulatePress();
    delay(3100); // Hold past 3s
    button.read();

    TEST_ASSERT_TRUE(button.gotLongPressed(3000)); // Should detect long press
}

// Setup tests
void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_initial_state);
    RUN_TEST(test_press);
    RUN_TEST(test_release);
    RUN_TEST(test_double_click);
    RUN_TEST(test_long_press);
    UNITY_END();
}

void loop() {}

// Main function for native testing
#ifndef ARDUINO
int main() {
    setup();
    return 0;
}
#endif
