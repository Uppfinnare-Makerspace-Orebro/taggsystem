#include "users.h"
#if __has_include(<Arduino.h>)
#include <Arduino.h>
#endif

void User::show() {
#if __has_include(<Arduino.h>)
    // Print the array in hex format
    for (auto elem : UID.data) {
        Serial.print("0x");
        if (elem < 0x10) {
            Serial.print("0"); // Print leading zero for single digit hex values
        }
        Serial.println(elem, HEX); // Print each element in hex
    }
#endif
}

User *Users::find(UIDt uid) {
    for (User &user : users) {
        if (user == uid) {
            return &user;
        }
    }
    return nullptr;
}

User *Users::findAdmin(UIDt uid) {
    if (auto *user = find(uid)) {
        if (user->isAdmin()) {
            return user;
        }
    }

    return nullptr;
}

bool Users::add(UIDt uid, bool isAdmin) {
    if (auto *user = find(uid)) {
        if (isAdmin && !user->isAdmin()) {
            user->isAdmin(true);
            return true;
        }
        return false;
    }
    for (User &user : users) {
        if (user == BADUSER) {
            user = User{uid, isAdmin};
            return true;
        }
    }
    return false;
}

bool Users::del(UIDt uid) {
    if (auto *user = find(uid)) {
        *user = User{};
        return true;
    }
    return false;
}

void Users::show() {
    for (User &user : users) {
        if (!(user == BADUSER)) {
            user.show();
        }
    }
}
