#include <string>
#include <vector>
#include "Token.hh"

using namespace std;

class Lexer
{
private:
    std::string input;

protected:
    std::string getInput()
    {
        return this->input;
    }

public:
    Lexer(std::string input)
    {
        this->input = input;
    }

    std::vector<Token> tokenize()
    {
        // TODO
        std::vector<Token> tokens = {};

        return tokens;
    }
};
