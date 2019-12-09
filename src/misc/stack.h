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
class Stack : public Wrapper<std::stack<std::shared_ptr<T>>>
{
public:
    Stack(std::stack<std::shared_ptr<T>> value = std::stack<std::shared_ptr<T>>())
        : Wrapper<std::stack<std::shared_ptr<T>>>(value)
    {
        //
    }

    ~Stack()
    {
        this->clear();
    }

    void push(T item)
    {
        this->value.push(std::make_shared<T>(item));
    }

    std::shared_ptr<T> pop()
    {
        std::optional<std::shared_ptr<T>> result = this->tryPop();

        if (!result.has_value())
        {
            throw std::out_of_range("No more items in stack to pop");
        }

        return *result;
    }

    std::shared_ptr<T> popOr(std::shared_ptr<T> alternative)
    {
        std::optional<std::shared_ptr<T>> existingItem = this->tryPop();

        if (existingItem.has_value())
        {
            return existingItem;
        }

        return alternative;
    }

    std::optional<std::shared_ptr<T>> tryPop()
    {
        // Underlying stack contains no more items to pop.
        if (this->value.empty())
        {
            return std::nullopt;
        }

        std::shared_ptr<T> result = this->value.top();

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
            std::optional<std::shared_ptr<T>> item = this->tryPop();

            // TODO: Is value check necessary?
            if (item.has_value())
            {
                item.reset();
            }
        }
    }
};
} // namespace ionir
