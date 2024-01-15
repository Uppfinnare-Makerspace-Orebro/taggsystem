#include "state.h"
#include "led.h"
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

    if (users.isEmpty()) {
        state = NoUsers;
    }

    switch (state) {
    case Start:
        return handleStart(users, id, isPressed);
        break;
    case AddUser:
        handleAddUser(users, id, isPressed);
        break;
    case AddAdmin:
        handleAddAdmin(users, id, isPressed);
        break;
    case RemoveUser:
        handleRemoveUser(users, id, isPressed);
        break;

    case NoUsers:
        handleNoUser(users, id, isPressed);
        break;
    }

    return false;
}

bool State::handleStart(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        return false;
    }

    if (!users.find(*id)) {
        // Serial.print("User ");
        // Serial.print(id);
        // Serial.println("not found");
        return false;
    }

    // Only admins can access the menu
    if (!users.findAdmin(*id)) {
        wait();
        return true;
    }

    if (isPressed) {
        wait();
        currentId = *id;
        state = AddUser;
        flash(1);
        return false;
    }

    wait();
    return true;
}

void State::handleAddUser(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        if (isPressed) {
            state = AddAdmin;
            flash(2);
            wait();
        }
        return;
    }

    /// The first user has probably not removed their tag
    if (*id == currentId) {
        return;
    }

    users.add(*id);
    reset();
    wait();
}

void State::handleAddAdmin(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        if (isPressed) {
            state = RemoveUser;
            flash(3);
            wait();
        }
        return;
    }
    /// The first user has probably not removed their tag
    if (*id == currentId) {
        return;
    }

    users.add(*id, true);
    reset();
    wait();
}

void State::handleRemoveUser(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        if (isPressed) {
            reset();
            wait();
        }
        return;
    }

    /// Removing yourself is not allowed (since it could lead to no admin being
    /// active)
    if (*id == currentId) {
        return;
    }

    users.del(*id);
    reset();
    wait();
}

void State::handleNoUser(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        flash(3, 200);
        return;
    }

    users.add(*id, true);

    flash(10);
    reset();
    wait();
}
