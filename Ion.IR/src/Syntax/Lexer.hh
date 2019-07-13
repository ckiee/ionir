#include <string>
#include <vector>
#include <map>
#include "Token.hh"
#include "Misc/TokenConstants.hh"

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

    Token next()
    {
        if (this->index == this->length)
        {
            return nullptr;
        }

        Token *token = new Token(TokenType::Unknown, this->getAsString());
        char character = this->get();

        // Ignore whitespace.
        if (isspace(character))
        {
            while (isspace(this->get()))
            {
                this->skip(1);
            }
        }

		std::map<char, TokenType> symbols = this->constants.getSymbols();
		std::map<char, TokenType>::iterator i;

		for (i = symbols.begin(); i != symbols.end(); i++) {
			if ((*token).getValue().rfind(i->first(), 0) == 0) {
				// TODO
			}
		}

        // TODO: Complete implementation.

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

        std::vector<Token> tokens = {};

        // TODO: Complete implementation.

        return tokens;
    }
};
