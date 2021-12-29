//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//

#ifndef SERVER_H_
#define SERVER_H_


#include <thread>
#include <netinet/in.h>
#include "sys/socket.h"
#include "CLI.h"
#include<signal.h>



#include <pthread.h>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<signal.h>
#include <sstream>


using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};

class SocketIO : public DefaultIO{
public:
    int sockIO;
    virtual string read();

    virtual void write(string text);

    virtual void write(float f);

    virtual void read(float *f);
};
// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    SocketIO io;
    virtual void handle(int clientID){
        io.sockIO = clientID;
        CLI cli(&io);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    thread* t; // the thread to run the start() method in
    int serverPort;
    bool running;
    int sock;
    sockaddr_in hint;
    sockaddr_in hint2;

    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
