#include "lexer.h"

namespace ionir
{
char Lexer::getChar() const
{
    // Return null character if reached end of input.
    if (!this->hasNext())
    {
        return '\0';
    }

    // Otherwise, return the corresponding character.
    return this->input[this->index];
}

std::string Lexer::getCharAsString() const
{
    return std::string(1, this->getChar());
}

size_t Lexer::getLength() const
{
    return this->length;
}

size_t Lexer::setIndex(size_t index)
{
    // Index cannot be negative.
    if (index < 0)
    {
        index = 0;
    }
    // Keep index within bounds.
    else if (index >= this->length)
    {
        index = this->length;
    }

    this->index = index;

    return this->index;
}

size_t Lexer::skip(size_t amount)
{
    return this->setIndex(this->index + amount);
}

bool Lexer::matchExpression(Token *token, TokenType type, std::regex regex)
{
    // Substring from the current index to get the viable matching string.
    std::string input = this->input.substr(this->index);
    std::smatch match;

    bool success = std::regex_search(input, match, regex);

    // If successful, return a new token with different value and type.
    if (success)
    {
        // Extract the captured value from the match.
        std::string value = match[0];

        // Modify the result.
        *token = Token(type, value, token->getStartPosition());

        // Skip the capture value's amount.
        this->skip(value.length());

        // Return true to indicate success.
        return true;
    }

    // Return false to indicate failure.
    return false;
}

void Lexer::processWhitespace()
{
    // Ignore whitespace.
    while (isspace(this->getChar()))
    {
        this->skip();
    }
}

Lexer::Lexer(std::string input) : constants()
{
    this->input = input;
    this->length = this->input.length();

    // Input string must contain at least one character.
    if (!this->length || this->length < 1)
    {
        throw std::invalid_argument("Input must be a string with one or more character(s)");
    }

    // Initialize local simple & complex identifiers map.
    this->simpleIdentifiers = this->constants.getSimpleIdentifiers();
    this->complexIdentifiers = this->constants.getComplexIdentifiers();

    // Reset the index, setting its initial value.
    this->begin();
}

size_t Lexer::getIndex() const
{
    return this->index;
}

void Lexer::begin()
{
    this->index = 0;
}

bool Lexer::hasNext() const
{
    return this->index < this->length;
}

std::optional<Token> Lexer::next()
{
    // No more possible tokens to retrieve.
    if (!this->hasNext())
    {
        return std::nullopt;
    }

    // Set the initial Token buffer as Unknown.
    Token token = Token(TokenType::Unknown, this->getCharAsString(), this->index);
    char character = this->getChar();

    // Ignore whitespace if applicable.
    this->processWhitespace();

    std::string tokenValue = token.getValue();

    for (this->simpleIterator = simpleIdentifiers.begin(); this->simpleIterator != simpleIdentifiers.end(); this->simpleIterator++)
    {
        // Test the first letter of the subject to continue.
        if (tokenValue[0] == this->simpleIterator->first[0])
        {
            // Produce a Regex instance to match the exact value of the simple identifier. It is important that the initial value is escaped of any Regex special characters.
            std::regex regex = Util::createPureRegex(this->simpleIterator->first);

            // If the match starts with a letter, modify the regex to force either whitespace or EOF at the end.
            if (std::regex_match(tokenValue, Regex::identifier))
            {
                // Modify the plain regex to meet requirements at the end.
                regex = std::regex(this->simpleIterator->first + "(?:\\s|$)");
            }

            if (this->matchExpression(&token, this->simpleIterator->second, regex))
            {
                // Reduce the position.
                // TODO: Causing problems, works when commented HERE.
                //this.SetPosition(this.Position - token.Value.Length - pair.Key.Length);

                // Skim the last character off.
                token = Token(token.getType(), this->simpleIterator->first, token.getStartPosition());

                // Return the token, no need to skip its value.
                return token;
            }
        }
    }

    // Begin iteration through complex identifiers.
    for (this->complexIterator = this->complexIdentifiers.begin(); this->complexIterator != this->complexIdentifiers.end(); this->complexIterator++)
    {
        // If it matches, return the token (already modified by the matchExpression function).
        if (this->matchExpression(&token, this->complexIterator->second, this->complexIterator->first))
        {
            return token;
        }
    }

    // At this point the token was not identified. Skip over any captured value.
    this->skip(tokenValue.length());

    // Return the default token. The token type defaults to unknown.
    return token;
}

std::string Lexer::getInput() const
{
    return this->input;
}

std::vector<Token> Lexer::scan()
{
    // Reset index to avoid carrying over previous information.
    this->begin();

    // TODO: Should be a list, then converted to a vector.
    std::vector<Token> tokens = {};

    std::optional<Token> token;

    while (this->hasNext())
    {
        token = this->next();

        // No more tokens to process.
        if (!token.has_value())
        {
            break;
        }

        // Display a warning if the token's type is unknown.
        if ((*token).getType() == TokenType::Unknown)
        {
            // TODO: Issue warning instead of plain cout.
            std::cout << "Warning: Unknown token encountered" << std::endl;
        }

        // Append the token to the result.
        tokens.push_back(*token);
    }

    return tokens;
}
} // namespace ionir
