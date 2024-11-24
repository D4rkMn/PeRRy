#include "P/Visitor/InstructionVisitor/InstructionVisitor.h"
#include "P/Visitor/InstructionVisitor/StackObject.h"

#include "P/Instruction/Instruction.h"
#include "P/Instruction/Program.h"
using namespace std;

std::runtime_error P::InstructionVisitor::InterpretError(const std::string& s) {
    string msg = "Error: " + s + " - Línea " + to_string(pc + 1);
    return runtime_error(msg);
}

void P::InstructionVisitor::interpret(Program* p) {
    program = p;
    program->accept(this);
    program = nullptr;
}

void P::InstructionVisitor::visit(Program* p) {
    env.addLevel();
    markFunctionStack.push({0, ".null"});
    for (; pc < program->instructions.size(); pc++) {
        program->instructions[pc]->accept(this);
    }
    env.removeLevel();
}

void P::InstructionVisitor::visit(PopInstruction* ins) {
    mainStack.pop();
}

void P::InstructionVisitor::visit(StopInstruction* ins) {
    pc = program->instructions.size() + 100;
}

void P::InstructionVisitor::visit(EnterInstruction* ins) {
    env.addLevel();
}

void P::InstructionVisitor::visit(MarkInstruction* ins) {
    string currentFunction = markFunctionStack.top().second;
    if (ins->functionEnter) {
        markFunctionStack.push({mainStack.size(), currentFunction + to_string(unique++)});
    }
    else {
        env.addLevel();
        markStack.push({mainStack.size(), currentFunction});
    }
}

void P::InstructionVisitor::visit(ReturnInstruction* ins) {
    if (ins->type == ReturnInstruction::SCOPE) {
        if (markStack.empty()) {
            throw InterpretError("No hay ningun stack frame marcado");
        }
        if (markStack.top().first > mainStack.size()) {
            throw InterpretError("Stack frame ha sido modificado erróneamente");
        }
        while (markStack.top().first < mainStack.size()) {
            mainStack.pop();
        }
        markStack.pop();
        env.removeLevel();
        return;
    }
    if (markFunctionStack.empty()) {
        throw InterpretError("No hay ningun stack frame marcado");
    }
    if (markFunctionStack.top().first > mainStack.size()) {
        throw InterpretError("Stack frame ha sido modificado erróneamente");
    }
    env.removeLevel();
    bool returning = false;
    int64_t returnValue = 0;
    if (ins->type == ReturnInstruction::F_RET) {
        auto _value = mainStack.top(); mainStack.pop();
        if (_value->getType() != IStackObject::VALUE_OBJECT) {
            throw InterpretError("Los elementos del stack no coinciden con la operación");
        }
        ValueObject* value = dynamic_cast<ValueObject*>(_value);
        returnValue = value->value;
        returning = true;
    }
    while (!mainStack.empty() && markFunctionStack.top().first < mainStack.size()) {
        mainStack.pop();
    }
    string currentFunction = markFunctionStack.top().second;
    while (!markStack.empty() && markStack.top().second == currentFunction) {
        markStack.pop();
        env.removeLevel();
    }
    markFunctionStack.pop();
    pc = pcStack.top(); pcStack.pop();
    if (returning) {
        mainStack.push(new ValueObject(returnValue));
    }
}

void P::InstructionVisitor::visit(FCallInstruction* ins) {
    pcStack.push(pc);
    pc = program->jumpTable[ins->functionName] - 1;
}

void P::InstructionVisitor::visit(LoadAddressInstruction* ins) {
    mainStack.push(new AddressObject(ins->id));
}

void P::InstructionVisitor::visit(LoadConstInstruction* ins) {
    mainStack.push(new ValueObject(ins->value));
}

void P::InstructionVisitor::visit(LoadVarInstruction* ins) {
    auto option = env.getVariableValue(ins->id);
    if (!option.has_value()) {
        string msg = ins->id + " no ha sido declarado en este scope";
        throw InterpretError(msg);
    }
    mainStack.push(new ValueObject(option.value()));
}

void P::InstructionVisitor::visit(StoreStackInstruction* ins) {
    if (mainStack.size() < 2) {
        throw InterpretError("El stack no tiene suficiente espacio para este operación");
    }
    auto _value = mainStack.top(); mainStack.pop();
    auto _target = mainStack.top(); mainStack.pop();
    if (_value->getType() != IStackObject::VALUE_OBJECT || _target->getType() != IStackObject::ADDRESS_OBJECT) {
        throw InterpretError("Los elementos del stack no coinciden con la operación");
    }
    ValueObject* value = dynamic_cast<ValueObject*>(_value);
    AddressObject* target = dynamic_cast<AddressObject*>(_target);
    bool exists = env.checkVariableExists(target->id);
    if (!exists) {
        env.addVariable(target->id, value->value);
    }
    else {
        env.updateVariableValue(target->id, value->value);
    }
}

