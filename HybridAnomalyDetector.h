

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();

    virtual void learnNoramlHelp(float m , string str1 , string str2, vector<Point*>&points);
};


#endif /* HYBRIDANOMALYDETECTOR_H_ */