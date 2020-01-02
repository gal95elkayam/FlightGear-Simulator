//
// Created by gal on 26/12/2019.
//

#include <iostream>
#include "PrintCommand.h"
#include "shutingYard.h"

PrintCommand::PrintCommand(vector<Map> *mapForShutingYard) {
    this->mapForShutingYard=mapForShutingYard;
}
int PrintCommand:: execute(int index,vector<string> &data,unordered_map<string, double>*forConnect){
    //check f the string is expression or text
    if(data[index][0]!=34){//34 is the char "
        //we meed the value of this perameter then we use shuting yard
        Interpreter *inter = new Interpreter();
        inter->setVariables(*mapForShutingYard);
        string s(data[index].data());
        Expression *exp1 = inter->interpret(s);
        cout<<exp1->calculate()<<endl;
    }
    else {
        //its text "text"
        cout << data[index] << endl;
    }

    return 2;
}
