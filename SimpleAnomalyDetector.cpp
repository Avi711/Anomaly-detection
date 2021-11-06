//
// Created by avi on 05/11/2021.
//

#include "SimpleAnomalyDetector.h"
#include <vector>
void SimpleAnomalyDetector ::learnNormal(const TimeSeries &ts) {
    std::vector<Feature> data = ts.getData2();

    for (int i = 1; i < data.size(); ++i) {
        int m = 0;
        int c = -1;
        for (int j = i; j < data.size(); ++j) {
            int** ar = new int* [5];
            int** ar2 = new int*[5];


        }
    }


}
