#pragma once

namespace ionir {
    class Pass;

    class VariableDecl : public Construct {
    public:
        VariableDecl();

        void accept(Pass &visitor) override;
    };
}
