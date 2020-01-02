//
// Created by gal on 26/12/2019.
//

#ifndef FLY_IFCOMMAND_H
#define FLY_IFCOMMAND_H



#include "ParserCommand.h"

class IfCommand : public Command{
public:
    const vector<string> createCommandVec(vector<string> &data,int constIndexForWhile);
    ParserCommand *parser;
    vector<Map >*mapForShutingYard;
    IfCommand(ParserCommand *parser,vector<Map >*mapForShutingYard){
        this->parser=parser;
        this->mapForShutingYard=mapForShutingYard;
    }
    bool conditionParser(int index,vector<string> &data);
    int execute(int index,vector<string> &data,unordered_map<string, double>*forConnect);
    string getOperator(const string &str);
    bool checkCondition(string &leftSide, string &operatorStr, string &rightSide);

};


#endif //FLY_IFCOMMAND_H
