
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

Circle minCircleBase(vector<Point> pointvec);

Circle findMinCircleRec(vector <Point> v1 ,vector <Point> v2 , int size  );

Circle buildCircleFromTwoPoints(Point &p1, Point &p2);

Circle buildCircleFromThreePoints(Point &p1, Point &p2, Point &p3);

float dist(Point &p1, Point &p2);

float incline(Point p1, Point p2);

int isPointInCircle(Point &p, Circle c);

int isCircleValid(vector<Point> &v, Circle c);

#endif /* MINCIRCLE_H_ */