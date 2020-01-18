#pragma once

#include <ionir/construct/function.h>
#include <ionir/const/const_name.h>

namespace ionir {
    class Bootstrap {
    public:
        static Ast functionAst(std::string id = ConstName::anonymous);

        static Ptr<Function> function(std::string id = ConstName::anonymous);
    };
}
