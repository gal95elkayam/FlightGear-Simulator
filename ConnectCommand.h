//
// Created by gal on 22/12/2019.
//

#ifndef FLY_CONNECTCOMMAND_H
#define FLY_CONNECTCOMMAND_H


#include "SymbolTable.h"


class ConnectCommand: public Command {

public:
     SymbolTable * symTable;
    void static readText(int listenFd,unordered_map<string, double>&forConnect);
    vector<int>*saveSocket;
    int execute(int index,vector<string> &data,unordered_map<string, double>*forConnect);
    vector<pthread_t> *threads;
    ConnectCommand(SymbolTable * symbolTable, vector<pthread_t> *threads,vector<int>*saveSocket);
};


#endif //FLY_CONNECTCOMMAND_H
