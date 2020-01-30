#include <ionir/const/token_const.h>

namespace ionir {
    TokenKindMap TokenConst::symbols = {
        {"@", TokenKind::SymbolAt},
        {":", TokenKind::SymbolColon},
        {"$", TokenKind::SymbolDollar},
        {"#", TokenKind::SymbolHash},
        {"(", TokenKind::SymbolParenthesesL},
        {")", TokenKind::SymbolParenthesesR},
        {"[", TokenKind::SymbolBracketL},
        {"]", TokenKind::SymbolBracketR},
        {",", TokenKind::SymbolComma},
        {"~", TokenKind::SymbolTilde},
        {"=", TokenKind::SymbolEqual},
        {";", TokenKind::SymbolSemiColon},
        {"*", TokenKind::SymbolStar},
        {"{", TokenKind::SymbolBraceL},
        {"}", TokenKind::SymbolBraceR},
        {"->", TokenKind::SymbolArrow},
    };
}
