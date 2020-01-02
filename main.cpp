#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <mutex>
#include <unistd.h>
#include "SymbolTable.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "LoopCommand.h"
#include "ParserCommand.h"
#include "IfCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"


using namespace std;
//int argc, char *arg[]
string replaceBracketsComma(string &str);
int lexer(string &str, vector<string>&data);
void userInitializeParameterMap(unordered_map<string,double > &user);
void simulatorInitializeParameterMap(unordered_map<string,double >&simulator);


int main(int argc,char *argv[]) {
    string name=argv[1];
    vector<string> data;
    static unordered_map<string,Command *> mappingCommand;
    unordered_map<string, double> simulator;
    unordered_map<string, double> user;
    //include all the variable and here value
    vector<Map >mapForShutingYard;
    //map contain name var,path,symbole-who bind
    vector<Test >tranferInfo;
    //in order to close the socket threads
    vector<int>saveSocket;
    vector<pthread_t> threads;
    mutex mutex;
    //pthread_mutex_t mutex;
    //in order to send message to simulator
    unordered_map<string, double>forConnect;
    ifstream in_s(name);
    int check;
    if (in_s.is_open()) {
        string line;
        string lineWiteoutBracketsComma;
        //read line by line from the text
        while (getline(in_s, line)) {
            lineWiteoutBracketsComma = replaceBracketsComma(line);
            lexer(line, data);
        }

        in_s.close();
    } else
        cout << "Could not open: " << endl;

    int index = 0;
    //initialize map with pass and value
    userInitializeParameterMap(user);
    simulatorInitializeParameterMap(simulator);
    SymbolTable *symbolTable = new SymbolTable(&simulator, &user, &forConnect,&mapForShutingYard,&tranferInfo);
    ParserCommand *parser= new ParserCommand(&forConnect, &mappingCommand);
    //map command
    mappingCommand.insert(make_pair("openDataServer", new OpenServerCommand(symbolTable, &threads,&saveSocket,&mutex)));
    mappingCommand.insert(make_pair("connectControlClient", new ConnectCommand(symbolTable, &threads,&saveSocket)));
    mappingCommand.insert(make_pair("var", new DefineVarCommand(symbolTable,&mapForShutingYard,&tranferInfo)));
    mappingCommand.insert(make_pair("while", new LoopCommand(parser,&mapForShutingYard,&user)));
    mappingCommand.insert(make_pair("if", new IfCommand(parser,&mapForShutingYard)));
    mappingCommand.insert(make_pair("Sleep", new SleepCommand()));
    mappingCommand.insert(make_pair("Print", new PrintCommand(&mapForShutingYard)));
    parser->doCommand(index,data);
    //close text
    in_s.close();
    for( int i=0; i<saveSocket.size(); i++){
        close(saveSocket[i]); //closing the listening socket
    }
    //delete all the command in the map
    for (auto &x : mappingCommand) {
        delete x.second;
    }
    delete symbolTable;
    delete parser;

}
    string replaceBracketsComma(string &str) {
        replace(str.begin(), str.end(), '\t', ' ');
        return str;
  }
