#include <ionir/const/const.h>
#include "const.h"
#include "bootstrap.h"

namespace ionir::test::bootstrap {
    Token token(TokenKind kind) {
        return Token(kind, "");
    }

    TokenStream tokenStream(int amountOfItems) {
        std::vector<Token> tokens = {};

        // Populate the tokens vector.
        for (int i = 0; i < amountOfItems; i++) {
            tokens.push_back(token());
        }

        // Create the Stream and provide the tokens.
        return TokenStream(tokens);
    }

    Parser parser(std::vector<Token> tokens) {
        return ionir::Parser(ionir::TokenStream(tokens));
    }

    ionshared::Ptr<LlvmModule> llvmModule(std::string identifier) {
        llvm::LLVMContext *llvmContext = new llvm::LLVMContext();
        llvm::Module *llvmModule = new llvm::Module("test", *llvmContext);

        return std::make_shared<LlvmModule>(llvmModule);
    }

    ionshared::Ptr<LlvmCodegenPass> llvmCodegenPass() {
        ionshared::Ptr<LlvmModule> module = llvmModule();

        ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules = std::make_shared<ionshared::SymbolTable<llvm::Module *>>(ionshared::SymbolTable<llvm::Module *>({
            {module->getId(), module->unwrap()}
        }));

        ionshared::Ptr<LlvmCodegenPass> llvmCodegenPass = std::make_shared<LlvmCodegenPass>(modules);

        if (!llvmCodegenPass->setModuleBuffer(module->getId())) {
            throw std::runtime_error("Could not set active module buffer during bootstrap process");
        }

        return llvmCodegenPass;
    }

    ionshared::Ptr<Function> emptyFunction(std::vector<ionshared::Ptr<Inst>> insts) {
        ionshared::Ptr<VoidType> returnType = TypeFactory::typeVoid();

        // TODO: Consider support for module here.
        ionshared::Ptr<Prototype> prototype = std::make_shared<Prototype>(test::constant::foobar, std::make_shared<Args>(), returnType, nullptr);

        ionshared::Ptr<BasicBlock> entrySection = std::make_shared<BasicBlock>(BasicBlockOpts{
            nullptr,
            BasicBlockKind::Entry,
            Const::basicBlockEntryId,
            {},
            insts
        });

        // TODO: Fix mumbo-jumbo debugging code. -------------

        typedef PtrSymbolTable<BasicBlock> t;
        typedef ionshared::SymbolTable<ionshared::Ptr<BasicBlock>> tt;

        auto t1 = std::map<std::string, ionshared::Ptr<BasicBlock>>{
            {entrySection->getId(), entrySection}
        };

        t sections = std::make_shared<tt>(t1);

        // --------------------

        ionshared::Ptr<Function> function = std::make_shared<Function>(prototype, nullptr);
        ionshared::Ptr<FunctionBody> body = std::make_shared<FunctionBody>(function, sections);

        entrySection->setParent(body);
        function->setBody(body);

        return function;
    }
}
