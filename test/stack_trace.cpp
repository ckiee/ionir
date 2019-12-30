#include <iostream>
#include <ionir/reporting/stack_trace.h>
#include <ionir/reporting/notice.h>
#include <ionir/const/const_name.h>
#include <ionir/misc/console_color.h>
#include "test_api/constant.h"
#include "pch.h"

using namespace ionir;

// TODO: Move to Test API.
inline Notice makeNotice() {
    return Notice(NoticeContext(ConstName::anonymous, 1, 2), NoticeType::Error, test::constant::foobar);
}

TEST(StackTraceTest, Initialize) {
    StackTrace stackTrace = StackTrace();
    Stack<Notice> &innerStack = stackTrace.unwrap();

    EXPECT_TRUE(innerStack.isEmpty());

    std::stack<Notice> stack = {};

    stack.push(makeNotice());
    stackTrace = StackTrace(stack);
    innerStack = stackTrace.unwrap();

    EXPECT_FALSE(innerStack.isEmpty());
    EXPECT_EQ(innerStack.size(), 1);
}

TEST(StackTraceTest, Push) {
    StackTrace stackTrace = StackTrace();
    Stack<Notice> &innerStack = stackTrace.unwrap();
    Notice notice = makeNotice();

    stackTrace.push(notice);

    EXPECT_FALSE(innerStack.isEmpty());
    EXPECT_EQ(innerStack.size(), 1);

    // TODO: Extract & compare notice. (At this point, .getStack() hasn't been tested yet).
}

TEST(StackTraceTest, GetStack) {
    // TODO
}

TEST(StackTraceTest, isEmpty) {
    // TODO
}

TEST(StackTraceTest, Size) {
    // TODO
}

// TODO: Need to verify that order after invoking Make() is preserved.
TEST(StackTraceTest, Make) {
    StackTrace stackTrace = StackTrace();

    stackTrace.push(makeNotice());

    std::optional<std::string> result = stackTrace.make();

    // TODO: Finish implementing test.
    std::cout << ("Make result (" + std::to_string(result->length()) + " chars): ") << ConsoleColor::red(*result);
}
