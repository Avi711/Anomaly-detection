//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//


#include "Server.h"

string SocketIO::read() {
    char buf[4096];
    recv(sock,buf, 4096,0);
    string s = "";
    for (int i = 0; i < 4096; i++) {
        s = s + buf[i];
    }
    return s;
}

void SocketIO::write(string text) {
    send(sock,text.c_str(),text.size() + 1,0);
}

void SocketIO::write(float f) {

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

}
void Server::stop(){
    running = false;
    t->join(); // do not delete this!
}

Server::~Server() {
}
