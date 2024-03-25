#include "archive.h"
#include "EEPROM.h"
#include "users.h"
#include <Arduino.h>

namespace {

void writeEeprom(size_t address, uint8_t value) {
    uint8_t currentValue = EEPROM.read(address);
    if (currentValue != value) {
        EEPROM.write(address, value);
    }
}

} // namespace

void OutArchive::write(uint8_t value) {
    writeEeprom(address, value);

    ++address;
}

uint8_t InArchive::read() {
    uint8_t value = EEPROM.read(address);
    ++address;
    return value;
}

void initEeprom() {
    bool isInitialized = true;

    for (size_t i = 0; i < eepromVersionString.size(); ++i) {
        if (EEPROM.read(i) != eepromVersionString[i]) {
            isInitialized = false;
            break;
        }
    }

    if (isInitialized) {
        return;
    }

    for (size_t i = 0; i < eepromVersionString.size(); ++i) {
        writeEeprom(i, eepromVersionString[i]);
    }

    auto usedEepromSize = User::size() * N_USERS + eepromStart;

    for (size_t i = eepromVersionString.size() + 1; i < usedEepromSize; ++i) {
        writeEeprom(i, 0xff);
    }
}
