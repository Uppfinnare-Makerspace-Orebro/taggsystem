#include "archive.h"
#include "led.h"
#include "users.h"
#include <array>

namespace {

auto eepromData =
    std::array<uint8_t, User::size() * N_USERS + eepromStart + 1>{};

}

void OutArchive::write(uint8_t value) {
    eepromData.at(address) = value;
    ++address;
}

void OutArchive::commit() {
    ///
}

uint8_t InArchive::read() {
    return eepromData.at(address++);
}

void flash(int num, int delayMs) {}

void resetEeprom() {
    eepromData.fill(0xff);
}
