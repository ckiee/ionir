#pragma once

#include <memory>
#include <type_traits>
#include <exception>
#include <optional>
#include <stack>
#include "misc/wrapper.h"

namespace ionir
{
template <typename T>
class Stack : public Wrapper<std::stack<std::unique_ptr<T>>>
{
public:
    Stack(std::stack<std::unique_ptr<T>> value = std::stack<std::unique_ptr<T>>())
        : Wrapper(value)
    {
        //
    }

    ~Stack()
    {
        this->clear();
    }

    void push(T item)
    {
        this->value.push(std::make_unique<T>(item));
    }

    std::unique_ptr<T> pop()
    {
        std::optional<std::unique_ptr<T>> result = this->tryPop();

        if (!result.has_value())
        {
            throw std::out_of_range("No more items in stack to pop");
        }

        return *result;
    }

    std::unique_ptr<T> popOr(std::unique_ptr<T> alternative)
    {
        std::optional<std::unique_ptr<T>> existingItem = this->tryPop();

        if (existingItem.has_value())
        {
            return existingItem;
        }

        return alternative;
    }

    std::optional<std::unique_ptr<T>> tryPop()
    {
        // Underlying stack contains no more items to pop.
        if (this->value.empty())
        {
            return std::nullopt;
        }

        std::unique_ptr<T> result = this->value.top();

        this->value.pop();

        return result;
    }

    bool isEmpty() const
    {
        return this->value.empty();
    }

    void clear()
    {
        while (!this->isEmpty())
        {
            std::optional<std::unique_ptr<T>> item = this->tryPop();

            // TODO: Is value check necessary?
            if (item.has_value())
            {
                item.reset();
            }
        }
    }
};
} // namespace ionir
