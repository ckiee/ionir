#include <string>
#include "../include/ionir/const/const.h"
#include "../include/ionir/container/map.h"
#include "pch.h"

using namespace ionir;

const int value = 1;

TEST(MapContainerTest, Initialize) {
    Map<std::string, int> map = Map<std::string, int>({
        {Const::foobar, value}
    });

    EXPECT_EQ(map.unwrap().size(), 1);
    EXPECT_EQ(map.unwrap()[Const::foobar], value);
}

TEST(MapContainerTest, Contains) {
    Map<std::string, int> map = Map<std::string, int>({
        {Const::foobar, value}
    });

    EXPECT_TRUE(map.contains(Const::foobar));
}

TEST(MapContainerTest, Insert) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_TRUE(map.insert(Const::foobar, value));
    EXPECT_TRUE(map.contains(Const::foobar));
    EXPECT_EQ(map.unwrap()[Const::foobar], value);
}

TEST(MapContainerTest, Lookup) {
    Map<std::string, int> map = Map<std::string, int>({
        {Const::foobar, value}
    });

    EXPECT_EQ(map.lookup(Const::foobar), value);
}

TEST(MapContainerTest, LookupOr) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_EQ(map.lookupOr(Const::foobar, value), value);
}

TEST(MapContainerTest, Size) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_EQ(map.size(), 0);

    map.insert(Const::foobar, value);

    EXPECT_EQ(map.size(), 1);
}

TEST(MapContainerTest, Remove) {
    Map<std::string, int> map = Map<std::string, int>({
        {Const::foobar, value}
    });

    EXPECT_EQ(map.size(), 1);
    EXPECT_TRUE(map.remove(Const::foobar));
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.remove(Const::foobar));
}
