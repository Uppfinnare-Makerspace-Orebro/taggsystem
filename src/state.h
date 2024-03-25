#pragma once

#include "uidt.h"
#include "users.h"
#include <utility>

class State {
private:
    enum StateNum {
        Start = 0,
        ButtonPressed,
        AddUser,
        AddAdmin,
        RemoveUser,

        NoUsers,
    };

    StateNum _state = Start;
    bool _isRelayOpen = false;
    Users *_users = nullptr;

    void reset();

public:
    State(Users &users)
        : _users(&users) {}

    void init() {
        if (_users->isEmpty()) {
            _state = NoUsers;
        }
    }

    /// Get the state of the relay output
    bool getRelayState();

    /// flash an appropriate amount of times on the led to display the current
    /// state
    void flashLed();

    /// Event that happends to the state
    void onButtonPress();
    void onButtonRelease();
    /// @param id is assumed to be valid
    void onCardShowed(const UIDt id);
};
