#include <iostream>
#include "exp.h"
#include "visitor.h"
#include <unordered_map>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int FunctionExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IFExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int BoolExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IdentifierExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int AssignStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int PrintStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int ReturnStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int IfStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int WhileStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}
int ForStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int FunDecList::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int FunDec::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int ParamDecList::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int ParamDec::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int VarDec::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int VarDecList::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}
int StatementList::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}
int Body::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////

int PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(IFExp* exp) {
    cout<< "ifexp(";
    exp->cond->accept(this);
    cout<< ",";
    exp->left->accept(this);
    cout<< ",";
    exp->right->accept(this);
    cout << ")" ;
    return 0;
}

int PrintVisitor::visit(FunctionExp* exp) {
    cout << exp->name << "(";
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        if (it != exp->args.begin()) cout << ", ";
        (*it)->accept(this);
    }
    cout << ")";
}

int PrintVisitor::visit(NumberExp* exp) {
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(BoolExp* exp) {
    if(exp->value) cout << "true";
    else cout << "false";
    return 0;
}

int PrintVisitor::visit(IdentifierExp* exp) {
    cout << exp->name;
    return 0;
}

void PrintVisitor::visit(AssignStatement* stm) {
    printTabs();
    cout << stm->id << " = ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStatement* stm) {
    printTabs();
    cout << "print(";
    stm->e->accept(this);
    cout << ");";
}

void PrintVisitor::visit(ReturnStatement* stm) {
    printTabs();
    cout << "return(";
    if (stm->e) stm->e->accept(this);
    cout << ");";
}

void PrintVisitor::visit(IfStatement* stm) {
    printTabs(); 
    cout << "if ";
    stm->condition->accept(this);
    cout << " then" << endl;
    stm->then->accept(this);
    if (stm->els) {
        cout << endl;
        printTabs(); 
        cout << "else" << endl;
        stm->els->accept(this);
    }
    cout << endl;
    printTabs();
    cout << "endif;";
}

void PrintVisitor::visit(WhileStatement* stm){
    printTabs(); 
    cout << "while ";
    stm->condition->accept(this);
    cout << " do" << endl;
    stm->b->accept(this);
    cout << "\n";
    printTabs();
    cout << "endwhile;";
}

void PrintVisitor::visit(ForStatement* stm){
    printTabs();
    cout << "for ";
    stm->start->accept(this);
    cout << " to ";
    stm->end->accept(this);
    cout << " step ";
    stm->step->accept(this);
    cout << " do" << endl;
    stm->b->accept(this);
    cout << "\n";
    printTabs();
    cout << "endfor;";
}

void PrintVisitor::visit(FunDecList* stm) {
    for (auto it = stm->fundecs.begin(); it != stm->fundecs.end(); it++) {
        (*it)->accept(this);
        cout << "\n\n";
    }
}

void PrintVisitor::visit(FunDec* stm) {
    cout << "fun " << stm->type << " " << stm->id << "(";
    if (stm->params) stm->params->accept(this);
    cout << ")\n";
    stm->body->accept(this);
    cout << "\nendfun";
}

void PrintVisitor::visit(ParamDecList* stm) {
    for (auto it = stm->params.begin(); it != stm->params.end(); it++) {
        if (it != stm->params.begin()) cout << ", ";
        it->accept(this);
    }
}

void PrintVisitor::visit(ParamDec* stm) {
    cout << stm->type << " " << stm->id;
}

void PrintVisitor::visit(VarDec* stm){
    printTabs();
    cout << "var ";
    cout << stm->type;
    cout << " ";
    for(auto i: stm->vars){
        cout << i;
        if (i != stm->vars.back()) cout << ", ";
    }
    cout << ";";
}

void PrintVisitor::visit(VarDecList* stm){
    for (auto it = stm->vardecs.begin(); it != stm->vardecs.end(); it++) {
        (*it)->accept(this);
        cout << endl;
    }
}

void PrintVisitor::visit(StatementList* stm){
    for (auto it = stm->stms.begin(); it != stm->stms.end(); it++) {
        if (it != stm->stms.begin()) cout << endl;
        (*it)->accept(this);
    }
}

void PrintVisitor::visit(Body* stm){
    depth++;
    stm->vardecs->accept(this);
    stm->slist->accept(this);
    depth--;
}

void PrintVisitor::imprimir(Program* program) {
    program->vardecs->accept(this);
    cout << "\n";
    program->fundecs->accept(this);
};

///////////////////////////////////////////////////////////////////////////////////

int EVALVisitor::visit(BinaryExp* exp) {
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);

    switch (exp->op) {
        case BinaryOp::PLUS_OP:       result = v1 + v2;  break;
        case BinaryOp::MINUS_OP:      result = v1 - v2;  break;
        case BinaryOp::MUL_OP:        result = v1 * v2;  break;
        case BinaryOp::DIV_OP: {
            if(v2 != 0) result = v1 / v2;
            else {
                cout << "Error: división por cero" << endl;
                result = 0;
            }
            break;
        }
        case BinaryOp::EQ_OP:     result = v1 == v2; break;
        case BinaryOp::LT_OP:       result = v1 < v2;  break;
        case BinaryOp::LE_OP:    result = v1 <= v2; break;
        default: {
            cout << "Operador desconocido" << endl;
            result = 0;
            break;
        }
    }
    return result;
}

