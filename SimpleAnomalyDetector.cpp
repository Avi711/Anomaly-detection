//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//

#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->current_correlation = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() noexcept {}

void SimpleAnomalyDetector::setCurrentCorrealtion(float cor) {
    this->current_correlation = cor;
}

void SimpleAnomalyDetector::findMaxDev(const TimeSeries &ts) {
    for (int i = 0; i < this->cf.size(); ++i) {
        float temp = 0, trs = 0;
        for (int j = 0; j < ts.getValuesByName(cf[i].feature1).size(); ++j) {
            float x = ts.getValuesByName(cf[i].feature1)[j];
            float y = ts.getValuesByName(cf[i].feature2)[j];
            Point p(x, y);
            trs = dev(p, cf[i].lin_reg);
            if (trs > temp) {
                temp = trs;
                cf[i].threshold = (temp) * 1.15;
            }
        }
    }
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    std::vector<Feature> data = ts.getData();
    vector<Point *> points;
    for (int i = 0; i < data.size(); ++i) {
        float m = 0, c = -1;
        for (int j = i + 1; j < data.size(); ++j) {
            float p = pearson(&data[i].getValues()[0], &data[j].getValues()[0], data[j].getValues().size());
            if (fabs(p) > m) {
                m = p;
                c = j;
            }
        }
        if (c != -1) {
            for (int k = 0; k < data[i].getValues().size(); ++k) {
                Point *t = new Point(data[i].getValue(k), data[c].getValue(k));
                points.push_back(t);
            }
            learnNormalHelp(m, data[i].getName(), data[c].getName(), points);

            for (Point *t: points) {
                delete t;
            }
        }
        points.clear();
    }
    // findMaxDev(ts);
}

void SimpleAnomalyDetector::learnNormalHelp(float m, string str1, string str2, vector<Point *> &points) {
    if (fabs(m) >= current_correlation) {
        correlatedFeatures cf1;
        cf1.feature1 = str1;
        cf1.feature2 = str2;
        cf1.corrlation = fabs(m);
        cf1.threshold = 0;
        cf1.lin_reg = linear_reg(&points[0], points.size());
        cf1.threshold = findThreshhold(points, cf1.lin_reg) * 1.1;
        this->cf.push_back(cf1);
    }
}

float SimpleAnomalyDetector::findThreshhold(vector<Point *> &points, Line l) {
    float maxDev = 0;
    float current = 0;
    for (Point *point: points) {
        current = dev(*point, l);
        if (current > maxDev) {
            maxDev = current;
        }
    }
    return maxDev;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<Point *> points;
    std::vector<AnomalyReport> reports;
    for (int i = 0; i < this->cf.size(); ++i) {
        for (int j = 0; j < ts.getValuesByName(cf[i].feature1).size(); ++j) {
            float x = ts.getValuesByName(cf[i].feature1)[j];
            float y = ts.getValuesByName(cf[i].feature2)[j];
            Point p(x, y);
            correlatedFeatures cor = cf[i];
            if (isAnomaly(p, cor)) {
                string s = cf[i].feature1 + '-' + cf[i].feature2;
                reports.push_back(AnomalyReport(s, j + 1));
            }
        }
    }
    return reports;
}

bool SimpleAnomalyDetector::isAnomaly(Point p, correlatedFeatures cf) {
    return (dev(p, cf.lin_reg) > cf.threshold);
}