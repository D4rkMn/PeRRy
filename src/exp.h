#ifndef EXP_H
#define EXP_H

#include <string>
#include <unordered_map>
#include <list>
#include "visitor.h"
using namespace std;
enum BinaryOp { PLUS_OP, MINUS_OP, MUL_OP, DIV_OP,LT_OP, LE_OP, EQ_OP };

class Body;

class Exp {
public:
    virtual int  accept(Visitor* visitor) = 0;
    virtual ~Exp() = 0;
    static string binopToChar(BinaryOp op);
};

class IFExp : public Exp {
public:
    Exp *cond,*left, *right;
    IFExp(Exp *cond, Exp* l, Exp* r);
    int accept(Visitor* visitor);
    ~IFExp();
};

class FunctionExp : public Exp {
public:
    std::list<Exp*> args;
    std::string name;
    FunctionExp(const std ::string& name) : name(name) {}
    ~FunctionExp() {}
    int accept(Visitor* visitor);
};

class BinaryExp : public Exp {
public:
    Exp *left, *right;
    string type;
    BinaryOp op;
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    int accept(Visitor* visitor);
    ~BinaryExp();
};

class NumberExp : public Exp {
public:
    int value;
    NumberExp(int v);
    int accept(Visitor* visitor);
    ~NumberExp();
};

class BoolExp : public Exp {
public:
    int value;
    BoolExp(bool v);
    int accept(Visitor* visitor);
    ~BoolExp();
};

class IdentifierExp : public Exp {
public:
    std::string name;
    IdentifierExp(const std::string& n);
    int accept(Visitor* visitor);
    ~IdentifierExp();
};

class Stm {
public:
    virtual int accept(Visitor* visitor) = 0;
    virtual ~Stm() = 0;
};

class AssignStatement : public Stm {
public:
    std::string id;
    Exp* rhs;
    AssignStatement(std::string id, Exp* e);
    int accept(Visitor* visitor);
    ~AssignStatement();
};

class PrintStatement : public Stm {
public:
    Exp* e;
    PrintStatement(Exp* e);
    int accept(Visitor* visitor);
    ~PrintStatement();
};

class ReturnStatement : public Stm {
public:
    Exp* e = nullptr;
    ReturnStatement(Exp* e) : e(e) {}
    int accept(Visitor* visitor);
    ~ReturnStatement() { if (e) delete e; }
};

class IfStatement : public Stm {
public:
    Exp* condition;
    Body* then;
    Body* els;
    IfStatement(Exp* condition, Body* then, Body* els);
    int accept(Visitor* visitor);
    ~IfStatement();
};
class WhileStatement : public Stm {
public:
    Exp* condition;
    Body* b;
    WhileStatement(Exp* condition, Body* b);
    int accept(Visitor* visitor);
    ~WhileStatement();
};

//FOR(int,int,int) stmlist endfor
class ForStatement : public Stm {
public:
    Exp* start;
    Exp* end;
    Exp* step;
    Body* b;
    ForStatement(Exp* start, Exp* end, Exp* step, Body* b);
    int accept(Visitor* visitor);
    ~ForStatement();
};

class Body{
public:
    VarDecList* vardecs;
    StatementList* slist;
    Body(VarDecList* vardecs, StatementList* stms);
    int accept(Visitor* visitor);
    ~Body();
};

class VarDec {
public:
    string type;
    list<string> vars;
    VarDec(string type, list<string> vars);
    int accept(Visitor* visitor);
    ~VarDec();
};

class ParamDec {
public:
    string type;
    string id;
    ParamDec(const string& type, const string& id) : type(type), id(id) {}
    int accept(Visitor* visitor);
    ~ParamDec() {}
};

class ParamDecList {
public:
    list<ParamDec> params;
    ParamDecList() {}
    int accept(Visitor* visitor);
    ~ParamDecList() {}
};

class FunDec {
public:
    string type;
    string id;
    ParamDecList* params = nullptr;
    Body* body = nullptr;
    FunDec(const string& type, const string& id) : type(type), id(id) {}
    int accept(Visitor* visitor);
    ~FunDec() { delete params; delete body; }
};

class VarDecList{
public:
    list<VarDec*> vardecs;
    VarDecList();
    void add(VarDec* vardec);
    int accept(Visitor* visitor);
    ~VarDecList();
};

class FunDecList {
public:
    list<FunDec*> fundecs;
    FunDecList() {}
    void add(FunDec* fundec) { fundecs.push_back(fundec); }
    int accept(Visitor* visitor);
    ~FunDecList() { for (auto it = fundecs.begin(); it != fundecs.end(); it++) delete *it; }
};

class StatementList {
public:
    list<Stm*> stms;
    StatementList();
    void add(Stm* stm);
    int accept(Visitor* visitor);
    ~StatementList();
};

class Program {
public:
    VarDecList* vardecs;
    FunDecList* fundecs;
    Program(VarDecList* vardecs, FunDecList* fundecs) : vardecs(vardecs), fundecs(fundecs) {}
    ~Program() { delete vardecs; delete fundecs; }
};



#endif // EXP_H