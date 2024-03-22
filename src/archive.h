#pragma once

#include <cstddef>
#include <stdint.h>

struct OutArchive {
    size_t address = 0;

    void write(uint8_t value);
};

struct InArchive {
    size_t address = 0;

    uint8_t read();
};
