#ifndef EXP_H
#define EXP_H

#include <list>
#include <string>
#include "ASTNodes/ISharedASTNode.h"

class IVisitor;

enum BinaryOp {
    PLUS_OP, MINUS_OP, MUL_OP, DIV_OP, // Arithmetic operators
    LESS_OP, LESS_EQ_OP, EQUALS_OP, // Boolean operators
    GREATER_OP, GREATER_EQ_OP, NEQUALS_OP // Boolean operators
};

class Exp {
public:
    virtual int  accept(IVisitor* visitor) = 0;
    virtual ~Exp() {}
    static std::string binopToString(BinaryOp op);
};

class BinaryExp : public Exp {
public:
    Exp *left, *right;
    BinaryOp op;
    BinaryExp(Exp*, Exp*, BinaryOp);
    ~BinaryExp();
    int accept(IVisitor*) override;
};

class IntegerExp : public Exp {
public:
    uint64_t value;
    VarType type;
    IntegerExp(uint64_t);
    ~IntegerExp() {}
    int accept(IVisitor*) override;
};

class IdentifierExp : public Exp {
public:
    std::string name;
    IdentifierExp(const std::string&);
    ~IdentifierExp() {}
    int accept(IVisitor*) override;
};

class FunctionExp : public Exp {
public:
    std::string name;
    std::list<Exp*> args;
    FunctionExp(const std::string&);
    ~FunctionExp();
    int accept(IVisitor*) override;
};

#endif