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
                    cf[i].threshold = (trs) * 1.1;
                }
            }
        }
    }

}
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    std::vector<Feature> data = ts.getData();
    vector<Point *> points;
    for (int i = 0; i < data.size(); ++i) {
        float m = 0, c=-1, sum = 0, counter = 0;
        for (int j = i + 1; j < data.size(); ++j) {
            float p = pearson(&data[i].getValues()[0], &data[j].getValues()[0], data[j].getValues().size());
            sum += fabs(p);
            counter++;
            if (std::fabs(p) > m) {
                m = p;
                c = j;
            }
        }
            if (c != -1 && fabs(m) > 0.9) {
                correlatedFeatures cf1;
                cf1.feature1 = data[i].getName();
                cf1.feature2 = data[c].getName();
                cf1.corrlation = fabs(m);
                cf1.threshold = 0;
                for (int k = 0; k < data[i].getValues().size(); ++k) {
                    Point *t = new Point(data[i].getValue(k), data[c].getValue(k));
                    points.push_back(t);
                }
                cf1.lin_reg = linear_reg(&points[0], data[i].getValues().size());
                for (Point *t : points) {
                    delete t;
                }
                points.clear();
                this->cf.push_back(cf1);
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
