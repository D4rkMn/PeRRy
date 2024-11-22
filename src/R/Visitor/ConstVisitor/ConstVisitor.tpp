#include "R/Visitor/ConstVisitor/ConstVisitor.h"
using namespace std;

template <typename T>
R::IVisitorReturn* R::ConstVisitor::evalBinaryExp(const T& v1, const T& v2, BinaryOp op) const {
    // eval expression
    T result;
    bool isBool = false;
    switch (op) {
        // Arithmetic operators
        case PLUS_OP: result = v1 + v2; break;
        case MINUS_OP: {
            result = v1 - v2;
            if (v1 <= v2 && lhsUnsigned) {
                string msg = "Error: La operacion de resta resultaria en underflow";
                throw runtime_error(msg);
            }
            break;
        }
        case MUL_OP: result = v1 * v2; break;
        case DIV_OP: result = v1 / v2; break;
        // Boolean operators
        case LESS_OP: result = (v1 < v2); isBool = true; break;
        case LESS_EQ_OP: result = (v1 <= v2); isBool = true; break;
        case EQUALS_OP: result = (v1 == v2); isBool = true; break;
        case GREATER_OP: result = (v1 > v2); isBool = true; break;
        case GREATER_EQ_OP: result = (v1 >= v2); isBool = true; break;
        case NEQUALS_OP: result = (v1 != v2); isBool = true; break;
        default: {
            string msg = "Error: Operacion binaria desconocida";
            throw runtime_error(msg);
        }
    }
    if (isBool) {
        return new VariantReturn(bool(result));
    }
    return new VariantReturn(result);
}

template <typename T>
R::IVisitorReturn* R::ConstVisitor::evalUnaryExp(const T& v, UnaryOp op) const {
    // eval expression
    T result;
    switch (op) {
        // Arithmetic operators
        case NEG_OP: result = -v; break;
        default: {
            string msg = "Error: Operacion unaria incompatible";
            throw runtime_error(msg);
        }
    }
    return new VariantReturn(result);
}