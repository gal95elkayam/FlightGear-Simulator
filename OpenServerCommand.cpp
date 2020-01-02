//
// Created by gal on 20/12/2019.
//
#include <netinet/in.h>
#include <unistd.h>
#include "OpenServerCommand.h"
#include "shutingYard.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <cstring>
#include <thread>
#include <algorithm>

#define MAX_BUFFER_SIZE 1024
using namespace std;
SymbolTable * OpenServerCommand::symTable;
vector<string> OpenServerCommand::splitFile;

//open server
int OpenServerCommand::execute(int index,vector<string> &data,unordered_map<string, double>*forConnect){
//    //check if the port is value or expression like ‫‪5000+4*100, according the "
    unsigned int port;
       if(data[index][0]!=34) { //34 is " in ascii
           Interpreter *inter = new Interpreter();
           string s(data[index].data());
           Expression *exp = inter->interpret(s);
           port = exp->calculate();
       }
       else{
           port=stoi(data[index].substr(1,data[index].length()));
       }
    char buffer[MAX_BUFFER_SIZE + 1];
    char doubleBuffer[2 * MAX_BUFFER_SIZE + 1];
    //readFromSimulator socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not readFromSimulator a socket"<<std::endl;
    }
    //bind socket to IP address
    // we first need to readFromSimulator the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    /////////////////////////////////////////
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    (*this->socketServer).push_back(client_socket);

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
    }
    std::cerr<<"accepting client"<<std::endl;
    close(socketfd);//closing the listening socket
    try {
        thread th([client_socket, this] { readFromSimulator(client_socket); });
        th.detach();
    }
    catch(...){
        cout<<"OpeneServerCommand::execute- ERROR: Couldn't create thread\n";
    }
    return index+1;
}
vector<string> OpenServerCommand::split(string str) {
    vector<string> tokens;
    tokens.clear();
    for (int i = 0; i < 36; i++) {
        int pos = str.find(",");
        tokens.push_back((str.substr(0, pos)));
        str = str.substr(pos + 1);
    }

    return tokens;
}


OpenServerCommand::OpenServerCommand(SymbolTable* symbolTable, vector<pthread_t> *thread, vector<int>*saveSocket,mutex* mutex_ig){
    this->threads=thread;
    this->symTable=symbolTable;
    this->socketServer=saveSocket;
}
//void OpenServerCommand::UpdateMap(char buffer[]){
//    string str=buffer;
//    string line;
//    int isExist;
//    vector<string> stringVals;
//    isExist=str.find("\n");
//    while(isExist >0){
//        line=str.substr(0,isExist);
//        cout<<"OpenServerCommand::UpdateMap values:  "<<line<<"\n";
//        stringVals = OpenServerCommand::split(line);
//        OpenServerCommand::symTable->Update(stringVals);
//        stringVals.clear();
//        str=str.substr(isExist+1,str.length());
//        isExist=str.find("\n");
//    }
//}
//here we get values from simulator and update the user map with this values
void OpenServerCommand::readFromSimulator(int client_socket) {
    string firstBuffer="";
    int temp=0;
    vector<string> stringVals;
    while(temp<1000){
        char line[1024] = {0};
        read(client_socket, line, 1024);
        string secondBuffer=line;
        firstBuffer=firstBuffer+secondBuffer;
        string firstToken=firstBuffer.substr(0,firstBuffer.find("\n"));
        string seconedToken=firstBuffer.substr(firstBuffer.find("\n")+1,firstBuffer.length());
        for (int i = 0; i < 36; i++) {
            int pos = firstToken.find(",");
            stringVals.push_back(firstToken.substr(0, pos));
            firstToken = firstToken.substr(pos + 1);
        }
                OpenServerCommand::symTable->Update(stringVals);
                stringVals.clear();
                firstBuffer=seconedToken;
    }

}


