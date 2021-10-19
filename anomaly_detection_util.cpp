//
// Created by avi on 14/10/2021.
//


#include "anomaly_detection_util.h"
#include "cmath"

float var(float *x, int size) {
    // calculating Expectation value
    float mu = 0;
    float var;
    for (int i = 0; i < size; ++i) {
        mu = mu + x[i];
    }
    mu = mu / size;

    for (int i = 0; i < size; ++i) {
        var = var + powf((x[i] - mu),(x[i] - mu));
    }
    return var;
}

float cov(float *x, float *y, int size) {
    float sum_x = 0;
    float sum_y = 0;
    float cov;
    for (int i = 0; i < size; ++i) {
        sum_x = sum_x + x[i];
        sum_y = sum_y + y[i];
    }
    cov = (sum_x + sum_y) / (2 * size) - (sum_x / size * sum_y / size);
    return cov;
}

float pearson(float *x, float *y, int size) {
    float person;
    float p_cov = cov(x,y,size);
    float alpha_x = sqrtf(var(x,size));
    float alpha_y = sqrtf(var(y,size));
    person = p_cov / (alpha_x * alpha_y);
    return person;
}

Line linear_reg(Point **points, int size) {
    if (size == 0) {
        throw(size);
    }
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
    b = y_hat - a * x_hat;
    x_hat = x_hat / size;
    y_hat = y_hat / size;
    return *(new Line(a,b));
}

float dev(Point p, Point **points, int size) {
    Line l = linear_reg(points, size);
    return dev(p, l);
}

float dev(Point p, Line l) {
    float f_x = l.a * p.x + l.b;
    float dev = f_x - p.y;
    if (dev < 0) {
        return -dev;
    } else {
        return dev;
    }
}
