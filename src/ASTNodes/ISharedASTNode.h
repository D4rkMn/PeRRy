#ifndef ISHAREDASTNODE_H
#define ISHAREDASTNODE_H

#include <string>

class IVisitor;

enum ASTNodeType {
    FUNCTION_NODE,
    LETVAR_NODE,
    STATICVAR_NODE,
    CONSTVAR_NODE,
    STM_NODE
};

class ISharedASTNode {
public:
    virtual void accept(IVisitor*) = 0;
    virtual ~ISharedASTNode() {}
    virtual ASTNodeType getType() const = 0;
};

#endif