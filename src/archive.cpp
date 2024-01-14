#include "archive.h"
#include "EEPROM.h"

void OutArchive::write(uint8_t value) {
    uint8_t currentValue = EEPROM.read(address);
    if (currentValue != value) {
        EEPROM.write(address, value);
    }

    ++address;
}

uint8_t InArchive::read() {
    uint8_t value = EEPROM.read(address);
    ++address;
    return value;
}
