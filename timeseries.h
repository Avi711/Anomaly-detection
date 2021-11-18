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

/*
 * Class representing one feature.
 * feature name and the vector of feature values.
 */
class Feature {
    string name;
    std::vector<float> vector;

public:
    // Constructor.
    Feature(string name) {
        this->name = name;
    }
    // Adding value to the vector.
    void addValue(float val) {
        vector.push_back(val);
    }
    // Getter for the name of the feature
    string getName() {
        return this->name;
    }
    // Getter for the vector of the values of the feature.
    std::vector<float> getValues() {
        return this->vector;
    }
    // Getter for the "i" value in the vector.
    float getValue(int i) {
        return vector[i];
    }
};

/*
 * Time series class representing Table of feature and their values.
 * The table stored as vector of Features, and every feature has a vector of his values.
 */

class TimeSeries {
    string csv;
    std::vector<Feature> vec;
    void loadCSV(string fileName);
public:
    // Constructor. gets the file name and loads the data from it.
    TimeSeries(const char* CSVfileName);
    // Getter for the Table of data.
    std::vector<Feature> getData() const;
    // get vector of values of a specific feature by name.
    vector<float> getValuesByName(string name) const;
};

#endif /* TIMESERIES_H_ */