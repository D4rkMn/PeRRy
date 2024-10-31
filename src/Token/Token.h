#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:

    enum Type {
        LET, MUT, COLON, // Variable declaration tokens
        INT32, INT64, // Type tokens
        PLUS, MINUS, MUL, DIV, // Arithmetic operators
        LESS, LESS_EQ, EQUALS, // Boolean comparisons
        GREATER, GREATER_EQ, NEQUALS, // Boolean comparisons
        LBRACKET, RBRACKET, // Scope tokens
        FUNCTION, RETURN, RARROW, // Function tokens
        IF, ELSE, // If-Else tokens
        FOR, RANGE, IN, // For tokens
        INTEGER, TRUE, FALSE, TEXT, // Literal tokens
        ASSIGN, ADVANCE, // Miscellaneous operators
        PRINTLN, // Print tokens
        LPAR, RPAR, COMMA, SEMICOLON, // General purpose tokens
        ID, // Identifier
        END, ERR // Meta-tokens
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string& source, int first, int last);

    static Token::Type wordToToken(const std::string&);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);
    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);
};

#endif