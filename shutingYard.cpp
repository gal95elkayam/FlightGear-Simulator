//            for(int it = 0; it < mp.size(); it++){
//                if(s.compare(mp[it].var)==0) {
//                    Expression *variable = new Value(mp[it].value);
//                    nums.push(variable);
//

#include <sstream>
#include <deque>
#include <stack>
#include "Expression.h"
#include "shutingYard.h"

//////BinaryOperator/////
BinaryOperator::BinaryOperator(Expression* a, Expression* b) {
    left =  a;
    right = b;
}
//double BinaryOperator:: calculate() {}
BinaryOperator:: ~BinaryOperator() {
    delete left;
    delete right;
}
/////Plus/////
Plus::Plus(Expression* leftPlus, Expression* rightPlus) : BinaryOperator(leftPlus, rightPlus){
}
double Plus::  calculate() {
    return  left->calculate()+ right->calculate();
}
Plus:: ~Plus() {}
/////Minus////
Minus::Minus(Expression* leftMinus, Expression* rightMinus) : BinaryOperator(leftMinus, rightMinus){}
double Minus::  calculate() {
    return  left->calculate()-right->calculate();}
Minus:: ~Minus() {
}
/////Mul///
Mul::Mul(Expression* leftMul, Expression* rightMule) : BinaryOperator(leftMul, rightMule){}
double Mul::  calculate() {
    return  left->calculate()*right->calculate();}
Mul:: ~Mul() {}
/////Div////
Div::Div(Expression* leftDiv, Expression* rightDiv) : BinaryOperator(leftDiv, rightDiv){}
double Div::  calculate() {
    if(right->calculate()==0)
        throw "division by zero";
    return left->calculate() / right->calculate();
}
Div:: ~Div() {}
////Value///
Value::Value( const double exp){
    value=exp;
}
double Value:: calculate()  {
    return value;
}
Value:: ~Value() {
}
////Variable///
Variable::Variable( string nameVar,double num){
    name=nameVar;
    value=num;
}
Variable& Variable:: operator++(){
    value++;
    return *this;
}
Variable& Variable:: operator--(){
    value--;
    return *this;
}
Variable& Variable:: operator+=(double valueUser){
    value+=valueUser;
    return *this;
}
Variable& Variable::  operator-=(double valueUser){
    value+=valueUser;
    return *this;
}
Variable& Variable:: operator++(int){

    Variable temp=*this;
    ++this->value;
    return *this;
}
Variable& Variable:: operator--(int){
    Variable temp=*this;
    --this->value;
    return *this;
}
double Variable:: calculate(){
    return this->value;
}
Variable:: ~Variable() {
}
////UnaryOperator////
UnaryOperator::UnaryOperator(Expression* a) {
    exp =  a;
}
//double UnaryOperator:: calculate() {}
UnaryOperator:: ~UnaryOperator() {
    delete exp;
}
/////UMinus/////
UMinus::UMinus(Expression* ex) : UnaryOperator(ex){}
double UMinus::  calculate() {
    return -(exp->calculate());
}
UMinus:: ~UMinus() {
}
/////UPlus////
UPlus::UPlus(Expression* ex) : UnaryOperator(ex){}
double UPlus::calculate() {
    return exp->calculate();
}
UPlus:: ~UPlus() {
}

//////Shunting_yard//////

