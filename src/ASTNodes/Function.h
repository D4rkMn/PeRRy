#ifndef FUNCTION_H
#define FUNCTION_H

#include <list>
#include <string>
#include "ASTNodes/ISharedASTNode.h"

class Body;

class ParamDec {
public:
    VarType type;
    std::string id;
    ParamDec(VarType, const std::string&);
    ~ParamDec() = default;
    void accept(IVisitor* visitor);
};

class ParamDecList {
public:
    std::list<ParamDec> params;
    ParamDecList() = default;
    ~ParamDecList() = default;
    void accept(IVisitor*);
};

class Function : public ISharedASTNode {
public:
    std::string id;
    ParamDecList* params;
    VarType type;
    Body* body;
    Function(const std::string&, ParamDecList*, VarType, Body*);
    ~Function();
    void accept(IVisitor*) override;
    ASTNodeType getType() const override { return FUNCTION_NODE; }
};

#endif