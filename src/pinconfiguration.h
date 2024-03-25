#pragma once

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
    // #ifdef ESP_PLATFORM
    config.rstPin = 9;
    config.ssPin = 10;
    config.buttonIn = 7;
    config.relayPin = 2;
    config.ledPin = 4;
    // #elif ESP8266
    // config.rstPin = D2;
    // config.ssPin = D8;
    // config.buttonIn = D1;
    // config.relayPin = D0;
    // config.ledPin = D4;
    // #endif

    return config;
}
