#pragma once

#include "stdint.h"

struct UIDt {
    uint8_t data[10];

    constexpr bool operator==(const UIDt &other) const {
        for (int i = 0; i < 10; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }
};
