//
// Created by avi on 06/11/2021.
//

#ifndef TIMESERIES_H_
#define TIMESERIES_H_



#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


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
    TimeSeries(const char* CSVfileName);
    string **getData();
    std::vector<Feature> getData2() const;
    vector<float> getValuesByName(string name) const;
};

#endif /* TIMESERIES_H_ */