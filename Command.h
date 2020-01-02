//
// Created by gal on 20/12/2019.
//

#include <string>
#include <vector>


#ifndef UNTITLED1_COMMEND_H
#define UNTITLED1_COMMEND_H

#endif //UNTITLED1_COMMEND_H
using namespace std;
class Command {
public:
    virtual int execute(int index,vector<string> &data,unordered_map<string, double>*forConnect) = 0;
    virtual ~Command() {}
};
