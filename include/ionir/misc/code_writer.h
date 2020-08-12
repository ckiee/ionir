#pragma once

#include <ionshared/misc/helpers.h>
#include <ionir/construct/module.h>
#include <ionir/construct/global.h>

namespace ionir {
    class CodeWriter {
    private:
        std::string buffer;

        void createModule(ionshared::Ptr<Module> construct);

        void createGlobal(ionshared::Ptr<Global> construct);

    public:
        CodeWriter();

        std::string make(ionshared::Ptr<Construct> rootConstruct) const;

        std::string getBuffer() const noexcept;

        void clear() noexcept;

        std::string consumeBuffer() noexcept;
    };
}
