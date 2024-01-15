#pragma once

#include "uidt.h"
#include <MFRC522.h>

class CardReader {
public:
    MFRC522 mfrc522; // Create MFRC522 instance

    CardReader(int ss, int rst);

    /// On success, @return true and save the read id, on failure return false
    bool tryRead();

    UIDt getId() {
        return id;
    }

private:
    UIDt id = {};
};
