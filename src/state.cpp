#include "state.h"
#include "print.h"
#include "uidt.h"

void State::wait() {
    isWaitingForButtonRelease = true;
}

void State::reset() {
    currentId = {};
    state = Start;
}

bool State::handle(Users &users, const UIDt *id, bool isPressed) {
    if (isWaitingForButtonRelease && (isPressed || id)) {
        return false;
    }

    isWaitingForButtonRelease = false;

    switch (state) {
    case Start:
        return handleStart(users, id, isPressed);
        break;
    case AddUser:

        break;
    case AddAdmin:
        break;
    case RemoveUser:
        break;
    }

    return false;
}

bool State::handleStart(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        return false;
    }

    if (!users.find(*id)) {
        Serial.print("User ");
        // Serial.print(id);
        Serial.println("not found");
        return false;
    }

    if (isPressed) {
        wait();
        currentId = *id;
        state = AddUser;
        return false;
    }

    wait();
    return true;
}

void State::handleAddUser(Users &users, const UIDt *id, bool isPressed) {
    if (id) {
        /// The first user has probably not removed their tag
        if (*id == currentId) {
            return;
        }

        users.add(*id);
        reset();
        wait();
    }

    if (isPressed) {
        state = AddAdmin;
        wait();
    }
}

void State::handleAddAdmin(Users &users, const UIDt *id, bool isPressed) {
    if (id) {
        /// The first user has probably not removed their tag
        if (*id == currentId) {
            return;
        }

        users.add(*id);
        reset();
        wait();
    }

    if (isPressed) {
        state = RemoveUser;
        wait();
    }
}
