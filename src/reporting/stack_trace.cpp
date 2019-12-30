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

    std::optional<std::string> StackTrace::make() {
        if (this->isEmpty()) {
            return std::nullopt;
        }

        std::stringstream stackTrace;
        Stack<Notice> items = Stack<Notice>();
        bool prime = true;

        while (!this->value.isEmpty()) {
            std::optional<Notice> notice = this->value.pop();

            // Notice must contain a value at this point.
            if (!notice.has_value()) {
                throw std::runtime_error("Unexpected notice to be null");
            }
            else if (!prime) {
                stackTrace << "\tat ";
            }

            // Append the notice's individual trace to the stack trace.
            stackTrace << notice->createTrace() << std::endl;

            // Save notice for re-population later.
            items.push(*notice);

            // Raise the prime flag to take effect upon next iteration.
            prime = false;
        }

        // Re-populate items.
        while (!items.isEmpty()) {
            this->push(items.pop());
        }

        // Return the resulting stack trace string.
        return stackTrace.str();
    }

}
