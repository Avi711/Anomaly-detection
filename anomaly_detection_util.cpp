//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//


#include <math.h>
#include "anomaly_detection_util.h"




float var(float* x, int size) {
    // calculating Expectation value
    float mu = 0, var = 0;
    for (int i = 0; i < size; ++i) {
        mu = mu + x[i];
    }
    mu = mu / size;

    for (int i = 0; i < size; ++i) {
        var += (x[i] - mu)*(x[i] - mu);
    }
    return var / size;
}



float cov(float *x, float *y, int size) {
    float sum_x = 0, sum_y = 0, sum_xy = 0, cov;
    for (int i = 0; i < size; ++i) {
        sum_x = sum_x + x[i];
        sum_y = sum_y + y[i];
        sum_xy += (x[i] * y[i]);
    }
    cov = sum_xy / (float)(size) - ((sum_x / (float)size) * (sum_y / (float)size));
    return cov;
}

float pearson(float *x, float *y, int size) {
    float pearson;
    float p_cov = cov(x,y,size);
    float alpha_x = sqrtf(var(x,size));
    float alpha_y = sqrtf(var(y,size));
    pearson = p_cov / (alpha_x * alpha_y);
    return pearson;
}

Line linear_reg(Point **points, int size) {
    float x_hat = 0,y_hat = 0,a,b;
    // Creating the arrays for the cov and var function.
    float* x = new float[size];
    float* y = new float[size];
    for (int i = 0; i < size; ++i) {
        x_hat = x_hat + points[i]->x;
        y_hat = y_hat + points[i]->y;
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    //Calculating the line
    a = cov(x,y,size) / var(x,size);
    x_hat = x_hat / (float)size;
    y_hat = y_hat / (float)size;
    b = y_hat - a * x_hat;
    return *(new Line(a,b));
}

float dev(Point p, Point **points, int size) {
    Line l = linear_reg(points, size);
    return dev(p, l);
}

float dev(Point p, Line l) {
    float dev = l.f(p.x) - p.y;
    if (dev < 0) {
        return -dev;
    } else {
        return dev;
    }
}