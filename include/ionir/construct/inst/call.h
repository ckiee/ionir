#pragma once

#include <string>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/construct/inst_yield.h>

namespace ionir {
    class Pass;

    class Function;

    struct CallInstOpts : InstOpts {
        PtrRef<Function> callee;

        std::vector<ionshared::Ptr<Construct>> args = {};
    };

    class CallInst : public Inst {
    private:
        PtrRef<Function> callee;

        std::vector<ionshared::Ptr<Construct>> args;

    public:
        explicit CallInst(const CallInstOpts &opts);

        void accept(Pass &visitor) override;

        [[nodiscard]] PtrRef<Function> getCallee() const;

        void setCallee(PtrRef<Function> callee);

        [[nodiscard]] std::vector<ionshared::Ptr<Construct>> getArgs() const noexcept;

        void setArgs(std::vector<ionshared::Ptr<Construct>> args) noexcept;
    };
}
