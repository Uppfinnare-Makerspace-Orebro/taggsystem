#include "Arduino.h"
#include "archive.h"
#include "cardreader.h"
#include "state.h"
#include "users.h"

#include <MFRC522.h>
#include <SPI.h>

constexpr auto RST_PIN = 9; // Configurable, see typical pin layout
constexpr auto SS_PIN = 10; // Configurable, see typical pin layout

constexpr auto buttonIn = 3;
constexpr auto buttonOut = 3;
constexpr auto relayPin = 2;
constexpr auto ledPin = 6;

Users users;
CardReader reader(SS_PIN, RST_PIN);

State state;

bool isButtonPressed() {
    return digitalRead(buttonIn);
}

void flash(int num, int delayMs) {
    for (int i = 0; i < num; ++i) {
        digitalWrite(ledPin, 1);
        delay(delayMs);
        digitalWrite(ledPin, 0);
        delay(delayMs);
    }
    delay(delayMs);
}

void setup() {
    auto arch = InArchive{};
    users.load(arch);

    pinMode(buttonIn, INPUT);
    pinMode(buttonOut, OUTPUT);
    pinMode(relayPin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    digitalWrite(buttonOut, 1);
    digitalWrite(ledPin, 0);
    digitalWrite(relayPin, 0);
}

void loop() {
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
        delay(1000);
    }
}
