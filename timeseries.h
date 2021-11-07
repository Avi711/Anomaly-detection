//
// Created by avi on 06/11/2021.
//


#ifndef ANOMALY_DETECTION_TIMESERIES_H
#define ANOMALY_DETECTION_TIMESERIES_H

//#include "SimpleAnomalyDetector.h"


#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

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
    void initializeData(string fileName);
    void loadCSV(string fileName);
public:
    TimeSeries(string csv);
    string **getData();
    std::vector<Feature> getData2() const;
    vector<float> getValuesByName(string name) const;
};

#endif //ANOMALY_DETECTION_TIMESERIES_H
