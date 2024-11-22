#include "R/ASTNodes/Stm.h"
#include "R/ASTNodes/Exp.h"
#include "R/ASTNodes/Program.h"
using namespace std;

// ExpStatement

R::ExpStatement::ExpStatement(Exp* exp) : exp(exp) {}
R::ExpStatement::~ExpStatement() { delete exp; }

// AssignStatement

R::AssignStatement::AssignStatement(const string& id, Exp* rhs)
    : id(id), rhs(rhs) {}
R::AssignStatement::~AssignStatement() { delete rhs; }

// AdvanceStatement

R::AdvanceStatement::AdvanceStatement(const string& id, Exp* rhs)
    : id(id), rhs(rhs) {}
R::AdvanceStatement::~AdvanceStatement() { delete rhs; }

// ReturnStatement

R::ReturnStatement::ReturnStatement(Exp* exp) : exp(exp) {}
R::ReturnStatement::~ReturnStatement() { delete exp; }

// PrintStatement

R::PrintStatement::PrintStatement(const string& s) : textLiteral(s) {}

R::PrintStatement::~PrintStatement() {
    for (auto it = expList.begin(); it != expList.end(); it++) {
        delete *it;
    }
}

// IfStatement

R::IfStatement::IfStatement(Exp* exp, Body* b1, Body* b2 = nullptr)
    : condition(exp), ifBody(b1), elseBody(b2) {}

R::IfStatement::~IfStatement() {
    delete condition;
    delete ifBody;
    if (elseBody) delete elseBody; 
}

// WhileStatement

R::WhileStatement::WhileStatement(Exp* exp, Body* body)
    : condition(exp), body(body) {}

R::WhileStatement::~WhileStatement() {
    delete condition;
    delete body;
}

// ForStatement

R::ForStatement::ForStatement(const string& id, Exp* start, Exp* end, Body* body)
    : id(id), start(start), end(end), body(body) {}

R::ForStatement::~ForStatement() {
    delete start;
    delete end;
    delete body;
}

// UnsafeStatement

R::UnsafeStatement::UnsafeStatement(Body* body) : body(body) {}
R::UnsafeStatement::~UnsafeStatement() { if (body) delete body; }

// ScopeStatement

R::ScopeStatement::ScopeStatement(Body* body) : body(body) {}
R::ScopeStatement::~ScopeStatement() { if (body) delete body; }