#pragma once

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#else

#include <iostream>

struct {
    template <typename T>
    void print(const T &value) {
        std::cout << value << std::endl;
    }

    template <typename T>
    void println(const T &value) {
        std::cout << value << std::endl;
    }
} Serial;

#endif
