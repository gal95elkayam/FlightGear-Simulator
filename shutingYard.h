//
// Created by gal on 18/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H
#include <map>
#include <vector>
#include "Expression.h"
#include "SymbolTable.h"


using namespace std;
class shuntingYard {
};


/////BinaryOperator//////
class BinaryOperator : public Expression{
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* a, Expression* b);
//    virtual double calculate();

    virtual ~BinaryOperator();
};
////Plus////
class Plus : public BinaryOperator {
public:
    Plus(Expression* leftPlus, Expression* rightPlus);
    virtual double calculate() ;
    virtual ~Plus();
};
/////Minus////
class Minus : public BinaryOperator {
public:
    Minus(Expression* leftMinus, Expression* rightMinus);
    virtual double calculate();
    virtual ~Minus();
};
/////Mul////
class Mul : public BinaryOperator {
public:
    Mul(Expression* leftMul, Expression* rightMule);
    virtual double calculate();
    virtual ~Mul();
};
/////Div////
class Div  : public BinaryOperator {
public:
    Div(Expression* leftDiv, Expression* rightDiv);
    virtual double calculate();
    virtual ~Div();
};
////Value/////
class Value: public Expression {
    double value;
public:
    Value(const double exp);
    virtual double calculate();
    virtual ~Value();
};

////Variable/////
class Variable: public Expression {
    string name;
    double value;
public:
    Variable( string nameVar,double num);
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double valueUser);
    Variable& operator-=(double valueUser);
    Variable& operator++(int a);
    Variable& operator--(int a);
    virtual double calculate();
    virtual ~Variable() ;
};
////UnaryOperator//////
class UnaryOperator: public Expression{
protected:
    Expression* exp;
public:
    UnaryOperator(Expression* a);
//    virtual double calculate();
    virtual ~UnaryOperator();
};
///UMinus////
class UMinus : public UnaryOperator {
public:
    UMinus(Expression* ex);
    virtual double calculate();
    virtual ~UMinus() ;
};
///UPlus/////
class UPlus: public UnaryOperator {
public:
    UPlus(Expression* ex);
    virtual double calculate();
    virtual ~UPlus();
};

//////Shunting_yard///
class Shunting_yard  {
private:
//    string infix;
    //Operators features(char,precedence)
    map<char, int> op = {
            {'(', 1},
            {'+', 2},
            {'-', 2},
            {'*', 3},
            {'/', 3},
            {'#',4},
            {'&',4}
    };
    bool isoperator(char);
public:
    Shunting_yard(string);
    Shunting_yard();
    vector<string> convert(string infix);
//    string checkExtraVariabe(string infix, int token);
//    string checkExtraDouble(string infix, int token);
//    string checkExtraVariabe(string fix);
    string checkIsalpha(string fix);
    string checkDigit(string fix);
    int checkUnary(string str);
    int checkOp2(string infix);
    string negativeMarker(string str);

};



///Interpreter//////

class Interpreter {
    bool isOperator(string);

public:

    Interpreter();
    Expression* interpret(string str);
    void setVariables(vector<Map>map);
    vector< Map> mp;
//    struct Flag_name_value {
//        string name;
//        double value;
//    };

};


#endif //EX1_EX1_H
