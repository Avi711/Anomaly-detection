//
// Created by avi on 05/11/2021.
//

#include "SimpleAnomalyDetector.h"
#include <vector>
void SimpleAnomalyDetector ::learnNormal(const TimeSeries &ts) {
    std::vector<Feature> data = ts.getData2();

    for (int i = 1; i < data.size(); ++i) {
        int m = 0;




    }


}