int EVALVisitor::visit(FunctionExp* exp) {
    // TODO   
}

int EVALVisitor::visit(NumberExp* exp) {
    return exp->value;
}

int EVALVisitor::visit(BoolExp* exp) {
    return exp->value;
}

int EVALVisitor::visit(IdentifierExp* exp) {
    return env.lookup(exp->name);
}

int EVALVisitor::visit(IFExp* pepito) {
    int condition = pepito->cond->accept(this);
    int trueResult = pepito->left->accept(this);
    int falseResult = pepito->right->accept(this);
    return condition ? trueResult : falseResult;
}

void EVALVisitor::visit(AssignStatement* stm) {
    int value = stm->rhs->accept(this);
    env.update(stm->id, value);
}

void EVALVisitor::visit(PrintStatement* stm) {
    cout << stm->e->accept(this) << "\n";
}

void EVALVisitor::visit(ReturnStatement* stm) {
    // TODO   
}

void EVALVisitor::visit(IfStatement* stm) {
    int condition = stm->condition->accept(this);
    if (condition != 0) {
        stm->then->accept(this);
    }
    else {
        if (stm->els) stm->els->accept(this);
    }
}

void EVALVisitor::visit(WhileStatement* stm) {
    int condition = stm->condition->accept(this);
    while (condition != 0) {
        stm->b->accept(this);
        condition = stm->condition->accept(this);
    }
}

void EVALVisitor::visit(ForStatement* stm){
    int start = stm->start->accept(this);
    int end = stm->end->accept(this);
    int step = stm->step->accept(this);

    int i;
    for (i = start; i != end; i += step) {
        stm->b->accept(this);
    }
    if (i == end) {
        stm->b->accept(this);
    }
}

void EVALVisitor::visit(FunDecList* stm) {
    // TODO
}

void EVALVisitor::visit(FunDec* stm) {
    // TODO
}

void EVALVisitor::visit(ParamDecList* stm) {
    // TODO
}

void EVALVisitor::visit(ParamDec* stm) {
    // TODO
}

void EVALVisitor::visit(VarDec* varDec) {
    for (auto it = varDec->vars.begin(); it != varDec->vars.end(); it++) {
        env.add_var(*it, varDec->type);
    }
}

void EVALVisitor::visit(VarDecList* stm) {
    for (auto it = stm->vardecs.begin(); it != stm->vardecs.end(); it++) {
        (*it)->accept(this);
    }
}

