#ifndef R_EXP_H
#define R_EXP_H

#include <list>
#include <string>
#include "R/ASTNodes/ISharedASTNode.h"
#include "R/Namespace.h"
#include "R/Utility/VarType.h"
#include <variant>

namespace R {
    enum BinaryOp {
        PLUS_OP, MINUS_OP, MUL_OP, DIV_OP, // Arithmetic operators
        LESS_OP, LESS_EQ_OP, EQUALS_OP, // Boolean operators
        GREATER_OP, GREATER_EQ_OP, NEQUALS_OP // Boolean operators
    };
    enum UnaryOp {
        NEG_OP, // Arithmetic operators
        NOT_OP // Boolean operators
    };
}

class R::Exp {
public:
    virtual R::IVisitorReturn* accept(IVisitor* visitor) = 0;
    virtual ~Exp() {}
    static std::string binopToString(BinaryOp op);
    static std::string unopToString(UnaryOp op);
};

class R::BinaryExp : public R::Exp {
public:
    Exp *left, *right;
    BinaryOp op;
    BinaryExp(Exp*, Exp*, BinaryOp);
    ~BinaryExp();
    IVisitorReturn* accept(IVisitor*) override;
};

class R::UnaryExp : public R::Exp {
public:
    Exp* exp;
    UnaryOp op;
    UnaryExp(Exp*, UnaryOp);
    ~UnaryExp();
    IVisitorReturn* accept(IVisitor*) override;
};

class R::IntegerExp : public R::Exp {
public:
    std::variant<int32_t, int64_t, uint32_t, uint64_t, bool> value;
    VarType type;
    bool isImplicit = false;
    IntegerExp(const std::string&);
    IntegerExp(const std::string&, VarType);
    IntegerExp(int32_t);
    IntegerExp(int64_t);
    IntegerExp(uint32_t);
    IntegerExp(uint64_t);
    IntegerExp(bool);
    ~IntegerExp() {}
    IVisitorReturn* accept(IVisitor*) override;
};

class R::IdentifierExp : public R::Exp {
public:
    std::string name;
    IdentifierExp(const std::string&);
    ~IdentifierExp() {}
    IVisitorReturn* accept(IVisitor*) override;
};

class R::FunctionExp : public R::Exp {
public:
    std::string name;
    std::list<Exp*> args;
    FunctionExp(const std::string&);
    ~FunctionExp();
    IVisitorReturn* accept(IVisitor*) override;
};

#endif