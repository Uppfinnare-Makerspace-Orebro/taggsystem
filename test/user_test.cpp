#include "archive.h"
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

TEST(UserTest, Archive) {
    {
        auto users = Users{};

        EXPECT_FALSE(users.isChanged());

        users.add(userData1);
        EXPECT_TRUE(users.isChanged());

        users.add(userData2, true);
        EXPECT_TRUE(users.isChanged());

        auto arch = OutArchive{};
        users.save(arch);

        EXPECT_FALSE(users.isChanged());
    }
    {
        auto users = Users{};
        auto arch = InArchive{};
        users.load(arch);

        EXPECT_FALSE(users.isChanged());

        EXPECT_TRUE(users.find(userData1));
        EXPECT_FALSE(users.findAdmin(userData1));
        EXPECT_TRUE(users.findAdmin(userData2));
    }
}

TEST(UserTest, IsEmpty) {
    auto users = Users{};

    EXPECT_TRUE(users.isEmpty());

    users.add(userData1);

    EXPECT_FALSE(users.isEmpty());
}

TEST(UserTest, Count) {
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
