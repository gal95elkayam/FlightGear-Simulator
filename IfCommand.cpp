//
// Created by gal on 26/12/2019.
//

#include <iostream>
#include <regex>
#include "IfCommand.h"
#include "shutingYard.h"

int IfCommand:: execute(int index,vector<string> &data,unordered_map<string, double>*forConnect){
    int constIndexForWhile = index;
    int findIndex;
    vector<string> temp =createCommandVec(data,constIndexForWhile);
    //check the condition
    if (conditionParser(constIndexForWhile, data)) {
        vector<string> temp =createCommandVec(data,constIndexForWhile);
        while(!temp.empty()) {
            for (int i = 0; i < temp.size(); i++) {
                if (temp[i].compare("end of line") == 0) {
                    findIndex = i;
                    break;
                }
            }
            //splite the command in the backend and read them one by one
            vector<string> sub(&temp[0], &temp[findIndex]);
            this->parser->doCommand(0, sub);
            temp.erase (temp.begin(),temp.begin()+findIndex+1);
            sub.clear();
        }

    }
    return temp.size()+4;
}
const vector<string> IfCommand::createCommandVec(vector<string> &data,int constIndexForWhile){
    vector<string>temp;
    int i= constIndexForWhile+1;
    while (data[i] != "}") {
        if(data[i]=="{") {
            i++;
            continue;
        }
        temp.push_back(data[i]);
        i++;
    }
    return temp;
}
bool IfCommand::conditionParser(int index,vector<string> &data){
    string leftSide;
    string condition;
    string rightSide;
    unsigned long conditionSize;
    condition = getOperator(data[index]);
    conditionSize = condition.length();
    leftSide = data[index].substr(0,data[index].find(condition));
    leftSide.erase(std::remove(leftSide.begin(),leftSide.end(),' '),leftSide.end());
    rightSide = data[index].substr(data[index].find(condition)+conditionSize);
    rightSide.erase(std::remove(rightSide.begin(),rightSide.end(),' '),rightSide.end());
    return checkCondition(leftSide, condition, rightSide);

}
//check the condition
bool IfCommand::checkCondition(string &leftSide, string &operatorStr, string &rightSide) {
    try {
        Interpreter *inter = new Interpreter();
        inter->setVariables(*mapForShutingYard);
        Expression *exp1 = inter->interpret(leftSide);
        double leftVal = exp1->calculate();
        Expression *exp2 = inter->interpret(rightSide);
        double rightVal = exp2->calculate();
//        cout<<"LoopCommand::checkCondition- check the value:leftVal: "<<leftVal<<"rightVal: "<<rightVal<<"\n";
        if (operatorStr == "==") {
            return rightVal == leftVal;
        } else if (operatorStr == "!=") {
            return rightVal != leftVal;
        } else if (operatorStr == "<") {
            return leftVal < rightVal;
        } else if (operatorStr == ">") {
            return leftVal > rightVal;
        } else if (operatorStr == ">=") {
            return leftVal >= rightVal;
        } else if (operatorStr == "<=") {
            return leftVal <= rightVal;
        } else {

            throw invalid_argument(operatorStr);
        }

    } catch (invalid_argument noMatch) {
        cout << " No such operator - " << noMatch.what() << endl;
    }
}

string IfCommand::getOperator(const string &line) {
    regex ex("(<=|>=|!=|==|>|<)");
    string res;
    smatch match;
    try {
        if (regex_search(line, match, ex) && match.size() > 0) {
            res = match.str(0);
        } else {
            res = string("");

        }
        return res;
    } catch (regex_error &e) {
        cout << e.what() << endl;
        throw e.what();
    }
}
