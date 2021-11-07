//
// Created by avi on 05/11/2021.
//


#ifndef ANOMALY_DETECTION_SIMPLEANOMALYDETECTOR_H_H
#define ANOMALY_DETECTION_SIMPLEANOMALYDETECTOR_H_H

#include "timeseries.h"
#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include <iostream>
#include <string>
#include <vector>


struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    std::vector<correlatedFeatures> correlated;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
};



#endif //ANOMALY_DETECTION_SIMPLEANOMALYDETECTOR_H_H
