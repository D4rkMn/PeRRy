#ifndef P_TOKEN_H
#define P_TOKEN_H

#include "P/Namespace.h"
#include <string>

class P::Token {
public:

    enum Type {
        // General purpose
        POP, STP,
        // Scope 
        MST, RET, 
        // Functions
        ENT, MSTp, RETn, RETv, CUP,
        // Stack values
        LDA, LDCc, LODc,
        // Storing variables
        STOc, INCc, SROc,
        // Branching
        LABEL, UJP, FJP,
        // Binary operations
        ADI, SBI, MPI, DVI, LESc, LEQc,
        GRTc, GEQc, EQUc, NEQc,
        // Unary operations
        NGI, NOT,
        // Print
        PRINT, PRINTLN,
        // Others
        ID, NUM,
        // Meta-tokens
        END, ERR
    };

    Type type;
    std::string text;
    size_t line;

    Token(Type, size_t);
    Token(Type, char, size_t);
    Token(Type, const std::string&, int, int, size_t);

    static Token::Type wordToToken(const std::string&);
};

std::ostream& operator<<(std::ostream& outs, const P::Token& tok);
std::ostream& operator<<(std::ostream& outs, const P::Token* tok);

#endif