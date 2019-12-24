#pragma once

namespace ionir {
    template<typename T>
    class Wrapper {
    protected:
        T value;

    public:
        explicit Wrapper(T value) : value(value) {
            //
        }

        virtual T unwrap() const {
            return this->value;
        }
    };
}
