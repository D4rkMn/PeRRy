#include <iostream>
#include "P/Token/Token.h"
using namespace std;

P::Token::Type P::Token::wordToToken(const string& word) {
    // General purpose
    if (word == "POP") return POP;
    if (word == "STP") return STP;
    // Scope 
    if (word == "MST") return MST;
    if (word == "RET") return RET; 
    // Functions
    if (word == "ENT") return ENT;
    if (word == "MSTp") return MSTp;
    if (word == "RETn") return RETn;
    if (word == "RETv") return RETv;
    if (word == "CUP") return CUP;
    // Stack values
    if (word == "LDA") return LDA;
    if (word == "LDCc") return LDCc;
    if (word == "LODc") return LODc;
    // Storing variables
    if (word == "STOc") return STOc;
    if (word == "INCc") return INCc;
    if (word == "SROc") return SROc;
    // Branching
    if (word == "UJP") return UJP;
    if (word == "FJP") return FJP;
    // Binary operations
    if (word == "ADI") return ADI;
    if (word == "SBI") return SBI;
    if (word == "MPI") return MPI;
    if (word == "DVI") return DVI;
    if (word == "LESc") return LESc;
    if (word == "LEQc") return LEQc;
    if (word == "GRTc") return GRTc;
    if (word == "GEQc") return GEQc;
    if (word == "EQUc") return EQUc;
    if (word == "NEQc") return NEQc;
    // Unary operations
    if (word == "NGI") return NGI;
    if (word == "NOT") return NOT;
    // Print
    if (word == "PRINT") return PRINT;
    if (word == "PRINTLN") return PRINTLN;
    return ERR;
}