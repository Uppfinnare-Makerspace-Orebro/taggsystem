#pragma once

#include <array>
#include <cstdint>

inline auto eepromData = [] {
    auto arr = std::array<uint8_t, 10000>{};
    for (auto &c : arr) {
        c = 0xff;
    }
    return arr;
}();

struct EEPROM_t {
    void write(int address, uint8_t value) {
        eepromData.at(address) = value;
    }

    uint8_t read(int address) {
        return eepromData.at(address);
    }
};

inline auto EEPROM = EEPROM_t{};
