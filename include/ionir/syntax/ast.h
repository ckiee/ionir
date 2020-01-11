#pragma once

#include <vector>
#include <ionir/construct/construct.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class AstNode;

    class AstNode {
    public:


        virtual Ast getChildNodes() const = 0;

        bool isLeafNode() const;
    };
}
