//
// Created by gal on 26/12/2019.
//

#ifndef FLY_PRINTCOMMAND_H
#define FLY_PRINTCOMMAND_H


#include <vector>
#include <unordered_map>
#include "SymbolTable.h"

class PrintCommand: public Command {
public:
    vector<Map >*mapForShutingYard;
    PrintCommand(vector<Map >*mapForShutingYard);
    int execute(int index,vector<string> &data,unordered_map<string, double>*forConnect);
};


#endif //FLY_PRINTCOMMAND_H
