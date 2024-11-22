#ifndef R_FUNCTION_H
#define R_FUNCTION_H

#include <list>
#include <string>
#include "R/ASTNodes/ISharedASTNode.h"
#include "R/Utility/VarType.h"
#include "R/Namespace.h"

class R::ParamDec {
public:
    VarType type;
    std::string id;
    bool mut;
    ParamDec(VarType, const std::string&, bool);
    ~ParamDec() = default;
    void accept(IVisitor* visitor);
};

class R::ParamDecList {
public:
    std::list<ParamDec> params;
    ParamDecList() = default;
    ~ParamDecList() = default;
    void accept(IVisitor*);
};

class R::Function : public ISharedASTNode {
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