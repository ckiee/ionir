#pragma once

namespace ionir
{
class Parser
{
protected:
    TokenStream stream;

    bool withinRange(long value, long from, long to);

    void expect(TokenType type);

public:
    Parser(TokenStream stream);

    /**
     * Parses a literal integer in the form of
     * long (or integer 64).
     */
    LiteralInteger *parseInteger();

    Extern *parseExtern();
};
} // namespace ionir
