#ifndef R_TOKEN_H
#define R_TOKEN_H

#include <string>
#include "R/Utility/VarType.h"
#include "R/ASTNodes/Exp.h"
#include "R/Namespace.h"

class R::Token {
public:

    enum Type {
        LET, CONST, STATIC, MUT, // Variable declaration tokens
        INT32, INT64, UINT32, UINT64, BOOL, // Type tokens
        PLUS, MINUS, MUL, DIV, // Arithmetic operators
        LESS, LESS_EQ, EQUALS, NOT, // Boolean comparisons
        GREATER, GREATER_EQ, NEQUALS, // Boolean comparisons
        UNSAFE, LBRACKET, RBRACKET, // Scope tokens
        FUNCTION, RETURN, RARROW, // Function tokens
        IF, ELSE, // If-Else tokens
        WHILE, // While tokens
        FOR, RANGE, IN, // For tokens
        INTEGER, TRUE, FALSE, TEXT, // Literal tokens
        ASSIGN, ADVANCE, // Miscellaneous operators
        PRINTLN, // Print tokens
        LPAR, RPAR, COMMA, SEMICOLON, // General purpose tokens
        ID, ID_DEC, // Identifier
        END, ERR // Meta-tokens
    };

    Type type;
    R::VarType varType = R::VarType::UNKNOWN_TYPE;
    std::string text;
    size_t line;

    Token(Type, size_t);
    Token(Type, char, size_t);
    Token(Type, const std::string&, int, int, size_t);

    static Token::Type wordToToken(const std::string&);

    bool isVarType() const;
    VarType toVarType() const;
    BinaryOp toBinaryOp() const;
};

std::ostream& operator<<(std::ostream& outs, const R::Token& tok);
std::ostream& operator<<(std::ostream& outs, const R::Token* tok);

#endif