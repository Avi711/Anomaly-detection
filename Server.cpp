//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//


#include "Server.h"

Server::Server(int port)throw (const char*) {

}

void Server::start(ClientHandler& ch)throw(const char*){
}

void Server::stop(){
    t->join(); // do not delete this!
}

Server::~Server() {
}

