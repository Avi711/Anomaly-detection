//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//

#include "timeseries.h"
#include "math.h"

void TimeSeries::loadCSV(string fileName) {
    std::ifstream file;
    file.open(fileName);
    string line;
    // Reading every line in the file and every segment in every line and inserting in to the data.
    for (int i = 0; getline(file, line); ++i) {
        string segment = line;
        std::stringstream string(line);
        for (int j = 0; getline(string, segment, ','); ++j) {
            if (i == 0) {
                // Creating new feature and pushing the vector of the features (The table)
                Feature feature(segment);
                vec.push_back(feature);
            } else {
                // Coverting from string to float.
                float v = std::stof(segment);
                // pushing the value to vector of specific feature (j)
                vec[j].addValue(v);
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