string Space(string &input)
{
    input.erase(std::remove(input.begin(),input.end(),' '),input.end());
    return input;
}
//splite the text to tokens in vector
    int lexer(string &str, vector<string> &data) {
        auto pos = str.find_first_not_of(' ');
        auto Trimmed = str.substr(pos != std::string::npos ? pos : 0);
        str=Trimmed;
        replace(str.begin(), str.end(), '\t', ' ');
        string word;
        string word2;
//        Space(str);
        //save the firat word from the str
        for (int i = 0; i < str.length(); i++) {
            while (str[i] != ' ' && str[i] != '(' && i < str.length()) {
                if (str[i] != '\t') {
                    word = word + str[i];
                }
                i++;
            }
            break;
        }
        Space(word);
        if ((word.compare("Print") == 0) || (word.compare("Sleep") == 0)) {
            data.push_back(word);
            word2 = str.substr(str.find('(') + 1);
            word2 = word2.substr(0, word2.length() - 1);
            data.push_back(word2);
            data.push_back("end of line");
            word2 = "";
        } else if ((word.compare("while") == 0) || (word.compare("if") == 0)) {
            data.push_back(word);
            word2 = str.substr(word.length() + 1);
            word2 = word2.substr(0, word2.length() - 1);
            data.push_back(word2);
            data.push_back("{");
//            data.push_back("end of line");
            word2 = "";
        } else if (word.compare("var") == 0) {
            data.push_back(word);
            word2 = str.substr(4);
            int token = str.find('=');
            string temp;
            if (str.find('=') == -1) {
                ///////////////////////////////////////////
                word2.erase(std::remove(word2.begin(),word2.end(),' '),word2.end());
                ////////////////////////////
                int x = word2.find('>');
                int y = word2.find('<');
                if (x > y) {
                    temp = word2.substr(0, x -1);
                    data.push_back(temp);
                    data.push_back("->");
                    replace(word2.begin(), word2.end(), '"', ' ');
                    word2 = word2.substr(x + 1);
                } else {
                    temp = word2.substr(0, y);
                    data.push_back(temp);
                    data.push_back("<-");
                    replace(word2.begin(), word2.end(), '"', ' ');
                    word2 = word2.substr(y + 1);
                }
                string word3= word2.substr(0,word2.find('('));
                Space((word3));
                data.push_back(word3);
                word2 = word2.substr(word2.find('(') + 1);
                word2 = word2.substr(0, word2.length() - 1);
                Space(word2);
                data.push_back(word2);
            } else {
                string temp;
                temp = word2.substr(0, word2.find('='));
                Space(temp);
                data.push_back(temp);
                data.push_back("=");
                word2 = word2.substr(word2.find('=') + 1);
                Space(word2);
                data.push_back(word2);
            }
            data.push_back("end of line");
        } else {
            if (str.find('=') == -1) {
                if (word.compare("}") != 0) {
                    data.push_back(word);
                    word2 = str.substr(str.find('(') + 1);
                    word2 = word2.substr(0, word2.length() - 1);
                    Space(word2);
                    if(word2.find(',')!=-1) {
                        string var = word2.substr(0, word2.find(','));
                        data.push_back(var);
                        string var2 = word2.substr(word2.find(',') + 1, word2.length());
                        data.push_back(var2);
                    }
                    else{
                        data.push_back(word2);
                    }
                } else {
                    data.push_back("}");
                }
            } else {
                string temp;
//                temp = str.substr(0, str.find('=')-1);
                temp = str.substr(0, str.find('='));
                Space(temp);
                data.push_back(temp);
                data.push_back("=");
                word2 = str.substr(str.find('=') + 1,str.length());
                Space(word2);
                data.push_back(word2);
            }
            data.push_back("end of line");
        }

    }
