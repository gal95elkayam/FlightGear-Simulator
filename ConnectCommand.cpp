//
// Created by gal on 22/12/2019.
//


#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <string>
#include <cstring>
#include <thread>
#include <mutex>
#include "ConnectCommand.h"
#include "shutingYard.h"


using namespace std;

//connect to server
int ConnectCommand::execute(int index,vector<string> &data,unordered_map<string, double>*forConnect){
    unsigned int port;
    if(data[index+1][0]!=34){ //34 is " in ascii
        Interpreter *inter = new Interpreter();
        string s(data[index+1].data());
        Expression *exp = inter->interpret(s);
        port = exp->calculate();
    }
    else{
        port=stoi(data[index].substr(1,data[index].length()));
    }

    cout<<"connectexecute"<<endl;
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr((data[index].substr(1,data[index].length()-2)).c_str());  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server" << std::endl;
    }
    (*this->saveSocket).push_back(client_socket);
    this->symTable->setSocketfd(client_socket);

    return 3;
}
ConnectCommand::ConnectCommand(SymbolTable * symbolTable, vector<pthread_t> *threads,vector<int>*saveSocket){
    this->symTable=symbolTable;
    this->threads=threads;
    this->saveSocket=saveSocket;

}
