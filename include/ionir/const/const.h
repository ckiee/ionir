#pragma once

#include <string>
#include <map>
#include <optional>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <ionir/construct/value/integer.h>
#include <ionir/lexical/token_kind.h>
#include <ionir/container/map.h>

namespace ionir {
    typedef llvm::IntegerType *(llvm::IntegerType::*LlvmIntTypeResolver)(llvm::LLVMContext &context);

    class Const {
    protected:
        static Map<IntegerKind, LlvmIntTypeResolver> integerTypeResolverMap;

    public:
        static const std::string sectionInternalPrefix;

        static const std::string sectionEntryId;

        static std::optional<LlvmIntTypeResolver> tryGetIntTypeResolver(IntegerKind kind);

        static std::map<TokenKind, int> operatorPrecedence;

        static const std::string foo;

        static const std::string bar;

        static const std::string foobar;
    };
}
