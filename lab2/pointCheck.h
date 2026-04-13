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

double dist(point p1, point p2);
double heronArea(point p1, point p2, point p3);

void printStatus(bool inside, bool onEdge); 

bool isInside_v(triangle t, point p, bool &isOnEdge);
bool isInside_h(triangle t, point p, bool &isOnEdge);
int displayProgram();
#endif