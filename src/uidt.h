#pragma once

#include "stdint.h"

struct UIDt {
    uint8_t data[10];

    constexpr bool operator==(const UIDt &other) const {
        return data == other.data;
    }
};
