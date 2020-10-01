#pragma once

#include <optional>
#include <string>
#include <vector>
#include <functional>
#include <ionshared/construct/base_construct.h>
#include <ionir/tracking/symbol_table.h>

namespace ionir {
    class Pass;

    class Inst;

    class Type;

    template<typename T>
    struct Value;

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

        RegisterAssign,

        ErrorMarker,

        Identifier,

        Struct
    };

    class Construct;

    typedef ionshared::Ast<Construct> Ast;

    struct Construct : ionshared::BaseConstruct<Construct, ConstructKind> {
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
        static Ast convertChildren(ionshared::PtrSymbolTable<T> symbolTable) {
            Ast children = {};
            auto symbolTableEntries = symbolTable->unwrap();

            for (const auto &[id, construct] : symbolTableEntries) {
                children.push_back(construct);
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

        explicit Construct(
            ConstructKind kind,
            std::optional<ionshared::SourceLocation> sourceLocation = std::nullopt,
            ionshared::OptPtr<Construct> parent = std::nullopt
        );

        virtual void accept(Pass &visitor) = 0;

        [[nodiscard]] virtual bool equals(const ionshared::Ptr<Construct> &other);

        // TODO: Move to BaseConstruct<> in ionshared.
        /**
         * Verify the members and properties of the node, and it's children to
         * ensure that this construct is well-formed. Without an implementation
         * by the derived class (or without being called by it), this will return
         * true if all the child nodes are successfully verified. If there are no
         * child nodes, the result will be true by default.
         */
        [[nodiscard]] virtual bool verify();

        [[nodiscard]] std::optional<std::string> findConstructKindName();
    };
}
