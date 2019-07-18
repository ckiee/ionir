#pragma once

class Listener
{
private:
    std::stack<std::string> ascentStack;

    std::stack<std::string> descentStack;

protected:
    std::stack<std::string> getAscentStack()
    {
        return this->ascentStack;
    }

    std::stack<std::string> getDescentStack()
    {
        return this->descentStack;
    }

public:
    void enterRule(std::string ruleName)
    {
        this->descentStack.push(ruleName);
    }

    void exitRule()
    {
        this->descentStack.pop();

        // TODO: Methods.
        std::string ruleName = this->descentStack.top();

        this->ascentStack.push("Exit" + ruleName);
        this->ascentStack.push("Enter" + ruleName);
    }

    void listen()
    {
        // TODO: Implement.
    }
};
