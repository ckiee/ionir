#include <set>
#include <ionir/container/set.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

const int value = 1;

TEST(SetContainerTest, Initialize) {
    Set<std::string> set = Set<std::string>({test::constant::foobar});

    std::set<std::string> underlyingSet = set.unwrap();

    EXPECT_EQ(underlyingSet.size(), 1);
    EXPECT_TRUE(underlyingSet.find(test::constant::foobar) != underlyingSet.end());
}

TEST(SetContainerTest, Insert) {
    Set<std::string> set = Set<std::string>();
    std::set<std::string> &underlyingSet = set.unwrap();

    EXPECT_EQ(underlyingSet.size(), 0);
    EXPECT_TRUE(set.insert(test::constant::foobar));
    EXPECT_EQ(underlyingSet.size(), 1);
    EXPECT_FALSE(set.insert(test::constant::foobar));
    EXPECT_EQ(underlyingSet.size(), 1);
}

TEST(SetContainerTest, Contains) {
    Set<std::string> set = Set<std::string>({test::constant::foo});

    EXPECT_TRUE(set.contains(test::constant::foo));
    EXPECT_FALSE(set.contains(test::constant::bar));
}

TEST(SetContainerTest, Clear) {
    Set<std::string> set = Set<std::string>({test::constant::foo});

    EXPECT_EQ(set.size(), 1);
    set.clear();
    EXPECT_EQ(set.size(), 0);
}

// TODO: Add more tests.
