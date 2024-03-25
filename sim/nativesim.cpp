#include "pinconfiguration.h"
#include <Arduino.h>
#include <MFRC522.h>
#include <thread>

int main(int argc, char *argv[]) {
    auto pins = getPinConfiguration();

    setup();

    bool isRunning = true;

    auto t = std::thread{[&isRunning]() {
        while (isRunning) {
            loop();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
        auto first = *MFRC522::uid.uidByte;
        std::cout << "current card " << (first ? std::to_string(first) : "none")
                  << "\n";
        std::cout << "led status: " << emulatedPins[pins.ledPin] << "\n";
        std::cout << "relay status: " << emulatedPins[pins.relayPin] << "\n";
        std::cout << "button status: " << emulatedPins[pins.buttonIn] << "\n";
        std::cout << "b: toggle button, 0: no card, 1-5 select card\n";
        std::cout << std::flush;
    }

    isRunning = false;
    t.join();

    return 0;
}
