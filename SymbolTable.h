//
// Created by gal on 20/12/2019.
//

#ifndef UNTITLED1_SYMBOLTABLE_H
#define UNTITLED1_SYMBOLTABLE_H

#include <sys/types.h>
#include <vector>
#include <unordered_map>
#include "Struct.h"
#include "Command.h"


class SymbolTable {
protected:
    int socketfd;
    unordered_map<string,double > *simulatorSymbolTable;
    unordered_map<string,double > *userSymbolTable;
//    pthread_mutex_t * m;
    unordered_map<string, double>*connectMap;
    vector<Map >*mapForShutingYard;


public:
    vector<Test >*tranferInfo;
    //mutex* mutex_ig;
    void setSocketfd(int socketfd);
    SymbolTable(unordered_map<string,double > *simulator, unordered_map<string,double > *user,
            unordered_map<string, double>*forConnect,vector<Map >*mapForShutingYard,vector<Test >*tranferInfo);
    void Update(vector<string>);
    void updateUserMap(string path, double value,string var);
    double getValueSimulator(string str);
    void setVarValueInSimulator(const string path, double value);

};

#endif //UNTITLED1_SYMBOLTABLE_H