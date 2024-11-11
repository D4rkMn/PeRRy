#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <list>
#include "ASTNodes/ISharedASTNode.h"

class Exp;

class VarDec : public ISharedASTNode {
public:
    bool mut;
    std::string id;
    VarType type;
    Exp* exp;
    VarDec(bool, const std::string&, VarType, Exp*);
    ~VarDec();
    void accept(IVisitor*) override;
    ASTNodeType getType() const override { return VARDEC_NODE; }
};

class Body {
public:
    std::list<ISharedASTNode*> bodyList;
    Body() = default;
    ~Body();
    void add(ISharedASTNode*);
    void accept(IVisitor*);
};

class Program {
public:
    std::list<ISharedASTNode*> programList;
    Program() = default;
    ~Program();
    void add(ISharedASTNode*);
    void accept(IVisitor*);
};

#endif