

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here
};

// you may add here helper classes

class standardIO : DefaultIO {
    virtual string read() {
        string ret;
        cin >> ret;
        return ret;
    }

    virtual void write(string text) {
        cout << text << endl;
    }

    virtual void write(float f) {
        cout << f << endl;
    }

    virtual void read(float *f) {
        cin >> *f;
    }

};

class Anomaly {
public:
    int start, end;
};

class Information {
public:
    float correlation;
    vector<correlatedFeatures> cfVector;
    vector<AnomalyReport> *arVector;
};

// you may edit this class
class Command {
protected:
    string description;
    DefaultIO *dio;

public:
    Command(DefaultIO *dio, string name) : dio(dio) {
        this->description = name;
    }

    virtual void execute() = 0;

    virtual ~Command() {}
};

class uploadCSVCommand : Command {
public:

    uploadCSVCommand(DefaultIO *dio) : Command(dio, "upload a time series csv file\n") {};

    virtual void execute() {
        dio->write("Please upload your local train CSV file.\n");
        string line = dio->read();
        ofstream out("trainFile.csv");
        while (line != "done") {
            out << line << endl;
        }
        dio->write("Upload complete.\n");

        dio->write("Please upload your local test CSV file.\n");
        string line1 = dio->read();
        ofstream out1("testFile.csv");
        while (line1 != "done") {
            out << line1 << endl;
        }
        dio->write("Upload complete.\n");
    }

};

class algoSetCommand : Command {
public:
    algoSetCommand(DefaultIO *dio) : Command(dio, "algorithm settings\n") {};

    virtual void execute(Information info) {

        while (true) {
            dio->write("The current correlation threshold is ");
            dio->write(info.correlation);
            dio->write("\n");
            float cor;
            dio->read(&cor);
            if (cor >= 0 && cor <= 1) {
                info.correlation = cor;
                break;
            } else
                dio->write("please choose a value between 0 and 1.\n");
        }
    }
};

class detectCommand : Command {
public:
    detectCommand(DefaultIO *dio) : Command(dio, "detect anomalies\n") {};

    virtual void execute(Information info) {
        TimeSeries ts("trainFile.csv");
        HybridAnomalyDetector ad;
        ad.learnNormal(ts);
        TimeSeries ts2("testFile.csv");
        vector<AnomalyReport> ar = ad.detect(ts2);
        //info.arVector = &ar;
        dio->write("anomaly detection complete.\n");
    }
};

class resultCommand : Command {
public:
    resultCommand(DefaultIO *dio) : Command(dio, "display results\n") {};

    virtual void execute(Information info) {
        vector<AnomalyReport> ar = info.arVector;
        for (AnomalyReport report: ar) {
            dio->write(report.timeStep);
            dio->write("    " + report.description + "\n");
        }
        dio->write("Done.\n");
    }
};

class analyzeCommand : Command {
public:
    analyzeCommand(DefaultIO *dio) : Command(dio, "upload anomalies and analyze results\n") {};
    vector<Anomaly> userAnomalies;

    virtual void execute(Information info) {
        string line = dio->read();
        dio->write("Please upload your local anomalies file.\n");
        while (line != "done") {
            std::string delimiter = ",";
            std::string token = line.substr(0, line.find(delimiter));
            std::string token1 = line.substr(line.find(delimiter) + 1, line.size());
            Anomaly anomaly ;
            anomaly.start=std::stoi(token);
            anomaly.end=std::stoi(token1);

        }
        dio->write("Upload complete.\n");
    }
};

class exitCommand : Command {
public:
    exitCommand(DefaultIO *dio) : Command(dio, "exit\n") {};

    virtual void execute() {}
};

// implement here your command classes



#endif /* COMMANDS_H_ */