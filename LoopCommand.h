//
// Created by gal on 24/12/2019.
//

#ifndef FLY_LOOPCOMMAND_H
#define FLY_LOOPCOMMAND_H



#include "ParserCommand.h"
#include "DefineVarCommand.h"

class LoopCommand: public Command{
public:
    //take only one line and send to parser to do this line command
//    vector<string>dataParser;
//    SymbolTable * symTable;
    ParserCommand *parser;
    vector<Map >*mapForShutingYard;
    unordered_map<string,double > *user;
    LoopCommand(ParserCommand *parser,vector<Map >*mapForShutingYard,unordered_map<string,double > *user){
        this->parser=parser;
//        this->symTable=symbolTable;
        this->mapForShutingYard=mapForShutingYard;
        this->user=user;
    }
    const vector<string> createCommandVec(vector<string> &data,int constIndexForWhile);
    bool conditionParser(int index,vector<string> &data);
    int execute(int index,vector<string> &data,unordered_map<string, double>*forConnect);
   string getOperator(const string &str);
bool checkCondition(string &leftSide, string &operatorStr, string &rightSide);
};


#endif //FLY_LOOPCOMMAND_H
