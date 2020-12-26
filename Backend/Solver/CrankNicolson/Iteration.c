#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double _Eop = 938.27;
double _hbarc = 0.1973;
double _c = 3.0 * pow(10,2);

double Psi0(double x);
{
    double A, K1,K2;
    double x0 = -0.100;
    double a = 0.050;
    double l  = 200000.0

    A = pow((1.0 / (2 * pi * pow(a,2))) , 0.25);
    K1 = exp(- pow((x - x0), 2) / (4.0 * pow(a, 2)));
    K2 = exp(1 * l * x);  
    
    return A * K1 * K2;
}

double deletaPotential()
{
    
}

double crank_nickelson()
{
    
}