#include "users.h"

#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above

Users users;

void setup() {}

void loop() {
    // Reset the loop if no new card present on the sensor/reader. This saves
    // the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    Serial.println("User added");
    Serial.println(mfrc522.uid.size);
    users.add(User::fromRaw(mfrc522.uid.uidByte));
    Serial.println("List of users");
    users.show();
}
