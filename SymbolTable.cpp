//
// Created by gal on 20/12/2019.
//

#include <cstring>
#include <unistd.h>
#include <mutex>
#include <iostream>
#include <thread>
#include <sys/socket.h>
#include "SymbolTable.h"
using namespace std;

SymbolTable::SymbolTable(unordered_map<string,double > *simulator, unordered_map<string,double > *user,
                         unordered_map<string, double>*forConnect,vector<Map >*mapForShutingYard,vector<Test >*tranferInfo)
{
    this->simulatorSymbolTable=simulator;
    this->userSymbolTable=user;
    this->connectMap=forConnect;
    this->mapForShutingYard=mapForShutingYard;
    this->tranferInfo=tranferInfo;
}
//update the user map by the value in the simulator "<-"
void SymbolTable::updateUserMap(string path, double value,string var){
    mutex g_i_mutex;
    g_i_mutex.lock();
    std::thread::id this_id = std::this_thread::get_id();
    int saveIndex;
   // std::cout << "updateUserMap:: Thread " << this_id <<" acquired lock...\n";
    (*userSymbolTable)[path]=value;
    for (int it = 0; it < (*this->mapForShutingYard).size(); it++) {
        if (var == (*this->mapForShutingYard)[it].var) {
            //we found in the map the we need to update the client or the simulator by the symbole
            saveIndex = it;
        }
    }
    (*this->mapForShutingYard)[saveIndex].value= (*userSymbolTable)[path];
//    cout<<"SymbolTable::updateUserMap::path "<<path<< "value: "<<value<<"\n";

    g_i_mutex.unlock();
   // std::cout << "updateUserMap:: Thread " << this_id <<"  released lock...\n";
}
//return value that associated to that path
double SymbolTable::getValueSimulator(string str){
    mutex g_i_mutex;
    lock_guard<std::mutex> lock(g_i_mutex);
    std::thread::id this_id = std::this_thread::get_id();
//    std::cout << "getValueSimulator:: Thread " << this_id <<" acquired lock...\n";
    double val= (*simulatorSymbolTable)[str];
//    std::cout << "getValueSimulator:: Thread " << this_id <<"  released lock...\n";
    return val;
}
//send message to simulator in order to update value
void SymbolTable::setVarValueInSimulator(const string path, double value) {
    mutex g_i_mutex;
    std::thread::id this_id = std::this_thread::get_id();
//    std::cout << "setVarValueInSimulator:: Thread " << this_id <<" acquired lock...\n";
    g_i_mutex.lock();
    (*this->connectMap).clear();
    (*userSymbolTable)[path] = value;
    (*simulatorSymbolTable)[path] = value;
//        cout << "in symbolTable calss -set variable for message: path  " << simulatorSymbolTable[path] << "value : "<< value << "\n";
    (*this->connectMap).insert(make_pair(path, value));
    string mes = "set " + (*this->connectMap).begin()->first + " " + to_string((*this->connectMap).begin()->second) +
                 "\r\n";
    int is_sent = send(this->socketfd, mes.c_str(), strlen(mes.c_str()), 0);
//    cout << "setVarValueInSimulator:: " << "thread " << this_id << "message: " << mes.c_str()
//         << "return value: " << is_sent << "\n";
//    std::cout << "setVarValueInSimulator:: Thread " << this_id << "  released lock...\n";
    g_i_mutex.unlock();
}
//update the user map with the values we get from the simulator
void SymbolTable::Update(vector<string>vals) {
    mutex g_i_mutex;
    int x=0;
    std::thread::id this_id = std::this_thread::get_id();
//    std::cout << "Update:: Thread " << this_id <<" acquired lock...\n";
    g_i_mutex.lock();
    try {
        (*userSymbolTable)[ "/instrumentation/airspeed-indicator/indicated-speed-kt"] = stod(
                vals.at(0));
        (*userSymbolTable)[ "/sim/time/warp"] = stod(vals.at(1));
        (*userSymbolTable)[ "/controls/switches/magnetos"] = stod(vals.at(2));
        (*userSymbolTable)["/instrumentation/heading-indicator/offset-deg"] = stod(
                vals.at(3));
        (*userSymbolTable)["/instrumentation/altimeter/indicated-altitude-ft"] = stod(
                vals.at(4));
        (*userSymbolTable)["/instrumentation/altimeter/pressure-alt-ft"] = stod(
                vals.at(5));
        (*userSymbolTable)[ "/instrumentation/attitude-indicator/indicated-pitch-deg"] = stod(
                vals.at(6));
        (*userSymbolTable)["/instrumentation/attitude-indicator/indicated-roll-deg"] = stod(
                vals.at(7));
        (*userSymbolTable)[ "/instrumentation/attitude-indicator/internal-pitch-deg"] = stod(
                vals.at(8));
        (*userSymbolTable)["/instrumentation/attitude-indicator/internal-roll-deg"] = stod(
                vals.at(9));
        (*userSymbolTable)[ "/instrumentation/encoder/indicated-altitude-ft"] = stod(
                vals.at(10));
        (*userSymbolTable)[ "/instrumentation/encoder/pressure-alt-ft"] = stod(vals.at(11));
        (*userSymbolTable)[ "/instrumentation/gps/indicated-altitude-ft"] = stod(
                vals.at(12));
        (*userSymbolTable)["/instrumentation/gps/indicated-ground-speed-kt"] = stod(
                vals.at(13));
        (*userSymbolTable)[ "/instrumentation/gps/indicated-vertical-speed"] = stod(
                vals.at(14));
        (*userSymbolTable)[ "/instrumentation/heading-indicator/indicated-heading-deg"] = stod(
                vals.at(15));
        (*userSymbolTable)["/instrumentation/magnetic-compass/indicated-heading-deg"] = stod(
                vals.at(16));
        (*userSymbolTable)[ "/instrumentation/slip-skid-ball/indicated-slip-skid"] = stod(
                vals.at(17));
        (*userSymbolTable)["/instrumentation/turn-indicator/indicated-turn-rate"] = stod(
                vals.at(18));
        (*userSymbolTable)[ "/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = stod(
                vals.at(19));
        (*userSymbolTable)[ "/controls/flight/aileron"] = stod(vals.at(20));
        (*userSymbolTable)[ "/controls/flight/elevator"] = stod(vals.at(21));
        (*userSymbolTable)["/controls/flight/rudder"] = stod(vals.at(22));
        (*userSymbolTable)[ "/controls/flight/flaps"] = stod(vals.at(23));
        (*userSymbolTable)["/controls/engines/engine/throttle"] = stod(vals.at(24));
        (*userSymbolTable)[ "/controls/engines/current-engine/throttle"] = stod(vals.at(25));
        (*userSymbolTable)[ "/controls/switches/master-avionics"] = stod(vals.at(26));
        (*userSymbolTable)["/controls/switches/starter"] = stod(vals.at(27));
        (*userSymbolTable)["/engines/active-engine/auto-start"] = stod(vals.at(28));
        (*userSymbolTable)["/controls/flight/speedbrake"] = stod(vals.at(29));
        (*userSymbolTable)["/sim/model/c172p/brake-parking"] = stod(vals.at(30));
        (*userSymbolTable)["/controls/engines/engine/primer"] = stod(vals.at(31));
        (*userSymbolTable)[ "/controls/engines/current-engine/mixture"] = stod(vals.at(32));
        (*userSymbolTable)[ "/controls/switches/master-bat"] = stod(vals.at(33));
        (*userSymbolTable)[ "/controls/switches/master-alt"] = stod(vals.at(34));
        (*userSymbolTable)[ "/engines/engine/rpm"] = stod(vals.at(35));

//    cout << (*userSymbolTable)["engine_rpm", "/engines/engine/rpm"] << "\n";
        for (int i = 0; i < tranferInfo->size(); i++) {
            for (unordered_map<string, double>::iterator it = (*userSymbolTable).begin();
                 it != (*userSymbolTable).end(); ++it)
                if ((*tranferInfo)[i].path == it->first) {
                    if (((*tranferInfo)[i].symbol == 0)) {
                        updateUserMap((*tranferInfo)[i].path, it->second, (*tranferInfo)[i].var);
                    }
                }
        }
    }
    catch (...){
        x=1;
        //cout<<"not good"<<endl;
    }
//    cout<<"SymbolTable::Update-- rpm:"<<vals.at(35)<< "\n";
    g_i_mutex.unlock();
//    std::cout << "Update:: Thread " << this_id <<"  released lock...\n";
}

void SymbolTable:: setSocketfd(int socketfd){
    this->socketfd=socketfd;
}
