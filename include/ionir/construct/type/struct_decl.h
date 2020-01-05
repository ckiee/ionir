#pragma once

namespace ionir {
    class Pass;

    class StructDecl : public Construct {
    public:
        StructDecl();

        void accept(Pass &visitor) override;
    };
}
