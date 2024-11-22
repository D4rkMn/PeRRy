#ifndef R_NAMESPACE_H
#define R_NAMESPACE_H

namespace R {
    class Token;
    class Scanner;
    class ScannerMovement;
    class Parser;
    template <class T> class Environment;
    // ISharedASTNode
    class ISharedASTNode;
    // Program AST
    class Program;
    class Body;
    class LetVar;
    class StaticVar;
    class ConstVar;
    // Function AST
    class Function;
    class ParamDecList;
    class ParamDec;
    // Stm AST
    class Stm;
    class ExpStatement;
    class AssignStatement;
    class AdvanceStatement;
    class ReturnStatement;
    class PrintStatement;
    class IfStatement;
    class WhileStatement;
    class ForStatement;
    class UnsafeStatement;
    class ScopeStatement;
    // Exp AST
    class Exp;
    class BinaryExp;
    class UnaryExp;
    class IntegerExp;
    class IdentifierExp;
    class FunctionExp;
    // Visitors
    class IVisitor;
    class PrintVisitor;
    class TypeVisitor;
    class ConstVisitor;
    class ExpReduceVisitor;
    class CodegenVisitor;
    // Visitor returns
    class IVisitorReturn;
    class TypeReturn;
    class VariantReturn;
    class ReducedReturn;
    // Utility
    class EnvVariable;
    class FunctionType;
    class NumberTester;
    // Compiler
    class Compiler;
}

#endif