
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {}

HybridAnomalyDetector::~HybridAnomalyDetector() {}

void HybridAnomalyDetector::learnNormalHelp(float m , string str1 , string str2, vector<Point*>&points){
    SimpleAnomalyDetector::learnNormalHelp(m,str1,str2,points);
    if (fabs(m) > 0.5 && fabs(m) < 0.9) {
        correlatedFeatures cf1;
        Circle c = findMinCircle(&points[0],points.size());
        cf1.feature1 = str1;
        cf1.feature2 = str2;
        cf1.corrlation = fabs(m);
        cf1.threshold = c.radius * 1.1;
        this->cf.push_back(cf1);
    }
}

bool HybridAnomalyDetector::isAnomaly(Point p, correlatedFeatures cf) {
    Circle c(Point(cf.dx,cf.dy),cf.threshold);
    bool simple = (cf.corrlation > 0.9) && SimpleAnomalyDetector::isAnomaly(p,cf);
    bool circle = (cf.corrlation > 0.5) && cf.corrlation < 0.9 && !isPointInCircle(p,c);
    return simple || circle;
}