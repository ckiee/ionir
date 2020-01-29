#pragma once

#include <iostream>

namespace ionir {
    enum class TokenKind {
        Dummy,

        Unknown,

        Identifier,

        LiteralString,

        LiteralDecimal,

        LiteralInt,

        LiteralCharacter,

        Whitespace,

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

        KeywordFunction,

        KeywordExtern,

        KeywordElse,

        KeywordGlobal,

        KeywordMutable,

        KeywordModule,

        TypeVoid,

        TypeBool,

        TypeInt16,

        TypeInt32,

        TypeInt64,

        TypeUnsignedInt16,

        TypeUnsignedInt32,

        TypeUnsignedInt64,

        TypeFloat16,

        TypeFloat32,

        TypeFloat64,

        TypeChar,

        TypeString,

        OperatorAdd,

        OperatorSub,

        OperatorMultiply,

        OperatorDivide,

        OperatorModulo,

        OperatorExponent,

        OperatorGreaterThan,

        OperatorLessThan
    };

    std::ostream &operator<<(std::ostream &stream, const TokenKind &tokenKind);
}
