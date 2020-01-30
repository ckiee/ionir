#include <algorithm>
#include <ionir/misc/util.h>
#include <ionir/const/const_name.h>
#include <ionir/const/token_const.h>

namespace ionir {
    bool TokenConst::isInitialized = false;

    std::map<std::string, TokenKind> TokenConst::simple = {};

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

    void TokenConst::pushSimple(std::string value, TokenKind tokenKind) {
        TokenConst::simple[value] = tokenKind;
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

    bool TokenConst::contains(std::vector<TokenKind> subject, TokenKind item) {
        return std::find(subject.begin(), subject.end(), item) != subject.end();
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

    TokenKindMap TokenConst::getComplexIds() {
        TokenConst::ensureInit();

        return TokenConst::complex;
    }

    TokenKindMap TokenConst::getSymbols() {
        TokenConst::ensureInit();

        return TokenConst::symbols;
    }

    TokenKindMap TokenConst::getKeywords() {
        TokenConst::ensureInit();

        return TokenConst::keywords;
    }

    TokenKindMap TokenConst::getOperators() {
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

    std::map<TokenKind, std::string> TokenConst::getNames() {
        TokenConst::ensureInit();

        return TokenConst::names;
    }

    std::optional<std::string> TokenConst::getTokenKindName(TokenKind tokenKind) {
        TokenConst::ensureInit();

        if (!Util::mapContains<TokenKind, std::string>(TokenConst::names, tokenKind)) {
            return std::nullopt;
        }

        return TokenConst::names[tokenKind];
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

        // TODO: Merge all maps into simple.

        // Raise initialized flag to prevent further attempts to re-initialize.
        TokenConst::isInitialized = true;
    }
}
