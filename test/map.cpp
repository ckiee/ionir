#include <string>
#include <ionir/const/const.h>
#include "test_api/constant.h"
#include "pch.h"

using namespace ionir;

const int value = 1;

TEST(MapContainerTest, Initialize) {
    Map<std::string, int> map = Map<std::string, int>({{test::constant::foobar, value}});

    EXPECT_EQ(map.unwrap().size(), 1);
    EXPECT_EQ(map.unwrap()[test::constant::foobar], value);
}

TEST(MapContainerTest, Contains) {
    Map<std::string, int> map = Map<std::string, int>({{test::constant::foobar, value}});

    EXPECT_TRUE(map.contains(test::constant::foobar));
}

TEST(MapContainerTest, Insert) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_TRUE(map.insert(test::constant::foobar, value));
    EXPECT_TRUE(map.contains(test::constant::foobar));
    EXPECT_EQ(map.unwrap()[test::constant::foobar], value);
}

TEST(MapContainerTest, Lookup) {
    Map<std::string, int> map = Map<std::string, int>({{test::constant::foobar, value}});

    EXPECT_EQ(map.lookup(test::constant::foobar), value);
}

TEST(MapContainerTest, LookupOr) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_EQ(map.lookupOr(test::constant::foobar, value), value);
}

TEST(MapContainerTest, Size) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_EQ(map.size(), 0);

    map.insert(test::constant::foobar, value);

    EXPECT_EQ(map.size(), 1);
}

TEST(MapContainerTest, Remove) {
    Map<std::string, int> map = Map<std::string, int>({{test::constant::foobar, value}});

    EXPECT_EQ(map.size(), 1);
    EXPECT_TRUE(map.remove(test::constant::foobar));
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.remove(test::constant::foobar));
}
