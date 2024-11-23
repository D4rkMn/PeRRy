#ifndef P_NAMESPACE_H
#define P_NAMESPACE_H

namespace P {
    class Token;
    class Scanner;
    class Parser;
    // Instructions
    class Instruction;
    class PopInstruction;
    class StopInstruction;
    class EnterInstruction;
    class MarkInstruction;
    class ReturnInstruction;
    class FCallInstruction;
    class LoadAddressInstruction;
    class LoadConstInstruction;
    class LoadVarInstruction;
    class StoreStackInstruction;
    class IncStackInstruction;
    class StoreToVarInstruction;
    class LabelInstruction;
    class JumpInstruction;
    class OpInstruction;
    class PrintInstruction;
    // Visitor
    class IVisitor;   
}

#endif