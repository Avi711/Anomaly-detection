//
// Created by avi on 05/11/2021.
//

#ifndef ANOMALY_DETECTION_ANOMALYDETECTOR_H
#define ANOMALY_DETECTION_ANOMALYDETECTOR_H
#include <iostream>
#include <vector>
#include <fstream>
using std::string;
using std::vector;

class TimeSeries{
    string** data;

public:
    TimeSeries(){}

    void loadCSV(string fileName){
        std::ifstream file;
        file.open(fileName);
        while(file.good()) {
            string line;
            getline(file,line,',');
            std::cout << line << std::endl;
        }

    };






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
