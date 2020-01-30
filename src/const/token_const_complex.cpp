#include <ionir/misc/regex.h>
#include <ionir/const/token_const.h>

namespace ionir {
    TokenKindMap TokenConst::complex = {
        {Regex::identifier, TokenKind::Identifier},
        {Regex::string, TokenKind::LiteralString},
        {Regex::decimal, TokenKind::LiteralDecimal},
        {Regex::integer, TokenKind::LiteralInt},
        {Regex::character, TokenKind::LiteralCharacter},
        {Regex::whitespace, TokenKind::Whitespace}
    };
}
