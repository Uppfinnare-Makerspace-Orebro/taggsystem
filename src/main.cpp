#include "archive.h"
#include "cardreader.h"
#include "led.h"
#include "state.h"
#include "users.h"
#include <Arduino.h>

#include <MFRC522.h>
#include <SPI.h>

namespace {

#if 1 // Old config for nodemcu

constexpr auto RST_PIN = D2; // Configurable, see typical pin layout
constexpr auto SS_PIN = D8;  // Configurable, see typical pin layout

constexpr auto buttonIn = D1; // 7;
constexpr auto relayPin = D0;
constexpr auto ledPin = D4;
#else
constexpr auto RST_PIN = 9; // Configurable, see typical pin layout
constexpr auto SS_PIN = 10; // Configurable, see typical pin layout

constexpr auto buttonIn = 7; // 7;
constexpr auto relayPin = 2;
constexpr auto ledPin = 4;
#endif

auto reader = CardReader{SS_PIN, RST_PIN};

auto users = Users{};
auto state = State{};

} // namespace

bool isButtonPressed() {
    return digitalRead(buttonIn);
}

void setup() {
    initEeprom();
    pinMode(buttonIn, INPUT_PULLUP);
    pinMode(relayPin, OUTPUT);
    initLed(ledPin);

    digitalWrite(ledPin, 0);
    digitalWrite(relayPin, 0);

    reader.init();
}

void loop() {
    Serial.println("loop()");
    digitalWrite(relayPin, 0);

    auto card = reader.read();

    if (card) {
        state.handle(users, nullptr, isButtonPressed());
        return;
    }

    bool relayState = state.handle(users, &*card, isButtonPressed());

    digitalWrite(relayPin, relayState);

    if (relayState) {
        // Serial.println("relay active");
        delay(1000);
    }
}
