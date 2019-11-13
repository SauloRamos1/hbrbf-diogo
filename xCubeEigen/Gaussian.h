#ifndef GAUSSIAN_H
#define GAUSSIAN_H
#include <cmath>
#include <iostream>
#include "RBF.h"
using namespace std;
class Gaussian: public RBF
{
public:
    Gaussian();
    double smooth;


    //center[n], vertex[n], ret[1]
    //here n = 3
    void computePhi(double *center, double *vertex, double *ret);

    void gradient(double *center, double *vertex, double grad[3]);

    void hessian(double *center, double *vetex, double hess[3][3]);



};

#endif // InverseMultiquadrics_H
