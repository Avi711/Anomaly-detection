//
// Created by avi on 06/11/2021.
//

#include "timeseries.h"

void TimeSeries::initializeData(string fileName) {
    int rows = 0;
    int columns = 0;
    std::ifstream file;
    file.open(fileName);
    string line;
    while (getline(file, line)) {
        if (rows == 1) {
            columns = std::count(line.begin(), line.end(), ',');
        }
        string segment = line;
        ++rows;
    }
    //columns = std::count(line.begin(), line.end(), ',');
    ++columns;

    data = new string *[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new string[columns];
    }
}

void TimeSeries::loadCSV(string fileName) {
    initializeData(fileName);
    std::ifstream file;
    file.open(fileName);
    string line;
    for (int i = 0; getline(file, line); ++i) {
        string segment = line;
        std::stringstream string(line);
        for (int j = 0; getline(string, segment, ','); ++j) {
            if (i == 0) {
                Feature *feature = new Feature(segment);
                vec.push_back(*feature);
            } else {
                vec[j].addValue(std::stof(segment));
            }
            data[i][j] = segment;
            // std::cout << data[i][j] << std::endl;
        }
    }
}

TimeSeries::TimeSeries(const char* CSVfileName) {
    this->csv = CSVfileName;
    loadCSV(csv);
}

string **TimeSeries::getData() {
    return this->data;
}
std::vector<Feature> TimeSeries::getData2() const {
    return this->vec;
}
vector<float> TimeSeries::getValuesByName(string name) const {
    for (Feature i: vec) {
        if (i.getName() == name)
            return i.getValues();
    }
}