#include <string>
#include <vector>
#include <map>
#include "Token.h"
#include "Misc/TokenConstants.h"
#include "Misc/Util.h"
#include "Misc/Regex.h"

class Lexer
{
private:
    std::string input;

    uint32_t length;

    uint32_t index;

	TokenConstants constants;

protected:
    char get()
    {
        return this->input[this->index];
    }

    std::string getAsString()
    {
        return std::string(1, this->get());
    }

    uint32_t getIndex()
    {
        return this->index;
    }

    uint32_t getLength()
    {
        return this->length;
    }

    void resetIndex()
    {
        this->index = 0;
    }

    int setIndex(uint32_t index)
    {
        // Keep index within bounds.
        if (index < 0)
        {
            index = 0;
        }
        else if (index >= this->length)
        {
            index = this->length - 1;
        }

        this->index = index;

        return this->index;
    }

    std::string getInput()
    {
        return this->input;
    }

    int skip(uint32_t amount)
    {
        return this->setIndex(this->index + amount);
    }

	bool matchExpression(Token *token, TokenType type, std::regex regex)
	{
		// Substring from the current index to get the viable matching string.
		std::string input = this->input.substr(this->index);
		std::smatch match;

		std::regex_search(input, match, regex);

		// If successful, return a new token with different value and type.
		if (match.length() > 0) {
			std::string value = match[0];

			// Modify the result.
			token = new Token(type, value, token->getStartPosition());

			// Skip the capture value's amount.
			this->skip(value.length());

			// Return true to indicate success.
			return true;
		}

		// Return false to indicate failure.
		return false;
	}

    Token next()
    {
        Token *token = new Token(TokenType::Unknown, this->getAsString(), this->index);
        char character = this->get();

        // Ignore whitespace.
        if (isspace(character))
        {
            while (isspace(this->get()))
            {
                this->skip(1);
            }
        }

		std::map<char, TokenType> symbolMap = this->constants.getSymbols();
		std::map<char, TokenType>::iterator symbolIterator;
		std::string tokenValue = token->getValue();

		for (symbolIterator = symbolMap.begin(); symbolIterator != symbolMap.end(); symbolIterator++) {
			if (tokenValue[0] == symbolIterator->first) {
				// Create the initial regex.
				std::regex regex = std::regex(std::string(1, symbolIterator->first));

				// If the match starts with a letter, modify the regex to force either whitespace or EOF at the end.
				if (std::regex_match(tokenValue, Regex::identifier)) {
					// TODO: Missing initial part to be regex escaped.
					regex = Util::createRegex(symbolIterator->first + "([^a-zA-Z_0-9])");
				}

				if (this->matchExpression(token, symbolIterator->second, regex)) {
					// Reduce the position.
					// TODO: Causing problems, works when commented HERE.
					//this.SetPosition(this.Position - token.Value.Length - pair.Key.Length);

					// Skim the last character off.
					token = new Token(token->getType(), std::string(1, symbolIterator->first), token->getStartPosition());

					// Return the token.
					return *token;
				}
			}
		}

		std::map<std::regex, TokenType> complexMap = this->constants.getComplex();
		std::map<std::regex, TokenType>::iterator complexIterator;

		// Complex types support.
		for (complexIterator = complexMap.begin(); complexIterator != complexMap.end(); complexIterator++) {
			// If it matches, return the token (already modified by the function).
			if (this->matchExpression(token, complexIterator->second, complexIterator->first)) {
				return *token;
			}
		}

		// At this point the token was not identified. Skip over any captured value.
		this->skip(tokenValue.length());

		// Return the default token. The token type defaults to unknown.
        return *token;
    }

public:
    Lexer(std::string input) : constants()
    {
        this->input = input;
        this->length = this->input.length();

        if (!this->length)
        {
            throw "Input must be a string with one or more character(s)";
        }

        this->resetIndex();
    }

    std::vector<Token> tokenize()
    {
        // Reset index to avoid carrying over previous information.
        this->resetIndex();

		// TODO: Should be a list, then converted to a vector.
        std::vector<Token> tokens = {};

		// Iterate through all possible tokens.
		for (Token token = this->next(); this->index < this->length - 1; token = this->next()) {
			if (token.getType() == TokenType::Unknown) {
				// TODO
				std::cout << "Warning: Unknown token encountered";
			}

			// Append the token to the result.
			tokens.push_back(token);
		}

        return tokens;
    }
};
