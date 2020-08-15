#pragma once

#include <ionir/construct/function.h>
#include <ionir/const/const_name.h>

namespace ionir {
    class Bootstrap {
    public:
        static Ast functionAst(const std::string &id = ConstName::anonymous);

        static ionshared::Ptr<Function> function(const std::string &id = ConstName::anonymous);

        static ionshared::Ptr<BasicBlock> basicBlock(
            ionshared::Ptr<FunctionBody> parent = nullptr,
            std::string id = ConstName::anonymous,
            BasicBlockKind basicBlockKind = BasicBlockKind::Entry
        );
    };
}
