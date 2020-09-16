#pragma once

#include <string>
#include <ionir/construct/inst_yield.h>

namespace ionir {
    class Pass;

    class Function;

    struct CallInstOpts : InstOpts {
        ionshared::Ptr<Function> callee;

        std::vector<ionshared::Ptr<Construct>> args = {};
    };

    class CallInst : public Inst {
    private:
        ionshared::Ptr<Function> callee;

        std::vector<ionshared::Ptr<Construct>> args;

    public:
        explicit CallInst(const CallInstOpts &opts);

        void accept(Pass &visitor) override;

        [[nodiscard]] ionshared::Ptr<Function> getCallee() const;

        void setCallee(ionshared::Ptr<Function> callee);

        [[nodiscard]] std::vector<ionshared::Ptr<Construct>> getArgs() const noexcept;

        void setArgs(std::vector<ionshared::Ptr<Construct>> args) noexcept;
    };
}
