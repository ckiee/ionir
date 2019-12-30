#include <sstream>
#include <ionir/reporting/stack_trace.h>

namespace ionir {
    StackTrace::StackTrace() : Wrapper<Stack<Notice>>({}) {
        //
    }

    StackTrace::StackTrace(Stack<Notice> value) : Wrapper<Stack<Notice>>(value) {
        //
    }

    StackTrace::StackTrace(std::stack<Notice> value) : StackTrace(Stack<Notice>(value)) {
        //
    }

    Stack<Notice> StackTrace::getStack() const {
        return this->value;
    }

    void StackTrace::push(Notice notice) {
        this->value.push(notice);
    }

    bool StackTrace::isEmpty() const {
        return this->value.isEmpty();
    }

    std::string StackTrace::make() {
        std::stringstream stackTrace;

        while (!this->value.isEmpty()) {
            std::optional<Notice> notice = this->value.pop();

            // Notice must contain a value at this point.
            if (!notice.has_value()) {
                throw std::runtime_error("Unexpected notice to be null");
            }

            // Append the notice's individual trace to the stack trace.
            stackTrace << "\tat " << notice->createTrace() << std::endl;

            // Push notice back in, re-populating stack.
            this->value.push(*notice);
        }

        return stackTrace.str();
    }

}
