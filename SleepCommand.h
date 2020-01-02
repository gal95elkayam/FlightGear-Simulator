//
// Created by gal on 26/12/2019.
//

#ifndef FLY_SLEEPCOMMAND_H
#define FLY_SLEEPCOMMAND_H


#include <unordered_map>
#include <thread>
#include "shutingYard.h"
class SleepCommand: public Command {
    int execute(int index,vector<string> &data,unordered_map<string, double>*forConnect);

};


#endif //FLY_SLEEPCOMMAND_H
