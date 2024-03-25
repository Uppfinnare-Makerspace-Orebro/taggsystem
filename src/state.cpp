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
        break;
    case ButtonPressed:
        // Show card while button is pressed to enter menu
        break;
    case AddUser:
        _state = AddAdmin;
        break;
    case AddAdmin:
        _state = RemoveUser;
        break;
    case RemoveUser:
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
        break;
    default:
        break;
    }
}

void State::onCardShowed(const UIDt id) {
    switch (_state) {
    case Start:
        if (_users->find(id)) {
            _isRelayOpen = true;
        }
        break;
    case ButtonPressed:
        if (_users->findAdmin(id)) {
            _state = AddUser;
        }
        break;
    case AddUser:
        _users->add(id);
        _state = Start;
        break;
    case AddAdmin:
        _users->add(id, true);
        _state = Start;
        break;
    case RemoveUser:
        _users->del(id);
        _state = Start;
        break;
    case NoUsers:
        _users->add(id, true);
        _state = Start;
        break;
    }
}
