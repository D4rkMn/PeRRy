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
        case R::Token::LET: cout << "TOKEN(LET)"; break;
        case R::Token::CONST: cout << "TOKEN(CONST)"; break;
        case R::Token::STATIC: cout << "TOKEN(STATIC)"; break;
        case R::Token::MUT: cout << "TOKEN(MUT)"; break;
        // Type tokens
        case R::Token::INT32: cout << "TOKEN(INT32)"; break;
        case R::Token::INT64: cout << "TOKEN(INT64)"; break;
        case R::Token::UINT32: cout << "TOKEN(UINT64)"; break;
        case R::Token::UINT64: cout << "TOKEN(UINT64)"; break;
        case R::Token::BOOL: cout << "TOKEN(BOOL)"; break;
        // Arithmetic operators
        case R::Token::PLUS: cout << "TOKEN(PLUS)"; break;
        case R::Token::MINUS: cout << "TOKEN(MINUS)"; break;
        case R::Token::MUL: cout << "TOKEN(MUL)"; break;
        case R::Token::DIV: cout << "TOKEN(DIV)"; break;
        // Boolean comparisons
        case R::Token::LESS: cout << "TOKEN(LESS)"; break;
        case R::Token::LESS_EQ: cout << "TOKEN(LESS_EQ)"; break;
        case R::Token::EQUALS: cout << "TOKEN(EQUALS)"; break;
        case R::Token::GREATER: cout << "TOKEN(GREATER)"; break;
        case R::Token::GREATER_EQ: cout << "TOKEN(GREATER_EQ)"; break;
        case R::Token::NEQUALS: cout << "TOKEN(NEQUALS)"; break;
        // Scope tokens
        case R::Token::UNSAFE: cout << "TOKEN(UNSAFE)"; break;
        case R::Token::LBRACKET: cout << "TOKEN(LBRACKET)"; break;
        case R::Token::RBRACKET: cout << "TOKEN(RBRACKET)"; break;
        // Function tokens
        case R::Token::FUNCTION: cout << "TOKEN(FUNCTION)"; break;
        case R::Token::RETURN: cout << "TOKEN(RETURN)"; break;
        case R::Token::RARROW: cout << "TOKEN(RARROW)"; break;
        // If-Else tokens
        case R::Token::IF: cout << "TOKEN(IF)"; break;
        case R::Token::ELSE: cout << "TOKEN(ELSE)"; break;
        // While tokens
        case R::Token::WHILE: cout << "TOKEN(WHILE)"; break;
        // For tokens
        case R::Token::FOR: cout << "TOKEN(FOR)"; break;
        case R::Token::RANGE: cout << "TOKEN(RANGE)"; break;
        case R::Token::IN: cout << "TOKEN(IN)"; break;
        // Literal tokens
        case R::Token::INTEGER: cout << "TOKEN(INTEGER)"; break;
        case R::Token::TRUE: cout << "TOKEN(TRUE)"; break;
        case R::Token::FALSE: cout << "TOKEN(FALSE)"; break;
        case R::Token::TEXT: cout << "TOKEN(TEXT)"; break;
        // Miscellaneous operators
        case R::Token::ASSIGN: cout << "TOKEN(ASSIGN)"; break;
        case R::Token::ADVANCE: cout << "TOKEN(ADVANCE)"; break;
        // Print tokens
        case R::Token::PRINTLN: cout << "TOKEN(PRINTLN)"; break;
        // General purpose tokens
        case R::Token::LPAR: cout << "TOKEN(LPAR)"; break;
        case R::Token::RPAR: cout << "TOKEN(RPAR)"; break;
        case R::Token::COMMA: cout << "TOKEN(COMMA)"; break;
        case R::Token::SEMICOLON: cout << "TOKEN(SEMICOLON)"; break;
        // Identifier
        case R::Token::ID: cout << "TOKEN(ID)"; break;
        case R::Token::ID_DEC: cout << "TOKEN(ID_DEC)"; break;
        // Meta-tokens
        case R::Token::END: cout << "TOKEN(END)"; break;
        case R::Token::ERR: cout << "TOKEN(ERR)"; break; 
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