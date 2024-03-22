#include "users.h"
#if __has_include(<Arduino.h>)
#include <Arduino.h>
#endif

void User::show() const {
#if __has_include(<Arduino.h>)
    // Print the array in hex format
    for (auto elem : id().data) {
        Serial.print("0x");
        if (elem < 0x10) {
            Serial.print("0"); // Print leading zero for single digit hex values
        }
        Serial.println(elem, HEX); // Print each element in hex
    }
#endif
}

UserRef Users::find(UIDt uid) {
    for (size_t i = 0; i < N_USERS; ++i) {
        auto ref = UserRef{i};
        if (*ref == uid) {
            return ref;
        }
    }
    return {};
}

UserRef Users::findAdmin(UIDt uid) {
    if (auto ref = find(uid)) {
        if (ref.get().isAdmin()) {
            return ref;
        }
    }

    return {};
}

bool Users::add(UIDt uid, bool isAdmin) {
    if (auto ref = find(uid)) {
        auto user = ref.get();
        if (isAdmin && !user.isAdmin()) {
            del(user.id());
            add(user.id(), true);
            return true;
        }
        return false;
    }

    for (size_t i = 0; i < N_USERS; ++i) {
        auto ref = UserRef{i};
        if (!ref) {
            ref = User{uid, isAdmin};
            return true;
        }
    }

    return false;
}

bool Users::del(UIDt uid) {
    if (auto user = find(uid)) {
        user = User{};
        return true;
    }
    return false;
}

void Users::show() const {
    for (size_t i = 0; i < N_USERS; ++i) {
        auto ref = UserRef{i};
        if (ref) {
            ref.get().show();
        }
    }
}

bool Users::isEmpty() const {
    for (size_t i = 0; i < N_USERS; ++i) {
        auto ref = UserRef{i};
        if (ref) {
            return false;
        }
    }

    return true;
}

int Users::count() const {
    int count = 0;
    for (size_t i = 0; i < N_USERS; ++i) {
        auto ref = UserRef{i};
        if (ref) {
            ++count;
        }
    }

    return count;
}
