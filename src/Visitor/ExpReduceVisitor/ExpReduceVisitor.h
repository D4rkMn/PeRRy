#ifndef EXPREDUCEVISITOR_H
#define EXPREDUCEVISITOR_H

#include "Visitor/IVisitor.h"
#include "ASTNodes/Exp.h"

class IntegerExp;

class ExpReduceVisitor : public IVisitor {
private:
    void replaceNode(Exp*&);
    IntegerExp* getNode(IVisitorReturn*) const;

    template <typename T>
    IntegerExp* evalBinaryExp(const T&, const T&, BinaryOp) const;
    IntegerExp* evalBinaryExp_b(const bool&, const bool&, BinaryOp) const;

    template <typename T>
    IntegerExp* evalUnaryExp(const T&, UnaryOp) const;
    IntegerExp* evalUnaryExp_b(const bool&, UnaryOp) const;

public:
    void reduce(Program*);
    // Program
    void visit(Program*) override;
    void visit(Body*) override;
    void visit(LetVar*) override;
    void visit(StaticVar*) override;
    void visit(ConstVar*) override;
    // Function
    void visit(Function*) override;
    void visit(ParamDecList*) override;
    void visit(ParamDec*) override;
    // Stm
    void visit(ExpStatement*) override;
    void visit(AssignStatement*) override;
    void visit(AdvanceStatement*) override;
    void visit(ReturnStatement*) override;
    void visit(PrintStatement*) override;
    void visit(IfStatement*) override;
    void visit(WhileStatement*) override;
    void visit(ForStatement*) override;
    void visit(UnsafeStatement*) override;
    void visit(ScopeStatement*) override;
    // Exp
    IVisitorReturn* visit(BinaryExp*) override;
    IVisitorReturn* visit(UnaryExp*) override;
    IVisitorReturn* visit(IntegerExp*) override;
    IVisitorReturn* visit(IdentifierExp*) override;
    IVisitorReturn* visit(FunctionExp*) override;
};

#include "Visitor/ExpReduceVisitor/ExpReduceVisitor.tpp"

#endif