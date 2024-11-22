#ifndef R_PROGRAM_H
#define R_PROGRAM_H

#include <string>
#include <list>
#include "R/ASTNodes/ISharedASTNode.h"
#include "R/Utility/VarType.h"
#include "R/Namespace.h"

class R::LetVar : public ISharedASTNode {
public:
    bool mut;
    std::string id;
    VarType type;
    Exp* exp;
    LetVar(bool, const std::string&, VarType, Exp*);
    ~LetVar();
    void accept(IVisitor*) override;
    ASTNodeType getType() const override { return LETVAR_NODE; }
};

class R::StaticVar : public ISharedASTNode {
public:
    bool mut;
    std::string id;
    VarType type;
    Exp* exp;
    StaticVar(bool, const std::string&, VarType, Exp*);
    ~StaticVar();
    void accept(IVisitor*) override;
    ASTNodeType getType() const override { return STATICVAR_NODE; }
};

class R::ConstVar : public ISharedASTNode {
public:
    std::string id;
    VarType type;
    Exp* exp;
    ConstVar(const std::string&, VarType, Exp*);
    ~ConstVar();
    void accept(IVisitor*) override;
    ASTNodeType getType() const override { return CONSTVAR_NODE; }
};

class R::Body {
public:
    std::list<ISharedASTNode*> bodyList;
    Body() = default;
    ~Body();
    void add(ISharedASTNode*);
    void accept(IVisitor*);
};

class R::Program {
public:
    std::list<ISharedASTNode*> programList;
    Program() = default;
    ~Program();
    void add(ISharedASTNode*);
    void accept(IVisitor*);
};

#endif