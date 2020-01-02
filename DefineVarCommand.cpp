//
// Created by gal on 12/12/2019.
//

#include <algorithm>
#include <sstream>
#include <iostream>
#include "DefineVarCommand.h"
#include "Expression.h"
#include "shutingYard.h"

DefineVarCommand::DefineVarCommand(SymbolTable * symbolTable,vector<Map >*mapForShutingYard,vector<Test >*tranferInfo){
    this->symTable=symbolTable;
    this->mapForShutingYard=mapForShutingYard;
    this->tranferInfo=tranferInfo;
}
//deal with var command
int DefineVarCommand::execute(int index,vector<string> &data,unordered_map<string, double>*forConnect) {

    int indexForReturn=0;
    bool notUpdate=false;
    int saveIndex=-1;
    int indexForPlaceVar;
    //we need to update from the simulator to user
    if (data[index + 1]=="<-") {
        indexForReturn=5;
        //take the name of the var,and the path- we know to update the simulator
        (*tranferInfo).push_back({data[index], data[index+3], 0});
        //update the user-get the value from the simulator
        double valueSimulator = this->symTable->getValueSimulator(data[index+3]);
        //update the globla map for shuting yard
        (*this->mapForShutingYard).push_back({data[index], valueSimulator});
        //update the user by this value
        this->symTable->updateUserMap(data[index+3], valueSimulator,data[index]);
        return indexForReturn;
    }
    //we need to update from the user to simulator
    else if (data[index + 1]=="->") {
        indexForReturn=5;
        //take the name of the var, and we know to update the user
        (*tranferInfo).push_back({data[index], data[index+3], 1});
        return indexForReturn;
    }
    // else- declare a var to hold some value- (need to checkIsValue expression)
    else if (data[index]=="=")  {
        indexForReturn= 3;
        //search if the var is in the tranferInfo else insert to mapForShutingYard vector
        for (int it = 0; it < (*tranferInfo).size(); it++) {
            if (data[index - 1] == (*tranferInfo)[it].var) {
                //we found in the map the we need to update the client or the simulator by the symbole
                saveIndex = it;
            }
        }
    }
    /////its like var h0 = heading
    else{
        int in;
        indexForReturn=4;
        for (int it = 0; it < (*this->mapForShutingYard).size(); it++) {
            if ((data[index+2]== (*mapForShutingYard)[it].var)) {
                in = it;
            }
        }
        (*this->mapForShutingYard).push_back({data[index],(*mapForShutingYard)[in].value});
        notUpdate=true;
    }
    //the var define in tranferInfo
    if (saveIndex != -1  && notUpdate==false) {
        //check value or expression or variable
        bool checkValue = checkIsValue(data, index+1);
        //its value
        if (checkValue == true) {
            //insert to global map for the shutimg yard
            try {
                (*this->mapForShutingYard).push_back({data[index - 1], stod(data[index + 1])});
            }
            catch (...){
                cout<<"DefineVarCommand::execute "<< data[index + 1]<<endl;
            }
            //need to update the simulator
            if ((*tranferInfo)[saveIndex].symbol == 1) {
                try {
                    this->symTable->setVarValueInSimulator((*tranferInfo)[saveIndex].path, stod(data[index + 1]));
                }
                catch (...){
                    cout<<"DefineVarCommand::execute 2"<< data[index + 1]<<endl;
                }
            }
        }
        //its variable like ---> mixture = roll
        else if((checkIsVariable(data[index+1]))>=0){
            indexForPlaceVar=checkIsVariable(data[index+1]);
            (*this->mapForShutingYard).push_back({data[index-1],(*mapForShutingYard)[indexForPlaceVar].value});
            //need to update the simulator
            if ((*tranferInfo)[saveIndex].symbol == 1) {
                this->symTable->setVarValueInSimulator((*tranferInfo)[saveIndex].path,(*mapForShutingYard)[indexForPlaceVar].value);
            }
        }

            //its expression
        else {
            Interpreter *inter = new Interpreter();
//            setVar(data.at(index+1));
            inter->setVariables(*mapForShutingYard);
            Expression *exp = inter->interpret(data[index + 1]);
            double result = exp->calculate();
            //update the global map
            (*this->mapForShutingYard).push_back({data[index - 1], result});
            //update the simulator
            if ((*tranferInfo)[saveIndex].symbol == 1) {
                this->symTable->setVarValueInSimulator((*tranferInfo)[saveIndex].path, result);
            }
        }
    }
    //the var doesnt define in tranferInfo
    if(saveIndex==-1 && notUpdate==false) {
        //checkIsValue if value or expression
        bool checkValue = checkIsValue(data, index);
        if (checkValue == true) {
            //insert to global map for the shutimg yard
            try {
                (*this->mapForShutingYard).push_back({data[index - 1], stod(data[index + 1])});
            }
            catch(...){
                cout<<"DefineVarCommand::execute 3"<<data[index + 1]<<endl;
            }
        }
            //its variable like ---> ho = roll
        else if((checkIsVariable(data[index+1]))>=0) {
            indexForPlaceVar = checkIsVariable(data[index + 1]);
            (*this->mapForShutingYard).push_back({data[index - 1], (*mapForShutingYard)[indexForPlaceVar].value});
        }
        else {
            Interpreter *inter = new Interpreter();
            inter->setVariables(*this->mapForShutingYard);
            Expression *exp = inter->interpret(data[index + 1]);
            double result = exp->calculate();
            //update the global map
            (*this->mapForShutingYard).push_back({data[index - 1], result});

        }
    }
    return indexForReturn;
}




bool DefineVarCommand::checkIsValue(vector<string> data, int index) {
    try
    {
        stod(data[index]);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

int DefineVarCommand::checkIsVariable( string str) {
    int index=-1;
    try {
        for (int it = 0; it <(*tranferInfo).size(); it++) {
            if (str==(*tranferInfo)[it].var)
                index = it;
        }
    }
    catch (...) {
        index = -1;
    }
    return index;
}
