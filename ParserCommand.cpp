//
// Created by gal on 24/12/2019.
//

#include <iostream>
#include <regex>
#include <unistd.h>
#include <mutex>
#include "ParserCommand.h"
#include "shutingYard.h"
#include "LoopCommand.h"

ParserCommand::ParserCommand( unordered_map<string, double>*forConnect,unordered_map<string, Command *> *mapCommand)
{
    this->forConnect=forConnect;
    this->data=data;
    this->mapCommand=mapCommand;

}
//pass the vector with all the data from the txt file and do there command
int ParserCommand::doCommand(int index,vector<string>&data) {

    while (index < data.size()) {
        string datafinf = data[index];
        if (datafinf.compare("end of line") == 0) {
            index += 1;
            continue;
        }
        Command *c;
        try {
            c = (*mapCommand).at(datafinf);

        }
        catch (...) {
//in this case we get somthing like roll=heading
            c = (*mapCommand).at("var");
        }
        if (c != NULL) {
//pass to the class the command need be execute
            index += c->execute(index + 1, data, forConnect);
        }
    }
    return index;
}