#include <set>
#include <string>
#include <ionir/const/const.h>
#include <ionir/container/set.h>
#include "pch.h"

using namespace ionir;

const int value = 1;

TEST(SetContainerTest, Initialize) {
    Set<std::string> set = Set<std::string>({
        Const::foobar
    });

    std::set<std::string> underlyingSet = set.unwrap();

    EXPECT_EQ(underlyingSet.size(), 1);
    EXPECT_TRUE(underlyingSet.find(Const::foobar) != underlyingSet.end());
}

TEST(SetContainerTest, Insert) {
    Set<std::string> set = Set<std::string>();
    std::set<std::string> &underlyingSet = set.unwrap();

    EXPECT_EQ(underlyingSet.size(), 0);
    EXPECT_TRUE(set.insert(Const::foobar));
    EXPECT_EQ(underlyingSet.size(), 1);
    EXPECT_FALSE(set.insert(Const::foobar));
    EXPECT_EQ(underlyingSet.size(), 1);
}

TEST(SetContainerTest, Contains) {
    Set<std::string> set = Set<std::string>({
        Const::foo
    });

    EXPECT_TRUE(set.contains(Const::foo));
    EXPECT_FALSE(set.contains(Const::bar));
}

TEST(SetContainerTest, Clear) {
    Set<std::string> set = Set<std::string>({
        Const::foo
    });

    EXPECT_EQ(set.size(), 1);
    set.clear();
    EXPECT_EQ(set.size(), 0);
}

// TODO: Add more tests.
