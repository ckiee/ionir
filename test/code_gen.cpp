#include <vector>
#include <ionir/passes/codegen/llvm_codegen_pass.h>
#include <ionir/passes/semantic/name_resolution_pass.h>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/llvm/llvm_module.h>
#include <ionir/const/const.h>
#include <ionir/const/const_name.h>
#include <ionir/passes/pass_manager.h>
#include "test_api/bootstrap.h"
#include "test_api/compare.h"
#include "test_api/const.h"

using namespace ionir;

TEST(CodeGenTest, VisitExtern) {
    Ptr<LlvmCodegenPass> visitor = test::bootstrap::llvmCodegenPass();
    Ptr<Type> returnType = std::make_shared<Type>(ConstName::typeVoid);
    Ptr<Args> args = std::make_shared<Args>();
    Ptr<Prototype> prototype = std::make_shared<Prototype>(test::constant::foobar, args, returnType);
    Ptr<Extern> externConstruct = std::make_shared<Extern>(prototype);

    visitor->visitExtern(externConstruct);

    LlvmModule module = LlvmModule(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module.getAsString(), "extern_simple"));
}

TEST(CodeGenTest, VisitEmptyFunction) {
    Ptr<LlvmCodegenPass> visitor = test::bootstrap::llvmCodegenPass();
    Ptr<Type> returnType = std::make_shared<Type>(ConstName::typeVoid);

    Ptr<Prototype> prototype =
        std::make_shared<Prototype>(test::constant::foobar, std::make_shared<Args>(), returnType);

    Ptr<Block> body = std::make_shared<Block>(nullptr);

    Ptr<Section> section = std::make_shared<Section>(SectionOpts{
        body,
        SectionKind::Entry,
        "entry"
    });

    // TODO: Fix mumbo-jumbo debugging code.
    // --------------------------

    typedef PtrSymbolTable<Section> t;
    typedef SymbolTable<Ptr<Section>> tt;

    auto sectionsVal = std::map<std::string, Ptr<Section>>{
        {Const::sectionEntryId, section}
    };

    t sectionsMap = std::make_shared<tt>(sectionsVal);

    // ---------------------------

    body->setSymbolTable(sectionsMap);

    Ptr<Function> function = std::make_shared<Function>(prototype, body);

    body->setParent(function);
    visitor->visitFunction(function);

    LlvmModule module = LlvmModule(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module.getAsString(), "function_empty"));
}

TEST(CodeGenTest, VisitEmptyGlobal) {
    Ptr<LlvmCodegenPass> visitor = test::bootstrap::llvmCodegenPass();
    Ptr<IntegerType> type = std::make_shared<IntegerType>(IntegerKind::Int32);
    Ptr<Global> globalVar = std::make_shared<Global>(type, test::constant::foobar);

    visitor->visitGlobal(globalVar);

    LlvmModule module = LlvmModule(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module.getAsString(), "global_empty"));
}

TEST(CodeGenTest, VisitGlobalWithValue) {
    Ptr<LlvmCodegenPass> visitor = test::bootstrap::llvmCodegenPass();
    Ptr<IntegerType> type = std::make_shared<IntegerType>(IntegerKind::Int32);

    Ptr<Global> globalVar = std::make_shared<Global>(type, test::constant::foobar,
        std::make_shared<IntegerValue>(type, 123)->staticCast<Value<>>());

    visitor->visitGlobal(globalVar);

    LlvmModule module = LlvmModule(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module.getAsString(), "global_init"));
}

TEST(CodeGenTest, VisitAllocaInst) {
    Ptr<LlvmCodegenPass> visitor = test::bootstrap::llvmCodegenPass();

    std::vector<Ptr<Inst>> insts = {
        std::make_shared<AllocaInst>(AllocaInstOpts{
            nullptr,
            test::constant::foobar,
            std::make_shared<Type>(ConstName::typeInt32)
        })
    };

    Ptr<Function> function = test::bootstrap::emptyFunction(insts);

    visitor->visitFunction(function);

    LlvmModule module = LlvmModule(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module.getAsString(), "inst_alloca"));
}

TEST(CodeGenTest, VisitBranchInst) {
    PassManager passManager = PassManager();

    passManager.registerPass(std::make_shared<NameResolutionPass>());

    Ptr<Section> body = std::make_shared<Section>(SectionOpts{
        nullptr,
        SectionKind::Label,
        "if_body",
        {}
    });

    Ptr<BooleanValue> condition = std::make_shared<BooleanValue>(true);
    PtrRef<Section> bodySectionRef = std::make_shared<Ref<Section>>("if_body", nullptr, body);

    // TODO: Use some sort of factory design pattern.
    auto branchInst = std::make_shared<BranchInst>(BranchInstOpts{
        body,
        condition,

        /**
         * Point both body and otherwise sections to
         * the same section for testing purposes. LLVM
         * is smart enough to create a different label,
         * even if both attempt to reference the same label.
         * Unsure however how it would handle splitting of
         * instructions if there were to be contained inside
         * the section once it creates the new label.
         */
        bodySectionRef,
        bodySectionRef
    });

    branchInst->getBodyRef()->setOwner(branchInst);
    branchInst->getOtherwiseRef()->setOwner(branchInst);

    Ptr<LlvmCodegenPass> llvmCodegenPass = test::bootstrap::llvmCodegenPass();

    Ptr<Function> function = test::bootstrap::emptyFunction({
        branchInst
    });

    passManager.run({
        function
    });

    llvmCodegenPass->visitFunction(function);

    LlvmModule module = LlvmModule(llvmCodegenPass->getModule());

    std::cout << module.getAsString() << '\n';
    EXPECT_TRUE(test::compare::ir(module.getAsString(), "inst_branch"));
}
