#include "newton.h"
#include <iostream>
#include <cmath>

using namespace std;
newton::newton() {
    x_init = 0.0;
    eps = 0.001;
    delta_x = 1e-6;
}
newton::~newton(){}

void newton::setInitialGuess(double guess) {
    x_init = guess;
}

void newton::setTolerance(double eps_val) {
    eps = eps_val;
}

void newton::setDeltaX(double dx) {
    delta_x = dx;
}

double newton::f(double val) {
    return val + sqrt(val) + cbrt(val) - 2.5; 
}

double newton::df(double val) {
    return (f(val + delta_x) - f(val)) / delta_x;
}

int newton::count(double &x) {
    cout << endl << "NEWTON METHOD" << endl;
    cout << "set initial guess" << endl;
    cin >> x_init;
    cout << "set epsilon(e.g. 0.001)" << endl;
    cin >> eps;
    cout << "set delta(e.g. 1e-6)" << endl;
    cin >> delta_x;

    double x_next; 
    int max_iter = 1000;    
    int iter = 0;

    while (iter < max_iter) {
        double derivative = df(x_init);
        
        if (abs(derivative) < 1e-12) {
            cout << "error. derivative equals to 0" << endl;
            return 1; 
        }

        x_next = x_init - f(x_init) / derivative;

        if (abs(x_next - x_init) <= eps) {
            x = x_next; 
            cout << "newton x: " << x << endl;
            return 0;  
        }

        x_init = x_next;
        iter++;
    }
    
    cout << "iteration limit reached. no solutions found" << endl;
    return 2; 
}