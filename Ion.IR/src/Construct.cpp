#include "ConstructType.hh"

class Construct {
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
