#pragma once

#include <type_traits>
#include <exception>
#include <optional>
#include <stack>
#include "misc/wrapper.h"

namespace ionir {
    template<typename T>
    class Stack : public Wrapper<std::stack<T>> {
    public:
        Stack(std::stack<T> value = std::stack<T>())
                : Wrapper<std::stack<T>>(value) {
            //
        }

        ~Stack() {
            // TODO: Is there need clear an std::shared_ptr stack be?
            this->clear();
        }

        void push(T item) {
            this->value.push(item);
        }

        T pop() {
            std::optional<T> result = this->tryPop();

            if (!result.has_value()) {
                throw std::out_of_range("No more items in stack to pop");
            }

            return *result;
        }

        T popOr(T alternative) {
            std::optional<T> existingItem = this->tryPop();

            if (existingItem.has_value()) {
                return existingItem;
            }

            return alternative;
        }

        std::optional<T> tryPop() {
            // Underlying stack contains no more items to pop.
            if (this->value.empty()) {
                return std::nullopt;
            }

            T result = this->value.top();

            this->value.pop();

            return result;
        }

        bool isEmpty() const {
            return this->value.empty();
        }

        void clear() {
            while (!this->isEmpty()) {
                std::optional<T> item = this->tryPop();

                if (item.has_value() && std::is_pointer<T>::value) {
                    item.reset();
                }
            }
        }
    };
}
