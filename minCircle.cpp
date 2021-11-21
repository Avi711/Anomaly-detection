//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//

#include "minCircle.h"
#include <cmath>


Circle findMinCircleRec(vector<Point> v1, vector<Point> v2, int size) {
    if (size == 0 || v2.size() == 3)
        return minCircleBase(v2);
    Point p = v1[size - 1];
    Circle c = findMinCircleRec(v1, v2, size - 1);
    if (isPointInCircle(p, c))
        return c;
    v2.push_back(p);
    return findMinCircleRec(v1, v2, size - 1);
}

Circle minCircleBase(vector<Point> pointvec) {
    if (pointvec.empty())
        return {{0, 0}, 0};
    if (pointvec.size() == 1)
        return {{pointvec[0].x, pointvec[0].y}, 0};
    if (pointvec.size() == 2)
        return buildCircleFromTwoPoints(pointvec[0], pointvec[1]);
    for(int i=0;i<3;i++) {
        for (int j = 0; j < 3; j++) {
            Circle c = buildCircleFromTwoPoints(pointvec[i], pointvec[j]);
            if (isCircleValid(&pointvec[0], c)){
                return c;
            }

        }
    }
        return buildCircleFromThreePoints(pointvec[0], pointvec[1], pointvec[2]);

}

/*
 *
 */
Circle findMinCircle(Point **points, size_t size) {
    vector<Point> vec;
    for (size_t i = 0; i < size; i++) {
        vec.push_back(*points[i]);
    }
    vector<Point> vec2;
    return findMinCircleRec(vec, vec2, vec.size());
    Point p(5, 7);
    Circle c(p, 7);
    return c;
}

float incline(Point p1, Point p2) {
    return ((p1.y - p2.y) / (p1.x - p2.x));
}

/*
 *
 */
Circle buildCircleFromThreePoints(Point &p1, Point &p2, Point &p3) {

    if (incline(p1, p2) == incline(p2, p3))
        exit(333333);

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
    Circle cirlce(mid, r);
    return cirlce;
}

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
 *
 */
int isCircleValid(vector<Point> &v, Circle c) {
    for (int i = 0; i < v.size(); i++) {
        if (!(isPointInCircle(v[i], c)))
            return 0;
    }
    return 1;
}