//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
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
    std::vector<Feature> vec;
    void loadCSV(string fileName);
public:
    TimeSeries(const char* CSVfileName);
    std::vector<Feature> getData() const;
    vector<float> getValuesByName(string name) const;
};

#endif /* TIMESERIES_H_ */