#include "bootstrap.h"

namespace ionir::test::bootstrap {
    Token token(TokenType type) {
        return Token(type, "");
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
        ionir::TokenStream *stream = new ionir::TokenStream(tokens);

        return ionir::Parser(stream);
    }

    Ptr<Module> module(std::string identifier) {
        llvm::LLVMContext *llvmContext = new llvm::LLVMContext();
        llvm::Module *llvmModule = new llvm::Module("test", *llvmContext);

        return std::make_shared<Module>(llvmModule);
    }

    Ptr<LlvmVisitor> llvmVisitor() {
        return std::make_shared<LlvmVisitor>(module()->unwrap());
    }

    Ptr<Function> emptyFunction(std::vector<Ptr<Inst>> insts) {
        Ptr<Type> returnType = std::make_shared<Type>("void");
        Ptr<Prototype> prototype = std::make_shared<Prototype>("foobar", std::make_shared<Args>(), returnType);

        Ptr<Section> entrySection = std::make_shared<Section>(SectionOpts{
            nullptr,
            SectionKind::Entry,
            "entry",
            insts,
        });

        std::vector<Ptr<Section>> sections = {
            entrySection,
        };

        Ptr<Function> function = std::make_shared<Function>(prototype, nullptr);
        Ptr<Block> body = std::make_shared<Block>(function, sections);

        function->setBody(body);

        return function;
    }
}
