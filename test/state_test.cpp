#include "state.h"
#include "uidt.h"
#include <gtest/gtest.h>

constexpr auto userData1 = UIDt{0x01};
constexpr auto userData2 = UIDt{0x02};

namespace {

/// Repeating because that is what is probably going to happend in reality
bool repeatMessage(State &state, Users &users, const UIDt *id, bool isPressed) {
    bool isEnabled = false;

    for (int i = 0; i < 100; ++i) {
        if (state.handle(users, id, isPressed)) {
            isEnabled = true;
        }
    }

    return isEnabled;
}

} // namespace

TEST(StateTest, OpenRelay) {
    auto users = Users{};
    auto state = State{};

    users.add(userData1);

    EXPECT_FALSE(repeatMessage(state, users, &userData2, false));
    EXPECT_TRUE(repeatMessage(state, users, &userData1, false));
}

TEST(StateTest, AddUser) {
    auto users = Users{};
    auto state = State{};

    users.add(userData1);

    EXPECT_FALSE(repeatMessage(state, users, &userData2, false));
    EXPECT_FALSE(repeatMessage(state, users, nullptr, true));
}
