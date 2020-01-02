//
// Created by gal on 26/12/2019.
//

#include <iostream>
#include "SleepCommand.h"


int SleepCommand ::execute(int index,vector<string> &data,unordered_map<string, double>*forConnect) {
    // Calculate the expression that params represents.
    Interpreter *inter = new Interpreter();
    string s(data[index].data());
    Expression *exp1 = inter->interpret(s);
    int time = exp1->calculate();
//    cout<<"SleepCommand ::execute thread main sleep- sleep time :  "<<time<<"\n";
    /* Stop main thread */
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    return 2;
}


