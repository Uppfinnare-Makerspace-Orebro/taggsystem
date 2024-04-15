#include "led.h"
#include <Arduino.h>

namespace {

int ledPin = 0;

unsigned long timeLeftOnCurrent = 0;
int numberOfRemainingFlashes = 0;
bool ledState = false;
int delayMs = 100;

/// Used if flash(...) is called more than once
int currentFlashNum = 0;

} // namespace

void flash(int num, int delayMs) {
    if (currentFlashNum == num) {
        return;
    }
    ::delayMs = delayMs;
    numberOfRemainingFlashes = num;
    digitalWrite(ledPin, 1);
    ledState = true;
    currentFlashNum = num;
}

void initLed(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
}

void setLed(bool value) {
    digitalWrite(ledPin, value);
}

void updateLed(int passedMs) {
    if (passedMs == 0) {
        return;
    }
    // std::cout << "update led" << passedMs << "\n";
    // std::cout << "remainingn flashes " << numberOfRemainingFlashes << "\n";
    // std::cout << "time left on current " << timeLeftOnCurrent << "\n";
    // std::cout << "led status " << ledState << "\n";

    if (timeLeftOnCurrent > 0) {
        if (passedMs >= timeLeftOnCurrent) {
            timeLeftOnCurrent = 0;
        }
        else {
            timeLeftOnCurrent -= passedMs;
            return;
        }
    }

    if (!ledState) {
        if (numberOfRemainingFlashes == 0) {
            currentFlashNum = 0;
            return;
        }
        --numberOfRemainingFlashes;
    }

    ledState = !ledState;
    timeLeftOnCurrent = delayMs;
    setLed(ledState);
}
