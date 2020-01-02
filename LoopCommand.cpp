//
// Created by gal on 24/12/2019.
//

#include <regex>
#include <iostream>
#include "LoopCommand.h"
#include "shutingYard.h"
#include "DefineVarCommand.h"

//while command
int LoopCommand:: execute(int index,vector<string> &data,unordered_map<string, double>*forConnect) {
    int constIndexForWhile = index;
    int findIndex;
    vector<string> temp =createCommandVec(data,constIndexForWhile);
    //check the condition
    while (conditionParser(constIndexForWhile, data)) {
        vector<string> temp =createCommandVec(data,constIndexForWhile);
        while(!temp.empty()) {
            for (int i = 0; i < temp.size(); i++) {
                if (temp[i].compare("end of line") == 0) {
                    findIndex = i;
                    break;
                }
            }
            //splite the command in backend one by one
            vector<string> sub(&temp[0], &temp[findIndex]);
            this->parser->doCommand(0, sub);
            temp.erase (temp.begin(),temp.begin()+findIndex+1);
            sub.clear();
        }

    }
    return temp.size()+4;
}
const vector<string> LoopCommand::createCommandVec(vector<string> &data,int constIndexForWhile){
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
bool LoopCommand::conditionParser(int index,vector<string> &data){
    string leftSide;
    string condition;
    string rightSide;
    unsigned long conditionSize;
    condition = getOperator(data[index]);
    conditionSize = condition.length();
    //get the left side of the condition
    leftSide = data[index].substr(0,data[index].find(condition));
    leftSide.erase(std::remove(leftSide.begin(),leftSide.end(),' '),leftSide.end());
    //get  the right side of the condition
    rightSide = data[index].substr(data[index].find(condition)+conditionSize);
    rightSide.erase(std::remove(rightSide.begin(),rightSide.end(),' '),rightSide.end());
    return checkCondition(leftSide, condition, rightSide);

}
//check the condition
bool LoopCommand::checkCondition(string &leftSide, string &operatorStr, string &rightSide) {
    try {
        Interpreter *inter = new Interpreter();
        inter->setVariables(*mapForShutingYard);
        Expression *exp1 = inter->interpret(leftSide);
        double leftVal = exp1->calculate();
        Expression *exp2 = inter->interpret(rightSide);
        double rightVal = exp2->calculate();
        //return answer accompanying the operator
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

string LoopCommand::getOperator(const string &line) {
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
