#include "dyhotomia.h"
#include <iostream>
#include <cmath>

using namespace std;
dyhotomia::dyhotomia(){
    a = 0.0;
    b = 0.0;
    eps = 0.001;
}
dyhotomia::~dyhotomia(){}

void dyhotomia::setVolumes(double vol_a, double vol_b) {
    a = vol_a;
    b = vol_b;
}

void dyhotomia::setTolerance(double vol_eps) {
    eps = vol_eps;
}

//2
double dyhotomia::f (double val) {
    return val + sqrt(val) + cbrt(val) - 2.5; 
}

int dyhotomia::count(double &x) {
    cout << "f(x) = x + x^(1/2) + x^(1/3) - 2.5" << endl << "DYHOTOMIA METHOD" << endl << endl;
    cout << "set interval for dyhotomia(a, b)"<< endl;
    cin >> a >> b;
    cout << "set epsilon(e.g. 0.001)" << endl;
    cin >> eps;
    
    if(f(a) * f(b) > 0) {
        cout << "no solutions on the interval" << endl;
        return 1;
    }
    double c;

    while (abs(b-a) > eps){
        c = (a+b) / 2.0;

        if (f(a) * f(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }

    x = (a + b) / 2.0;

    cout << "dyhotomia x: " << x << endl;
    return 0;
}