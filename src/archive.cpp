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

void OutArchive::commit() {
    commitEeprom();
}

uint8_t InArchive::read() {
    uint8_t value = EEPROM.read(address);
    ++address;
    return value;
}

void initEeprom() {
    const auto usedEepromSize = User::size() * N_USERS + eepromStart;
    Serial.println("in initEeprom():");
#if ESP32
    EEPROM.begin(usedEepromSize);
#endif
    bool isInitialized = true;

    for (size_t i = 0; i < eepromVersionString.size(); ++i) {
        if (EEPROM.read(i) != eepromVersionString[i]) {
            isInitialized = false;
            break;
        }
    }

    if (isInitialized) {
        Serial.println("EEPROM: already initialized");
        return;
    }

    Serial.println("EEPROM: reinitializing");

    for (size_t i = 0; i < eepromVersionString.size(); ++i) {
        writeEeprom(i, eepromVersionString[i]);
    }

    for (size_t i = eepromVersionString.size() + 1; i < usedEepromSize; ++i) {
        writeEeprom(i, 0xff);
    }

    commitEeprom();
}

void commitEeprom() {
#ifdef ESP32
    EEPROM.commit();
#endif
}
