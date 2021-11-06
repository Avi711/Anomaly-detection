//
// Created by avi on 05/11/2021.
//

#ifndef ANOMALY_DETECTION_ANOMALYDETECTOR_H
#define ANOMALY_DETECTION_ANOMALYDETECTOR_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::string;
using std::vector;





class TimeSeries {
    string **data;
public:
    TimeSeries() {}
    void initializeData(string fileName) {
        int rows = 0;
        int columns = 0;
        std::ifstream file;
        file.open(fileName);
        string line;
        while (getline(file, line)) {
            string segment = line;
            ++rows;
        }
        columns = std::count(line.begin(), line.end(), ',');
        ++columns;

        data = new string *[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new string[columns];
        }
    }

    void loadCSV(string fileName) {
        initializeData(fileName);
        std::ifstream file;
        file.open(fileName);
        string line;
        for (int i = 0; getline(file, line); ++i) {
            string segment = line;
            std::stringstream string(line);
            for (int j = 0; getline(string, segment, ','); ++j) {
                data[i][j] = segment;
                std::cout << data[i][j] << std::endl;
            }
        }
    };

    string **getData() {
        return this->data;
    }
};

class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};




#endif //ANOMALY_DETECTION_ANOMALYDETECTOR_H
