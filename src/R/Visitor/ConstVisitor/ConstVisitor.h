#ifndef R_CONSTVISITOR_H
#define R_CONSTVISITOR_H

#include "R/Visitor/IVisitor.h"
#include "R/Environment/Environment.h"
#include "R/Visitor/ConstVisitor/VariantReturn.h"
#include "R/Utility/EnvVariable.h"
#include "R/ASTNodes/Exp.h"
#include "R/Namespace.h"

class R::ConstVisitor : public IVisitor {
private:

    enum class ExpParentType {
        NONE,
        BINARY_EXP,
        UNARY_EXP,
        FUNCTION_EXP
    };
    bool fetchingForConst = false;
    bool replacingRootExp = false;
    bool deleteConstDec = false;
    Exp* expParent = nullptr;
    ExpParentType parentType = ExpParentType::NONE;
    bool lhsUnsigned = false;

    Environment<EnvVariable> varEnv;
    Environment<ConstVariant> constEnv;

    ConstVariant getValue(IVisitorReturn*) const;

    template <typename T>
    IVisitorReturn* evalBinaryExp(const T&, const T&, BinaryOp) const;
    IVisitorReturn* evalBinaryExp_b(const bool&, const bool&, BinaryOp) const;

    template <typename T>
    IVisitorReturn* evalUnaryExp(const T&, UnaryOp) const;
    IVisitorReturn* evalUnaryExp_b(const bool&, UnaryOp) const;
    
    void replaceBinary(BinaryExp*, IdentifierExp*, const ConstVariant&);
    void replaceFunction(FunctionExp*, IdentifierExp*, const ConstVariant&);
    void replaceASTNode(Exp*&, const ConstVariant&);

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

#include "R/Visitor/ConstVisitor/ConstVisitor.tpp"

#endif