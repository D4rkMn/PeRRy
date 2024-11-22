#ifndef R_TYPEVISITOR_H
#define R_TYPEVISITOR_H

#include "R/Visitor/IVisitor.h"
#include "R/Environment/Environment.h"
#include "R/Utility/VarType.h"
#include "R/Utility/EnvVariable.h"
#include "R/Utility/FunctionType.h"
#include "R/Namespace.h"
#include <iostream>
#include <variant>

class R::TypeVisitor : public IVisitor {
private:
    Environment<EnvVariable> varEnv;
    Environment<FunctionType> functionEnv;
    bool checkingComparison = false;
    bool awaitingReturn = false;
    VarType expectedReturnType = VarType::UNKNOWN_TYPE;
    VarType obtainedReturnType = VarType::UNKNOWN_TYPE;
    VarType lhsType = VarType::VOID_TYPE;
    VarType getType(IVisitorReturn*) const;
    std::runtime_error TypeError(VarType, VarType) const;
    void checkTypes(VarType, VarType) const;
    bool tryImplicitCast(VarType, IntegerExp*&) const;
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

#endif