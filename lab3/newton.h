#ifndef NEWTON_H
#define NEWTON_H

class newton {
public:
    newton(void);
    ~newton(void);

    void setInitialGuess(double guess);
    void setTolerance(double eps_tol);
    void setDeltaX(double dx);

    int count(double &x);
private:
    double x_init;
    double eps;
    double delta_x;

    double f(double val);
    double df(double val);
};
#endif