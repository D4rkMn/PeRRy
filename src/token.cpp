#include <iostream>
#include "token.h"

using namespace std;

Token::Token(Type type):type(type) { text = ""; }

Token::Token(Type type, char c):type(type) { text = string(1, c); }

Token::Token(Type type, const string& source, int first, int last):type(type) {
    text = source.substr(first, last);
}

std::ostream& operator << ( std::ostream& outs, const Token & tok )
{
    switch (tok.type) {
        // Arithmetic operators
        case Token::PLUS: outs << "TOKEN(PLUS)"; break;
        case Token::MINUS: outs << "TOKEN(MINUS)"; break;
        case Token::MUL: outs << "TOKEN(MUL)"; break;
        case Token::DIV: outs << "TOKEN(DIV)"; break;
        // Boolean comparisons
        case Token::LT: outs << "TOKEN(LT)"; break;
        case Token::LE: outs << "TOKEN(LE)"; break;
        case Token::EQ: outs << "TOKEN(EQ)"; break;
        // Literals
        case Token::NUM: outs << "TOKEN(NUM)"; break;
        case Token::TRUE : outs << "TOKEN(TRUE)"; break;
        case Token::FALSE : outs << "TOKEN(FALSE)"; break;
        // Statement tokens
        case Token::PRINT: outs << "TOKEN(PRINT)"; break;
        case Token::ASSIGN: outs << "TOKEN(ASSIGN)"; break;
        // General purpose tokens
        case Token::PI: outs << "TOKEN(PI)"; break;
        case Token::PD: outs << "TOKEN(PD)"; break;
        case Token::COMA: outs << "TOKEN(COMA)"; break;
        case Token::PC: outs << "TOKEN(PC)"; break;
        // If-Else tokens
        case Token::IF: outs << "TOKEN(IF)"; break;
        case Token::THEN: outs << "TOKEN(THEN)"; break;
        case Token::ELSE: outs << "TOKEN(ELSE)"; break;
        case Token::ENDIF: outs << "TOKEN(ENDIF)"; break;
        case Token::IFEXP: outs << "TOKEN(IFEXP)"; break;
        // While tokens
        case Token::WHILE: outs << "TOKEN(WHILE)"; break;
        case Token::DO: outs << "TOKEN(DO)"; break;
        case Token::ENDWHILE: outs << "TOKEN(ENDWHILE)"; break;
        // For tokens
        case Token::FOR : outs << "TOKEN(FOR)"; break;
        case Token::ENDFOR : outs << "TOKEN(ENDFOR)"; break;
        // Function tokens
        case Token::FUN: outs << "TOKEN(FUN)"; break;
        case Token::ENDFUN: outs << "TOKEN(ENDFUN)"; break;
        case Token::RETURN: outs << "TOKEN(RETURN)"; break;
        // Var tokens
        case Token::VAR: outs << "TOKEN(VAR)"; break;
        // Id
        case Token::ID: outs << "TOKEN(ID)"; break;
        // Meta-tokens
        case Token::ERR: outs << "TOKEN(ERR)"; break;
        case Token::END: outs << "TOKEN(END)"; break;
        default: outs << "TOKEN(UNKNOWN)"; break;
    }
    return outs;
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
    return outs << *tok;
}