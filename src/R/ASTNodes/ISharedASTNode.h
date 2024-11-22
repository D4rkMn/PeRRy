#ifndef R_ISHAREDASTNODE_H
#define R_ISHAREDASTNODE_H

#include <string>
#include "R/Namespace.h"

namespace R {
    enum ASTNodeType {
        FUNCTION_NODE,
        LETVAR_NODE,
        STATICVAR_NODE,
        CONSTVAR_NODE,
        STM_NODE
    };
}

class R::ISharedASTNode {
public:
    virtual void accept(IVisitor*) = 0;
    virtual ~ISharedASTNode() {}
    virtual R::ASTNodeType getType() const = 0;
};

#endif