//initialize map
    void userInitializeParameterMap(unordered_map<string,double > &user){
        //////user-map
        user["/instrumentation/airspeed-indicator/indicated-speed-kt"]=0;
        user["/sim/time/warp"]=0;
        user["/controls/switches/magnetos"]=0;
        user["/instrumentation/heading-indicator/offset-deg"]=0;
        user["/instrumentation/altimeter/indicated-altitude-ft"]=0;
        user["/instrumentation/altimeter/pressure-alt-ft"]=0;
        user["/instrumentation/attitude-indicator/indicated-pitch-deg"]=0;
        user["/instrumentation/attitude-indicator/indicated-roll-deg"]=0;
        user["/instrumentation/attitude-indicator/internal-pitch-deg"]=0;
        user["/instrumentation/attitude-indicator/internal-roll-deg"]=0;
        user["/instrumentation/encoder/indicated-altitude-ft"]=0;
        user["/instrumentation/encoder/pressure-alt-ft"]=0;
        user["/instrumentation/gps/indicated-altitude-ft"]=0;
        user["/instrumentation/gps/indicated-ground-speed-kt"]=0;
        user["/instrumentation/gps/indicated-vertical-speed"]=0;
        user["/instrumentation/heading-indicator/indicated-heading-deg"]=0;
        user["/instrumentation/magnetic-compass/indicated-heading-deg"]=0;
        user["/instrumentation/slip-skid-ball/indicated-slip-skid"]=0;
        user["/instrumentation/turn-indicator/indicated-turn-rate"]=0;
        user["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"]=0;
        user["/controls/flight/aileron"]=0;
        user["/controls/flight/elevator"]=0;
        user["/controls/flight/rudder"]=0;
        user["/controls/flight/flaps"]=0;
        user["/controls/engines/engine/throttle"]=0;
        user["/controls/engines/current-engine/throttle"]=0;
        user["/controls/switches/master-avionics"]=0;
        user["/controls/switches/starter"]=0;
        user["/engines/active-engine/auto-start"]=0;
        user["/controls/flight/speedbrake"]=0;
        user["/sim/model/c172p/brake-parking"]=0;
        user["/controls/engines/engine/primer"]=0;
        user["/controls/engines/current-engine/mixture"]=0;
        user["/controls/switches/master-bat"]=0;
        user["/controls/switches/master-alt"]=0;
        user["/engines/engine/rpm"]=0;

    }
//initialize simulator map
    void simulatorInitializeParameterMap(unordered_map<string,double > &simulator) {
        /////////simulator-map
        simulator["/instrumentation/airspeed-indicator/indicated-speed-kt"]=0;
        simulator["/sim/time/warp"]=0;
        simulator["/controls/switches/magnetos"]=0;
        simulator["/instrumentation/heading-indicator/offset-deg"]=0;
        simulator["/instrumentation/altimeter/indicated-altitude-ft"]=0;
        simulator["/instrumentation/altimeter/pressure-alt-ft"]=0;
        simulator["/instrumentation/attitude-indicator/indicated-pitch-deg"]=0;
        simulator["/instrumentation/attitude-indicator/indicated-roll-deg"]=0;
        simulator["/instrumentation/attitude-indicator/internal-pitch-deg"]=0;
        simulator["/instrumentation/attitude-indicator/internal-roll-deg"]=0;
        simulator["/instrumentation/encoder/indicated-altitude-ft"]=0;
        simulator["/instrumentation/encoder/pressure-alt-ft"]=0;
        simulator["/instrumentation/gps/indicated-altitude-ft"]=0;
        simulator["/instrumentation/gps/indicated-ground-speed-kt"]=0;
        simulator["/instrumentation/gps/indicated-vertical-speed"]=0;
        simulator["/instrumentation/heading-indicator/indicated-heading-deg"]=0;
        simulator["/instrumentation/magnetic-compass/indicated-heading-deg"]=0;
        simulator["/instrumentation/slip-skid-ball/indicated-slip-skid"]=0;
        simulator["/instrumentation/turn-indicator/indicated-turn-rate"]=0;
        simulator["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"]=0;
        simulator["/controls/flight/aileron"]=0;
        simulator["/controls/flight/elevator"]=0;
        simulator["/controls/flight/rudder"]=0;
        simulator["/controls/flight/flaps"]=0;
        simulator["/controls/engines/engine/throttle"]=0;
        simulator["/controls/engines/current-engine/throttle"]=0;
        simulator["/controls/switches/master-avionics"]=0;
        simulator["/controls/switches/starter"]=0;
        simulator["/engines/active-engine/auto-start"]=0;
        simulator["/controls/flight/speedbrake"]=0;
        simulator["/sim/model/c172p/brake-parking"]=0;
        simulator["/controls/engines/engine/primer"]=0;
        simulator["/controls/engines/current-engine/mixture"]=0;
        simulator["/controls/switches/master-bat"]=0;
        simulator["/controls/switches/master-alt"]=0;
        simulator["/engines/engine/rpm"]=0;
    }

