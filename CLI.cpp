//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//


#include "CLI.h"
#define DEFAULT_CORRELATION 0.9
CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    commands.push_back(new uploadCSVCommand(dio));
    commands.push_back(new algoSetCommand(dio));
    commands.push_back(new detectCommand(dio));
    commands.push_back(new resultCommand(dio));
    commands.push_back(new analyzeCommand(dio));
    commands.push_back(new exitCommand(dio));
}

void CLI::printMenu() {
    dio->write("Welcome to the Anomaly Detection Server.\n");
    dio->write("Please choose an option:\n");
    for (Command* command : this->commands) {
        dio->write(command->description);
    }
}


void CLI::start(){
    printMenu();
    string input = "1";
    input = dio->read();
    Information info;
    info.correlation = DEFAULT_CORRELATION;
    while(input != "6") {
        commands[std::stoi(input) - 1]->execute(info);
        printMenu();
        input = dio->read();
    }
}


CLI::~CLI() {
    for (Command* command : this->commands) {
        delete(command);
    }
}
