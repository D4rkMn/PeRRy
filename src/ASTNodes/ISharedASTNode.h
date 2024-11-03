#ifndef ISHAREDASTNODE_H
#define ISHAREDASTNODE_H

#include <string>

class IVisitor;

enum VarType {
    INT32_TYPE,
    INT64_TYPE,
    VOID_TYPE,
    UNKNOWN_TYPE
};

std::string varTypeToString(VarType);

enum ASTNodeType {
    FUNCTION_NODE,
    VARDEC_NODE,
    STM_NODE
};

class ISharedASTNode {
public:
    virtual int accept(IVisitor*) = 0;
    virtual ~ISharedASTNode() {}
    virtual ASTNodeType getType() const = 0;
};

#endif