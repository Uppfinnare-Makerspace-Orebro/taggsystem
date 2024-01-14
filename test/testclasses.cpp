#include "archive.h"
#include "led.h"
#include <array>

namespace {

auto eepromData = std::array<uint8_t, 10000>{};

}

void OutArchive::write(uint8_t value) {
    eepromData.at(address) = value;
    ++address;
}

uint8_t InArchive::read() {
    return eepromData.at(address++);
}

void flash(int num) {}
