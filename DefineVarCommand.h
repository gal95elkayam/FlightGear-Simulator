//
// Created by gal on 22/12/2019.
//

#ifndef FLY_DEFINEVARCOMMAND_H
#define FLY_DEFINEVARCOMMAND_H


//
// Created by gal on 12/12/2019.
//

#ifndef UNTITLED1_DEFINEVARCOMMAND_H
#define UNTITLED1_DEFINEVARCOMMAND_H


#include "SymbolTable.h"

class DefineVarCommand : public Command{
protected:
    SymbolTable * symTable;
    //1-symbol setting user, 0- setting symbol simulator

public:
    vector<Test >*tranferInfo;
    vector<Map >*mapForShutingYard;
    DefineVarCommand(SymbolTable * symbolTable,vector<Map >*mapForShutingYard, vector<Test >*tranferInfo);
    int execute(int index,vector<string> &data,unordered_map<string, double>*forConnect);
    bool checkIsValue(vector<string>data, int index);
    void setVar(string str);
    int checkIsVariable( string str);
};


#endif //UNTITLED1_DEFINEVARCOMMAND_H
#endif //FLY_DEFINEVARCOMMAND_H
