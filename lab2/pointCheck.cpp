#include <iostream>
#include <cmath>
#include "pointCheck.h"
using namespace std;
bool isTriangleAPoint(triangle t) {
    return (t.a.x == t.b.x && t.a.y == t.b.y) && (t.b.x == t.c.x && t.b.y == t.c.y);
}

bool isDegenerate(triangle t) {
    return vectorProduct(t.a, t.b, t.c) == 0;
}
double vectorProduct(point a, point b, point p) {
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

bool isInside(triangle t, point p, bool &isOnEdge) {
    isOnEdge = false;
    double v1 = vectorProduct(t.a, t.b, p);
    double v2 = vectorProduct(t.b, t.c, p);
    double v3 = vectorProduct(t.c, t.a, p);
    if (v1 == 0 || v2 == 0 || v3 == 0) {
        bool hasPos = (v1 > 0 || v2 > 0 || v3 > 0);
        bool hasNeg = (v1 < 0 || v2 < 0 || v3 < 0);
        
        if (!(hasPos && hasNeg)) {
            isOnEdge = true;
        }
        return false;
    }
    return (v1 > 0 && v2 > 0 && v3 > 0) || (v1 < 0 && v2 < 0 && v3 < 0);
}
int displayProgram(){
bool isOnEdge = false;
triangle t;

cout << "Enter the coordinates of the triangle vertices (x y): ";
cin >> t.a.x >> t.a.y >> t.b.x >> t.b.y >> t.c.x >> t.c.y;

if (isTriangleAPoint(t)) {
    cout << "The triangle is a point." << endl;
    return 0;
}
if (isDegenerate(t)) {
    cout << "The triangle is degenerate (a line)." << endl;
    return 0;
}
cout << "Enter the amount of points to check: ";
int n;
cin >> n;

for (int i = 0; i < n; i++) {
cout << "Enter the coordinates of the point " << i + 1 << "(x y): ";
point p;
cin >> p.x >> p.y;
if (isInside(t, p, isOnEdge)) {
        cout << "The point is inside the triangle." << endl;
    } else {
            if (isOnEdge) {
                cout << "The point is on the edge of the triangle." << endl;
                isOnEdge = false;
            } else {
                cout << "The point is outside the triangle." << endl;
            }
    }
}
return 0;
}
