#include "P/Namespace.h"
#include "P/Instruction/Instruction.h"
#include "P/Instruction/Program.h"
#include "P/Visitor/IVisitor.h"

void P::Program::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::PopInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::StopInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::EnterInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::MarkInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::ReturnInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::FCallInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::LoadAddressInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::LoadConstInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::LoadVarInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::StoreStackInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::IncStackInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::StoreToVarInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::LabelInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::JumpInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::BinaryOpInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::UnaryOpInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void P::PrintInstruction::accept(IVisitor* visitor) {
    visitor->visit(this);
}
