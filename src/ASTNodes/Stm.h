#ifndef STM_H
#define STM_H

#include <string>
#include <list>
#include "ASTNodes/ISharedASTNode.h"

class Exp;
class Body;
class IVisitor;

class Stm : public ISharedASTNode {
public:
    virtual ~Stm() {}
    ASTNodeType getType() const override { return STM_NODE; }
};

class ExpStatement : public Stm {
public:
    Exp* exp;
    ExpStatement(Exp*);
    ~ExpStatement();
    int accept(IVisitor*) override;
};

class AssignStatement : public Stm {
public:
    std::string id;
    Exp* rhs;
    AssignStatement(const std::string&, Exp*);
    ~AssignStatement();
    int accept(IVisitor*) override;
};

class AdvanceStatement : public Stm {
public:
    std::string id;
    Exp* rhs;
    AdvanceStatement(const std::string&, Exp*);
    ~AdvanceStatement();
    int accept(IVisitor*) override;
};

class ReturnStatement : public Stm {
public:
    Exp* exp;
    ReturnStatement(Exp*);
    ~ReturnStatement();
    int accept(IVisitor*) override;
};

class PrintStatement : public Stm {
public:
    std::string textLiteral;
    std::list<Exp*> expList;
    PrintStatement(const std::string&);
    ~PrintStatement();
    int accept(IVisitor*) override;
};

class IfStatement : public Stm {
public:
    Exp* condition;
    Body* ifBody;
    Body* elseBody;
    IfStatement(Exp*, Body*, Body*);
    ~IfStatement();
    int accept(IVisitor*) override;
};

class ForStatement : public Stm {
public:
    std::string id;
    Exp* start;
    Exp* end;
    Body* body;
    ForStatement(const std::string&, Exp*, Exp*, Body*);
    ~ForStatement();
    int accept(IVisitor* visitor) override;
};

#endif