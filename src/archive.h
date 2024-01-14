#pragma once

#include <stdint.h>

class OutArchive {
    int address = 0;

public:
    void write(uint8_t value);
};

class InArchive {
    int address = 0;

public:
    uint8_t read();
};
