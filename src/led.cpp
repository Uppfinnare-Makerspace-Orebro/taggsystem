#include "led.h"
#include <Arduino.h>

namespace {

int ledPin = 0;

}

void flash(int num, int delayMs) {
    for (int i = 0; i < num; ++i) {
        digitalWrite(ledPin, 1);
        delay(delayMs);
        digitalWrite(ledPin, 0);
        delay(delayMs);
    }
    delay(delayMs);
}

void initLed(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
}
