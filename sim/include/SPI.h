#pragma once

struct SPI_t {
    void begin(){};
};

inline auto SPI = SPI_t{};
