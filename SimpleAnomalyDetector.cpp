//
// Created by avi on 05/11/2021.
//

#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {}

SimpleAnomalyDetector::~SimpleAnomalyDetector() noexcept {}

void SimpleAnomalyDetector::findMaxDev(const TimeSeries &ts) {
    float trs = 0;
    for (int i = 0; i < this->cf.size(); ++i) {
        if (cf[i].corrlation >= cf[i].threshold) {
            for (int j = 0; j < ts.getValuesByName(cf[i].feature1).size(); ++j) {
                float x = ts.getValuesByName(cf[i].feature1)[j];
                float y = ts.getValuesByName(cf[i].feature2)[j];
                Point p(x, y);
                trs = dev(p, cf[i].lin_reg);
                if (trs > cf[i].threshold) {
                    cf[i].threshold = (trs) * 1.225;
                }
            }
        }
    }

}
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    std::vector<Feature> data = ts.getData();
    vector<Point *> points;
    for (int i = 0; i < data.size(); ++i) {
        int m = 0;
        int c = -1;
        float sum = 0, counter = 0;
        for (int j = i + 1; j < data.size(); ++j) {
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
                cf1.threshold = 0;
                for (int k = 0; k < data[i].getValues().size(); ++k) {
                    Point *p = new Point(data[i].getValue(k), data[j].getValue(k));
                    points.push_back(p);
                }
                cf1.lin_reg = linear_reg(&points[0], data[i].getValues().size());
                for (Point *p : points) {
                    delete p;
                }
                points.clear();
                this->cf.push_back(cf1);
            }
        }
        for (int m = 0; m < cf.size(); m++) {
            if (cf[m].corrlation < 0.90) cf.erase(cf.begin() + m);
        }
    }
    findMaxDev(ts);
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<Point *> points;
    std::vector<AnomalyReport> reports;
    for (int i = 0; i < this->cf.size(); ++i) {
            for (int j = 0; j < ts.getValuesByName(cf[i].feature1).size(); ++j) {
                float x = ts.getValuesByName(cf[i].feature1)[j];
                float y = ts.getValuesByName(cf[i].feature2)[j];
                Point p(x, y);
                if (dev(p, cf[i].lin_reg) > cf[i].threshold) {
                    string s = cf[i].feature1 + '-' + cf[i].feature2;
                    reports.push_back(AnomalyReport(s, ts.getData()[0].getValues()[j]));
                }
            }
        }
    return reports;
}
