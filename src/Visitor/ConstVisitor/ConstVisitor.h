#ifndef CONSTVISITOR_H
#define CONSTVISITOR_H

#include "Visitor/IVisitor.h"
#include "Environment/Environment.h"
#include "Environment/HeapEnvironment.h"
#include "Utility/EnvVariable.h"

class IEnvConst;
class Exp;
class IdentifierExp;
class BinaryExp;
class FunctionExp;

class ConstVisitor : public IVisitor {
private:

    enum class ExpParentType {
        NONE,
        BINARY_EXP,
        FUNCTION_EXP
    };
    bool fetchingForConst = false;
    Exp* expParent = nullptr;
    ExpParentType parentType = ExpParentType::NONE;

    Environment<EnvVariable> varEnv;
    HeapEnvironment<IEnvConst*> constEnv;

    long long getValue(IVisitorReturn*) const;
    long long envConstToLLong(IEnvConst*) const;
    void replaceBinary(BinaryExp*, IdentifierExp*, long long);
    void replaceFunction(FunctionExp*, IdentifierExp*, long long);

public:
    void replace(Program*);
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
    IVisitorReturn* visit(IdentifierExp*) override;
    IVisitorReturn* visit(FunctionExp*) override;
};

#endif