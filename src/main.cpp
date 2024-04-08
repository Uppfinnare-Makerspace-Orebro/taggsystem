#include "Arduino.h"
#include "archive.h"
#include "cardreader.h"
#include "led.h"
#include "pinconfiguration.h"
#include "state.h"
#include "users.h"
#include <Arduino.h>

#include <MFRC522.h>
#include <SPI.h>

namespace {

constexpr auto pins = getPinConfiguration();

// #if 1 // Old config for nodemcu

// constexpr auto RST_PIN = D2; // Configurable, see typical pin layout
// constexpr auto SS_PIN = D8;  // Configurable, see typical pin layout

// constexpr auto buttonIn = D1; // 7;
// constexpr auto relayPin = D0;
// constexpr auto ledPin = D4;
// #else
// constexpr auto RST_PIN = 9; // Configurable, see typical pin layout
// constexpr auto SS_PIN = 10; // Configurable, see typical pin layout

// constexpr auto buttonIn = 7; // 7;
// constexpr auto relayPin = 2;
// constexpr auto ledPin = 4;
// #endif

auto reader = CardReader{pins.ssPin, pins.rstPin};

auto users = Users{};
auto state = State{users};

bool previousButtonState = false;

} // namespace

void handleButtonPress(State &state) {
    auto buttonState = digitalRead(pins.buttonIn);
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
    Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial)
        ; // Do nothing if no serial port is opened (added for Arduinos based on
          // ATMEGA32U4)
    delay(2000); // Wait for the user to connect with monitor
    Serial.println("setup()");
    initEeprom();
    state.init();
    pinMode(pins.buttonIn, INPUT_PULLUP);
    pinMode(pins.relayPin, OUTPUT);
    initLed(pins.ledPin);

    digitalWrite(pins.ledPin, 0);
    digitalWrite(pins.relayPin, 0);

    reader.init();
}

void loop() {
    digitalWrite(pins.relayPin, 0);

    handleButtonPress(state);

    if (auto card = reader.read()) {
        state.onCardShowed(*card);
    }

    if (state.getRelayState()) {
        setLed(true);
        digitalWrite(pins.relayPin, HIGH);
        Serial.println("Open relay");
        delay(1000);
        digitalWrite(pins.relayPin, LOW);
        setLed(false);
    }

    state.flashLed();
}
