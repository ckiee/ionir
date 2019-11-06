#pragma once

namespace ionir
{
class Lexer : public Generator<Token>
{
private:
    std::string input;

    size_t length;

    size_t index;

    TokenConstants constants;

    std::map<std::string, TokenType> simpleIdentifiers;

    std::map<std::string, TokenType>::iterator simpleIterator;

    std::vector<std::pair<std::regex, TokenType>> complexIdentifiers;

    std::vector<std::pair<std::regex, TokenType>>::iterator complexIterator;

protected:
    char getChar() const;

    std::string getCharAsString() const;

    size_t getLength() const;

    size_t setIndex(size_t index);

    size_t skip(size_t amount = 1);

    bool matchExpression(Token *token, TokenType type, std::regex regex);

    void processWhitespace();

public:
    size_t getIndex() const;

    virtual void begin();

    /**
     * Whether the index has not reached the input's length.
     */
    virtual bool hasNext() const;

    /**
     * Process the next token.
     */
    virtual std::optional<Token> next();

    Lexer(std::string input);

    std::string getInput() const;

    std::vector<Token> tokenize();
};
} // namespace ionir
