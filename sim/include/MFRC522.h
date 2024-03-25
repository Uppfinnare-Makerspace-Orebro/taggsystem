#pragma once

#include <array>

/// Simulated rfc reader
struct MFRC522 {
    MFRC522(int, int) {}

    void PCD_Init() {}

    bool PICC_IsNewCardPresent() {
        return isPresent;
    }

    bool PICC_ReadCardSerial() {
        return isPresent;
    }

    void PCD_DumpVersionToSerial() {}

    static inline bool isPresent = false;

    static inline std::array<unsigned char, 10> _uidByte = {};

    static inline struct UID {
        static inline unsigned char *uidByte = _uidByte.data();
    } uid;
};
