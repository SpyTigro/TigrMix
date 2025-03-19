#include <Arduino.h>
#include <unity.h>
#include "Button.h"

Button testButton(2);  // Simulated button on pin 2

void test_gotPressed() {
    digitalWrite(2, LOW);  // Simulate button press
    delay(10);  // Allow debounce
    TEST_ASSERT_TRUE(testButton.gotPressed());
}

void test_gotReleased() {
    digitalWrite(2, HIGH);  // Simulate button release
    delay(10);
    TEST_ASSERT_TRUE(testButton.gotReleased());
}

void test_doubleClicked() {
    digitalWrite(2, LOW);
    delay(50);
    digitalWrite(2, HIGH);
    delay(50);
    digitalWrite(2, LOW);
    delay(50);
    digitalWrite(2, HIGH);
    delay(50);

    TEST_ASSERT_TRUE(testButton.doubleClicked(250));
}

void setup() {
    delay(2000);  // Allow time for serial monitor
    UNITY_BEGIN(); // Start testing
    RUN_TEST(test_gotPressed);
    RUN_TEST(test_gotReleased);
    RUN_TEST(test_doubleClicked);
    UNITY_END();   // End testing
}

void loop() { }