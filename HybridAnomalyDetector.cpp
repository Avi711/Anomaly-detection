
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {}

HybridAnomalyDetector::~HybridAnomalyDetector() {}

void SimpleAnomalyDetector::learnNoramlHelp(float m , string str1 , string str2, vector<Point*>&points){
    if (fabs(m) > 0.5 && fabs(m) < 0.9  ) {
        correlatedFeatures cf1;
        cf1.feature1 = str1;
        cf1.feature2 = str2;
        cf1.corrlation = fabs(m);
        cf1.threshold = 0;
        Circle c = findMinCircle(&points[0],points.size());



        this->cf.push_back(cf1);
    }

}

