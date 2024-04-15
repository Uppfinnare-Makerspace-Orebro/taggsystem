#pragma once

#include "archive.h"
#include "cardreader.h"
#include "led.h"
#include "users.h"
#include <chrono>
#include <iostream>
#include <map>
#include <thread>

constexpr auto INPUT = 1;
constexpr auto OUTPUT = 2;
constexpr auto INPUT_PULLUP = 3;
constexpr auto HIGH = 1;
constexpr auto LOW = 0;

inline std::map<int, int> emulatedPins;
inline bool isPinChanged = false;
inline UIDt emulatedCard;

inline void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds{ms});
}

inline int digitalRead(int pin) {
    return emulatedPins[pin];
}

inline void digitalWrite(int pin, int value) {
    auto &pinValue = emulatedPins[pin];

    if (pinValue != value) {
        pinValue = value;
        isPinChanged = true;
        std::cout << "pin " << pin << " set to " << value << std::endl;
    }
}

inline void pinMode(int pin, int value) {
    // ignore
}

inline unsigned long millis() {
    auto time = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
}

void setup();
void loop();

constexpr auto HEX = 10;

struct {
    template <typename T>
    void print(const T &value) {
        std::cout << value << std::endl;
    }

    template <typename T>
    void println(const T &value, int format = 0) {
        std::cout << value << std::endl;
    }

    void begin(int rate) {}

    operator bool() {
        return true;
    }
} Serial;

#define F(x) x
