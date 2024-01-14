#pragma once

#include "uidt.h"
#include <MFRC522.h>

class CardReader {
    MFRC522 mfrc522; // Create MFRC522 instance

    CardReader(int ss, int rst);

    void init(int ss_pin, int rst_pin);
    bool tryRead();
    UIDt id;
};
