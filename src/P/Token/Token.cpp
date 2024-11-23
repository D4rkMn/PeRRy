#include <iostream>
#include "P/Token/Token.h"
using namespace std;

P::Token::Token(Type type, size_t line) : type(type), line(line) { text = ""; }

P::Token::Token(Type type, char c, size_t line) : type(type), line(line) { text = string(1, c); }

P::Token::Token(Type type, const string& source, int first, int last, size_t line) : type(type), line(line) {
    text = source.substr(first, last);
}

std::ostream& operator<<(std::ostream& outs, const P::Token& tok) {
    switch (tok.type) {
        // General purpose
        case P::Token::POP: outs << "TOKEN(POP)"; break;
        case P::Token::STP: outs << "TOKEN(STP)"; break;
        // Scope
        case P::Token::MST: outs << "TOKEN(MST)"; break;
        case P::Token::RET: outs << "TOKEN(RET)"; break;
        // Function
        case P::Token::ENT: outs << "TOKEN(ENT)"; break;
        case P::Token::MSTp: outs << "TOKEN(MSTp)"; break;
        case P::Token::RETn: outs << "TOKEN(RETn)"; break;
        case P::Token::RETv: outs << "TOKEN(RETv)"; break;
        case P::Token::CUP: outs << "TOKEN(CUP)"; break;
        // Stack values
        case P::Token::LDA: outs << "TOKEN(LDA)"; break;
        case P::Token::LDCc: outs << "TOKEN(LDCc)"; break;
        case P::Token::LODc: outs << "TOKEN(LODc)"; break;
        // Storing variables
        case P::Token::STOc: outs << "TOKEN(STOc)"; break;
        case P::Token::INCc: outs << "TOKEN(INCc)"; break;
        case P::Token::SROc: outs << "TOKEN(SROc)"; break;
        // Branching
        case P::Token::LABEL: outs << "TOKEN(LABEL)"; break;
        case P::Token::UJP: outs << "TOKEN(UJP)"; break;
        case P::Token::FJP: outs << "TOKEN(FJP)"; break;
        // Binary operations
        case P::Token::ADI: outs << "TOKEN(ADI)"; break;
        case P::Token::SBI: outs << "TOKEN(SBI)"; break;
        case P::Token::MPI: outs << "TOKEN(MPI)"; break;
        case P::Token::DVI: outs << "TOKEN(DVI)"; break;
        case P::Token::LESc: outs << "TOKEN(LESc)"; break;
        case P::Token::LEQc: outs << "TOKEN(LEQc)"; break;
        case P::Token::GRTc: outs << "TOKEN(GRTc)"; break;
        case P::Token::GEQc: outs << "TOKEN(GEQc)"; break;
        case P::Token::EQUc: outs << "TOKEN(EQUc)"; break;
        case P::Token::NEQc: outs << "TOKEN(NEQc)"; break;
        // Unary operations
        case P::Token::NGI: outs << "TOKEN(NGI)"; break;
        case P::Token::NOT: outs << "TOKEN(NOT)"; break;
        // Print
        case P::Token::PRINT: outs << "TOKEN(PRINT)"; break;
        case P::Token::PRINTLN: outs << "TOKEN(PRINTLN)"; break;
        // Others
        case P::Token::ID: outs << "TOKEN(ID)"; break;
        case P::Token::NUM: outs << "TOKEN(NUM)"; break;
        // Meta-Tokens
        case P::Token::END: outs << "TOKEN(END)"; break;
        case P::Token::ERR: outs << "TOKEN(ERR)"; break;
        default: outs << "TOKEN(UNKNOWN)"; break;
    }   
    return outs;
}

std::ostream& operator<<(std::ostream& outs, const P::Token* tok) {
    return outs << *tok;
}

