//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//


#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

/*
 * this struct represent couple of correlated features
 * we save their names , their corrlation (we calculate) ,  (in float) their linear regression (we calculate) ,
 * and their threshold (above this values the features have corrlation together)
 */
struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    // default
    Circle c = Circle(Point(0, 0), 0);
};

/*
 * This class is actually Simple Anomaly Detector extend from Time Series Anomaly Detector
 * Time series is our data we work on , we have here vector of correlated Features
 * and functions to create and run our Simple Anomaly Detector
 */
class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
protected:
    vector<correlatedFeatures> cf;
    float current_correlation;
public:
    //constructor
    SimpleAnomalyDetector();

    //distructor
    virtual ~SimpleAnomalyDetector();

    void setCurrentCorrealtion(float cor);

    /*
     * Here we find the correlative pairs (columns of time series)
     */
    virtual void learnNormal(const TimeSeries &ts);

    /*
     * here we detect the anomalies and insert them into vector
     */
    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    /**
     * help function to determine whether there is an anomaly.
     * @return true if there is anomaly false otherwise.
     */
    virtual bool isAnomaly(Point p, correlatedFeatures cf);

    /*For the testability of the department. In this method we return
     * List of correlative properties as described in the code. Thus, we can check that learning is normal
     */
    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    /*
     * find the max deviation between point and the line equation of the points
     * its help us to set the threshold.
     */
    virtual void findMaxDev(const TimeSeries &ts);

    virtual float findThreshhold(vector<Point *> &points, Line l);

    virtual void learnNormalHelp(float m, string str1, string str2, vector<Point *> &points);

};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
