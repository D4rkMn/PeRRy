#include "Visitor/ConstVisitor/ConstVisitor.h"
using namespace std;

template <typename T>
IVisitorReturn* ConstVisitor::evalBinaryExp(T v1, T v2, BinaryOp op) const {
    // eval expression
    T result;
    switch (op) {
        // Arithmetic operators
        case PLUS_OP: result = v1 + v2; break;
        case MINUS_OP: result = v1 - v2; break;
        case MUL_OP: result = v1 * v2; break;
        case DIV_OP: result = v1 / v2; break;
        // Boolean operators
        case LESS_OP: result = (v1 < v2); break;
        case LESS_EQ_OP: result = (v1 <= v2); break;
        case EQUALS_OP: result = (v1 == v2); break;
        case GREATER_OP: result = (v1 > v2); break;
        case GREATER_EQ_OP: result = (v1 >= v2); break;
        case NEQUALS_OP: result = (v1 != v2); break;
        default: {
            string msg = "Error: Operacion binaria desconocida";
            throw runtime_error(msg);
        }
    }
    return new VariantReturn(result);
}