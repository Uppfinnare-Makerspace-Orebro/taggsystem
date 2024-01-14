#ifndef USERS_H
#define USERS_H

#include "uidt.h"
#include <stdint.h>

constexpr auto BADUSER =
    UIDt{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef int IDXt;
#define N_USERS 50
#define IDX_BADUSER (N_USERS + 1)

enum class UserType : char {
    Normal,
    Admin,
};

class User {
private:
    UIDt UID = BADUSER;
    UserType type = UserType::Normal;

public:
    explicit User(UIDt uid) {
        UID = uid;
    }
    User() = default;
    bool operator==(const User &other) {
        return other.UID == UID;
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
};

class Users {
private:
    User users[N_USERS];

public:
    Users();
    bool find(UIDt uid);
    bool add(UIDt uid);
    bool del(UIDt uid);
    void show();
};

#endif // USERS_H
