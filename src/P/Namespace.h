#ifndef P_NAMESPACE_H
#define P_NAMESPACE_H

namespace P {
    class Token;
    class Scanner;
    class Parser;
    template <class T> class Environment;
    // Instructions
    class Program;
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
    class BinaryOpInstruction;
    class UnaryOpInstruction;
    class PrintInstruction;
    // Visitor
    class IVisitor;
    class InstructionVisitor;
    class IStackObject;   
    class AddressObject;
    class ValueObject;
}

#endif