
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------


Circle findMinCircle(Point** points,size_t size);

Circle buildCircleFromThreePoints(Point &p1, Point &p2, Point &p3);

float distance(Point &p1, Point &p2);

int isPointInCircle(Point &p, Circle c);

bool isCircleValid(Point **points, Circle c);

#endif /* MINCIRCLE_H_ */