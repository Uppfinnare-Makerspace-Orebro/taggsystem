#pragma once

#include "basicoptional.h"
#include "uidt.h"
#include <MFRC522.h>

class CardReader {
public:
    MFRC522 mfrc522; // Create MFRC522 instance

    bool hadCard = false;

    CardReader(int ss, int rst);

    void init();

    /// Try to read a card, but only return true the first time the card is read
    /// without pause
    BasicOptional<UIDt> read();
};