void P::InstructionVisitor::visit(IncStackInstruction* ins) {
    if (mainStack.size() < 2) {
        throw InterpretError("El stack no tiene suficiente espacio para este operación");
    }
    auto _value = mainStack.top(); mainStack.pop();
    auto _target = mainStack.top(); mainStack.pop();
    if (_value->getType() != IStackObject::VALUE_OBJECT || _target->getType() != IStackObject::ADDRESS_OBJECT) {
        throw InterpretError("Los elementos del stack no coinciden con la operación");
    }
    ValueObject* value = dynamic_cast<ValueObject*>(_value);
    AddressObject* target = dynamic_cast<AddressObject*>(_target);
    bool exists = env.checkVariableExists(target->id);
    if (!exists) {
        env.addVariable(target->id, value->value);
    }
    else {
        int64_t currentValue = env.getVariableValue(target->id).value();
        env.updateVariableValue(target->id, currentValue + value->value);
    }
}

void P::InstructionVisitor::visit(StoreToVarInstruction* ins) {
    if (mainStack.empty()) {
        throw InterpretError("El stack no tiene suficiente espacio para este operación");
    }
    auto _value = mainStack.top(); mainStack.pop();
    if (_value->getType() != IStackObject::VALUE_OBJECT) {
        throw InterpretError("Los elementos del stack no coinciden con la operación");
    }
    ValueObject* value = dynamic_cast<ValueObject*>(_value);
    env.addVariable(ins->id, value->value);
}

void P::InstructionVisitor::visit(LabelInstruction* ins) {
    // pass
}

void P::InstructionVisitor::visit(JumpInstruction* ins) {
    // FJP
    if (!ins->unconditional) {
        if (mainStack.empty()) {
            throw InterpretError("El stack no tiene suficiente espacio para este operación");   
        }
        auto _value = mainStack.top(); mainStack.pop();
        if (_value->getType() != IStackObject::VALUE_OBJECT) {
            throw InterpretError("Los elementos del stack no coinciden con la operación");
        }
        ValueObject* value = dynamic_cast<ValueObject*>(_value);
        if (value->value != 0) return; // if true, dont jump
    }
    // UJP
    pc = program->jumpTable[ins->label];
}

void P::InstructionVisitor::visit(BinaryOpInstruction* ins) {
    if (mainStack.size() < 2) {
        throw InterpretError("El stack no tiene suficiente espacio para este operación");
    }
    auto _value1 = mainStack.top(); mainStack.pop();
    auto _value2 = mainStack.top(); mainStack.pop();
    if (_value1->getType() != IStackObject::VALUE_OBJECT || _value2->getType() != IStackObject::VALUE_OBJECT) {
        throw InterpretError("Los elementos del stack no coinciden con la operación");
    }
    ValueObject* value1 = dynamic_cast<ValueObject*>(_value1);
    ValueObject* value2 = dynamic_cast<ValueObject*>(_value2);
    // inverted because of LIFO
    int64_t v1 = value2->value, v2 = value1->value, result = 0;
    switch (ins->op) {
        case Op::ADD: result = v1 + v2; break;
        case Op::SUB: result = v1 - v2; break;
        case Op::MUL: result = v1 * v2; break;
        case Op::DIV: result = v1 / v2; break;
        case Op::LESS: result = v1 < v2; break;
        case Op::LESS_EQ: result = v1 <= v2; break;
        case Op::GREATER: result = v1 > v2; break;
        case Op::GREATER_EQ: result = v1 >= v2; break;
        case Op::EQUALS: result = v1 == v2; break;
        case Op::NEQUALS: result = v1 != v2; break;
        default: {
            throw InterpretError("Operacion binaria inválida");
        }
    }
    mainStack.push(new ValueObject(result));
}

void P::InstructionVisitor::visit(UnaryOpInstruction* ins) {
    if (mainStack.empty()) {
        throw InterpretError("El stack no tiene suficiente espacio para este operación");
    }
    auto _value = mainStack.top(); mainStack.pop();
    if (_value->getType() != IStackObject::VALUE_OBJECT) {
        throw InterpretError("Los elementos del stack no coinciden con la operación");
    }
    ValueObject* value = dynamic_cast<ValueObject*>(_value);
    int64_t v = value->value, result = 0;
    switch (ins->op) {
        case Op::NEG: result = -v; break;
        case Op::NOT: result =(v == 0) ? 1 : 0; break;
        default: {
            throw InterpretError("Operacion unaria inválida");
        }
    }
    mainStack.push(new ValueObject(result));
}

void P::InstructionVisitor::visit(PrintInstruction* ins) {
    if (ins->doNewLine) {
        cout << "\n";
        return;
    }
    if (mainStack.empty()) {
        throw InterpretError("El stack no tiene suficiente espacio para este operación");
    }
    auto _value = mainStack.top(); mainStack.pop();
    if (_value->getType() != IStackObject::VALUE_OBJECT) {
        throw InterpretError("Los elementos del stack no coinciden con la operación");
    }
    ValueObject* value = dynamic_cast<ValueObject*>(_value);
    cout << value->value << " ";
}
