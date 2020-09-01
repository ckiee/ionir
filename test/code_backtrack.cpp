#include <string>
#include <ionir/error_handling/code_backtrack.h>
#include "pch.h"

using namespace ionir;

// TODO: Need to verify that order after invoking Make() is preserved.
//TEST(CodeBacktractTest, CreateCodeBlockNear) {
//    TokenStream stream = TokenStream({
//        Token(TokenKind::Identifier, "lorem", 0, 0),
//        Token(TokenKind::Identifier, "ipsum", 5, 1),
//        Token(TokenKind::Identifier, "dolor", 10, 1),
//        Token(TokenKind::Identifier, "amet", 15, 1),
//        Token(TokenKind::Identifier, "testing", 10, 1),
//        Token(TokenKind::Identifier, "this", 15, 2),
//        Token(TokenKind::Identifier, "thing", 10, 2),
//        Token(TokenKind::Identifier, "to", 15, 3),
//        Token(TokenKind::Identifier, "see", 10, 3),
//        Token(TokenKind::Identifier, "if", 15, 3),
//        Token(TokenKind::Identifier, "it", 10, 4),
//        Token(TokenKind::Identifier, "AFTER", 15, 5),
//        Token(TokenKind::Identifier, "WARDS", 10, 5),
//        Token(TokenKind::Identifier, "once", 15, 6),
//        Token(TokenKind::Identifier, "again", 10, 6),
//    });
//
//    // TODO: CodeBacktrack now also takes in 'input'.
//    //    CodeBacktrack backtrack = CodeBacktrack(stream);
//    //    auto codeBlock = backtrack.createCodeBlockNear(4);
//    //
//    //    if (codeBlock.has_value()) {
//    //        //        std::cout << *codeBlock;
//    //        // TODO: 'codeBlock' is no longer a string.
//    //    }
//    //    else {
//    //        std::cout << "Code block has no value" << std::endl;
//    //    }
//}
