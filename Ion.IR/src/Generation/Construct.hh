#include "ConstructType.hh"
#include "Visitable.hh"

class Construct : public Visitable<Construct, LlvmVisitor> {
private:
    ConstructType type;

public:
    Construct(ConstructType type) {
        this->type = type;
    }

    ConstructType getType() {
        return this->type;
    }
};
