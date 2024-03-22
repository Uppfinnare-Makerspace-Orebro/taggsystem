#ifndef USERS_H
#define USERS_H

#include "archive.h"
#include "uidt.h"
#include <cstddef>
#include <stdint.h>

constexpr auto BADUSER = UIDt{};

typedef int IDXt;
#define N_USERS 50
#define IDX_BADUSER (N_USERS + 1)

class User {
private:
    UIDt _id = BADUSER;
    bool _isAdmin : 1;

    static constexpr auto _size = sizeof(_id.data) + 1;

public:
    static constexpr size_t size() {
        return _size;
    }

    explicit User(UIDt uid, bool isAdmin)
        : _id{uid}
        , _isAdmin{isAdmin} {}
    User() = default;
    bool operator==(const User &other) const {
        return other._id == _id;
    }
    bool operator==(const UIDt &id) const {
        return _id == id;
    }
    bool operator!=(const UIDt &id) const {
        return _id != id;
    }

    void show() const;
    UIDt id() const {
        return _id;
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

    void save(OutArchive &arch) const {
        for (auto c : _id.data) {
            arch.write(c);
        }
        arch.write(_isAdmin ? 1 : 0xff);
    }

    void load(InArchive &arch) {
        for (auto &c : _id.data) {
            c = arch.read();
        }
        auto adm = arch.read();
        _isAdmin = adm == 1;
    }

    bool isValid() const {
        return _id != BADUSER;
    }
};

struct UserRef {
    static constexpr size_t npos = static_cast<size_t>(-1);

    size_t index = npos;

    UserRef() = default;
    UserRef(size_t index)
        : index(index) {}
    UserRef(const UserRef &) = default;
    UserRef &operator=(const UserRef &) = default;

    /// Const here to make sure that the user does not think changes to the
    /// object will be automatically saved
    const User operator*() const {
        auto arch = InArchive{index * User::size()};
        auto user = User{};
        user.load(arch);
        return user;
    }

    const User get() const {
        return operator*();
    }

    void operator=(const User &user) {
        auto arch = OutArchive{index * User::size()};
        user.save(arch);
    }

    operator bool() const {
        return index != npos && get().isValid();
    }
};

class Users {
public:
    struct UserIterator;
    UserRef find(UIDt uid);
    UserRef findAdmin(UIDt uid);

    /// @returns false if user already exist, true if user was added
    bool add(UIDt uid, bool isAdmin = false);
    bool del(UIDt uid);

    void show() const;

    bool isEmpty() const;
    int count() const;
};

#endif // USERS_H
