#include "cardreader.h"
#include "SPI.h"
#include <Arduino.h>

CardReader::CardReader(int ss, int rst)
    : mfrc522(ss, rst) {
    Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial)
        ; // Do nothing if no serial port is opened (added for Arduinos based on
          // ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    delay(4); // Optional delay. Some board do need more time after init to be
              // ready, see Readme
    mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card
                                       // Reader details
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

bool CardReader::tryRead() {
    // Reset the loop if no new card present on the sensor/reader. This saves
    // the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return false;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
        return false;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    // Serial.println("User added");
    // Serial.println(mfrc522.uid.size);
    // id.data = mfrc522.uid.uidByte;
    memcpy(id.data, mfrc522.uid.uidByte, 10);

    // users.add(User::fromRaw(mfrc522.uid.uidByte));
}
