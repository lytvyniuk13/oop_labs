#ifndef POINTCHECK_H
#define POINTCHECK_H
struct point {
    double x, y;
};

struct triangle {
    point a, b, c;
};

bool isDegenerate(triangle t);
bool isTriangleAPoint(triangle t);
double vectorProduct(point a, point b, point p);
bool isInside(triangle t, point p, bool &isOnEdge);
int displayProgram();
#endif