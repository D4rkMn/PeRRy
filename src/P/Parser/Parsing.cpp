#include <iostream>
#include <stdexcept>
#include "P/Parser/Parser.h"

#include "P/Instruction/Instruction.h"
using namespace std;

list<P::Instruction*> P::Parser::parseProgram() {
    if (isDebug) cout << "Iniciando Parser:\n";
    list<Instruction*> program;
    while (!isAtEnd()) {
        program.push_back(parseInstruction());
    }
    if (isDebug) cout << "Parsing exitoso\n\n";
    return program;
}

P::Instruction* P::Parser::parseInstruction() {
    if (match(Token::POP)) {
        return new PopInstruction();
    }
    if (match(Token::STP)) {
        return new StopInstruction();
    }
    if (match(Token::MST)) {
        return new MarkInstruction(false);
    }
    if (match(Token::RET)) {
        return new ReturnInstruction(ReturnInstruction::SCOPE);
    }
    if (match(Token::ENT)) {
        if (!match(Token::ID)) {
            throw SyntaxError("Se esperaba un identificador");
        }
        return new EnterInstruction(previous->text);
    }
    if (match(Token::MSTp)) {
        return new MarkInstruction(true);
    }
    if (match(Token::RETn)) {
        return new ReturnInstruction(ReturnInstruction::F_VOID);
    }
    if (match(Token::RETv)) {
        return new ReturnInstruction(ReturnInstruction::F_RET);
    }
    if (match(Token::CUP)) {
        if (!match(Token::ID)) {
            throw SyntaxError("Se esperaba un identificador");
        }
        return new FCallInstruction(previous->text);
    }
    if (match(Token::LDA)) {
        if (!match(Token::ID)) {
            throw SyntaxError("Se esperaba un identificador");
        }
        return new LoadAddressInstruction(previous->text);
    }
    if (match(Token::LDCc)) {
        if (!match(Token::NUM)) {
            throw SyntaxError("Se esperaba un número");
        }
        return new LoadConstInstruction(stoll(previous->text));
    }
    if (match(Token::LODc)) {
        if (!match(Token::ID)) {
            throw SyntaxError("Se esperaba un identificador");
        }
        return new LoadVarInstruction(previous->text);
    }
    if (match(Token::STOc)) {
        return new StoreStackInstruction();
    }
    if (match(Token::INCc)) {
        return new IncStackInstruction();
    }
    if (match(Token::SROc)) {
        if (!match(Token::ID)) {
            throw SyntaxError("Se esperaba un identificador");
        }
        return new StoreToVarInstruction(previous->text);
    }
    if (match(Token::LABEL)) {
        return new LabelInstruction(stoll(previous->text));
    }
    if (match(Token::UJP)) {
        return new JumpInstruction(true);
    }
    if (match(Token::FJP)) {
        return new JumpInstruction(false);
    }
    if (
        match(Token::ADI) || match(Token::SBI) ||
        match(Token::MPI) || match(Token::DVI) ||
        match(Token::LESc) || match(Token::LEQc) ||
        match(Token::GRTc) || match(Token::GEQc) ||
        match(Token::EQUc) || match(Token::NEQc) ||
        match(Token::NGI) || match(Token::NOT)
    ) { 
        return new OpInstruction(tokenToOp(*previous));
    }
    if (match(Token::PRINT)) {
        return new PrintInstruction(false);
    }
    if (match(Token::PRINTLN)) {
        return new PrintInstruction(true);
    }
    string msg = "Error: Instrucción desconocida - '" + current->text + "'";
    throw runtime_error(msg); 
}