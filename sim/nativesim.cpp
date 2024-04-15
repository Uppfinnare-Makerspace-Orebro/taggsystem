#include "pinconfiguration.h"
#include <Arduino.h>
#include <MFRC522.h>
#include <chrono>
#include <thread>

namespace {

unsigned char firstIdChar = 0;
auto pins = getPinConfiguration();

void drawText() {
    std::cout << "\n-------------------------------------------------\n";
    std::cout << "current card "
              << (firstIdChar ? std::to_string(firstIdChar) : "none") << "\n";
    std::cout << "led status: " << emulatedPins[pins.ledPin] << "\n";
    std::cout << "relay status: " << emulatedPins[pins.relayPin] << "\n";
    std::cout << "button status: " << !emulatedPins[pins.buttonIn] << "\n";
    std::cout << "b: toggle button, 0: no card, 1-5 select card\n";
    std::cout << "=================================================\n";
    std::cout << std::flush;
}

} // namespace

int main(int argc, char *argv[]) {
    setup();

    emulatedPins[pins.buttonIn] = true; // True is off

    bool isRunning = true;

    auto t = std::thread{[&isRunning]() {
        while (isRunning) {
            loop();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }};

    auto displayThread = std::thread{[&isRunning]() {
        while (isRunning) {
            if (isPinChanged) {
                isPinChanged = false;
                drawText();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }};

    for (std::string line; std::getline(std::cin, line);) {
        if (line == "exit") {
            break;
        }
        if (line.size() == 1) {
            switch (line.front()) {
            case 'b':
                emulatedPins[pins.buttonIn] = !emulatedPins[pins.buttonIn];
                break;
            case '0':
                MFRC522::isPresent = false;
                MFRC522::_uidByte = {};
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                MFRC522::isPresent = true;
                MFRC522::_uidByte = {};
                *MFRC522::uid.uidByte = line.front() - '0';
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        firstIdChar = *MFRC522::uid.uidByte;
        drawText();
    }

    isRunning = false;
    t.join();
    displayThread.join();

    return 0;
}
