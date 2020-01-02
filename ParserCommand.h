//
// Created by gal on 24/12/2019.
//

#ifndef FLY_PARSERCOMMAND_H
#define FLY_PARSERCOMMAND_H


#include <unordered_map>
#include "DefineVarCommand.h"

class ParserCommand {
public:
    unordered_map<string, double>*forConnect;
    unordered_map<string, Command *> *mapCommand;
    vector<string>data;
//    SymbolTable * symbolTable;
//    vector<Map >*mapForShutingYard;

    ParserCommand( unordered_map<string, double>*forConnect,unordered_map<string, Command *> *mapCommand);
    int doCommand(int index,vector<string>&data);
};


#endif //FLY_PARSERCOMMAND_H
