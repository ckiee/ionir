#include <ionir/const/token_const.h>
#include <ionir/const/const.h>
#include <ionir/misc/util.h>

namespace ionir {
    Map<IntegerKind, LlvmIntTypeResolver> Const::integerTypeResolverMap = {};

    const std::string Const::basicBlockInternalPrefix = ".";

    const std::string Const::basicBlockEntryId = "entry";

    std::map<TokenKind, int> Const::operatorPrecedence = {
        {TokenKind::OperatorAdd, 20}, {TokenKind::OperatorSub, 20},
        {TokenKind::OperatorMultiply, 40},
        {TokenKind::OperatorDivide, 40},
        {TokenKind::OperatorModulo, 40},
        {TokenKind::OperatorExponent, 80}
    };

    std::map<ConstructKind, std::string> Const::constructNames = {
        {ConstructKind::Type, "Type"},
        {ConstructKind::FunctionBody, "Block"},
        {ConstructKind::Prototype, "Prototype"},
        {ConstructKind::Function, "Function"},
        {ConstructKind::Extern, "Extern"},
        {ConstructKind::Inst, "Instruction"},
        {ConstructKind::Global, "Global"},
        {ConstructKind::BasicBlock, "Section"},
        {ConstructKind::VariableRef, "VariableReference"},
        {ConstructKind::VariableDecl, "VariableDeclaration"},
        {ConstructKind::StructDecl, "StructDeclaration"},
        {ConstructKind::Module, "Module"},
        {ConstructKind::Ref, "Reference"},
        {ConstructKind::Value, "Value"}
    };

    // TODO: Refactor.
    // Const::Const()
    // {
    //     // Register integer kind -> integer type resolvers.
    //     auto map = this->integerTypeResolverMap.unwrap();

    //     // TODO: Fix insertion error.
    //     // map.insert(IntegerKind::Int1, &llvm::IntegerType::getInt1Ty);
    //     // map.insert(IntegerKind::Int32, &llvm::IntegerType::getInt32Ty);
    //     // map.insert(IntegerKind::Int64, &llvm::IntegerType::getInt64Ty);
    //     // map.insert(IntegerKind::Int128, &llvm::IntegerType::getInt128Ty);
    // }

    std::optional<LlvmIntTypeResolver> Const::tryGetIntTypeResolver(IntegerKind kind) {
        return *Const::integerTypeResolverMap.lookup(kind);
    }

    std::optional<std::string> Const::getConstructKindName(ConstructKind constructKind) {
        if (Util::mapContains<ConstructKind, std::string>(Const::constructNames, constructKind)) {
            return Const::constructNames[constructKind];
        }

        return std::nullopt;
    }
}
