#include <iostream>
#include "R/Token/Token.h"
using namespace std;

R::Token::Type R::Token::wordToToken(const string& word) {
    // Variable declaration tokens
    if (word == "let") return LET;
    if (word == "const") return CONST;
    if (word == "static") return STATIC;
    if (word == "mut") return MUT;
    // Type tokens
    if (word == "i32") return INT32;
    if (word == "i64") return INT64;
    if (word == "u32") return UINT32;
    if (word == "u64") return UINT64;
    if (word == "bool") return BOOL;
    // Function tokens
    if (word == "fn") return FUNCTION;
    if (word == "return") return RETURN;
    // Scope tokens
    if (word == "unsafe") return UNSAFE;
    // If-Else tokens
    if (word == "if") return IF;
    if (word == "else") return ELSE;
    // While tokens
    if (word == "while") return WHILE;
    // For tokens
    if (word == "for") return FOR;
    if (word == "in") return IN;
    // Literals
    if (word == "true") return TRUE;
    if (word == "false") return FALSE;
    return ERR;
}