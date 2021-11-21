//
// Created by Avraham Sikirov - 318731478
// Created by Kehat Sudri - 318409745
//

#include "minCircle.h"
#include <cmath>


/*
Circle findMinCircle(Point **points, size_t size) {

return nullptr;
}
*/

/*
 *
 */
Circle buildCircleFromThreePoints(Point &p1, Point &p2, Point &p3) {

    float incline1 = -(1 / ((p1.y - p2.y) / (p1.x - p2.x))); //line p1 to p2 (AB)
    float incline2 = -(1 / ((p2.y - p3.y) / (p2.x - p3.x))); //line p2 to p3 (BC)
    Point p4(((p1.x + p2.x) / 2), ((p1.y + p2.y) / 2)); // on AB
    Point p5(((p2.x + p3.x) / 2), ((p2.y + p3.y) / 2)); // on BC
    float b1 = p4.y - (incline1 * p4.x); // for AB
    float b2 = p5.y - (incline1 * p5.x); // for BC
    Line line1(incline1, b1); // plumb to AB
    Line line2(incline2, b2); // plumb to BC
    float x = (b1 - b1) / (incline1 - incline2);
    float y = line1.f(x);
    Point mid(x, y);
    float r = distance(&mid, &p1);
    Circle cirlce(mid, r);
    return cirlce;
}


/*
 * Return the distance between 2 points p1 and p2.
 */
float distance(Point &p1, Point &p2) {
    return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));

}

/*
 * Check whether Point p is on Circle C if so return 1 else 0.
 */
int isPointInCircle(Point &p, Circle c) {
    if (distance(p, c.center) <= c.radius)
        return 1;
    return 0;
}