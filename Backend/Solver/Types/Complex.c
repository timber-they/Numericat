#include "Complex.h"
#include <stdio.h>
#include <math.h>

Complex imaginaryUnit = COMPLEX(0,1);

Complex sumComplex(Complex a, Complex b)
{
    return COMPLEX(a.real + b.real, .imaginary = a.imaginary + b.imaginary);
}
Complex subtractComplex(Complex a, Complex b)
{
    return COMPLEX(a.real - b.real, .imaginary = a.imaginary - b.imaginary);
}
Complex multiplyComplex(Complex a, Complex b)
{
    return COMPLEX(a.real * b.real - a.imaginary * b.imaginary,
                      a.real * b.imaginary + a.imaginary * b.real);
}
Complex divideComplex(Complex a, Complex b)
{
    double division = b.real * b.real + b.imaginary * b.imaginary;
    return COMPLEX((a.real * b.real + a.imaginary * b.imaginary) / division,
                      (a.imaginary * b.real - a.real * b.imaginary) / division);
}
Complex powerComplex(Complex a, Complex b)
{
    if (absSquareComplex(a) < 0.0000000001)
        // 0^x=0
        return COMPLEX(0,0);
    double a_arg = atan2(a.imaginary, a.real);
    double a_r = sqrt(a.real * a.real + a.imaginary * a.imaginary);
    return expComplex(sumComplex(multiplyComplex(COMPLEX(log(a_r), 0), b),
                                 multiplyComplex(COMPLEX(0, .imaginary = a_arg), b)));
}
Complex expComplex(Complex b)
{
    return multiplyComplex(COMPLEX(exp(b.real), .imaginary = 0),
                           COMPLEX(cos(b.imaginary), .imaginary = sin(b.imaginary)));
}
double absSquareComplex(Complex c)
{
    return c.real * c.real + c.imaginary * c.imaginary;
}
void printComplex(Complex c)
{
    printf("(%lf;%lfi)", c.real, c.imaginary);
}
