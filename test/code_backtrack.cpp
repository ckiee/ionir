#include <iostream>
#include <string>
#include <ionir/reporting/code_backtrack.h>
#include "pch.h"

using namespace ionir;

// TODO: Need to verify that order after invoking Make() is preserved.
TEST(CodeBacktractTest, CreateCodeBlockNear) {
    TokenStream stream = TokenStream({
        Token(TokenType::Identifier, "lorem", 0, 0),
        Token(TokenType::Identifier, "ipsum", 5, 1),
        Token(TokenType::Identifier, "dolor", 10, 1),
        Token(TokenType::Identifier, "amet", 15, 1),
        Token(TokenType::Identifier, "testing", 10, 1),
        Token(TokenType::Identifier, "this", 15, 2),
        Token(TokenType::Identifier, "thing", 10, 2),
        Token(TokenType::Identifier, "to", 15, 3),
        Token(TokenType::Identifier, "see", 10, 3),
        Token(TokenType::Identifier, "if", 15, 3),
        Token(TokenType::Identifier, "it", 10, 4),
        Token(TokenType::Identifier, "AFTER", 15, 5),
        Token(TokenType::Identifier, "WARDS", 10, 5),
        Token(TokenType::Identifier, "once", 15, 6),
        Token(TokenType::Identifier, "again", 10, 6),
    });

    CodeBacktrack backtrack = CodeBacktrack(stream);
    auto codeBlock = backtrack.createCodeBlockNear(4);

    if (codeBlock.has_value()) {
        //        std::cout << *codeBlock;
        // TODO: 'codeBlock' is no longer a string.
    }
    else {
        std::cout << "Code block has no value" << std::endl;
    }
}
