#ifndef P_IVISITOR_H
#define P_IVISITOR_H

#include "P/Namespace.h"

class P::IVisitor {
public:
    bool isDebug = true;
    virtual void visit(Program*) = 0;
    virtual void visit(PopInstruction*) = 0;
    virtual void visit(StopInstruction*) = 0;
    virtual void visit(EnterInstruction*) = 0;
    virtual void visit(MarkInstruction*) = 0;
    virtual void visit(ReturnInstruction*) = 0;
    virtual void visit(FCallInstruction*) = 0;
    virtual void visit(LoadAddressInstruction*) = 0;
    virtual void visit(LoadConstInstruction*) = 0;
    virtual void visit(LoadVarInstruction*) = 0;
    virtual void visit(StoreStackInstruction*) = 0;
    virtual void visit(IncStackInstruction*) = 0;
    virtual void visit(StoreToVarInstruction*) = 0;
    virtual void visit(LabelInstruction*) = 0;
    virtual void visit(JumpInstruction*) = 0;
    virtual void visit(BinaryOpInstruction*) = 0;
    virtual void visit(UnaryOpInstruction*) = 0;
    virtual void visit(PrintInstruction*) = 0;
};

#endif