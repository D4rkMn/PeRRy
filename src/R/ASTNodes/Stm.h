#ifndef R_STM_H
#define R_STM_H

#include <string>
#include <list>
#include "R/ASTNodes/ISharedASTNode.h"

class R::Stm : public ISharedASTNode {
public:
    virtual ~Stm() {}
    ASTNodeType getType() const override { return STM_NODE; }
};

class R::ExpStatement : public Stm {
public:
    Exp* exp;
    ExpStatement(Exp*);
    ~ExpStatement();
    void accept(IVisitor*) override;
};

class R::AssignStatement : public Stm {
public:
    std::string id;
    Exp* rhs;
    AssignStatement(const std::string&, Exp*);
    ~AssignStatement();
    void accept(IVisitor*) override;
};

class R::AdvanceStatement : public Stm {
public:
    std::string id;
    Exp* rhs;
    AdvanceStatement(const std::string&, Exp*);
    ~AdvanceStatement();
    void accept(IVisitor*) override;
};

class R::ReturnStatement : public Stm {
public:
    Exp* exp;
    ReturnStatement(Exp*);
    ~ReturnStatement();
    void accept(IVisitor*) override;
};

class R::PrintStatement : public Stm {
public:
    std::string textLiteral;
    std::list<Exp*> expList;
    PrintStatement(const std::string&);
    ~PrintStatement();
    void accept(IVisitor*) override;
};

class R::IfStatement : public Stm {
public:
    Exp* condition;
    Body* ifBody;
    Body* elseBody;
    IfStatement(Exp*, Body*, Body*);
    ~IfStatement();
    void accept(IVisitor*) override;
};

class R::WhileStatement : public Stm {
public:
    Exp* condition;
    Body* body;
    WhileStatement(Exp*, Body*);
    ~WhileStatement();
    void accept(IVisitor*) override;
};

class R::ForStatement : public Stm {
public:
    std::string id;
    Exp* start;
    Exp* end;
    Body* body;
    ForStatement(const std::string&, Exp*, Exp*, Body*);
    ~ForStatement();
    void accept(IVisitor*) override;
};

class R::UnsafeStatement : public Stm {
public:
    Body* body;
    UnsafeStatement(Body*);
    ~UnsafeStatement();
    void accept(IVisitor*) override;
};

class R::ScopeStatement : public Stm {
public:
    Body* body;
    ScopeStatement(Body*);
    ~ScopeStatement();
    void accept(IVisitor*) override;
};

#endif