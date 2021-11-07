//
// Created by avi on 05/11/2021.
//

#ifndef ANOMALY_DETECTION_ANOMALYDETECTOR_H
#define ANOMALY_DETECTION_ANOMALYDETECTOR_H
#include "anomaly_detection_util.h"
#include "timeseries.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::string;
using std::vector;


class Feature {
    string name;
    std::vector<float> vector;
public:
    Feature(string name) {
        this->name = name;
    }
    void addValue(float val) {
        vector.push_back(val);
    }
    string getName() {
        return this->name;
    }
    std::vector<float> getValues() {
        return this->vector;
    }
    float getValue(int i) {
        return vector[i];
    }
};


class TimeSeries {
    string csv;
    string **data;
    std::vector<Feature> vec;
    //std::vector<correlatedFeatures> correlatedFeatures;

    void initializeData(string fileName);
    void loadCSV(string fileName);
public:
    TimeSeries(string csv);
    string **getData();
    std::vector<Feature> getData2() const;

    vector<float> getValuesByName(string name);
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