Shunting_yard::Shunting_yard() {

}
//define operator
bool Shunting_yard::isoperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c== '&'|| c=='#';
}
//define Unary
int Shunting_yard::checkUnary(string str) {
    istringstream readSentence(str);
    int check;
    char dummy;
    bool isUnary= false;
    char token = readSentence.peek();
    //if Uplus return 1
    if (token == '+') {
        check = 1;
        isUnary=true;
    }
    //if UMinus return 1
    if (token == '-') {
        check = 2;
        isUnary=true;
    } else
        check = 0;
    if(isUnary) {
        readSentence >> dummy;
        token = readSentence.peek();
        if (isdigit(token))
            return check;
        if(isalpha(token))
            throw "bad input";
        if( token=='(')
            return check;;
    }
    return check;
}
//check if we get digit
string Shunting_yard:: checkDigit(string fix) {
    deque<string> var;
    int flag=0;
    string str;
    istringstream readSentence(fix);
    char dummy;
    string a;
    //check not set variable
    char token = readSentence.peek();
    if(token==-1)
        throw "bed set variable";
    while ((int) readSentence.tellg() != EOF) {
        token = readSentence.peek();
        if(token==-1)
            break;
        if (!isoperator(token)) {
            if (token == ')') {
                break;
            }
            //it can be . or digit
            if (token == '.' || isdigit(token)) {
                if(token=='.'){
                    flag++;
                }
                if(flag>2)
                    throw "bad input";
                a += token;
                var.push_back(a);
                readSentence >> dummy;
            }
            else
                //bad digit
                return a;
        }else
            break;
    }
    return a;
}
//check variable
string Shunting_yard:: checkIsalpha(string fix) {
    deque<string> var;
    string str;
    istringstream readSentence(fix);
    char dummy;
    string a;
    while ((int) readSentence.tellg() != EOF) {
        char token = readSentence.peek();
        //end of string
        if(token==-1)
            break;
        if (!isoperator(token)) {
            if (token == ')') {
                break;
            }
            if(token=='_' || isdigit(token) || isalpha(token)) {
                a += token;
                var.push_back(a);
                readSentence >> dummy;
            }
            else {
                throw "erorr alpha";
            }
        }
        else
            break;
    }
    return a;
}

//count operator next each other
int Shunting_yard::checkOp2(string infix){
    istringstream readSentence(infix);
    int index=0;
    int countOperator=0;
    char dummy;
    int flag=0;
    while ((int) readSentence.tellg() != EOF) {
        //check only two char if there are  two opertor- error
        char token = readSentence.peek();
        if(index<2) {
            if(token=='/'){
                index++;
                flag=1;
                readSentence >> dummy;
            }
            else if (isoperator(token)) {
                countOperator++;
                if(flag==1 && (token=='-'|| token=='+')) {
                    countOperator--;
                }
            }
            index++;
            readSentence >> dummy;
        } else
            break;
    }
    return countOperator;
}
string Shunting_yard::negativeMarker(string str) {
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (i == 0) {
            if (str[i] == '-' && str[i + 1] == '(') {
                str[i] = '#';
            }
            if (str[i] == '+' && str[i + 1] == '(') {
                str[i] = '&';
            }
        }
        if (str[i] == '(' && str[i + 1] == '-' && isdigit(str[i + 2])) {
            str[i + 1] = '#';
        }
        if (!(isdigit(str[i])) && str[i + 1] == '-' && str[i + 2] == '(') {
            str[i + 1] = '#';
        }
    }
    return str;
}
//convert string to postfix
vector<string> Shunting_yard::convert(string infix) {
    stack<char> operators;
//    int warning;
//    int unaryFirstChar=checkUnary(infix);
    //////////////////
    string sh=negativeMarker(infix);
    istringstream readSentence(sh);
    char tmp;
    //check if the prev token is digit for the unary
//    bool tokenBool = true;
    vector<string> strings;
    while ((int) readSentence.tellg() != EOF) {
        char token = readSentence.peek();
//      if (isalpha(token) || isdigit(token))
        if (isalpha(token)|| token=='_') {
//            tokenBool = false;
            string getVariable = checkIsalpha(sh);
            strings.push_back(getVariable);
            sh = sh.substr(getVariable.length());
            for (unsigned i = 0; i < getVariable.length(); i++) {
                readSentence >> tmp;
            }
        }
            //if the char is digit we will check it
        else if (isdigit(token)) {
//            tokenBool = false;
            string getVariable = checkDigit(sh);
            strings.push_back(getVariable);
            sh = sh.substr(getVariable.length());
            for (unsigned i = 0; i < getVariable.length(); i++) {
                readSentence >> tmp;
            }
        }
            //if the char is operator check
        else if (isoperator(token) || token == '#' || token == '&') {
            int b = checkOp2(sh);
            if (b == 2) {
                throw "two operator next each other";
                break;
            }
            //check if unary operator "-" indicate #
            if (token == '#') {
                //check if the first char in the string is -
//                tokenBool = false;
                readSentence >> tmp;
                operators.push('#');
                sh = sh.substr(1);
                continue;
            }
            //check if the stack of the operator is empty
//                if (!operators.empty()) {
//                    if ((operators.top() == '(' && tokenBool)) {
//                        tokenBool = false;
//                        checkUnary(infix);
////                        warning=checkNum2;
//                        readSentence >> tmp;
//                        operators.push('#');
//                        infix = infix.substr(1);
//                        continue;
//                    }
//                }
            //check if unary operator "+" indicate &
            if (token == '&') {
                //check if the first charin the string is +
//                tokenBool = false;
                readSentence >> tmp;
                operators.push('&');
                sh = sh.substr(1);
                continue;
            }
            //check if the stack of the operator is empty
//                if(!operators.empty()){
//                    if ((operators.top() == '(' && tokenBool)) {
//                        tokenBool = false;
//                        checkUnary(infix);
////                        warning=checkNum3;
//                        readSentence >> tmp;
//                        operators.push('&');
//                        infix = infix.substr(1);
//                        continue;
//                    }
//                }

            char o1 = token;
            string a;
            if (!operators.empty()) {
                char top = operators.top();
                while (isoperator(top)) {
                    //check precedence
                    if (op.find(o1)->second <= (op.find(top)->second)) {
                        // convert char to string and push it to the list<string>
                        a += top;
                        strings.push_back(a);
                        operators.pop();
                    } else break;
                    if (operators.empty())
                        break;
                    else top = operators.top();
                }
            }
//            tokenBool = true;
            operators.push(o1);
            readSentence >> tmp;
            sh = sh.substr(1);
        }else if (token == '(') {
            operators.push(token);
            readSentence >> tmp;
            sh = sh.substr(1);
        }
        else if (token == ')') {
            while (operators.top() != '(' && !operators.empty()) {
                string a;
                a += operators.top();
                strings.push_back(a);
                operators.pop();
            }
            if (operators.empty()) {
                throw ("Mismatched parenthesis");
            }
            operators.pop();
            readSentence >> tmp;
            sh = sh.substr(1);
        }
            //recognize space and moving on
        else {
            readSentence.get(tmp);
        }

    }
    if (!operators.empty()) {
        if (operators.top() == '(') {
            throw ("Mismatched parenthesis");
        }
        int size = operators.size();
        for (int i = 0; i < size; i++) {
            string a;
            a += operators.top();
            strings.push_back(a);
            operators.pop();
        }
    }
    return strings;

}



