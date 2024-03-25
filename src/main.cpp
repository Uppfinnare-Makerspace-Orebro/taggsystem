#include "Arduino.h"
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
auto state = State{users};

bool previousButtonState = false;

} // namespace

void handleButtonPress(State &state) {
    auto buttonState = digitalRead(buttonIn);
    if (buttonState) {
        if (previousButtonState != buttonState) {
            delay(100); // Dumb debouncing
            state.onButtonPress();
        }
    }
    else {
        if (previousButtonState != buttonState) {
            delay(100);
            state.onButtonRelease();
        }
    }
    previousButtonState = buttonState;
}

void setup() {
    initEeprom();
    state.init();
    pinMode(buttonIn, INPUT_PULLUP);
    pinMode(relayPin, OUTPUT);
    initLed(ledPin);

    digitalWrite(ledPin, 0);
    digitalWrite(relayPin, 0);

    reader.init();
}

void loop() {
    digitalWrite(relayPin, 0);

    handleButtonPress(state);

    if (auto card = reader.read()) {
        state.onCardShowed(*card);
    }

    if (state.getRelayState()) {
        setLed(true);
        digitalWrite(relayPin, HIGH);
        Serial.println("Open relay");
        delay(1000);
        digitalWrite(relayPin, LOW);
        setLed(false);
    }

    state.flashLed();
}
