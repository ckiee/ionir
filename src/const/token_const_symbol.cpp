#include <ionir/const/token_const.h>

namespace ionir {
    BiMap<std::string, TokenKind> TokenConst::symbols = BiMap<std::string, TokenKind>(std::map<std::string, TokenKind>({
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
        {"->", TokenKind::SymbolArrow}
    }));
}
