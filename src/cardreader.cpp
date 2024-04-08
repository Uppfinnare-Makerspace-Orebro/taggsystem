#include "cardreader.h"
#include "SPI.h"
#include <Arduino.h>
#include <cstring>

CardReader::CardReader(int ss, int rst)
    : mfrc522(ss, rst) {}

void CardReader::init() {
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    delay(4); // Optional delay. Some board do need more time after init to be
              // ready, see Readme
    mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card
                                       // Reader details
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

BasicOptional<UIDt> CardReader::read() {
    // Reset the loop if no new card present on the sensor/reader. This saves
    // the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent()) {
        hadCard = false;
        return {};
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
        hadCard = false;
        return {};
    }

    auto id = UIDt{};

    if (hadCard) {
        return {};
    }

    memcpy(id.data, mfrc522.uid.uidByte, 10);

    hadCard = true;

    return id;
}
