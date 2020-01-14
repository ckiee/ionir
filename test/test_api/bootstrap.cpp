#include <ionir/const/const.h>
#include "constant.h"
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
        return std::make_shared<LlvmCodegenPass>(llvmModule()->unwrap());
    }

    Ptr<Function> emptyFunction(std::vector<Ptr<Inst>> insts) {
        Ptr<Type> returnType = std::make_shared<Type>("void");
        Ptr<Prototype> prototype = std::make_shared<Prototype>(test::constant::foobar, std::make_shared<Args>(), returnType);

        Ptr<Section> entrySection = std::make_shared<Section>(SectionOpts{
            nullptr,
            SectionKind::Entry,
            Const::sectionEntryId,
            insts,
        });

        // TODO: Fix mumbo-jumbo debugging code. -------------

        typedef PtrSymbolTable<Section> t;
        typedef SymbolTable<Ptr<Section>> tt;

        auto t1 = std::map<std::string, Ptr<Section>>{
            {entrySection->getId(), entrySection}
        };

        t sections = std::make_shared<tt>(t1);

        // --------------------

        Ptr<Function> function = std::make_shared<Function>(prototype, nullptr);
        Ptr<Block> body = std::make_shared<Block>(function, sections);

        function->setBody(body);

        return function;
    }
}
