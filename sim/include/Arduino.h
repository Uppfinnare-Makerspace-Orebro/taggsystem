#pragma once

#include "archive.h"
#include "cardreader.h"
#include "led.h"
#include <chrono>
#include <emscripten.h>
#include <thread>

constexpr auto INPUT = 1;
constexpr auto OUTPUT = 2;

inline void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds{ms});
}

inline int digitalRead(int pin) {
    return EM_ASM_INT({ return digitalRead($0); }, pin);
}

inline void digitalWrite(int pin, int value) {
    EM_ASM({digitalWrite($0, $1)}, pin, value);
}

inline void pinMode(int pin, int value) {
    // ignore
}

inline CardReader::CardReader(int ss, int rst) {
    // ignore
}

inline bool CardReader::tryRead() {
    auto card = EM_ASM_INT({ return getCard(); });
    if (card == 0) {
        return false;
    }

    id = {};
    id.data[0] = card;

    return true;
}

void setup();
void loop();

#include <iostream>

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
} Serial;

#include <array>

inline auto eepromData = [] {
    auto arr = std::array<uint8_t, 10000>{};
    for (auto &c : arr) {
        c = 0xff;
    }
    return arr;
}();

inline void OutArchive::write(uint8_t value) {
    eepromData.at(address) = value;
    ++address;
}

inline uint8_t InArchive::read() {
    return eepromData.at(address++);
}

inline void initLed(int pin) {}

inline void flash(int num, int delayMs) {
    EM_ASM({ flashLed($0, $1); }, num, delayMs);
}
