#include "archive.h"
#include "testclasses.h"
#include "users.h"
#include <gtest/gtest.h>

constexpr auto userData1 =
    UIDt{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
constexpr auto userData2 =
    UIDt{0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

TEST(UserTest, SingleUser) {
    resetEeprom();
    auto users = Users{};

    EXPECT_FALSE(users.find(userData1));

    users.add(userData1);

    EXPECT_TRUE(users.find(userData1));

    EXPECT_FALSE(users.findAdmin(userData1));

    users.add(userData1, true);

    EXPECT_TRUE(users.findAdmin(userData1));
}

TEST(UserTest, MultipleUsers) {
    resetEeprom();
    auto users = Users{};

    EXPECT_FALSE(users.find(userData1));
    EXPECT_FALSE(users.find(userData2));
    users.add(userData1);
    EXPECT_TRUE(users.find(userData1));
    users.add(userData2);
    EXPECT_TRUE(users.find(userData2));

    users.del(userData2);
    EXPECT_FALSE(users.find(userData2));
}

TEST(UserTest, IsEmpty) {
    resetEeprom();
    auto users = Users{};

    EXPECT_TRUE(users.isEmpty());

    users.add(userData1);

    EXPECT_FALSE(users.isEmpty());
}

TEST(UserTest, Count) {
    resetEeprom();
    auto users = Users{};

    EXPECT_EQ(users.count(), 0);

    users.add(userData1);

    EXPECT_EQ(users.count(), 1);

    users.add(userData1); // Same user

    EXPECT_EQ(users.count(), 1);

    users.add(userData2); // Same user

    EXPECT_EQ(users.count(), 2);
}

// Main function running all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
