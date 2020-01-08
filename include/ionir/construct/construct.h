#pragma once

#include <vector>
#include <functional>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    enum class ConstructKind {
        Type,

        /**
         * A block, possibly containing statements.
         */
            Block,

        /**
         * Function prototype used to declare externs
         * or actual functions.
         */
            Prototype,

        Function,

        /**
         * An external function definition.
         */
            Extern,

        Instruction,

        Global,

        Section,

        VariableReference,

        VariableDeclaration,

        Expr,

        StructDeclaration,

        Module
    };

    class Construct;

    typedef std::vector<Ptr<Construct>> ConstructChildren;

    class Construct : public std::enable_shared_from_this<Construct> {
    private:
        ConstructKind constructKind;

    public:
        template<class T>
        static ConstructChildren convertChildren(std::vector<Ptr<T>> vector) {
            // TODO: Ensure T is child of Construct.
            ConstructChildren children = {};

            for (const auto item : vector) {
                children.push_back(item);
            }

            return children;
        }

        explicit Construct(ConstructKind kind);

        virtual void accept(Pass &visitor) = 0;

        virtual ConstructChildren getChildren() const;

        ConstructKind getConstructKind() const;

        /**
         * Verify the members and properties of the node.
         * Without an implementation by the derived class,
         * this will always return true.
         */
        virtual bool verify() const;

        Ptr<Construct> getPtr();

        template<class T>
        Ptr<T> cast() {
            return std::static_pointer_cast<T>(this->getPtr());
        }

        Ptr<Construct> nativeCast();
    };
}
