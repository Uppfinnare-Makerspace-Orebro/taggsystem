#pragma once

#include <cstddef>
#include <stdint.h>
#include <string_view>

const auto eepromVersionString = std::string_view{"SUF001"};
const auto eepromStart = eepromVersionString.size() + 1;

/// Reset eeprom if it is not initialized with the right version string
void initEeprom();

struct OutArchive {
    OutArchive(size_t address)
        : address(address) {}

    size_t address = {};

    void write(uint8_t value);
};

struct InArchive {
    InArchive(size_t address)
        : address(address) {}

    size_t address = {};

    uint8_t read();
};
