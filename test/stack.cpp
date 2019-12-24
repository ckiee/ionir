#include <optional>
#include "misc/stack.h"
#include "pch.h"

using namespace ionir;

TEST(StackTest, Push) {
    Stack<int> stack = Stack<int>();

    stack.push(0);

    EXPECT_EQ(stack.unwrap().top(), 0);
}

TEST(StackTest, IsEmpty) {
    Stack<int> stack = Stack<int>();

    EXPECT_TRUE(stack.isEmpty());
    stack.push(0);
    EXPECT_FALSE(stack.isEmpty());
}

TEST(StackTest, TryPop) {
    Stack<int> stack = Stack<int>();

    stack.push(0);

    std::optional<int> result = stack.tryPop();

    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(*result, 0);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, Pop) {
    Stack<int> stack = Stack<int>();

    stack.push(0);

    int result;

    EXPECT_NO_THROW(result = stack.pop());
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, PopThrows) {
    Stack<int> stack = Stack<int>();

    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackTest, Clear) {
    Stack<int> stack = Stack<int>();

    stack.push(0);
    EXPECT_FALSE(stack.isEmpty());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}
