#include <iostream>
#include "Token.h"

using namespace std;

Token::Token(Type type, size_t line) : type(type), line(line) { text = ""; }

Token::Token(Type type, char c, size_t line) : type(type), line(line) { text = string(1, c); }

Token::Token(Type type, const string& source, int first, int last, size_t line) : type(type), line(line) {
    text = source.substr(first, last);
}

std::ostream& operator << ( std::ostream& outs, const Token & tok ) {
    switch (tok.type) {
        // Variable declaration tokens
        case Token::LET: cout << "TOKEN(LET)"; break;
        case Token::CONST: cout << "TOKEN(CONST)"; break;
        case Token::STATIC: cout << "TOKEN(STATIC)"; break;
        case Token::MUT: cout << "TOKEN(MUT)"; break;
        // Type tokens
        case Token::INT32: cout << "TOKEN(INT32)"; break;
        case Token::INT64: cout << "TOKEN(INT64)"; break;
        case Token::UINT32: cout << "TOKEN(UINT64)"; break;
        case Token::UINT64: cout << "TOKEN(UINT64)"; break;
        case Token::BOOL: cout << "TOKEN(BOOL)"; break;
        // Arithmetic operators
        case Token::PLUS: cout << "TOKEN(PLUS)"; break;
        case Token::MINUS: cout << "TOKEN(MINUS)"; break;
        case Token::MUL: cout << "TOKEN(MUL)"; break;
        case Token::DIV: cout << "TOKEN(DIV)"; break;
        // Boolean comparisons
        case Token::LESS: cout << "TOKEN(LESS)"; break;
        case Token::LESS_EQ: cout << "TOKEN(LESS_EQ)"; break;
        case Token::EQUALS: cout << "TOKEN(EQUALS)"; break;
        case Token::GREATER: cout << "TOKEN(GREATER)"; break;
        case Token::GREATER_EQ: cout << "TOKEN(GREATER_EQ)"; break;
        case Token::NEQUALS: cout << "TOKEN(NEQUALS)"; break;
        // Scope tokens
        case Token::UNSAFE: cout << "TOKEN(UNSAFE)"; break;
        case Token::LBRACKET: cout << "TOKEN(LBRACKET)"; break;
        case Token::RBRACKET: cout << "TOKEN(RBRACKET)"; break;
        // Function tokens
        case Token::FUNCTION: cout << "TOKEN(FUNCTION)"; break;
        case Token::RETURN: cout << "TOKEN(RETURN)"; break;
        case Token::RARROW: cout << "TOKEN(RARROW)"; break;
        // If-Else tokens
        case Token::IF: cout << "TOKEN(IF)"; break;
        case Token::ELSE: cout << "TOKEN(ELSE)"; break;
        // While tokens
        case Token::WHILE: cout << "TOKEN(WHILE)"; break;
        // For tokens
        case Token::FOR: cout << "TOKEN(FOR)"; break;
        case Token::RANGE: cout << "TOKEN(RANGE)"; break;
        case Token::IN: cout << "TOKEN(IN)"; break;
        // Literal tokens
        case Token::INTEGER: cout << "TOKEN(INTEGER)"; break;
        case Token::TRUE: cout << "TOKEN(TRUE)"; break;
        case Token::FALSE: cout << "TOKEN(FALSE)"; break;
        case Token::TEXT: cout << "TOKEN(TEXT)"; break;
        // Miscellaneous operators
        case Token::ASSIGN: cout << "TOKEN(ASSIGN)"; break;
        case Token::ADVANCE: cout << "TOKEN(ADVANCE)"; break;
        // Print tokens
        case Token::PRINTLN: cout << "TOKEN(PRINTLN)"; break;
        // General purpose tokens
        case Token::LPAR: cout << "TOKEN(LPAR)"; break;
        case Token::RPAR: cout << "TOKEN(RPAR)"; break;
        case Token::COMMA: cout << "TOKEN(COMMA)"; break;
        case Token::SEMICOLON: cout << "TOKEN(SEMICOLON)"; break;
        // Identifier
        case Token::ID: cout << "TOKEN(ID)"; break;
        case Token::ID_DEC: cout << "TOKEN(ID_DEC)"; break;
        // Meta-tokens
        case Token::END: cout << "TOKEN(END)"; break;
        case Token::ERR: cout << "TOKEN(ERR)"; break; 
        default: outs << "TOKEN(UNKNOWN)"; break;
    }
    return outs;
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
    return outs << *tok;
}

bool Token::isVarType() const {
    return (
        type == Token::INT32 ||
        type == Token::INT64 ||
        type == Token::UINT32 ||
        type == Token::UINT64 ||
        type == Token::BOOL
    );
}

VarType Token::toVarType() const {
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

BinaryOp Token::toBinaryOp() const {
    switch (type) {
        // Arithmetic operators
        case Token::PLUS: return BinaryOp::PLUS_OP; break;
        case Token::MINUS: return BinaryOp::MINUS_OP; break;
        case Token::MUL: return BinaryOp::MUL_OP; break;
        case Token::DIV: return BinaryOp::DIV_OP; break;
        // Boolean operators
        case Token::LESS: return BinaryOp::LESS_OP; break;
        case Token::LESS_EQ: return BinaryOp::LESS_EQ_OP; break;
        case Token::GREATER: return BinaryOp::GREATER_OP; break;
        case Token::GREATER_EQ: return BinaryOp::GREATER_EQ_OP; break;
        case Token::EQUALS: return BinaryOp::EQUALS_OP; break;
        case Token::NEQUALS: return BinaryOp::NEQUALS_OP; break;
        // Default
        default: {
            string msg = "Error: Tipo no permitido - " + text;
            throw runtime_error(msg);
        }
    }
}