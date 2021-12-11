//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//

#include "minCircle.h"
#include <cmath>
#include <chrono>

/**
 * recursive function for calculating minimal circle when given vector of points.
 * @param v1 vector of points.
 * @param v2 array of 1,2 or 3 points for the base cases.
 * @param size size
 * @return recursively return minimal circle.
 */

Circle findMinCircleRec(vector<Point> &v1, vector<Point> v2, int size) {
    if (size == 0 || v2.size() == 3)
        return minCircleBase(v2);
    Point p = v1[size - 1];
    Circle c = findMinCircleRec(v1, v2, size - 1);
    if (isPointInCircle(p, c))
        return c;
    v2.push_back(p);
    return findMinCircleRec(v1, v2, size - 1);
}

/**
 * Base cases for bulding circle from array of point (1,2 or 3 point)
 * @param pointvec vector of points.
 * @return Circle built from 1,2 or 3 points.
 */

Circle minCircleBase(vector<Point> &pointvec) {
    if (pointvec.empty())
        return {{0, 0}, 0};
    if (pointvec.size() == 1)
        return {{pointvec[0].x, pointvec[0].y}, 0};
    if (pointvec.size() == 2)
        return buildCircleFromTwoPoints(pointvec[0], pointvec[1]);
    for(int i=0;i<3;i++) {
        for (int j = 0; j < 3; j++) {
            Circle c = buildCircleFromTwoPoints(pointvec[i], pointvec[j]);
            if (isCircleValid(pointvec, c)){
                return c;
            }
        }
    }
    return buildCircleFromThreePoints(pointvec[0], pointvec[1], pointvec[2]);
}

/**
 * Given array of point builds circle which all the points in the circle.
 * @param points points.
 * @param size size of array.
 * @return minimum circle built when all points in the circle.
 */
Circle findMinCircle(Point **points, size_t size) {
    vector<Point> vec;
    for (size_t i = 0; i < size; i++) {
        vec.push_back(*points[i]);
    }
    return findMinCircleRec(vec, {}, size);
}

float incline(Point p1, Point p2) {
    return ((p1.y - p2.y) / (p1.x - p2.x));
}

/**
 * given 3 points, the function builds a circle from them if possible.
 * @param p1 fist point.
 * @param p2 second point.
 * @param p3 third point.
 * @return circle created from 3 points.
 */
Circle buildCircleFromThreePoints(Point &p1, Point &p2, Point &p3) {

    if (incline(p1, p2) == incline(p2, p3))
        exit(1);

    float incline1 = -(1 / ((p1.y - p2.y) / (p1.x - p2.x))); //line p1 to p2 (AB)
    float incline2 = -(1 / ((p2.y - p3.y) / (p2.x - p3.x))); //line p2 to p3 (BC)

    Point p4(((p1.x + p2.x) / 2), ((p1.y + p2.y) / 2)); // on AB
    Point p5(((p2.x + p3.x) / 2), ((p2.y + p3.y) / 2)); // on BC

    float b1 = p4.y - (incline1 * p4.x); // for AB
    float b2 = p5.y - (incline2 * p5.x); // for BC

    Line line1(incline1, b1); // plumb to AB
    Line line2(incline2, b2); // plumb to BC
    float x = (b2 - b1) / (incline1 - incline2);
    float y = line1.f(x);
    Point mid(x, y);
    float r = dist(mid, p1);
    Circle circle(mid, r);
    return circle;
}

/**
 * Function building minimum circle when given two points.
 * @param p1 first point.
 * @param p2 second point.
 * @return minimum circle.
 */
Circle buildCircleFromTwoPoints(Point &p1, Point &p2) {

    Point mid(((p1.x + p2.x) / 2), (p1.y + p2.y) / 2);
    float r = dist(p1, mid);
    Circle c(mid, r);
    return c;
}

/*
 * Return the distance between 2 points p1 and p2.
 */
float dist(Point &p1, Point &p2) {
    float a = pow(p1.x - p2.x, 2);
    float b = pow(p1.y - p2.y, 2);
    return sqrt(a + b);
}

/*
 * Check whether Point p is on Circle C if so return 1 else 0.
 */
int isPointInCircle(Point &p, Circle c) {
    if (dist(p, c.center) <= c.radius)
        return 1;
    return 0;
}

/*
 * function to check if all the points in given array are witting the radius of a given circle.
 */
int isCircleValid(vector<Point> &v, Circle c) {
    for (Point & i : v) {
        if (!(isPointInCircle(i, c)))
            return 0;
    }
    return 1;
}