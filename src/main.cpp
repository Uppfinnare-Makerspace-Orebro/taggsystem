#include "archive.h"
#include "cardreader.h"
#include "led.h"
#include "state.h"
#include "users.h"
#include <Arduino.h>

#include <MFRC522.h>
#include <SPI.h>

constexpr auto RST_PIN = 9; // Configurable, see typical pin layout
constexpr auto SS_PIN = 10; // Configurable, see typical pin layout

constexpr auto buttonIn = 7;
constexpr auto buttonOut = 3;
constexpr auto relayPin = 2;

namespace {

Users users;
CardReader reader(SS_PIN, RST_PIN);
constexpr auto ledPin = 6;

State state;

} // namespace

bool isButtonPressed() {
    return digitalRead(buttonIn);
}

void setup() {
    auto arch = InArchive{};
    users.load(arch);

    pinMode(buttonIn, INPUT);
    pinMode(buttonOut, OUTPUT);
    pinMode(relayPin, OUTPUT);
    initLed(ledPin);

    digitalWrite(buttonOut, 1);
    digitalWrite(ledPin, 0);
    digitalWrite(relayPin, 0);

    reader.init();
}

void loop() {
    Serial.println("loop()");
    digitalWrite(relayPin, 0);
    if (!reader.tryRead()) {
        state.handle(users, nullptr, isButtonPressed());
        return;
    }

    auto id = reader.getId();

    auto relayState = state.handle(users, &id, isButtonPressed());

    if (users.isChanged()) {
        auto arch = OutArchive{};
        users.save(arch);
    }

    digitalWrite(relayPin, relayState);

    if (relayState) {
        Serial.println("relay active");
        delay(1000);
    }
}
