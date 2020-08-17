#include <algorithm>
#include <ionir/misc/util.h>
#include <ionir/const/const_name.h>
#include <ionir/const/token_const.h>

namespace ionir {
    bool TokenConst::isInitialized = false;

    BiMap<std::string, TokenKind> TokenConst::simple = BiMap<std::string, TokenKind>();

    std::vector<std::pair<std::regex, TokenKind>> TokenConst::complex = {};

    BiMap<std::string, TokenKind> TokenConst::keywords = BiMap<std::string, TokenKind>();

    TokenKindVector TokenConst::types = {
        TokenKind::TypeVoid,
        TokenKind::TypeBool,
        TokenKind::TypeInt16,
        TokenKind::TypeInt32,
        TokenKind::TypeInt64,
        TokenKind::TypeUnsignedInt16,
        TokenKind::TypeUnsignedInt32,
        TokenKind::TypeUnsignedInt64,
        TokenKind::TypeFloat16,
        TokenKind::TypeFloat32,
        TokenKind::TypeFloat64,
        TokenKind::TypeChar,
        TokenKind::TypeString
    };

    TokenKindVector TokenConst::insts = {
        TokenKind::InstAlloca,
        TokenKind::InstBranch,
        TokenKind::InstCall,
        TokenKind::InstReturn,
        TokenKind::InstStore
    };

    bool TokenConst::pushSimple(std::string value, TokenKind tokenKind) {
        return TokenConst::simple.insert(std::move(value), tokenKind);
    }

    bool TokenConst::sortByKeyLength(const std::pair<std::string, TokenKind> &a, const std::pair<std::string, TokenKind> &b) {
        return a.first > b.first;
    }

    void TokenConst::ensureInit() {
        if (!TokenConst::getIsInitialized()) {
            throw std::runtime_error("Not initialized");
        }
    }

    bool TokenConst::contains(std::vector<TokenKind> subject, TokenKind item) {
        return std::find(subject.begin(), subject.end(), item) != subject.end();
    }

    const BiMap<std::string, TokenKind> &TokenConst::getSimpleIds() {
        return TokenConst::simple;
    }

    SimplePairVector TokenConst::getSortedSimpleIds() {
        TokenConst::ensureInit();

        SimplePairVector result = {};

        for (const auto &pair : TokenConst::simple.getFirstMap().unwrapConst()) {
            result.push_back(pair);
        }

        std::sort(result.begin(), result.end(), TokenConst::sortByKeyLength);

        return result;
    }

    const std::vector<std::pair<std::regex, TokenKind>> &TokenConst::getComplexIds() {
        TokenConst::ensureInit();

        return TokenConst::complex;
    }

    const BiMap<std::string, TokenKind> &TokenConst::getSymbols() {
        TokenConst::ensureInit();

        return TokenConst::symbols;
    }

    const BiMap<std::string, TokenKind> &TokenConst::getKeywords() {
        TokenConst::ensureInit();

        return TokenConst::keywords;
    }

    const BiMap<std::string, TokenKind> &TokenConst::getOperators() {
        TokenConst::ensureInit();

        return TokenConst::operators;
    }

    const TokenKindVector &TokenConst::getTypes() {
        TokenConst::ensureInit();

        return TokenConst::types;
    }

    const TokenKindVector &TokenConst::getInsts() {
        TokenConst::ensureInit();

        return TokenConst::insts;
    }

    std::map<TokenKind, std::string> TokenConst::getNames() {
        TokenConst::ensureInit();

        return TokenConst::names;
    }

    std::optional<std::string> TokenConst::getTokenKindName(TokenKind tokenKind) {
        TokenConst::ensureInit();

        if (!ionshared::Util::mapContains<TokenKind, std::string>(TokenConst::names, tokenKind)) {
            return std::nullopt;
        }

        return TokenConst::names[tokenKind];
    }

    bool TokenConst::getIsInitialized() {
        return TokenConst::isInitialized;
    }

    std::optional<std::string> TokenConst::findSimpleValue(TokenKind tokenKind) {
        for (const auto &entry : TokenConst::simple.getFirstMap().unwrapConst()) {
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

        // Initialize keywords bidirectional map.
        TokenConst::keywords = BiMap<std::string, TokenKind>(std::map<std::string, TokenKind>{
            // Instructions.
            {ConstName::instCall, TokenKind::InstCall},
            {ConstName::instStore, TokenKind::InstStore},
            {ConstName::instReturn, TokenKind::InstReturn},
            {ConstName::instAlloca, TokenKind::InstAlloca},
            {ConstName::instBranch, TokenKind::InstBranch},

            // Keywords.
            {"fn", TokenKind::KeywordFunction},
            {"module", TokenKind::KeywordModule},
            {"extern", TokenKind::KeywordExtern},
            {"global", TokenKind::KeywordGlobal},
            {"else", TokenKind::KeywordElse},
            {"mut", TokenKind::KeywordMutable},

            // Types keywords.
            {ConstName::typeVoid, TokenKind::TypeVoid},
            {ConstName::typeBool, TokenKind::TypeBool},
            {ConstName::typeInt16, TokenKind::TypeInt16},
            {ConstName::typeInt32, TokenKind::TypeInt32},
            {ConstName::typeInt64, TokenKind::TypeInt64},
            {ConstName::typeUnsignedInt16, TokenKind::TypeUnsignedInt16},
            {ConstName::typeUnsignedInt32, TokenKind::TypeUnsignedInt32},
            {ConstName::typeUnsignedInt64, TokenKind::TypeUnsignedInt64},
            {ConstName::typeFloat16, TokenKind::TypeFloat16},
            {ConstName::typeFloat32, TokenKind::TypeFloat32},
            {ConstName::typeFloat64, TokenKind::TypeFloat64},
            {ConstName::typeChar, TokenKind::TypeChar},
            {ConstName::typeString, TokenKind::TypeString}
        });

        // Merge simple maps.
        TokenConst::simple = TokenConst::symbols.merge(TokenConst::simple);
        TokenConst::simple = TokenConst::keywords.merge(TokenConst::simple);
        TokenConst::simple = TokenConst::operators.merge(TokenConst::simple);

        // Initialize complex maps.
        TokenConst::complex = {
            {Regex::identifier, TokenKind::Identifier},
            {Regex::string, TokenKind::LiteralString},
            {Regex::decimal, TokenKind::LiteralDecimal},
            {Regex::integer, TokenKind::LiteralInteger},
            {Regex::character, TokenKind::LiteralCharacter},
            {Regex::whitespace, TokenKind::Whitespace}
        };

        /**
         * Raise initialized flag to prevent further
         * attempts to re-initialize.
         */
        TokenConst::isInitialized = true;
    }
}
