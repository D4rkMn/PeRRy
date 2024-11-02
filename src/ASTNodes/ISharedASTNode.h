#ifndef ISHAREDASTNODE_H
#define ISHAREDASTNODE_H

class Visitor;

enum VarType {
    INT32_TYPE,
    INT64_TYPE,
    VOID_TYPE,
    UNKNOWN_TYPE
};

enum ASTNodeType {
    FUNCTION_NODE,
    VARDEC_NODE,
    STM_NODE
};

class ISharedASTNode {
public:
    virtual int accept(Visitor*) = 0;
    virtual ~ISharedASTNode() = 0;
    virtual ASTNodeType getType() const = 0;
};

#endif