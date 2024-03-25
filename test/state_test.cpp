#include "state.h"
#include "testclasses.h"
#include "uidt.h"
#include <gtest/gtest.h>

constexpr auto userData1 = UIDt{0x01};
constexpr auto userData2 = UIDt{0x02};

TEST(StateTest, OpenRelay) {
    resetEeprom();
    auto users = Users{};
    auto state = State{users};

    users.add(userData1);

    state.onCardShowed(userData2);
    EXPECT_FALSE(state.getRelayState());
    state.onCardShowed(userData1);
    EXPECT_TRUE(state.getRelayState());
}

TEST(StateTest, AddUser) {
    resetEeprom();
    auto users = Users{};
    auto state = State{users};

    EXPECT_TRUE(users.add(userData1, true));

    state.onButtonPress();
    state.onCardShowed(userData1);
    state.onButtonRelease();

    state.onCardShowed(userData2);
    EXPECT_FALSE(state.getRelayState());

    EXPECT_TRUE(users.find(userData2));
}

TEST(StateTest, AddAdmin) {
    resetEeprom();
    auto users = Users{};
    auto state = State{users};

    EXPECT_TRUE(users.add(userData1, true));

    EXPECT_FALSE(state.getRelayState());

    state.onButtonPress();
    state.onCardShowed(userData1);
    state.onButtonRelease();
    EXPECT_FALSE(state.getRelayState());

    state.onButtonPress();
    state.onButtonRelease();
    EXPECT_FALSE(state.getRelayState());

    state.onCardShowed(userData2);
    EXPECT_FALSE(state.getRelayState());

    EXPECT_TRUE(users.find(userData2));
    EXPECT_TRUE(users.findAdmin(userData2));
}

TEST(StateTest, RemoveUser) {
    resetEeprom();
    auto users = Users{};
    auto state = State{users};

    EXPECT_TRUE(users.add(userData1, true));
    EXPECT_TRUE(users.add(userData2, false));

    state.onButtonPress();
    state.onCardShowed(userData1);
    state.onButtonRelease();

    state.onButtonPress();
    state.onButtonRelease();

    state.onButtonPress();
    state.onButtonRelease();
    EXPECT_FALSE(state.getRelayState());

    state.onCardShowed(userData2);
    EXPECT_FALSE(state.getRelayState());

    EXPECT_FALSE(users.find(userData2));
}

TEST(StateTest, PreventFromRemoveOneSelf) {
    resetEeprom();
    auto users = Users{};
    auto state = State{users};

    EXPECT_TRUE(users.add(userData1, true));
    EXPECT_TRUE(users.add(userData2, false));

    state.onButtonPress();
    state.onCardShowed(userData1);
    state.onButtonRelease();

    state.onButtonPress();
    state.onButtonRelease();

    state.onButtonPress();
    state.onButtonRelease();
    EXPECT_FALSE(state.getRelayState());

    state.onCardShowed(userData1);

    EXPECT_TRUE(users.find(userData2));
}

TEST(StateTest, MakeFirstUserAdmin) {
    resetEeprom();
    auto users = Users{};
    auto state = State{users};
    state.init();

    state.onCardShowed(userData1);

    EXPECT_TRUE(users.find(userData1));
    EXPECT_TRUE(users.findAdmin(userData1));
}
