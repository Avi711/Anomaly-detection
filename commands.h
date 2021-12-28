

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <iomanip>
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
    int lines;
    vector<correlatedFeatures> cfVector;
    vector<AnomalyReport> arVector;
};

// you may edit this class
class Command {
protected:
    DefaultIO *dio;

public:
    string description;
    Command(DefaultIO *dio, string name) : dio(dio) {
        this->description = name;
    }

    virtual void execute(Information &info) = 0;

    virtual ~Command() {}
};

class uploadCSVCommand : public Command {
public:

    uploadCSVCommand(DefaultIO *dio) : Command(dio, "1.upload a time series csv file\n") {};

    virtual void execute(Information &info) {
        int lines = -1;    // -1 Because of the first line (A,B,C,D....)
        dio->write("Please upload your local train CSV file.\n");
        string line = dio->read();
        ofstream outTrain("trainFile.csv");
        while (line != "done") {
            outTrain << line << endl;
            lines = lines + 1;
            line = dio->read();
        }
        info.lines = lines;
        dio->write("Upload complete.\n");

        dio->write("Please upload your local test CSV file.\n");
        string line1 = dio->read();
        ofstream outTest("testFile.csv");
        while (line1 != "done") {
            outTest << line1 << endl;
            line1 = dio->read();
        }
        dio->write("Upload complete.\n");
    }

};

class algoSetCommand : public Command {
public:
    algoSetCommand(DefaultIO *dio) : Command(dio, "2.algorithm settings\n") {};

    virtual void execute(Information &info) {

        while (true) {
            dio->write("The current correlation threshold is ");
            dio->write(info.correlation);
            dio->write("\n");
            dio->write("Type a new threshold\n");
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

class detectCommand : public Command {
public:
    detectCommand(DefaultIO *dio) : Command(dio, "3.detect anomalies\n") {};

    virtual void execute(Information &info) {
        TimeSeries ts("trainFile.csv");
        HybridAnomalyDetector ad;
        ad.learnNormal(ts);
        TimeSeries ts2("testFile.csv");
        info.arVector = ad.detect(ts2);
        dio->write("anomaly detection complete.\n");
    }
};

class resultCommand : public Command {
public:
    resultCommand(DefaultIO *dio) : Command(dio, "4.display results\n") {};

    virtual void execute(Information &info) {
        vector<AnomalyReport> ar = info.arVector;
        for (AnomalyReport report: ar) {
            dio->write(report.timeStep);
            dio->write("\t" + report.description + "\n");
        }
        dio->write("Done.\n");
    }
};

class analyzeCommand : public Command {
public:
    analyzeCommand(DefaultIO *dio) : Command(dio, "5.upload anomalies and analyze results\n") {};

    vector<Anomaly> combine(vector<AnomalyReport> &ar) {
        vector<Anomaly> result;
        int len = ar.size();
        int start = 0, end =0;
        for (int i = 0; i < len; ++i) {
            start = ar[i].timeStep;
            end = ar[i].timeStep;
            while(ar[i].description == ar[i + 1].description && ar[i].timeStep + 1 == ar[i + 1].timeStep) {
                end = ar[i + 1].timeStep;
                ++i;
            }
            Anomaly anomaly;
            anomaly.start = start;
            anomaly.end = end;
            result.push_back(anomaly);
        }
        return result;
    }
    bool isIntersect(Anomaly anom1, Anomaly anom2) {
        if (anom1.end >= anom2.start && anom1.end <= anom2.end) {
            return true;
        }
        if (anom1.start <= anom2.end && anom1.start >= anom2.start) {
            return true;
        }
        return false;
    }
    virtual void execute(Information &info) {
        vector<Anomaly> userAnomalies;
        vector<Anomaly> serverAnomalies;
        string line = dio->read();
        dio->write("Please upload your local anomalies file.\n");
        int userAnomalyRange = 0, FP = 0, TP =0;

        while (line != "done") {
            string  delim = ",";
            string token1 = line.substr(0, line.find((delim)));
            string token2 = line.substr(line.find(delim) + 1, line.size());
            Anomaly anomaly;
            anomaly.start = stoi(token1);
            anomaly.end = stoi(token2);
            userAnomalyRange = userAnomalyRange + (anomaly.end - anomaly.start) + 1;
            userAnomalies.push_back(anomaly);
            line = dio->read();
        }


        dio->write("Upload complete.\n");
        serverAnomalies = combine(info.arVector);
        float P = userAnomalies.size();
        float N = info.lines - userAnomalyRange;


        for (Anomaly serverAnom : serverAnomalies){
            int flag = 0;
            for (Anomaly userAnom : userAnomalies) {
                if (isIntersect(serverAnom, userAnom) || isIntersect(userAnom, serverAnom)) {
                    ++TP;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                ++FP;
        }
        float truePositiveRate = ((int)(1000*TP/P))/1000.0f;
        float falsePositiveRate = ((int)(1000*FP/N))/1000.0f;
        dio->write("True Positive Rate: ");
        dio->write(truePositiveRate);
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write(falsePositiveRate);
        dio->write("\n");
    }
};

class exitCommand : public Command {
public:
    exitCommand(DefaultIO *dio) : Command(dio, "6.exit\n") {};

    virtual void execute(Information &info) {}
};

// implement here your command classes

#endif /* COMMANDS_H_ */