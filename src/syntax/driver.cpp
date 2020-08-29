#include <ionir/syntax/driver.h>
#include <ionir/lexical/lexer.h>
#include <ionir/syntax/parser.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir::driver {
    ionshared::LlvmIrString run(const std::string &input) {
        Lexer lexer = Lexer(input);

        ionshared::Ptr<TokenStream> tokenStream =
            std::make_shared<TokenStream>(lexer.scan());

        Parser parser = Parser(tokenStream);
        LlvmCodegenPass llvmCodegenPass = LlvmCodegenPass();

        while (tokenStream->hasNext()) {
            AstPtrResult<Module> moduleResult = parser.parseModule();

            if (util::hasValue(moduleResult)) {
                llvmCodegenPass.visitModule(util::getResultValue(moduleResult));
            }
        }

        ionshared::LlvmIrString llvmIr;
        auto llvmModules =  llvmCodegenPass.getModules()->unwrap();

        for (const auto &[id, llvmModule] : llvmModules) {
            llvmIr += ionshared::LlvmModule(llvmModule).getAsString();
        }

        return llvmIr;
    }
}