//////Interpreter///////
Interpreter::Interpreter(){

}
//define operator
bool Interpreter::isOperator(string c)
{
    return c=="+" || c == "-" || c == "*" || c == "/" || c == "^"|| c== "&"|| c=="#";
}
void Interpreter::setVariables(vector<Map>mp) {
   this->mp=mp;
}
//get postfix and if we see number or variable push to stack if opertor pop from the stack of num
//numbers and make expression and push to the stack<Expression *> nums
Expression* Interpreter::interpret(string str) {
    map< string, double >::iterator it;
    vector<string> postfix;
    Shunting_yard* n=new Shunting_yard();
    postfix=n->convert(str);
    stack<Expression *> nums;
//    int index=0;
    char tmp;
    for(string s:postfix){
        istringstream readSentance(s);
        char token = readSentance.peek();
        if (isalpha(token) || token=='_') {
            for (int it = 0; it < mp.size(); it++) {
                if (s.compare(mp[it].var) == 0) {
                    Expression *variable = new Value(mp[it].value);
                    nums.push(variable);

                }
            }
        }
        else if (isdigit(token)){
            try {
                nums.push(new Value(stod(s)));
                readSentance >> tmp;
            }
            catch(exception& e) {
                throw "bad input";
            }
        }
        else {
            Expression *num2 = nums.top();
            nums.pop();
            //if # recognize minus unarry
            if (s == "#") {
                readSentance >> tmp;
                nums.push(new UMinus(num2));
                continue;
            }
                //if & recognize plus unarry
            else if (s == "&") {
                nums.push(new UPlus(num2));
                readSentance >> tmp;
                nums.push(new UPlus(num2));
                continue;
            }
            if (isOperator(s))
            {
                Expression *num1 = new Value(0);
                Expression *res;
                if (!nums.empty()) {
                    num1 = nums.top();
                    nums.pop();
                }
                if (s == "+" || s == "-") {
                    if (token == '-')
                        num2 = new Mul(num2, new UMinus(new Value(1)));
                    res = new Plus(num1, num2);
                } else if (s == "*" || s =="/") {
                    if (token == '/')
                        num2 = new Div(new Value(1), num2);
                    res = new Mul(num1, num2);
                }
                nums.push(res);
                readSentance >> tmp;
            }
        }

    }
    return nums.top();
}

