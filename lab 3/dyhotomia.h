#ifndef DYHOTOMIA_H
#define DYHOTOMIA_H

class dyhotomia {
public:
    dyhotomia(void);
    ~dyhotomia(void);

    int count (double &x);

    void setVolumes(double vol_a, double vol_b);
    void setTolerance(double vol_eps);
private:
    double a, b, eps;
    double f(double val);
};



#endif