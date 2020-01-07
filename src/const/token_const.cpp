#include <algorithm>
#include <ionir/const/const_name.h>
#include <ionir/const/token_const.h>

namespace ionir {
    bool TokenConst::isInitialized = false;

    std::map<std::string, TokenKind> TokenConst::simple = {};

    std::vector<std::pair<std::regex, TokenKind>> TokenConst::complex = {};

    TokenKindVector TokenConst::keywords = {};

    TokenKindVector TokenConst::symbols = {};

    TokenKindVector TokenConst::operators = {};

    TokenKindVector TokenConst::types = {
        TokenKind::TypeVoid,
        TokenKind::TypeString,
        TokenKind::TypeInt16,
        TokenKind::TypeInt32,
        TokenKind::TypeInt64,
    };

    TokenKindVector TokenConst::insts = {
        TokenKind::InstAlloca,
        TokenKind::InstBranch,
        TokenKind::InstCall,
        TokenKind::InstReturn,
        TokenKind::InstStore
    };

    void TokenConst::pushComplex(std::regex regex, TokenKind tokenKind) {
        TokenConst::complex.push_back(std::make_pair(regex, tokenKind));
    }

    void TokenConst::pushSimple(std::string value, TokenKind tokenKind) {
        TokenConst::simple[value] = tokenKind;
    }

    void TokenConst::pushSymbol(std::string value, TokenKind tokenKind) {
        TokenConst::pushSimple(value, tokenKind);
        TokenConst::symbols.push_back(tokenKind);
    }

    void TokenConst::pushKeyword(std::string value, TokenKind tokenKind) {
        TokenConst::pushSimple(value, tokenKind);
        TokenConst::keywords.push_back(tokenKind);
    }

    void TokenConst::pushOperator(std::string value, TokenKind tokenKind) {
        TokenConst::pushSimple(value, tokenKind);
        TokenConst::operators.push_back(tokenKind);
    }

    bool TokenConst::sortByKeyLength(const std::pair<std::string, TokenKind> &a,
        const std::pair<std::string, TokenKind> &b) {
        return a.first > b.first;
    }

    void TokenConst::ensureInit() {
        if (!TokenConst::getIsInitialized()) {
            throw std::runtime_error("Not initialized");
        }
    }

    std::map<std::string, TokenKind> TokenConst::getSimpleIds() {
        return TokenConst::simple;
    }

    SimplePairVector TokenConst::getSortedSimpleIds() {
        TokenConst::ensureInit();

        SimplePairVector result = {};

        for (const auto pair : TokenConst::simple) {
            result.push_back(pair);
        }

        std::sort(result.begin(), result.end(), TokenConst::sortByKeyLength);

        return result;
    }

    std::vector<std::pair<std::regex, TokenKind>> TokenConst::getComplexIds() {
        TokenConst::ensureInit();

        return TokenConst::complex;
    }

    TokenKindVector TokenConst::getSymbols() {
        TokenConst::ensureInit();

        return TokenConst::symbols;
    }

    TokenKindVector TokenConst::getKeywords() {
        TokenConst::ensureInit();

        return TokenConst::keywords;
    }

    TokenKindVector TokenConst::getOperators() {
        TokenConst::ensureInit();

        return TokenConst::operators;
    }

    TokenKindVector TokenConst::getTypes() {
        TokenConst::ensureInit();

        return TokenConst::types;
    }

    TokenKindVector TokenConst::getInsts() {
        TokenConst::ensureInit();

        return TokenConst::insts;
    }

    bool TokenConst::getIsInitialized() {
        return TokenConst::isInitialized;
    }

    std::optional<std::string> TokenConst::findSimpleValue(TokenKind tokenKind) {
        for (const auto entry : TokenConst::simple) {
            if (entry.second == tokenKind) {
                return entry.first;
            }
        }

        return std::nullopt;
    }

