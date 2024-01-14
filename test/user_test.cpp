#include "users.h"
#include <gtest/gtest.h>

constexpr auto userData1 =
    UIDt{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
constexpr auto userData2 =
    UIDt{0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

TEST(UserTest, SingleUser) {
    auto users = Users{};

    EXPECT_FALSE(users.find(userData1));

    users.add(userData1);

    EXPECT_TRUE(users.find(userData1));

    EXPECT_FALSE(users.findAdmin(userData1));

    users.add(userData1, true);

    EXPECT_TRUE(users.findAdmin(userData1));
}

TEST(UserTest, MultipleUsers) {
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

// Main function running all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
