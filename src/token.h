#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:

    enum Type {
        PLUS, MINUS, MUL, DIV, // Arithmetic operators
        LT, LE, EQ, // Boolean comparisons
        NUM, TRUE, FALSE, // Literals
        PRINT, ASSIGN, // Statement tokens
        PI, PD, COMA, PC, // General purpose tokens
        IF, THEN, ELSE, ENDIF, IFEXP, // If-Else tokens
        WHILE, DO, ENDWHILE, // While tokens
        FOR, ENDFOR, // For tokens
        FUN, ENDFUN, RETURN, // Function tokens
        VAR, // Var tokens
        ID, // Id
        END, ERR // Meta-tokens
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string& source, int first, int last);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);
    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);
};

#endif // TOKEN_H