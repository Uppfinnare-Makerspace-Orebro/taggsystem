#pragma once

#include <cstddef>
#include <stdint.h>
#include <string_view>

const auto eepromVersionString = std::string_view{"SUF001"};
const auto eepromStart = eepromVersionString.size() + 1;

/// Reset eeprom if it is not initialized with the right version string
void initEeprom();

/// This is used for esp32 since it writes whole blocks to flash memory
/// If not used, the data will not be saved
void commitEeprom();

struct OutArchive {
    OutArchive(size_t address)
        : address(address + eepromStart) {}

    size_t address = {};

    void write(uint8_t value);

    // For devices that emulates eeprom on flash
    void commit();
};

struct InArchive {
    InArchive(size_t address)
        : address(address + eepromStart) {}

    size_t address = {};

    uint8_t read();
};
