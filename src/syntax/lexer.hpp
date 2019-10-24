#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "../syntax/token.h"
#include "../misc/token_constants.hpp"
#include "../misc/util.hpp"
#include "../misc/regex.hpp"

namespace ionir
{
class Lexer
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
    char getChar()
    {
        return this->input[this->index];
    }

    std::string getCharAsString()
    {
        return std::string(1, this->getChar());
    }

    size_t getLength()
    {
        return this->length;
    }

    void resetIndex()
    {
        this->index = 0;
    }

    size_t setIndex(size_t index)
    {
        // Index cannot be negative.
        if (index < 0)
        {
            index = 0;
        }
        // Keep index within bounds.
        else if (index > this->length - 1)
        {
            index = this->length - 1;
        }

        this->index = index;

        return this->index;
    }

    size_t skip(size_t amount = 1)
    {
        return this->setIndex(this->index + amount);
    }

    bool matchExpression(Token *token, TokenType type, std::regex regex)
    {
        // Substring from the current index to get the viable matching string.
        std::string input = this->input.substr(this->index);
        std::smatch match;

        bool success = std::regex_search(input, match, regex);

        std::cout << "@matchExpression: Test input :: ' " << input << " ' (len:" << input.length() << ") :: success:" << success << std::endl;

        // If successful, return a new token with different value and type.
        if (success)
        {
            // Extract the captured value from the match.
            std::string value = match[0];

            // Modify the result.
            *token = Token(type, value, token->getStartPosition());

            std::cout << "Skipping len: " << value.length() << " (" << value << ")" << std::endl;

            // Skip the capture value's amount.
            this->skip(value.length());

            // Return true to indicate success.
            return true;
        }

        // Return false to indicate failure.
        return false;
    }

    void processIteration(std::vector<Token> tokens, Token token)
    {
        std::cout << "Loop ; " << this->index << std::endl;

        if (token.getType() == TokenType::Unknown)
        {
            // TODO: Issue warning instead of plain cout.
            std::cout << "Warning: Unknown token encountered" << std::endl;
        }

        std::cout << "Got token :: ~~> " << token << std::endl;

        // Append the token to the result.
        tokens.push_back(token);
    }

    void processWhitespace()
    {
        // Ignore whitespace.
        while (isspace(this->getChar()))
        {
            this->skip();
        }
    }

public:
    size_t getIndex()
    {
        return this->index;
    }

    Token next()
    {
        std::cout << "[!] next" << std::endl;

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

                std::cout << "Using initial regex: " << Util::escapeRegex(this->simpleIterator->first) << std::endl;

                // If the match starts with a letter, modify the regex to force either whitespace or EOF at the end.
                if (std::regex_match(tokenValue, Regex::identifier))
                {
                    // Modify the plain regex to meet requirements at the end.
                    regex = std::regex(this->simpleIterator->first + "(?:\\s|$)");
                    std::cout << "---- REGEX HAS BEEN MODIFIED ---" << std::endl;
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

    Lexer(std::string input) : constants()
    {
        this->input = input;
        this->length = this->input.length();

        if (!this->length || this->length < 1)
        {
            throw "Input must be a string with one or more character(s)";
        }

        // Initialize local simple & complex identifiers map.
        this->simpleIdentifiers = this->constants.getSimpleIdentifiers();
        this->complexIdentifiers = this->constants.getComplexIdentifiers();

        // Reset the index, setting its initial value.
        this->resetIndex();
    }

    std::string getInput()
    {
        return this->input;
    }

    std::vector<Token> tokenize()
    {
        // Reset index to avoid carrying over previous information.
        this->resetIndex();

        // TODO: Should be a list, then converted to a vector.
        std::vector<Token> tokens = {};

        Token initialToken = Token(TokenType::Unknown, "", this->index);

        // Iterate through all possible tokens.
        for (Token token = this->next(); this->index < this->length - 1; token = this->next())
        {
            std::cout << "Loop ..."
                      << "@" << this->index << " until >= " << this->length - 1 << std::endl;
            this->processIteration(tokens, token);

            break;
        }

        // Iterate over the last token.
        Token lastToken = this->next();

        this->processIteration(tokens, lastToken);

        return tokens;
    }
};
} // namespace ionir
