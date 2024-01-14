#ifndef USERS_H
#define USERS_H

#include "uidt.h"
#include <stdint.h>

constexpr auto BADUSER =
    UIDt{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef int IDXt;
#define N_USERS 50
#define IDX_BADUSER (N_USERS + 1)

class User {
private:
    UIDt UID = BADUSER;
    bool _isAdmin = false;

public:
    explicit User(UIDt uid, bool isAdmin)
        : UID{uid}
        , _isAdmin{isAdmin} {}
    User() = default;
    bool operator==(const User &other) {
        return other.UID == UID;
    }
    bool operator==(const UIDt &id) {
        return UID == id;
    }
    void show();
    UIDt getUID() {
        return UID;
    }
    static UIDt fromRaw(const uint8_t *b) {
        auto id = UIDt{};
        for (int i = 0; i < 10; ++i) {
            id.data[i] = b[i];
        }
        return id;
    }

    bool isAdmin() const {
        return _isAdmin;
    }

    void isAdmin(bool value) {
        _isAdmin = value;
    }
};

class Users {
private:
    User users[N_USERS];

public:
    User *find(UIDt uid);
    User *findAdmin(UIDt uid);
    bool add(UIDt uid, bool isAdmin = false);
    bool del(UIDt uid);

    void show();
};

#endif // USERS_H
