#include <ionir/test/util.h>
#include <ionir/test/compare.h>
#include <ionir/test/filesystem.h>
#include <ionir/test/const.h>

using namespace ionir::test;

TEST(TestApiTest, TrimSimpleString) {
    EXPECT_EQ(util::trim(" test "), "test");
}

TEST(TestApiTest, TrimString) {
    EXPECT_EQ(util::trim("  hello world  "), "hello world");
}

TEST(TestApiTest, LeftTrimString) {
    EXPECT_EQ(util::leftTrim("  hello world  "), "hello world  ");
}

TEST(TestApiTest, RightTrimString) {
    EXPECT_EQ(util::rightTrim("  hello world  "), "  hello world");
}

TEST(TestApiTest, CompareStrings) {
    // Compare strings without extra spacing.
    EXPECT_TRUE(compare::strings("test", "test"));
    EXPECT_FALSE(compare::strings("hello", "world"));

    // Compare strings with extra spacing.
    EXPECT_TRUE(compare::strings("  test  ", "test"));
    EXPECT_TRUE(compare::strings("test", "  test  "));
}

TEST(TestApiTest, JoinPaths) {
    EXPECT_EQ(fs::joinPaths("foo", "bar"), "foo/bar");
}

TEST(TestApiTest, FileExists) {
    EXPECT_TRUE(fs::exists(__FILE__));
    EXPECT_FALSE(fs::exists(".__madeup.file"));
}

TEST(TestApiTest, ResolvePath) {
    EXPECT_TRUE(fs::exists(fs::resolvePath("README.md")));
}

// TODO: Tests for resolveTestPath(...) missing.

// TODO: 'input' folder was removed.
//TEST(TestApiTest, ReadFileContents) {
//    std::optional<std::string> contents = fs::readFileContents(fs::resolvePath("test/input/test.txt"));
//
//    EXPECT_TRUE(contents.has_value());
//    EXPECT_EQ(*contents, ionir::test::constant::foobar + "\n");
//}
