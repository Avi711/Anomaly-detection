//
// Created by avi on 05/11/2021.
//

#include "SimpleAnomalyDetector.h"
#include <vector>

SimpleAnomalyDetector ::SimpleAnomalyDetector() {}

SimpleAnomalyDetector ::~SimpleAnomalyDetector() noexcept {}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    std::vector<Feature> data = ts.getData2();

    for (int i = 1; i < data.size(); ++i) {
        int m = 0;
        int c = -1;
        float sum = 0, counter = 0;
        for (int j = i; j < data.size(); ++j) {
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
/*                vector<Point *> points;
                for (int k = 0; k < data[i].getValues().size(); i++) {
                    points.push_back(new Point(data[i].getValue(k), (data[j].getValue(k))));
                    cf1.lin_reg = linear_reg(&points[0], data[i].getValues().size());
                }*/
                this->correlated.push_back(cf1);
            }
        }
        float avg = sum / counter;
        for (int m = 0; m < correlated.size(); m++) {
            correlated[m].threshold = avg;
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<Point *> points;
    for(int i = 0; i < this->correlated.size(); ++i) {
        if (correlated[i].corrlation >= correlated[i].threshold) {
            for (int j = 0; j < ts.getValuesByName(correlated[i].feature1).size(); ++j) {
                float x = ts.getValuesByName(correlated[i].feature1)[j];
                float y= ts.getValuesByName(correlated[i].feature2)[j];
                Point *p = new Point(x,y);
                points.push_back(p);
            }
            correlatedfinal.push_back(correlated[i]);
        }
        correlated[i].lin_reg = linear_reg(&points[0], points.size());
    }
    for(int i = 0; i < this->correlated.size(); ++i) {
        if (correlated[i].corrlation >= correlated[i].threshold) {
            for (int j = 0; j < ts.getValuesByName(correlated[i].feature1).size(); ++j) {
                float x = ts.getValuesByName(correlated[i].feature1)[j];
                float y= ts.getValuesByName(correlated[i].feature2)[j];
                Point *p = new Point(x,y);
                if(dev(*p, correlated[i].lin_reg) > correlated[i].corrlation) {

                }
            }
            correlatedfinal.push_back(correlated[i]);
        }
        correlated[i].lin_reg = linear_reg(&points[0], points.size());
    }
    std::vector<AnomalyReport> a;
    return a;
}
vector<correlatedFeatures> SimpleAnomalyDetector ::getNormalModel() {
    return this->correlatedfinal;
}