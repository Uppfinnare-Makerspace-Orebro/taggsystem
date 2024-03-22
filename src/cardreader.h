#pragma once

#include "basicoptional.h"
#include "uidt.h"
#include <MFRC522.h>

class CardReader {
public:
    MFRC522 mfrc522; // Create MFRC522 instance

    CardReader(int ss, int rst);

    void init();

    BasicOptional<UIDt> read();
};
