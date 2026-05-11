#include "dyhotomia.h"
#include "newton.h"

int main() {
    dyhotomia* dyho = new dyhotomia();
    newton* newt = new newton();
    double x = 0.0; 
    dyho->count(x);
    newt->count(x);
    delete dyho;
    delete newt;
    return 0;
}