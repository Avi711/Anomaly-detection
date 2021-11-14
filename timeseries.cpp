//
// Created by avi on 06/11/2021.
//

#include "timeseries.h"

void TimeSeries::loadCSV(string fileName) {
    std::ifstream file;
    file.open(fileName);
    string line;
    for (int i = 0; getline(file, line); ++i) {
        string segment = line;
        std::stringstream string(line);
        for (int j = 0; getline(string, segment, ','); ++j) {
            if (i == 0) {
                Feature feature(segment);
                vec.push_back(feature);
            } else {
                vec[j].addValue(std::stof(segment));
            }
        }
    }
}

TimeSeries::TimeSeries(const char* CSVfileName) {
    this->csv = CSVfileName;
    loadCSV(csv);
}

std::vector<Feature> TimeSeries::getData() const {
    return this->vec;
}
vector<float> TimeSeries::getValuesByName(string name) const {
    for (Feature i: vec) {
        if (i.getName() == name)
            return i.getValues();
    }
}