void EVALVisitor::visit(StatementList* stm){
    for (auto it = stm->stms.begin(); it != stm->stms.end(); it++) {
        (*it)->accept(this);
    }
}

void EVALVisitor::visit(Body* b){
    env.add_level();
    b->vardecs->accept(this);
    b->slist->accept(this);
    env.remove_level();
}

void EVALVisitor::ejecutar(Program* program){
    program->vardecs->accept(this);
    program->fundecs->accept(this);
}

///////////////////////////////////////////////////////////////////////////////////

//0 = undefined
//1 = int
//2 = bool
const int UNDEFINED_TYPE = 0;
const int INT_TYPE = 1;
const int BOOL_TYPE = 2;

int TypeVisitor::visit(BinaryExp* exp) {
    // no type checking
    return UNDEFINED_TYPE;
}

int TypeVisitor::visit(FunctionExp* exp) {
    // TODO
}

int TypeVisitor::visit(NumberExp* exp) {
    // no type checking
    return INT_TYPE;
}

int TypeVisitor::visit(BoolExp* exp) {
    // no type checking
    return BOOL_TYPE;
}

int TypeVisitor::visit(IdentifierExp* exp) {
    // no type checking  
    return UNDEFINED_TYPE;
}

int TypeVisitor::visit(IFExp* exp) {
    // no type checking  
    return UNDEFINED_TYPE;
}

void TypeVisitor::visit(AssignStatement* stm) {
    bool declared = env.check(stm->id);
    if (!declared) {
        string s = "Error en type checker - La variable " + stm->id + " no ha sido declarada en este scope!\n";
        throw runtime_error(s);
    }
    int type = stm->rhs->accept(this);
    string string_type = env.lookup_type(stm->id);
    if (
        (string_type == "int" && type != INT_TYPE) ||
        (string_type == "bool" && type != BOOL_TYPE)
    ) {
        string s = "Warning en type checker - Tipos incompatibles en la asignación\n";
        cerr << s;
    }
}

void TypeVisitor::visit(PrintStatement* stm) {
    // no type checking   
}

void TypeVisitor::visit(ReturnStatement* stm) {
    // TODO
}

void TypeVisitor::visit(IfStatement* stm) {
    stm->then->accept(this);
    if (stm->els) {
        stm->els->accept(this);
    }
}

void TypeVisitor::visit(WhileStatement* stm) {
    stm->b->accept(this);
}

void TypeVisitor::visit(ForStatement* stm) {
    stm->b->accept(this);
}

void TypeVisitor::visit(FunDecList* stm) {
    // TODO
}

void TypeVisitor::visit(FunDec* stm) {
    // TODO
}

void TypeVisitor::visit(ParamDecList* stm) {
    // TODO
}

void TypeVisitor::visit(ParamDec* stm) {
    // TODO
}

void TypeVisitor::visit(VarDec* varDec) {
    for (auto it = varDec->vars.begin(); it != varDec->vars.end(); it++) {
        int level = env.get_level(*it);
        if (level == -1 || level != env.get_current_level()) {
            env.add_var(*it, varDec->type);
            continue;
        }
        string s = "Error en type checker - La variable " + *it + " ya ha sido declarada previamente!\n";
        throw runtime_error(s);
    }
}

void TypeVisitor::visit(VarDecList* stm) {
    for (auto it = stm->vardecs.begin(); it != stm->vardecs.end(); it++) {
        (*it)->accept(this);
    }
}

void TypeVisitor::visit(StatementList* stm) {
    for (auto it = stm->stms.begin(); it != stm->stms.end(); it++) {
        (*it)->accept(this);
    }
}

void TypeVisitor::visit(Body* b) {
    env.add_level();
    b->vardecs->accept(this);
    b->slist->accept(this);
    env.remove_level();
}

void TypeVisitor::check(Program* program){
    program->vardecs->accept(this);
    program->fundecs->accept(this);
}