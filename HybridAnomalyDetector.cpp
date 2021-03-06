
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {}

HybridAnomalyDetector::~HybridAnomalyDetector() {}

void HybridAnomalyDetector::learnNormalHelp(float m , string str1 , string str2, vector<Point*>&points){
    SimpleAnomalyDetector::learnNormalHelp(m,str1,str2,points);
    if (fabs(m) > 0.5 && fabs(m) < current_correlation) {
        correlatedFeatures cf1;
        cf1.c = findMinCircle(&points[0],points.size());
        cf1.feature1 = str1;
        cf1.feature2 = str2;
        cf1.corrlation = fabs(m);
        cf1.threshold = cf1.c.radius * 1.1;
        this->cf.push_back(cf1);
    }
}

bool HybridAnomalyDetector::isAnomaly(Point p, correlatedFeatures cf) {
    Point p1 = cf.c.center;
    bool simple = (cf.corrlation >= current_correlation) && SimpleAnomalyDetector::isAnomaly(p,cf);
    bool circle = (cf.corrlation > 0.5) && (cf.corrlation < current_correlation) && dist(p1,p) > cf.threshold;
    return (simple || circle);
}