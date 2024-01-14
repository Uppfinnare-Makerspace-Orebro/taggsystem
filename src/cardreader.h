#pragma once

#include "uidt.h"
#include <MFRC522.h>

class CardReader {
public:
    MFRC522 mfrc522; // Create MFRC522 instance

    CardReader(int ss, int rst);

    bool tryRead();
    UIDt getId();

private:
    UIDt id;
};
