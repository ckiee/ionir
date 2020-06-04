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

    Ptr<LlvmModule> llvmModule(std::string identifier) {
        llvm::LLVMContext *llvmContext = new llvm::LLVMContext();
        llvm::Module *llvmModule = new llvm::Module("test", *llvmContext);

        return std::make_shared<LlvmModule>(llvmModule);
    }

    Ptr<LlvmCodegenPass> llvmCodegenPass() {
        Ptr<LlvmModule> module = llvmModule();

        Ptr<LlvmCodegenPass> llvmCodegenPass = std::make_shared<LlvmCodegenPass>(Map<std::string, llvm::Module *>({
            {module->getId(), module->unwrap()}
        }));

        if (!llvmCodegenPass->setModuleBuffer(module->getId())) {
            throw std::runtime_error("Could not set active module buffer during bootstrap process");
        }

        return llvmCodegenPass;
    }

    Ptr<Function> emptyFunction(std::vector<Ptr<Inst>> insts) {
        Ptr<VoidType> returnType = TypeFactory::typeVoid();
        Ptr<Prototype> prototype = std::make_shared<Prototype>(test::constant::foobar, std::make_shared<Args>(), returnType);

        Ptr<BasicBlock> entrySection = std::make_shared<BasicBlock>(BasicBlockOpts{
            nullptr,
            BasicBlockKind::Entry,
            Const::basicBlockEntryId,
            insts,
        });

        // TODO: Fix mumbo-jumbo debugging code. -------------

        typedef PtrSymbolTable<BasicBlock> t;
        typedef SymbolTable<Ptr<BasicBlock>> tt;

        auto t1 = std::map<std::string, Ptr<BasicBlock>>{
            {entrySection->getId(), entrySection}
        };

        t sections = std::make_shared<tt>(t1);

        // --------------------

        Ptr<Function> function = std::make_shared<Function>(prototype, nullptr);
        Ptr<FunctionBody> body = std::make_shared<FunctionBody>(function, sections);

        entrySection->setParent(body);
        function->setBody(body);

        return function;
    }
}
