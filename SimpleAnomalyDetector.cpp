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
            float p = pearson(&data[i].getValues()[0],&data[j].getValues()[0], data[j].getValues().size());
            if (std::abs(p) > m) {
                m = p;
                c = j;
            }
            if (c != -1) {

            }
        }
    }


}
