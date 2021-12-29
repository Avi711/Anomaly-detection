//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//


#include "Server.h"
#define BYTE 1

string SocketIO::read() {
    char buf = ' ';
    string input = "";
    while (buf != '\n') {
        recv(sockIO,&buf, BYTE,0);
        input = input + buf;
    }
    return input;
}

void SocketIO::write(string text) {
    send(sockIO,text.c_str(),text.size(),0);
}

void SocketIO::write(float f) {
    std::ostringstream ss;
    ss << f;
    std::string s(ss.str());
    write(s);
}

void SocketIO::read(float *f) {

}



Server::Server(int port)throw (const char*) {
    this->serverPort = port;
    this->sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock == -1)
        throw "fail";
    this->hint.sin_family = AF_INET;
    this->hint.sin_addr.s_addr = INADDR_ANY;
    this->hint.sin_port = htons(port);

    int bind1 = bind(sock,(sockaddr*)&hint,sizeof(hint));
    if (bind1 < 0) {
        throw "fail";
    }
    int listen1 = listen(sock,10);
    if (listen1 < 0)
        throw "fail";
    running = true;
}

void Server::start(ClientHandler& ch)throw(const char*){
    t=new thread([&ch,this](){
        while(running){
            socklen_t clientSize=sizeof(hint2);
            alarm(1);
            int clientSock = accept(sock,(struct sockaddr*)&hint2,&clientSize);
            if(clientSock>0){
                ch.handle(clientSock);
                close(clientSock);
            }
            alarm(0);

        }
        close(sock);
    });

}
void Server::stop(){
    running = false;
    t->join(); // do not delete this!
}

Server::~Server() {
}
