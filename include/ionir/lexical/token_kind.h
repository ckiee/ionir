#pragma once

#include <iostream>

namespace ionir {
    enum class TokenKind {
        Unknown,

        Dummy,

        Whitespace,

        Identifier,

        LiteralString,

        LiteralDecimal,

        LiteralInteger,

        LiteralCharacter,

        SymbolAt,

        SymbolColon,

        SymbolDollar,

        SymbolHash,

        SymbolParenthesesL,

        SymbolParenthesesR,

        SymbolBracketL,

        SymbolBracketR,

        SymbolComma,

        SymbolTilde,

        SymbolEqual,

        SymbolSemiColon,

        SymbolStar,

        SymbolBraceL,

        SymbolBraceR,

        SymbolArrow,

        InstCall,

        InstStore,

        InstReturn,

        InstAlloca,

        InstBranch,

        InstJump,

        KeywordFunction,

        KeywordExtern,

        KeywordElse,

        KeywordGlobal,

        KeywordMutable,

        KeywordModule,

        TypeVoid,

        TypeBool,

        TypeInt8,

        TypeInt16,

        TypeInt32,

        TypeInt64,

        TypeUnsignedInt8,

        TypeUnsignedInt16,

        TypeUnsignedInt32,

        TypeUnsignedInt64,

        TypeFloat16,

        TypeFloat32,

        TypeFloat64,

        TypeChar,

        TypeString,

        OperatorAdd,

        OperatorSubtract,

        OperatorMultiply,

        OperatorDivide,

        OperatorModulo,

        OperatorExponent,

        OperatorGreaterThan,

        OperatorLessThan
    };

    std::ostream &operator<<(std::ostream &stream, const TokenKind &tokenKind);
}
