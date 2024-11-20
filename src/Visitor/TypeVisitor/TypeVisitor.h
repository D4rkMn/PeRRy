#ifndef TYPEVISITOR_H
#define TYPEVISITOR_H

#include "Visitor/IVisitor.h"
#include "Environment/Environment.h"
#include "Utility/VarType.h"
#include "Utility/EnvVariable.h"
#include "Utility/FunctionType.h"
#include <iostream>

class TypeVisitor : public IVisitor {
private:
    Environment<EnvVariable> varEnv;
    Environment<FunctionType> functionEnv;
    VarType expectedReturnType = VarType::UNKNOWN_TYPE;
    VarType getType(IVisitorReturn*) const;
    std::runtime_error TypeError(VarType, VarType) const;
    void checkTypes(VarType, VarType) const;
public:
    void check(Program*);
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
    void visit(ForStatement*) override;
    void visit(UnsafeStatement*) override;
    void visit(ScopeStatement*) override;
    // Exp
    IVisitorReturn* visit(BinaryExp*) override;
    IVisitorReturn* visit(IntegerExp*) override;
    IVisitorReturn* visit(BoolExp*) override;
    IVisitorReturn* visit(IdentifierExp*) override;
    IVisitorReturn* visit(FunctionExp*) override;
};

#endif