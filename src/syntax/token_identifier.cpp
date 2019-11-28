#include <algorithm>
#include "token_identifier.h"

namespace ionir
{
bool TokenIdentifier::contains(std::vector<TokenType> subject, TokenType item)
{
    return std::find(subject.begin(), subject.end(), item) != subject.end();
}

TokenIdentifier::TokenIdentifier(TokenConstants *constants) : constants(constants)
{
}

bool TokenIdentifier::isSymbol(TokenType type)
{
    return this->contains(this->constants->getSymbols(), type);
}

bool TokenIdentifier::isNumeric(TokenType type)
{
    // TODO: Need to define numeric group.
    return false;
}

bool TokenIdentifier::isOperator(TokenType type)
{
    return this->contains(this->constants->getOperators(), type);
}
} // namespace ionir
