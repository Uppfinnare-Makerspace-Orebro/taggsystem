#pragma once

#include "Arduino.h"
// #include "pins_arduino.h"

struct PinConfiguration {
    int rstPin = 0;
    int ssPin = 0;
    int buttonIn = 0;
    int relayPin = 0;
    int ledPin = 0;
};

constexpr PinConfiguration getPinConfiguration() {
    auto config = PinConfiguration{};

// Esp32 config
#ifdef ESP_PLATFORM
    config.rstPin = 4; // Not spi standard

    // Where to connect cables
    // MISO = 19 (Connects to MOSI on RFID)
    // MOSI = 23 (Connects to MISO on RFID)
    // SCK = 18
    config.ssPin = 5;

    // Builtin led is on D2

    config.buttonIn = 16;
    config.relayPin = 4;
    config.ledPin = 2;
#warning "this is esp32"

//
#else
#warning "this is arduino config"
    config.rstPin = 9;
    config.ssPin = 10;
    config.buttonIn = 7;
    config.relayPin = 2;
    config.ledPin = 4;
#endif
    // #elif ESP8266
    // config.rstPin = D2;
    // config.ssPin = D8;
    // config.buttonIn = D1;
    // config.relayPin = D0;
    // config.ledPin = D4;
    // #endif

    return config;
}
