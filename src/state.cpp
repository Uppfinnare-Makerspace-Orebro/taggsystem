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

    Serial.println("num users:");
    Serial.println(users.count());
    if (users.isEmpty()) {
        Serial.println("no users");
        state = NoUsers;
    }

    switch (state) {
    case Start:
        return handleStart(users, id, isPressed);
        break;
    case AddUser:
        flash(1);
        handleAddUser(users, id, isPressed);
        break;
    case AddAdmin:
        flash(2);
        handleAddAdmin(users, id, isPressed);
        break;
    case RemoveUser:
        flash(3);
        handleRemoveUser(users, id, isPressed);
        break;

    case NoUsers:
        handleNoUser(users, id, isPressed);
        break;
    }

    return false;
}

bool State::handleStart(Users &users, const UIDt *id, bool isPressed) {
    Serial.println("start()");
    Serial.println("hasId?");
    Serial.println(!!id);
    Serial.println("pressed:");
    Serial.println(isPressed);
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
        return false;
    }

    wait();
    return true;
}

void State::handleAddUser(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        if (isPressed) {
            state = AddAdmin;
            wait();
        }
        return;
    }

    /// The first user has probably not removed their tag
    if (*id == currentId) {
        return;
    }

    Serial.println("Added user");
    users.add(*id);
    reset();
    wait();
}

void State::handleAddAdmin(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        if (isPressed) {
            state = RemoveUser;
            wait();
        }
        return;
    }
    /// The first user has probably not removed their tag
    if (*id == currentId) {
        return;
    }

    Serial.println("Added admin");
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

    Serial.println("Deleted user");
    users.del(*id);
    reset();
    wait();
}

void State::handleNoUser(Users &users, const UIDt *id, bool isPressed) {
    if (!id) {
        flash(3, 200);
        return;
    }

    Serial.println("Add first root user");
    users.add(*id, true);

    flash(10);
    reset();
    wait();
}
