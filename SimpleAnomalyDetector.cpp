//
// Created by avi on 05/11/2021.
//

#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {}

SimpleAnomalyDetector::~SimpleAnomalyDetector() noexcept {}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    std::vector<Feature> data = ts.getData2();
    vector<Point *> points;
    for (int i = 1; i < data.size(); ++i) {
        int m = 0;
        int c = -1;
        float sum = 0, counter = 0;
        for (int j = i; j < data.size(); ++j) {
            if (i == j) continue;
            float p = pearson(&data[i].getValues()[0], &data[j].getValues()[0], data[j].getValues().size());
            sum += fabs(p);
            counter++;
            if (std::fabs(p) > m) {
                m = p;
                c = j;
            }
            if (c != -1) {
                correlatedFeatures cf1;
                cf1.feature1 = data[i].getName();
                cf1.feature2 = data[j].getName();
                cf1.corrlation = fabs(p);
                for (int k = 0; k < data[i].getValues().size(); ++k) {
                    Point *p = new Point(data[i].getValue(k),data[j].getValue(k));
                    points.push_back(p);
                }
                cf1.lin_reg = linear_reg(&points[0], data[i].getValues().size());
                points.clear();
                this->cf.push_back(cf1);
            }
        }
        float avg = sum / counter;
        for (int m = 0; m < cf.size(); m++) {
            if (cf[m].corrlation < avg) cf.erase(cf.begin() + m);
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<Point *> points;
    std::vector<AnomalyReport> reports;
    for(int i = 0; i < this->cf.size(); ++i) {
        if (cf[i].corrlation >= cf[i].threshold) {
            for (int j = 0; j < ts.getValuesByName(cf[i].feature1).size(); ++j) {
                float x = ts.getValuesByName(cf[i].feature1)[j];
                float y= ts.getValuesByName(cf[i].feature2)[j];
                Point *p = new Point(x,y);
                points.push_back(p);
            }
        }
        cf[i].lin_reg = linear_reg(&points[0], points.size());
        points.clear();
    }
    for(int i = 0; i < this->cf.size(); ++i) {
        if (cf[i].corrlation >= cf[i].threshold) {
            for (int j = 0; j < ts.getValuesByName(cf[i].feature1).size(); ++j) {
                float x = ts.getValuesByName(cf[i].feature1)[j];
                float y= ts.getValuesByName(cf[i].feature2)[j];
                Point *p = new Point(x,y);
                if(dev(*p, cf[i].lin_reg) > cf[i].corrlation) {
                    reports.push_back(AnomalyReport("report", ts.getData2()[0].getValues()[j]));
                }
            }
        }
    }

    return reports;
}
