#include "ASTNodes/Stm.h"
using namespace std;

// ExpStatement

ExpStatement::ExpStatement(Exp* exp) : exp(exp) {}
ExpStatement::~ExpStatement() { delete exp; }

// AssignStatement

AssignStatement::AssignStatement(const string& id, Exp* rhs)
    : id(id), rhs(rhs) {}
AssignStatement::~AssignStatement() { delete rhs; }

// AdvanceStatement

AdvanceStatement::AdvanceStatement(const string& id, Exp* rhs)
    : id(id), rhs(rhs) {}
AdvanceStatement::~AdvanceStatement() { delete rhs; }

// ReturnStatement

ReturnStatement::ReturnStatement(Exp* exp) : exp(exp) {}
ReturnStatement::~ReturnStatement() { delete exp; }

// PrintStatement

PrintStatement::PrintStatement(const string& s) : textLiteral(s) {}

PrintStatement::~PrintStatement() {
    for (auto it = expList.begin(); it != expList.end(); it++) {
        delete *it;
    }
}

// IfStatement

IfStatement::IfStatement(Exp* exp, Body* b1, Body* b2 = nullptr)
    : condition(exp), ifBody(b1), elseBody(b2) {}

IfStatement::~IfStatement() {
    delete condition;
    delete ifBody;
    if (elseBody) delete elseBody; 
}

// ForStatement

ForStatement::ForStatement(Exp* start, Exp* end, Body* body)
    : start(start), end(end), body(body) {}

ForStatement::~ForStatement() {
    delete start;
    delete end;
    delete body;
}