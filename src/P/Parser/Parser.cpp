#include <iostream>
#include <stdexcept>

#include "P/Parser/Parser.h"
using namespace std;

void P::Parser::resetScanner() { scanner = nullptr; }

void P::Parser::setScanner(Scanner* s) { 
    scanner = s;
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        string msg = "Error: Primer token no reconocido: '" + current->text + "' - línea " + to_string(current->line);
        throw runtime_error(msg);
    }
}

bool P::Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool P::Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return (current->type == ttype);
}

bool P::Parser::advance() {
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

bool P::Parser::isAtEnd() {
    return (current->type == Token::END);
}

runtime_error P::Parser::SyntaxError(const string& msg) const {
    string s = "Error: " + msg + ", pero en lugar se encontró '" + current->text + "' - línea " + to_string(current->line);
    return runtime_error(s);
}

P::Op P::Parser::tokenToOp(P::Token token) const {
    switch (token.type) {
        // Arithmetic
        case Token::ADI: return Op::ADD; break;
        case Token::SBI: return Op::SUB; break;
        case Token::MPI: return Op::MUL; break;
        case Token::DVI: return Op::DIV; break;
        case Token::NGI: return Op::NEG; break;
        // Logical
        case Token::LESc: return Op::LESS; break;
        case Token::LEQc: return Op::LESS_EQ; break;
        case Token::GRTc: return Op::GREATER; break;
        case Token::GEQc: return Op::GREATER_EQ; break;
        case Token::EQUc: return Op::EQUALS; break;
        case Token::NEQc: return Op::NEQUALS; break;
        case Token::NOT: return Op::NOT; break;
        default: {
            string msg = "Error: Operacion inválida - '" + current->text + "'";
            throw runtime_error(msg);
        }
    }
}