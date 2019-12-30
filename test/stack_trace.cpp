#include <iostream>
#include <ionir/reporting/stack_trace.h>
#include <ionir/reporting/notice.h>
#include "test_api/constant.h"
#include "pch.h"

using namespace ionir;

// TODO: Move to Test API.
Notice makeNotice() {
    return Notice(NoticeContext(0, 0, 0), NoticeType::Error, test::constant::foobar);
}

TEST(StackTraceTest, Initialize) {
    StackTrace stackTrace = StackTrace();
    Stack<Notice> innerStack = stackTrace.unwrap();

    EXPECT_TRUE(innerStack.isEmpty());
    EXPECT_EQ(innerStack.size(), 1);

    std::stack<Notice> stack = {};

    stack.push(makeNotice());
    stackTrace = StackTrace(stack);

    EXPECT_FALSE(stackTrace.unwrap().isEmpty());
}

TEST(StackTraceTest, Push) {
    StackTrace stackTrace = StackTrace();
    Stack<Notice> innerStack = stackTrace.unwrap();
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

TEST(StackTraceTest, Make) {
    StackTrace stackTrace = StackTrace();

    stackTrace.push(makeNotice());

    std::string result = stackTrace.make();

    std::cout << result;
}
