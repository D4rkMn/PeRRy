#ifndef EXP_H
#define EXP_H

#include <list>
#include <string>
#include "ASTNodes/ISharedASTNode.h"

class Visitor;

enum BinaryOp {
    PLUS_OP, MINUS_OP, MUL_OP, DIV_OP, // Arithmetic operators
    LESS_OP, LESS_EQ_OP, EQUALS_OP, // Boolean operators
    GREATER_OP, GREATER_EQ_OP, NEQUALS_OP // Boolean operators
};

class Exp {
public:
    virtual int  accept(Visitor* visitor) = 0;
    virtual ~Exp() = 0;
    static std::string binopToString(BinaryOp op);
};

class BinaryExp : public Exp {
public:
    Exp *left, *right;
    BinaryOp op;
    BinaryExp(Exp*, Exp*, BinaryOp);
    ~BinaryExp();
    int accept(Visitor*) override;
};

class IntegerExp : public Exp {
public:
    int value;
    IntegerExp(int);
    ~IntegerExp() = default;
    int accept(Visitor*) override;
};

class IdentifierExp : public Exp {
public:
    std::string name;
    IdentifierExp(const std::string&);
    ~IdentifierExp() = default;
    int accept(Visitor*) override;
};

class FunctionExp : public Exp {
public:
    std::string name;
    std::list<Exp*> args;
    FunctionExp(const std::string&);
    ~FunctionExp();
    int accept(Visitor*) override;
};

#endif