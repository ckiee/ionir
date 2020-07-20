#pragma once

#include <optional>
#include <string>
#include <vector>
#include <functional>
#include <ionshared/construct/bare_construct.h>
#include <ionir/misc/helpers.h>
#include <ionir/tracking/symbol_table.h>

namespace ionir {
    class Pass;

    enum class ConstructKind {
        Type,

        /**
         * A function body, possibly containing statements.
         */
        FunctionBody,

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

        Inst,

        Global,

        BasicBlock,

        VariableRef,

        VariableDecl,

        StructDecl,

        Module,

        Ref,

        Value,

        RegisterAssign
    };

    class Construct;

    typedef ionshared::Ast<Construct> Ast;

    class Construct : public std::enable_shared_from_this<Construct> {
    private:
        ConstructKind constructKind;

    public:
        template<class T>
        static Ast convertChildren(std::vector<ionshared::Ptr<T>> vector) {
            // TODO: Ensure T is child of AstNode.
            Ast children = {};

            for (const auto item : vector) {
                children.push_back(item);
            }

            return children;
        }

        template<class T>
        static Ast convertChildren(SymbolTable<T> symbolTable) {
            Ast children = {};

            for (const auto &[key, value] : symbolTable.unwrap()) {
                children.push_back(value);
            }

            return children;
        }

        template<typename TFirst, typename TSecond>
        static Ast mergeChildren(TFirst first, TSecond second) {
            Ast children = {};

            for (const auto item : first) {
                children.push_back(item);
            }

            for (const auto item : second) {
                children.push_back(item);
            }

            return children;
        }

        explicit Construct(ConstructKind kind);

        virtual void accept(Pass &visitor) = 0;

        virtual Ast getChildNodes();

        virtual bool equals(ionshared::Ptr<Construct> other);

        bool isLeafNode();

        ConstructKind getConstructKind() const;

        /**
         * Verify the members and properties of the node.
         * Without an implementation by the derived class,
         * this will always return true.
         */
        virtual bool verify();

        ionshared::Ptr<Construct> getPtr();

        /**
         * Used to cast pointers to related types, for example casting
         * void* to the appropriate type.
         */
        template<typename T>
        ionshared::Ptr<T> staticCast() {
            return std::static_pointer_cast<T>(this->getPtr());
        }

        /**
         * Used to convert pointers and references at runtime.
         * Should be generally used for casting a pointer or reference
         * up or down an inheritance chain (inheritance hierarchy).
         */
        template<class T>
        ionshared::Ptr<T> dynamicCast() {
            return std::dynamic_pointer_cast<T>(this->getPtr());
        }

        ionshared::Ptr<Construct> nativeCast();

        std::optional<std::string> getConstructName();
    };
}
