//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    vector<Command*> commands;
    // you can add data members
public:
    CLI(DefaultIO* dio);
    void start();
    void printMenu();
    virtual ~CLI();
};

#endif /* CLI_H_ */