    void TokenConst::init() {
        // Static members have already been initialized. Do not continue.
        if (TokenConst::isInitialized) {
            return;
        }

        // Register symbols.
        TokenConst::pushSymbol("@", TokenKind::SymbolAt);
        TokenConst::pushSymbol(":", TokenKind::SymbolColon);
        TokenConst::pushSymbol("$", TokenKind::SymbolDollar);
        TokenConst::pushSymbol("#", TokenKind::SymbolHash);
        TokenConst::pushSymbol("(", TokenKind::SymbolParenthesesL);
        TokenConst::pushSymbol(")", TokenKind::SymbolParenthesesR);
        TokenConst::pushSymbol("[", TokenKind::SymbolBracketL);
        TokenConst::pushSymbol("]", TokenKind::SymbolBracketR);
        TokenConst::pushSymbol(",", TokenKind::SymbolComma);
        TokenConst::pushSymbol("~", TokenKind::SymbolTilde);
        TokenConst::pushSymbol("=", TokenKind::SymbolEqual);
        TokenConst::pushSymbol(";", TokenKind::SymbolSemiColon);
        TokenConst::pushSymbol("*", TokenKind::SymbolStar);
        TokenConst::pushSymbol("{", TokenKind::SymbolBraceL);
        TokenConst::pushSymbol("}", TokenKind::SymbolBraceR);
        TokenConst::pushSymbol("->", TokenKind::SymbolArrow);

        // Register instructions & keywords.
        TokenConst::pushKeyword(ConstName::instCall, TokenKind::InstCall);
        TokenConst::pushKeyword(ConstName::instStore, TokenKind::InstStore);
        TokenConst::pushKeyword(ConstName::instReturn, TokenKind::InstReturn);
        TokenConst::pushKeyword(ConstName::instAlloca, TokenKind::InstAlloca);
        TokenConst::pushKeyword(ConstName::instBranch, TokenKind::InstBranch);
        TokenConst::pushKeyword("fn", TokenKind::KeywordFunction);
        TokenConst::pushKeyword("module", TokenKind::KeywordModule);
        TokenConst::pushKeyword("extern", TokenKind::KeywordExtern);
        TokenConst::pushKeyword("global", TokenKind::KeywordGlobal);
        TokenConst::pushKeyword("else", TokenKind::KeywordElse);
        TokenConst::pushKeyword("mut", TokenKind::KeywordMutable);
        TokenConst::pushKeyword(ConstName::typeVoid, TokenKind::TypeVoid);
        TokenConst::pushKeyword(ConstName::typeString, TokenKind::TypeString);
        TokenConst::pushKeyword(ConstName::typeInt16, TokenKind::TypeInt16);
        TokenConst::pushKeyword(ConstName::typeInt32, TokenKind::TypeInt32);
        TokenConst::pushKeyword(ConstName::typeInt64, TokenKind::TypeInt64);

        // Register operators.
        TokenConst::pushOperator("+", TokenKind::OperatorAdd);
        TokenConst::pushOperator("-", TokenKind::OperatorAdd);
        TokenConst::pushOperator("*", TokenKind::OperatorMultiply);
        TokenConst::pushOperator("/", TokenKind::OperatorDivide);
        TokenConst::pushOperator("%", TokenKind::OperatorModulo);
        TokenConst::pushOperator("^", TokenKind::OperatorExponent);
        TokenConst::pushOperator(">", TokenKind::OperatorGreaterThan);
        TokenConst::pushOperator("<", TokenKind::OperatorLessThan);

        // Initialize complex map.
        TokenConst::pushComplex(Regex::identifier, TokenKind::Identifier);
        TokenConst::pushComplex(Regex::string, TokenKind::LiteralString);
        TokenConst::pushComplex(Regex::decimal, TokenKind::LiteralDecimal);
        TokenConst::pushComplex(Regex::integer, TokenKind::LiteralInt);
        TokenConst::pushComplex(Regex::character, TokenKind::LiteralCharacter);
        TokenConst::pushComplex(Regex::whitespace, TokenKind::Whitespace);

        // Raise initialized flag to prevent further attempts to re-initialize.
        TokenConst::isInitialized = true;
    }
}
