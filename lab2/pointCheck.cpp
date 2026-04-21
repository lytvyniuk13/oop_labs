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

double dist(point p1, point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
double heronArea(point p1, point p2, point p3) {
    double a = dist(p1, p2);
    double b = dist(p2, p3);
    double c = dist(p3, p1);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

bool isInside_v(triangle t, point p, bool &isOnEdge) {
    isOnEdge = false;
    
    if (isTriangleAPoint(t)) {
        if (t.a.x == p.x && t.a.y == p.y) {
            isOnEdge = true;
        }
        return false;
    }

    if (isDegenerate(t)) {
        double d1 = dist(t.a, t.b);
        double d2 = dist(t.b, t.c);
        double d3 = dist(t.c, t.a);

        if (d2 >= d1 && d2 >= d3) {
            t.a = t.b; t.b = t.c;
        } else if (d3 >= d1 && d3 >= d2) {
            t.a = t.a; t.b = t.c;
        }
        
        double scalar = ((p.x - t.a.x) * (t.b.x - t.a.x) + (p.y - t.a.y) * (t.b.y - t.a.y)) / 
                        ((t.b.x - t.a.x) * (t.b.x - t.a.x) + (t.b.y - t.a.y) * (t.b.y - t.a.y));
        if (vectorProduct(t.a, t.b, p) != 0) return false;
        if (scalar < 0 || scalar > 1) return false;
        else isOnEdge = true; return false;
    }

    double v1 = vectorProduct(t.a, t.b, p);
    double v2 = vectorProduct(t.b, t.c, p);
    double v3 = vectorProduct(t.c, t.a, p);
    if (v1 == 0 || v2 == 0 || v3 == 0) {
        bool hasPos = (v1 > 0 || v2 > 0 || v3 > 0);
        bool hasNeg = (v1 < 0 || v2 < 0 || v3 < 0);
        if (v1 == 0 && v2 == 0 && v3 == 0) return false;
        else if (!(hasPos && hasNeg)) {
            isOnEdge = true;
        }
        
        return false;
    }
    return (v1 > 0 && v2 > 0 && v3 > 0) || (v1 < 0 && v2 < 0 && v3 < 0);
}

bool isInside_h(triangle t, point p, bool &isOnEdge) {
    isOnEdge = false;
    
    if (isTriangleAPoint(t)) {
        double dx = t.a.x - p.x;
        double dy = t.a.y - p.y;
        if (dx == 0 && dy == 0) {
            isOnEdge = true;
        }
        return false;
    }
    
    if (isDegenerate(t)) {
        double d1 = dist(t.a, t.b);
        double d2 = dist(t.b, t.c);
        double d3 = dist(t.c, t.a);

        if (d2 >= d1 && d2 >= d3) {
            t.a = t.b; t.b = t.c;
        } else if (d3 >= d1 && d3 >= d2) {
            t.a = t.a; t.b = t.c;
        }
        
        double scalar = ((p.x - t.a.x) * (t.b.x - t.a.x) + (p.y - t.a.y) * (t.b.y - t.a.y)) / 
                        ((t.b.x - t.a.x) * (t.b.x - t.a.x) + (t.b.y - t.a.y) * (t.b.y - t.a.y));
        if (vectorProduct(t.a, t.b, p) != 0) return false;
        if (scalar < 0 || scalar > 1) return false;
        else isOnEdge = true; return false;
    }

double totalArea = heronArea(t.a, t.b, t.c);
    double A1 = heronArea(p, t.a, t.b);
    double A2 = heronArea(p, t.b, t.c);
    double A3 = heronArea(p, t.c, t.a);
    
    if (A1 == 0 || A2 == 0 || A3 == 0) {
        isOnEdge = true;
        return false;
    }
    
    return abs(totalArea - (A1 + A2 + A3)) < 1e-7;

}

void printStatus(bool inside, bool onEdge) {
    if (inside) cout << "inside";
    else if (onEdge) cout << "on the edge";
    else cout << "outside";
    cout << endl;
}

int displayProgram(){
bool isOnEdge = false;
triangle t;

cout << "Enter the coordinates of the triangle vertices (x y): ";
if(!(cin >> t.a.x >> t.a.y >> t.b.x >> t.b.y >> t.c.x >> t.c.y)) {
    cerr << "Error reading triangle coordinates." << endl;
    return 1;
}

if (isTriangleAPoint(t)) {
    cout << "The triangle is a point." << endl;
}
else if (isDegenerate(t)) {
    cout << "The triangle is degenerate (a line)." << endl;
}

cout << "Enter the amount of points to check: ";
int n;
if(!(cin >> n)) {
    cerr << "Error reading the number of points." << endl;
    return 1;
}

for (int i = 0; i < n; i++) {
cout << "Enter the coordinates of the point " << i + 1 << "(x y): ";
point p;
if(!(cin >> p.x >> p.y)) {
    cerr << "Error reading point coordinates." << endl;
    return 1;
}
    cout << "VECTOR: "; printStatus(isInside_v(t, p, isOnEdge), isOnEdge);
    cout << "HERON: "; printStatus(isInside_h(t, p, isOnEdge), isOnEdge);

}
return 0;
}
