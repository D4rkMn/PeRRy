#include <iostream>
#include "R/Token/Token.h"
using namespace std;

R::Token::Token(Type type, size_t line) : type(type), line(line) { text = ""; }

R::Token::Token(Type type, char c, size_t line) : type(type), line(line) { text = string(1, c); }

R::Token::Token(Type type, const string& source, int first, int last, size_t line) : type(type), line(line) {
    text = source.substr(first, last);
}

std::ostream& operator<<(std::ostream& outs, const R::Token& tok) {
    switch (tok.type) {
        // Variable declaration tokens
        case R::Token::LET: outs << "TOKEN(LET)"; break;
        case R::Token::CONST: outs << "TOKEN(CONST)"; break;
        case R::Token::STATIC: outs << "TOKEN(STATIC)"; break;
        case R::Token::MUT: outs << "TOKEN(MUT)"; break;
        // Type tokens
        case R::Token::INT32: outs << "TOKEN(INT32)"; break;
        case R::Token::INT64: outs << "TOKEN(INT64)"; break;
        case R::Token::UINT32: outs << "TOKEN(UINT64)"; break;
        case R::Token::UINT64: outs << "TOKEN(UINT64)"; break;
        case R::Token::BOOL: outs << "TOKEN(BOOL)"; break;
        // Arithmetic operators
        case R::Token::PLUS: outs << "TOKEN(PLUS)"; break;
        case R::Token::MINUS: outs << "TOKEN(MINUS)"; break;
        case R::Token::MUL: outs << "TOKEN(MUL)"; break;
        case R::Token::DIV: outs << "TOKEN(DIV)"; break;
        // Boolean comparisons
        case R::Token::LESS: outs << "TOKEN(LESS)"; break;
        case R::Token::LESS_EQ: outs << "TOKEN(LESS_EQ)"; break;
        case R::Token::EQUALS: outs << "TOKEN(EQUALS)"; break;
        case R::Token::GREATER: outs << "TOKEN(GREATER)"; break;
        case R::Token::GREATER_EQ: outs << "TOKEN(GREATER_EQ)"; break;
        case R::Token::NEQUALS: outs << "TOKEN(NEQUALS)"; break;
        // Scope tokens
        case R::Token::UNSAFE: outs << "TOKEN(UNSAFE)"; break;
        case R::Token::LBRACKET: outs << "TOKEN(LBRACKET)"; break;
        case R::Token::RBRACKET: outs << "TOKEN(RBRACKET)"; break;
        // Function tokens
        case R::Token::FUNCTION: outs << "TOKEN(FUNCTION)"; break;
        case R::Token::RETURN: outs << "TOKEN(RETURN)"; break;
        case R::Token::RARROW: outs << "TOKEN(RARROW)"; break;
        // If-Else tokens
        case R::Token::IF: outs << "TOKEN(IF)"; break;
        case R::Token::ELSE: outs << "TOKEN(ELSE)"; break;
        // While tokens
        case R::Token::WHILE: outs << "TOKEN(WHILE)"; break;
        // For tokens
        case R::Token::FOR: outs << "TOKEN(FOR)"; break;
        case R::Token::RANGE: outs << "TOKEN(RANGE)"; break;
        case R::Token::IN: outs << "TOKEN(IN)"; break;
        // Literal tokens
        case R::Token::INTEGER: outs << "TOKEN(INTEGER)"; break;
        case R::Token::TRUE: outs << "TOKEN(TRUE)"; break;
        case R::Token::FALSE: outs << "TOKEN(FALSE)"; break;
        case R::Token::TEXT: outs << "TOKEN(TEXT)"; break;
        // Miscellaneous operators
        case R::Token::ASSIGN: outs << "TOKEN(ASSIGN)"; break;
        case R::Token::ADVANCE: outs << "TOKEN(ADVANCE)"; break;
        // Print tokens
        case R::Token::PRINTLN: outs << "TOKEN(PRINTLN)"; break;
        // General purpose tokens
        case R::Token::LPAR: outs << "TOKEN(LPAR)"; break;
        case R::Token::RPAR: outs << "TOKEN(RPAR)"; break;
        case R::Token::COMMA: outs << "TOKEN(COMMA)"; break;
        case R::Token::SEMICOLON: outs << "TOKEN(SEMICOLON)"; break;
        // Identifier
        case R::Token::ID: outs << "TOKEN(ID)"; break;
        case R::Token::ID_DEC: outs << "TOKEN(ID_DEC)"; break;
        // Meta-tokens
        case R::Token::END: outs << "TOKEN(END)"; break;
        case R::Token::ERR: outs << "TOKEN(ERR)"; break; 
        default: outs << "TOKEN(UNKNOWN)"; break;
    }
    return outs;
}

std::ostream& operator<<(std::ostream& outs, const R::Token* tok) {
    return outs << *tok;
}

bool R::Token::isVarType() const {
    return (
        type == Token::INT32 ||
        type == Token::INT64 ||
        type == Token::UINT32 ||
        type == Token::UINT64 ||
        type == Token::BOOL
    );
}

R::VarType R::Token::toVarType() const {
    switch (type) {
        case Token::INT32: return VarType::INT32_TYPE; break;
        case Token::INT64: return VarType::INT64_TYPE; break;
        case Token::UINT32: return VarType::UINT32_TYPE; break;
        case Token::UINT64: return VarType::UINT64_TYPE; break;
        case Token::BOOL: return VarType::BOOL_TYPE; break;
        default: {
            string msg = "Error: Tipo no permitido - " + text;
            throw runtime_error(msg);
        }
    }
}

R::BinaryOp R::Token::toBinaryOp() const {
    switch (type) {
        // Arithmetic operators
        case R::Token::PLUS: return BinaryOp::PLUS_OP; break;
        case R::Token::MINUS: return BinaryOp::MINUS_OP; break;
        case R::Token::MUL: return BinaryOp::MUL_OP; break;
        case R::Token::DIV: return BinaryOp::DIV_OP; break;
        // Boolean operators
        case R::Token::LESS: return BinaryOp::LESS_OP; break;
        case R::Token::LESS_EQ: return BinaryOp::LESS_EQ_OP; break;
        case R::Token::GREATER: return BinaryOp::GREATER_OP; break;
        case R::Token::GREATER_EQ: return BinaryOp::GREATER_EQ_OP; break;
        case R::Token::EQUALS: return BinaryOp::EQUALS_OP; break;
        case R::Token::NEQUALS: return BinaryOp::NEQUALS_OP; break;
        // Default
        default: {
            string msg = "Error: Tipo no permitido - " + text;
            throw runtime_error(msg);
        }
    }
}