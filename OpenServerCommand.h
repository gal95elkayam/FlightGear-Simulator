//
// Created by gal on 20/12/2019.
//
#ifndef UNTITLED1_OPENSERVERCOMMAND_H
#define UNTITLED1_OPENSERVERCOMMAND_H

#include <sys/types.h>
#include <mutex>
#include "SymbolTable.h"

class OpenServerCommand: public Command{
public:
    void UpdateMap(char buffer[]);
        vector<int>*socketServer;
    void readFromSimulator(int client_socket);
    int execute(int index,vector<string>& data,unordered_map<string, double>*forConnect);
    static vector<string> splitFile;
    static SymbolTable * symTable;
    vector<pthread_t> *threads;
    OpenServerCommand(SymbolTable* symbolTable, vector<pthread_t> *thread, vector<int>*saveSocket,mutex* mutex_ig);
    static vector<string> split(string buffer);
    virtual ~OpenServerCommand() {}
};


#endif //UNTITLED1_OPENSERVERCOMMAND_H