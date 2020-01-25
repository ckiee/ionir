#pragma once

#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/section.h>
#include <ionir/misc/helpers.h>
#include <ionir/construct/inst.h>
#include <ionir/misc/named.h>

namespace ionir {
    struct AllocaInstOpts : InstOpts {
        std::string id;

        Ptr<Type> type;
    };

    class AllocaInst : public Inst, public Named {
    private:
        Ptr<Type> type;

    public:
        // TODO: Missing support for array-type allocas.
        explicit AllocaInst(AllocaInstOpts opts);

        void accept(Pass &visitor) override;

        Ptr <Type> getType() const;

        void setType(Ptr <Type> type);
    };
}
