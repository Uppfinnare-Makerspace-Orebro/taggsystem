#include "state.h"
#include "led.h"
#include "print.h"
#include "uidt.h"

void State::reset() {
    _state = Start;
}

bool State::getRelayState() {
    return std::exchange(_isRelayOpen, false);
}

void State::flashLed() {
    switch (_state) {
    case Start:
        // Do nothing
        break;
    case ButtonPressed:
        ::flash(1, 100);
        break;
    case AddUser:
        ::flash(2, 100);
        break;
    case AddAdmin:
        ::flash(3, 100);
        break;
    case RemoveUser:
        ::flash(4, 100);
        break;
    case NoUsers:
        ::flash(10, 100);
        break;
    }
}

void State::onButtonPress() {
    switch (_state) {
    case Start:
        _state = ButtonPressed;
        Serial.println("menu: button pressed");
        break;
    case ButtonPressed:
        // Show card while button is pressed to enter menu
        break;
    case AddUser:
        Serial.println("menu: add admin");
        _state = AddAdmin;
        break;
    case AddAdmin:
        Serial.println("menu: remove user");
        _state = RemoveUser;
        break;
    case RemoveUser:
        Serial.println("menu: reset");
        _state = Start;
        break;
    case NoUsers:
        break;
    }
}

void State::onButtonRelease() {
    switch (_state) {
    case Start:
        break;
    case ButtonPressed:
        _state = Start;
        Serial.println("menu: button released without id shown");
        break;
    default:
        break;
    }
}

bool State::onCardShowed(const UIDt id) {
    switch (_state) {
    case Start:
        if (_users->find(id)) {
            _isRelayOpen = true;
            return false; // No delay
        }
        else {
            Serial.println("user not registered");
        }
        break;
    case ButtonPressed:
        if (_users->findAdmin(id)) {
            Serial.println("enter menu: add user");
            _state = AddUser;
        }
        else {
            Serial.println("menu: not admin, will not enter menu");
        }
        break;
    case AddUser:
        if (_users->add(id)) {
            Serial.println("add user");
        }
        _state = Start;
        break;
    case AddAdmin:
        if (_users->add(id, true)) {
            Serial.println("add admin");
        }
        _state = Start;
        break;
    case RemoveUser:
        if (_users->del(id)) {
            Serial.println("deleted user");
        }
        else {
            Serial.println("could not delete user");
        }

        if (_users->count() == 0) {
            _state = NoUsers;
        }
        else {
            _state = Start;
        }
        break;
    case NoUsers:
        Serial.println("add first admin user");
        _users->add(id, true);
        _state = Start;
        break;
    }
    return true;
}
