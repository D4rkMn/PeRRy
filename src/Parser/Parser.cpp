#include <iostream>
#include <stdexcept>

#include "Parser/Parser.h"
using namespace std;

Parser::Parser(Scanner* scanner) : scanner(scanner) {
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        string msg = "Error: Primer token no reconocido: '" + current->text + "' - línea " + to_string(current->line);
        throw runtime_error(msg);
    }
}

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return (current->type == ttype);
}

bool Parser::matchVarType() {
    if (checkVarType()) {
        advance();
        return true;
    }
    return false;
}

bool Parser::checkVarType() {
    return (
        check(Token::INT32) || 
        check(Token::INT64) || 
        check(Token::UINT32) || 
        check(Token::UINT64) || 
        check(Token::BOOL)
    );
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR)) {
            string msg = "Error: Carácter inválido: '" + current->text + "' - línea " + to_string(current->line);
            throw runtime_error(msg);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END);
}

void Parser::backtrack() {
    scanner->backtrack();
    current = previous;
    previous = nullptr;
}

runtime_error Parser::SyntaxError(const string& msg) const {
    string s = "Error: " + msg + ", pero en lugar se encontró '" + current->text + "' - línea " + to_string(current->line);
    return runtime_error(s);
}

VarType Parser::tokenTypeToVarType(Token::Type type) const {
    switch (type) {
        case Token::INT32: return VarType::INT32_TYPE; break;
        case Token::INT64: return VarType::INT64_TYPE; break;
        case Token::UINT32: return VarType::UINT32_TYPE; break;
        case Token::UINT64: return VarType::UINT64_TYPE; break;
        case Token::BOOL: return VarType::BOOL_TYPE; break;
        default: {
            string msg = "Error: Tipo no permitido - " + current->text;
            throw runtime_error(msg);
        }
    }
}

BinaryOp Parser::tokenTypeToBinaryOp(Token::Type type) const {
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
            string msg = "Error: Tipo no permitido - " + current->text;
            throw runtime_error(msg);
        }
    }
}