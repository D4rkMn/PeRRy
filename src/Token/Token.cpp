#include <iostream>
#include "Token.h"

using namespace std;

Token::Token(Type type):type(type) { text = ""; }

Token::Token(Type type, char c):type(type) { text = string(1, c); }

Token::Token(Type type, const string& source, int first, int last) : type(type) {
    text = source.substr(first, last);
}

std::ostream& operator << ( std::ostream& outs, const Token & tok ) {
    switch (tok.type) {
        // Variable declaration tokens
        case Token::LET: cout << "TOKEN(LET)"; break;
        case Token::MUT: cout << "TOKEN(MUT)"; break;
        case Token::COLON: cout << "TOKEN(COLON)"; break;
        // Type tokens
        case Token::INT32: cout << "TOKEN(INT32)"; break;
        case Token::INT64: cout << "TOKEN(INT64)"; break;
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
        case Token::LBRACKET: cout << "TOKEN(LBRACKET)"; break;
        case Token::RBRACKET: cout << "TOKEN(RBRACKET)"; break;
        // Function tokens
        case Token::FUNCTION: cout << "TOKEN(FUNCTION)"; break;
        case Token::RETURN: cout << "TOKEN(RETURN)"; break;
        case Token::RARROW: cout << "TOKEN(RARROW)"; break;
        // If-Else tokens
        case Token::IF: cout << "TOKEN(IF)"; break;
        case Token::ELSE: cout << "TOKEN(ELSE)"; break;
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