#include "cardreader.h"
#include "users.h"

#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above

Users users;
CardReader reader(SS_PIN, RST_PIN);

void setup() {}

void loop() {
    if (!reader.tryRead()) {
        return;
    }
    auto id = reader.getId();
    users.add(id);
    Serial.println("List of users");
    users.show();
}
